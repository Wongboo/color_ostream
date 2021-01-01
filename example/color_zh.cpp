#include "color_ostream.h"

using namespace color_ostream;
using namespace std;

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
    wcout << clr::red     << L" red "
              << clr::yellow  << L" yellow "
              << clr::green   << L" green "
              << clr::cyan    << L" cyan "
              << clr::blue    << L" blue "
              << clr::magenta << L" magenta "
              << clr::grey    << L" grey "
              << clr::white   << L" white "
              << clr::reset   << L" reset\n";
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
}