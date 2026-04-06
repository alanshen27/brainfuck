# Brainfuck

**In progress** — this repository is under active development.

Made in 1993 by Swiss student Urban Müller, `bf` was designed to minimalistic, with the language consisting of only 8 commands.

This makes the development and parsing packages simple, understandable, and maintainable, making it perfectly suitable for applications and research into compilers, interpreters, and other translators.

This repository contains a compiler and interperter.

## Installation

Make sure to have `g++` / `gcc` installed on your local machine, then use the scripts in `/scripts` to run any of the functions.

## Usage

From the repository root, build the main tool (interpreter + transpile / compiler):

```sh
g++ src/main.cpp src/modules/tokenizer.cpp src/modules/parser.cpp \
  src/modules/interpret.cpp src/modules/compile.cpp -o bin/m_brainfuck
```

Run a `.bf` file with the interpreter (30000-cell tape):

```sh
./bin/m_brainfuck path/to/program.bf
```

Transpile to C, which is then automatically compiled with `gcc -O3`, producing a native binary:

```sh
./bin/m_brainfuck path/to/program.bf --c myprogram
./myprogram
```

Optional development / testing binary with `--verbose` (see `src/dev.cpp`):

```sh
g++ src/dev.cpp src/modules/tokenizer.cpp src/modules/parser.cpp \
  src/modules/interpret.cpp src/modules/compile.cpp -o bin/d_brainfuck
./bin/d_brainfuck path/to/program.bf --verbose
```

## Contributing

Pull requests are welcome. Please open an issue first
to discuss what you would like to change.

## License

[MIT](LICENSE)