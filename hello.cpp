#include <span>
#include "color_ostream.h"

using namespace color_ostream;

int main() {
    cl_wcout.imbue(std::locale(std::locale(),"",LC_CTYPE));
    auto print = [&](const auto& s) {
        for (const auto &item : s)
            cl_wcout << item;
        cl_wcout << '\n';
    };

    std::wstring s= L"你好，沃德";
    print(s);
    std::wstring_view t = L"你好，世界";
    print(t);
    std::span<const wchar_t> u = L"哈啰，世界";
    print(u);
    return 0;
}
