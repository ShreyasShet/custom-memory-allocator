# Memory Layout

Each block in the allocator consists of three parts:

```text
+--------+-----------+--------+
| Header | Payload   | Footer |
+--------+-----------+--------+
```

Header stores:

```c
typedef struct header {
    size_t size_and_flags;
} Header;
```
Bit Layout for storing size and flags:

```text
 63                 4  3  2  1  0
+--+---------------+--+--+--+--+--+
|    Payload Size     |0 |0 |0 |A |
+--+---------------+--+--+--+--+--+
```
Bits 4 - 63 store payload size
Bits 1 - 3 reserved for future use
Bit 0 used as a allocation flag

eg: my_malloc(48)
Header Stores:
h->size_and_flags = 48 | 1

Footer stores:

```c
typedef struct footer {
    size_t size;
} Footer;
```

The footer acts as a boundary tag, allowing the allocator to locate the previous block during backward coalescing.

Example block:

```text
+----------------------+------------------+------------------+
|size_and_flags= 64 | 1| 64-byte payload  | size=64          |
+----------------------+------------------+------------------+
```
