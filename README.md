# get_next_line

> Read a file line by line, one call at a time — regardless of buffer size.

A 42 school project that implements `get_next_line`, a function which returns the next line from a file descriptor on each successive call. The implementation works with any `BUFFER_SIZE` (1, 42, 9999...) and preserves leftover data between calls using a static variable.

---

## Prototype

```c
char *get_next_line(int fd);
```

| Returns | Meaning |
| --- | --- |
| `"...\n"` | The next line, including the trailing newline |
| `"..."`   | The final line of the file (no trailing newline) |
| `NULL`    | Nothing left to read, or a read error occurred |

---

## Build

`BUFFER_SIZE` is provided at compile time via `-D`:

```sh
# Mandatory part
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
   get_next_line.c get_next_line_utils.c main.c -o gnl

# Bonus part (multiple file descriptors in parallel)
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
   get_next_line_bonus.c get_next_line_utils_bonus.c main.c -o gnl_bonus
```

---

## Usage

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int   fd = open("file.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

---

## How it works

```
            ┌──────────────────────────────────────────┐
   fd  ──►  │  read BUFFER_SIZE bytes  ──►  stash[]    │
            │  until '\n' is found or EOF              │
            └──────────────────┬───────────────────────┘
                               │
                               ▼
            ┌──────────────────────────────────────────┐
            │  split stash on first '\n':              │
            │    • return  →  everything up to '\n'    │
            │    • keep    →  the rest (next call)     │
            └──────────────────────────────────────────┘
```

A static variable holds whatever was read past the last returned newline, so the next call resumes exactly where the previous one stopped. The bonus version uses a single static array indexed by `fd`, allowing interleaved reads from multiple descriptors.

---

## Files

| File | Purpose |
| --- | --- |
| `get_next_line.c` / `get_next_line.h` | Mandatory part — single file descriptor |
| `get_next_line_utils.c` | Helpers: `ft_strlen`, `ft_strjoin`, `ft_strchr`, trimming |
| `get_next_line_bonus.c` / `get_next_line_bonus.h` | Bonus — multiple FDs in parallel |
| `get_next_line_utils_bonus.c` | Helpers for the bonus part |

---

## Notes

- No memory leaks — every allocation is paired with a `free`.
- Works on regular files, pipes, and stdin.
- Compiled with `-Wall -Wextra -Werror`, no warnings.

---

## Author

**hakaddou** — 42 student
