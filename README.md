# 🪣 FT_CONTAINERS

A C++98 re-implementation of three standard containers:
- `ft::vector`
- `ft::stack`
- `ft::map`

## 👩🏻‍🏫 What I have gained from the project

Working on this project helped me build practical knowledge of:
- implementing container internals with templates in C++98
- iterator behavior and compatibility with generic algorithms
- memory management patterns and exception-safe container operations
- binary tree-based associative container logic for `map`
- reproducing STL-like APIs and testing behavior against `std`

## 📦 Prerequisites

- A C++ compiler compatible with C++98 (`c++`/`clang++`/`g++`)
- `make`
- A Unix-like environment (Linux/macOS)

The project is compiled with these flags:
- `-Wall -Wextra -Werror -std=c++98`

## 🚀 Usage

Build the executable:

```bash
make
```

Run the main test program (requires a seed argument):

```bash
./containers 42
```

Useful make targets:

```bash
make run      # build + run
make clean    # remove object files
make fclean   # remove object files + executable
make re       # rebuild from scratch
```

If you want to compare behavior with the standard library vs your own implementation,
update the `#if` switch in `main.cpp`.
