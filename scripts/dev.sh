cd ..
g++ src/dev.cpp src/modules/tokenizer.cpp src/modules/parser.cpp src/modules/interpret.cpp src/modules/compile.cpp -o bin/d_brainfuck && bin/d_brainfuck test.bf --verbose