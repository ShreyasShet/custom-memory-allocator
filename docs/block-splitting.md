# Block Splitting

Without splitting:

```text
Free block: 128 bytes
Request: 16 bytes
```

Allocator returns the entire block:

```text
+----------------------+
| allocated 128 bytes  |
+----------------------+
```

Result:

```text
112 bytes wasted
```

With splitting:

```text
+-------------+------------------+
| alloc 16    | free remainder   |
+-------------+------------------+
```

The remaining memory can be reused by future allocations.

This significantly reduces internal fragmentation.
