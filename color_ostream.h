//source with changed: https://github.com/yurablok/colored-cout
#ifndef TEST_MODERN_CPP_COLOR_OSTREAM_H
#define TEST_MODERN_CPP_COLOR_OSTREAM_H

#include <iostream>
#include <iomanip>
#include <array>
#include <random>

#ifdef _WIN32
#   define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
#   define NOMINMAX // Fixes the conflicts with STL
#   include <Windows.h>
#   include <wincon.h>
#endif

namespace color_ostream {
#ifdef _WIN32
    enum class clr : uint16_t {
          grey       = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED
        , blue       = FOREGROUND_BLUE | FOREGROUND_INTENSITY
        , green      = FOREGROUND_GREEN | FOREGROUND_INTENSITY
        , cyan       = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY
        , red        = FOREGROUND_RED | FOREGROUND_INTENSITY
        , magenta    = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY
        , yellow     = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY
        , white      = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY
        , on_blue    = BACKGROUND_BLUE //| BACKGROUND_INTENSITY
        , on_red     = BACKGROUND_RED //| BACKGROUND_INTENSITY
        , on_magenta = BACKGROUND_BLUE | BACKGROUND_RED //| BACKGROUND_INTENSITY
        , on_grey    = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED
        , on_green   = BACKGROUND_GREEN | BACKGROUND_INTENSITY
        , on_cyan    = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY
        , on_yellow  = BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY
        , on_white   = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY
        , reset
#elif __linux__ || __unix__ || __APPLE__
    enum class clr : uint8_t {
        grey = 30,
        red = 31,
        green = 32,
        yellow = 33,
        blue = 34,
        magenta = 35,
        cyan = 36,
        white = 37,
        on_grey = 40,
        on_red = 41,
        on_green = 42,
        on_yellow = 43,
        on_blue = 44,
        on_magenta = 45,
        on_cyan = 46,
        on_white = 47,
        reset
#else
        static_assert(false, "unsupported platform");
#endif
    };

    template<class CharT, class Traits>
    inline std::basic_ostream<CharT, Traits> &operator<<(std::basic_ostream<CharT, Traits> &ostream, const clr color) {
#ifdef _WIN32
        static const uint16_t initial_attributes = [] {
            CONSOLE_SCREEN_BUFFER_INFO buffer_info;
            GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &buffer_info);
            return buffer_info.wAttributes;
        }();
        static uint16_t background = initial_attributes & 0x00F0;
        static uint16_t foreground = initial_attributes & 0x000F;
#endif
        if (color == clr::reset) {
#ifdef _WIN32
            ostream.flush();
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), initial_attributes);
#elif __linux__ || __unix__ || __APPLE__
            ostream << "\033[m";
#endif
        } else {
#ifdef _WIN32
            uint16_t set{};
            if (static_cast<uint16_t>(color) & 0x00F0) {
                background = static_cast<uint16_t>(color);
                set = background | foreground;
            }
            else if (static_cast<uint16_t>(color) & 0x000F) {
                foreground = static_cast<uint16_t>(color);
                set = background | foreground;
            }
            ostream.flush();
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), set);
#elif __linux__ || __unix__ || __APPLE__
            ostream << "\033[" << static_cast<uint32_t>(color) << "m";
#endif
        }
        return ostream;
    }

    constexpr std::array clrs{clr::red, clr::blue, clr::cyan, clr::green, clr::grey, clr::magenta, clr::white,
                              clr::yellow};

    template<typename T>
    concept io_manipulator = std::is_same_v<T, decltype(std::setw(1))> ||
                             std::is_same_v<T, decltype(std::showpos)> ||
                             std::is_same_v<T, decltype(std::boolalpha)> ||
                             std::is_same_v<T, decltype(std::showpoint)> ||
                             std::is_same_v<T, decltype(std::showbase)> ||
                             std::is_same_v<T, decltype(std::uppercase)> ||
                             std::is_same_v<T, decltype(std::hex)> ||
                             std::is_same_v<T, decltype(std::right)> ||
                             std::is_same_v<T, decltype(std::fixed)> ||
                             std::is_same_v<T, decltype(std::skipws)>;

    template<typename char_type, typename traits_type>
    class color_ostream : public std::basic_ostream<char_type, traits_type>{
        size_t i{};
    public:
        inline explicit color_ostream(std::basic_streambuf<char_type, traits_type> *_sb) { this->init(_sb); }
        using ostream = std::basic_ostream<char_type, traits_type>;
        template<typename T>
        requires requires (T a, ostream os){os << a;} && (!io_manipulator<T>)
        color_ostream& operator<<(T t){
            i = i == 7 ? 0 : i + 1;
            reinterpret_cast<ostream&>(*this) << clrs[i] << t;
            return *this;
        }
        inline color_ostream& operator<<(ostream& (*__pf)(ostream&))
        { return reinterpret_cast<color_ostream&>(__pf(reinterpret_cast<ostream&>(*this))); }
    };

    template<typename char_type, typename traits_type>
    class random_ostream : public std::basic_ostream<char_type, traits_type>{
        std::mt19937 gen = std::mt19937(std::random_device{}());
        std::uniform_int_distribution<int> dis = std::uniform_int_distribution(0, 7);
    public:
        inline explicit random_ostream(std::basic_streambuf<char_type, traits_type> *_sb) { this->init(_sb); }
        using ostream = std::basic_ostream<char_type, traits_type>;
        template<typename T>
        requires requires (T a, ostream os){os << a;} && (!io_manipulator<T>)
        random_ostream& operator<<(T t){
            reinterpret_cast<ostream&>(*this) << clrs[dis(gen)] << t;
            return *this;
        }
        inline random_ostream& operator<<(ostream& (*__pf)(ostream&))
        { return reinterpret_cast<random_ostream&>(__pf(reinterpret_cast<ostream&>(*this))); }
    };

#define color(x) \
    using os##x = decltype(std::x);\
    color_ostream<typename os##x::char_type, typename os##x::traits_type> cl_##x(std::x.rdbuf());\
    random_ostream<typename os##x::char_type, typename os##x::traits_type> rd_##x(std::x.rdbuf());

    color(wcout)
    color(cout)
    color(wcerr)
    color(cerr)
    color(wclog)
    color(clog)
}


#endif //TEST_MODERN_CPP_COLOR_OSTREAM_H
