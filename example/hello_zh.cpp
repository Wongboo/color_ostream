#include "color_ostream.h"

using namespace color_ostream;

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
    rd_wcout.imbue(std::locale(std::locale(),"",LC_CTYPE));
    rd_wcout << L"你好，沃德\n";
    rd_wcout << L"你好，世界\n";
    rd_wcout << L"哈啰，世界\n";

    rd256_wcout << L"\n256 color" << std::endl;
    rd256_wcout << L"你好，沃德\n";
    rd256_wcout << L"你好，世界\n";
    rd256_wcout << L"哈啰，世界\n";

    rdtrue_wcout << L"\ntrue color" << std::endl;
    rdtrue_wcout << L"你好，沃德\n";
    rdtrue_wcout << L"你好，世界\n";
    rdtrue_wcout << L"哈啰，世界\n";
    return 0;
}
