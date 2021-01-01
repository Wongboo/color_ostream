#include "color_ostream.h"

using namespace color_ostream;

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
    rd_wcout.imbue(std::locale(std::locale(),"",LC_CTYPE));
    rd_wcout << L"Hello world\n";
    rd_wcout << L"Hola Mundo\n";
    rd_wcout << L"Bonjour le monde\n";

    rd256_wcout << L"\n256 color" << std::endl;
    rd256_wcout << L"Hello world\n";
    rd256_wcout << L"Hola Mundo\n";
    rd256_wcout << L"Bonjour le monde\n";

    rdtrue_wcout << L"\ntrue color" << std::endl;
    rdtrue_wcout << L"Hello world\n";
    rdtrue_wcout << L"Hola Mundo\n";
    rdtrue_wcout << L"Bonjour le monde\n";
    return 0;
}
