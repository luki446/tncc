#include <fmt/core.h>

int main() {
    fmt::print("Hello, World!\n");
    
    #ifdef DEBUG
        fmt::print("Debug only\n");
    #endif

}