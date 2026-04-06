#include <chrono>
#include <fstream>
#include <sstream>
#include "modules/tokenizer.hpp"
#include "modules/parser.hpp"
#include "modules/interpret.hpp"
#include "utils/printer.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        Printer::error("Usage: brainfuck <input.bf> --verbose (optional)");
        return 1;
    }

    std::string filename = argv[1];
    bool verbose = false;
    if (argc == 3 && std::string(argv[2]) == "--verbose") {
        verbose = true;
        Printer::println("verbose mode enabled", Color::green);
    }

    Printer::print("input file ", Color::dim);
    Printer::println(filename, Color::cyan);

    std::ifstream file(filename);
    if (!file.is_open()) {
        Printer::error("could not open file: " + filename);
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string text = buffer.str();

    Printer::println("tokenizing...", Color::dim);
    auto t1 = std::chrono::high_resolution_clock::now();
    Tokenizer tokenizer(text);
    std::vector<Token> tokens = tokenizer.execute();
    if (verbose) {
        for (const Token& token : tokens) {
            Printer::println(token.format(), Color::dim);
        }
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    auto tokenMs = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() / 1000.0;
    Printer::println(" complete (" + std::to_string(tokenMs).substr(0, 4) + "ms)", Color::green);

    Printer::print("parsing...", Color::dim);
    t1 = std::chrono::high_resolution_clock::now();
    Parser parser(tokens);
    parser.parse();
    if (verbose) {
        Printer::println("\n" + parser.rootNode().format(), Color::dim);
    }
    t2 = std::chrono::high_resolution_clock::now();
    auto parseMs = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() / 1000.0;
    Printer::println("complete (" + std::to_string(parseMs).substr(0, 4) + "ms)", Color::green);

    Printer::println("executing... ", Color::dim);
    t1 = std::chrono::high_resolution_clock::now();
    Interpreter interpreter(parser.rootNode(), 30000);
    interpreter.execute();
    t2 = std::chrono::high_resolution_clock::now();
    auto execMs = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() / 1000.0;  
    Printer::print("execution time: ", Color::dim);
    Printer::println(" complete (" + std::to_string(execMs).substr(0, 4) + "ms)", Color::green);

    return 0;
}   