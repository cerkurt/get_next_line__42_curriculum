*This project has been created as part of the 42 curriculum by **cerkurt***.

---

## 📑 Table of Contents

- [Project Overview](#project-overview)
- [Project Files](#project-files)
- [Function Prototype](#function-prototype)
- [How get_next_line Works](#how-get_next_line-works)
- [Detailed Lifecycle](#detailed-lifecycle)
- [BUFFER_SIZE](#buffer_size)
- [Memory Management](#memory-management)
- [Bonus Part](#bonus-part)
- [Error Handling](#error-handling)
- [Compilation & Usage](#compilation--usage)
- [Testing](#testing)
- [42 Norm & Constraints](#42-norm--constraints)

---

## Project Overview

The goal of **get_next_line** is to write a function that returns a line read
from a file descriptor **each time it is called**.

The function must:
- Work with **any BUFFER_SIZE**
- Handle **very large lines** (giant lines)
- Be safe against **memory leaks and invalid access**
- Correctly manage **EOF and read errors**

This project introduces and reinforces key C concepts:
- Static variables
- File descriptors
- Dynamic memory management
- Defensive programming

---

## Project Files

### Mandatory

```
get_next_line.c
get_next_line.h
get_next_line_utils.c
```

### Bonus

```
get_next_line_bonus.c
get_next_line_bonus.h
get_next_line_utils_bonus.c
```

---

## Function Prototype

```c
char *get_next_line(int fd);
```

---

## How get_next_line Works

At a high level, the function:

1. Keeps a **static buffer** between calls
2. Reads from the file descriptor in chunks of `BUFFER_SIZE`
3. Appends each chunk to the buffer
4. Stops reading when a newline (`\n`) is found or EOF is reached
5. Extracts and returns **one line**
6. Stores the leftover data for the next call

Each call resumes exactly where the previous one stopped.

---

## Detailed Lifecycle

### 1. Input Validation

- Check if `fd` is valid
- Check if `BUFFER_SIZE > 0`
- Test `read(fd, 0, 0)` to detect early read errors

If any check fails → free buffer and return `NULL`.

### 2. Reading Phase

- Allocate a temporary buffer of size `BUFFER_SIZE + 1`
- Read from the file using `read()`
- Null-terminate the buffer (`temp_buf[read_bytes] = '\0'`)
- Append it to the static buffer using `gnl_join_and_free`

Reading continues until:
- A newline is found **OR**
- `read()` returns `0` (EOF)

### 3. Line Extraction

- Scan the buffer until the first newline
- Allocate exactly enough memory
- Copy the line (including `\n` if present)

### 4. Buffer Update

- Remove the returned line from the buffer
- Keep only the leftover content
- Free the old buffer

If no leftover exists, the buffer is freed and set to `NULL`.

---

## BUFFER_SIZE

- Defined **at compile time** using `-D BUFFER_SIZE=n`
- Controls how many bytes are read per `read()` call
- Does **not** limit line length

Example:

```bash
cc -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

---

## Memory Management

- Every `malloc` is checked
- All allocated memory is freed when no longer needed
- Static buffers are freed on EOF or error

---

## Bonus Part

The bonus version supports **multiple file descriptors at the same time**.

```c
static char *buffer[OPEN_MAX];
```

Each file descriptor has its **own independent buffer**.

---

## Error Handling

The function safely handles:
- Invalid file descriptors
- `read()` failures
- `malloc()` failures
- End-of-file conditions

---

## Compilation & Usage

### Compilation

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
   get_next_line.c get_next_line_utils.c
```

### Example Usage

```c
int fd = open("file.txt", O_RDONLY);
char *line;

while ((line = get_next_line(fd)) != NULL)
{
    printf("%s", line);
    free(line);
}
close(fd);
```

---

## Testing

Recommended tests:
- Empty files
- Files without trailing newline
- Giant lines
- Multiple BUFFER_SIZE values
- Multiple file descriptors (bonus)

---

## 42 Norm & Constraints

- Max 25 lines per function
- Max 4 variables per function
- Max 5 functions per file
- No forbidden functions
- Norm-compliant formatting

---
