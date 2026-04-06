#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include "modules/tokenizer.hpp"
#include "modules/parser.hpp"
#include "modules/interpret.hpp"
#include "utils/printer.hpp"
#include "modules/compile.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        Printer::error("Usage: brainfuck <input.bf> --c (for compiled)");
        return 1;
    }

    bool compile = false;
    std::string outputFilename = "a.out";

    if (argc == 4 && std::string(argv[2]) == "--c") {
        compile = true;
        outputFilename = argv[3];
    }

    std::string filename = argv[1];

    std::ifstream file(filename);
    if (!file.is_open()) {
        Printer::error("Could not open file: " + filename);
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string text = buffer.str();

    Tokenizer tokenizer(text);
    std::vector<Token> tokens = tokenizer.execute();

    Parser parser(tokens);
    parser.parse();

    if (compile) {
        Compiler compiler(parser.rootNode());
        std::string code = compiler.compile();
        
        // Write C code to temp file
        std::string tempFile = outputFilename + ".c";
        std::ofstream outfile(tempFile);
        outfile << code;
        outfile.close();
        
        // Compile with gcc
        std::string cmd = "gcc -O3 " + tempFile + " -o " + outputFilename;
        int result = std::system(cmd.c_str());
        
        if (result == 0) {
            std::remove(tempFile.c_str());  // Clean up temp .c file
            Printer::success("Compiled to: " + outputFilename);
        } else {
            Printer::error("Compilation failed");
            return 1;
        }
    } else {
        Interpreter interpreter(parser.rootNode(), 30000);
        interpreter.execute();
    }

    return 0;
}   