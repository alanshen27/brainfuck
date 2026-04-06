cd ..
g++ src/main.cpp src/modules/tokenizer.cpp src/modules/parser.cpp src/modules/interpret.cpp src/modules/compile.cpp -o bin/m_brainfuck && bin/m_brainfuck test.bf --c test.out && ./test.out
rm test.out