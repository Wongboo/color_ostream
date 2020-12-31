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

int main() {
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
```
color.cpp:
```C++
//color.cpp
#include "color_ostream.h"

using namespace color_ostream;
using namespace std;

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
    cout << clr::red     << " red "
              << clr::yellow  << " yellow "
              << clr::green   << " green "
              << clr::cyan    << " cyan "
              << clr::blue    << " blue "
              << clr::magenta << " magenta "
              << clr::grey    << " grey "
              << clr::white   << " white "
              << clr::reset   << " reset\n";
    wcout.imbue(locale(locale(),"",LC_CTYPE));
    wcout << clr::red     << clr::on_cyan    << L" 红色 "
              << clr::yellow  << clr::on_blue    << L" 黄色 "
              << clr::green   << clr::on_magenta << L" 绿色 "
              << clr::cyan    << clr::on_red     << L" 青色 "
              << clr::blue    << clr::on_yellow  << L" 蓝色 "
              << clr::magenta << clr::on_green   << L" 紫红 "
              << clr::grey    << clr::on_white   << L" 灰色 "
              << clr::white   << clr::on_grey    << L" 白色 "
              << clr::reset                      << L" 重置\n";
    for (size_t i{}; i < 9; ++i)
        wcout << random_color << L" 彩色 ";
    wcout << '\n';

    random_generator rd;
    for (size_t i{}; i < 9; ++i)
        wcout << clrs[random_color.get_num()] << L" 彩色 ";
    wcout << '\n';
}
```
