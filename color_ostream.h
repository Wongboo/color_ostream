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
    std::basic_ostream<CharT, Traits> &operator<<(std::basic_ostream<CharT, Traits> &ostream, const clr color) {
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
    concept io_manipulator = std::is_same_v<T, decltype(std::showpoint)> ||
                             std::is_same_v<T, decltype(std::setw(1))> ||
                             std::is_same_v<T, decltype(std::setbase(1))> ||
                             std::is_same_v<T, decltype(std::setfill(1))> ||
                             std::is_same_v<T, decltype(std::setprecision(1))> ||
                             std::is_same_v<T, decltype(std::get_time(nullptr, "1"))> ||
                             std::is_same_v<T, decltype(std::get_time(nullptr, L"1"))> ||
                             std::is_same_v<T, decltype(std::quoted("1"))> ||
                             std::is_same_v<T, decltype(std::quoted(L"1"))> ||
                             std::is_same_v<T, decltype(std::resetiosflags(std::ios_base::dec))>;

    template<typename char_type, typename traits_type,typename generator>
    class color_ostream : public std::basic_ostream<char_type, traits_type>{
        generator generator_;
    public:
        inline explicit color_ostream(std::basic_streambuf<char_type, traits_type> *_sb) 
            : std::basic_ostream<char_type, traits_type>(_sb) {}
        using ostream = std::basic_ostream<char_type, traits_type>;
        template<typename T>
        requires requires (T a, ostream os){os << a;} && (!io_manipulator<T>)
        inline color_ostream& operator<<(T t){
            static_cast<ostream&>(*this) << clrs[generator_.get_num()] << t;
            return *this;
        }
        inline color_ostream& operator<<(const char_type* str){
            for (size_t i{}; i < std::char_traits<wchar_t>::length(str); ++i)
                operator<<(str[i]);
            return *this;
        }
        inline color_ostream& operator<<(ostream& (*_pf)(ostream&))
        { return static_cast<color_ostream&>(_pf(static_cast<ostream&>(*this))); }
    };

    class random_generator{
        std::mt19937 gen {std::random_device{}()};
        std::uniform_int_distribution<size_t> dis {0, 7};
    public:
        inline size_t get_num(){return dis(gen);}
    };

    class circle_generator{
        size_t i{};
    public:
        inline size_t get_num(){return i = i == 7 ? 0 : i + 1;}
    };

    random_generator random_color; // NOLINT(cert-err58-cpp)
    template<class CharT, class Traits>
    [[deprecated("This is not good")]]
    inline std::basic_ostream<CharT, Traits> &operator<<(std::basic_ostream<CharT, Traits> &ostream, random_generator& rd){
        return ostream << clrs[rd.get_num()];
    }

#define COLORFUL(x) \
    using os##x = decltype(std::x);\
    color_ostream<typename os##x::char_type, typename os##x::traits_type, circle_generator> cc_##x(std::x.rdbuf());\
    color_ostream<typename os##x::char_type, typename os##x::traits_type, random_generator> rd_##x(std::x.rdbuf());
#define W_COLORFUL(x) COLORFUL(x) COLORFUL(w##x)

    W_COLORFUL(cout) // NOLINT(cert-err58-cpp)
    W_COLORFUL(cerr) // NOLINT(cert-err58-cpp)
    W_COLORFUL(clog) // NOLINT(cert-err58-cpp)
}


#endif //TEST_MODERN_CPP_COLOR_OSTREAM_H
