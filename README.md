# color
[中文说明](README_zh.md)  
Partly learned from: [colored-cout](https://github.com/yurablok/colored-cout)   
[![release](https://img.shields.io/badge/release-v1.0.0-green)](https://github.com/Wongboo/color/releases/)
![cpp](https://img.shields.io/badge/C%2B%2B-20-red) 
[![chat](https://img.shields.io/badge/Zhihu-chat-blue)](https://zhuanlan.zhihu.com/p/339653025)

## usage
Project is header-only,you can use it via directly include it(at least C++11）  
Let's see, how convenient is our [header](color_ostream.h):  
all you need to do is changing cout to rd_cout
| std | basic color | 256 color | true color |
|  :----: |  :----: |  :----: |  :----: |
| std::cout | color_ostream::rd_cout | color_ostream::rd256_cout | color_ostream::rdtrue_cout
| std::wcout | color_ostream::rd_wcout | color_ostream::rd256_wcout | color_ostream::rdtrue_wcout
| std::cerr | color_ostream::rd_cerr | color_ostream::rd256_cerr | color_ostream::rdtrue_cerr
| std::wcerr | color_ostream::rd_wcerr | color_ostream::rd256_wcerr | color_ostream::rdtrue_wcerr
| std::clog | color_ostream::rd_clog | color_ostream::rd256_clog | color_ostream::rdtrue_clog
| std::wclog | color_ostream::rd_wclog | color_ostream::rd256_wclog | color_ostream::rdtrue_wclog
### note
support for 256 color and true color needs corresponding support in terminal,such as [Windows terminal](https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&cad=rja&uact=8&ved=2ahUKEwjd4eLP4PXtAhWCwosBHSTRBwMQFjAIegQIAhAC&url=https%3A%2F%2Fgithub.com%2Fmicrosoft%2Fterminal&usg=AOvVaw1YH7kNCxSWtXhMBaNHmLvG),  Visual studio debug console, MacOS terminal.app, [iterm2](https://github.com/gnachman/iTerm2) all support 256 color.

## sample
![sample](sample.png)  

## example file
hello.cpp:
```C++
//hello.cpp
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
```
color.cpp:
```C++
//color.cpp
#include "color_ostream.h"

using namespace color_ostream;
using namespace std;

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
    std::cout << clr::red     << " red "
              << clr::yellow  << " yellow "
              << clr::green   << " green "
              << clr::cyan    << " cyan "
              << clr::blue    << " blue "
              << clr::magenta << " magenta "
              << clr::grey    << " grey "
              << clr::white   << " white "
              << clr::reset   << " reset\n";
    std::cout << clr::red     << clr::on_cyan    << " red "
              << clr::yellow  << clr::on_blue    << " yellow "
              << clr::green   << clr::on_magenta << " green "
              << clr::cyan    << clr::on_red     << " cyan "
              << clr::blue    << clr::on_yellow  << " blue "
              << clr::magenta << clr::on_green   << " magenta "
              << clr::grey    << clr::on_white   << " grey "
              << clr::white   << clr::on_grey    << " white "
              << clr::reset                      << " reset\n";
}
```
