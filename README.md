# get_next_line

A 42 school project that implements a function to read a file line by line from a file descriptor, regardless of the buffer size used.

## Function prototype

```c
char *get_next_line(int fd);
```

Each call returns the next line read from the file descriptor `fd`, including the terminating `\n` (except possibly on the last line). Returns `NULL` when there is nothing more to read or on error.

## Compiling

`BUFFER_SIZE` must be defined at compile time:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
   get_next_line.c get_next_line_utils.c -o gnl
```

## Files

- `get_next_line.c` / `get_next_line.h` — mandatory part (single fd).
- `get_next_line_utils.c` — helpers (`ft_strlen`, `ft_strjoin`, `ft_strchr`).
- `get_next_line_bonus.c` / `get_next_line_bonus.h` — bonus part, supports reading from multiple file descriptors in parallel using a single static variable.
- `get_next_line_utils_bonus.c` — helpers for the bonus part.

## How it works

A static buffer holds whatever has been read past the last returned newline so that the next call can resume from there. On each call, the function reads `BUFFER_SIZE` bytes at a time until it finds a `\n` or hits EOF, then splits the accumulated buffer into the line to return and the leftover to keep for the next call.

## Author

hakaddou — 42 student
