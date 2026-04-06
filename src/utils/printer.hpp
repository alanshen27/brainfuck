#pragma once

#include <string>
#include <iostream>

namespace Color {
    // @source https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
    constexpr const char* reset   = "\033[0m";
    constexpr const char* black   = "\033[30m";
    constexpr const char* red     = "\033[31m";
    constexpr const char* green   = "\033[32m";
    constexpr const char* yellow  = "\033[33m";
    constexpr const char* blue    = "\033[34m";
    constexpr const char* magenta = "\033[35m";
    constexpr const char* cyan    = "\033[36m";
    constexpr const char* white   = "\033[37m";
    
    constexpr const char* brightRed     = "\033[91m";
    constexpr const char* brightGreen   = "\033[92m";
    constexpr const char* brightYellow  = "\033[93m";
    constexpr const char* brightBlue    = "\033[94m";
    constexpr const char* brightMagenta = "\033[95m";
    constexpr const char* brightCyan    = "\033[96m";
    
    constexpr const char* bold      = "\033[1m";
    constexpr const char* dim       = "\033[2m";
    constexpr const char* underline = "\033[4m";
}

class Printer {
public:
    // basic outputs, minimal abstractions

    static void print(const std::string& text, const char* color = Color::reset) {
        std::cout << color << text << Color::reset;
    }

    static void println(const std::string& text, const char* color = Color::reset) {
        std::cout << color << text << Color::reset << std::endl;
    }

    // presets

    static void error(const std::string& text) {
        std::cerr << Color::red << "Error: " << text << Color::reset << std::endl;
    }

    static void warn(const std::string& text) {
        std::cout << Color::yellow << "Warning: " << text << Color::reset << std::endl;
    }

    static void success(const std::string& text) {
        std::cout << Color::green << text << Color::reset << std::endl;
    }

    static void info(const std::string& text) {
        std::cout << Color::cyan << text << Color::reset << std::endl;
    }
};
