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
    size_t size;
    int free;
} Header;
```

Footer stores:

```c
typedef struct footer {
    size_t size;
} Footer;
```

The footer acts as a boundary tag, allowing the allocator to locate the previous block during backward coalescing.

Example block:

```text
+------------------+------------------+------------------+
| size=64 free=0   | 64-byte payload  | size=64          |
+------------------+------------------+------------------+
```
