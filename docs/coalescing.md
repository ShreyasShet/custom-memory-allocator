# Coalescing

Coalescing merges adjacent free blocks into a larger block.

Example:

```text
+---------+---------+
| free 20 | free 30 |
+---------+---------+
```

After coalescing:

```text
+-------------------+
| free 74           |
+-------------------+
```

The merged size includes the reclaimed metadata between the two blocks.

The allocator performs:

* Forward coalescing
* Backward coalescing

using boundary tags (footers).

Coalescing reduces external fragmentation and allows larger future allocations to succeed.
