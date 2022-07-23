#include "co_context/io_context.hpp"
#include "co_context/lazy_io.hpp"
#include <errno.h>

using namespace std::literals;
using namespace co_context;

task<> delay_output() {
    int result = co_await timeout(1.14514s);
    printf("Hello timeout!\n(result = %d)\n", result); // Expect result == -62
    // co_context_stop();
}

task<> my_clock() {
    for (int cnt = 0;;) {
        printf("Time = %d\n", cnt++);
        co_await (timeout(1s) && lazy::write(STDOUT_FILENO, "Tick\n", 0));
    }
}

int main() {
    io_context ctx{32768};
    // ctx.co_spawn(delay_output());
    ctx.co_spawn(my_clock());
    ctx.run();

    return 0;
}