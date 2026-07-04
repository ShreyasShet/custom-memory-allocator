# custom-memory-allocator

Project Overview:
Custom memory allocator written in C to explore
memory management techniques used by malloc.

Current implementation includes:
- Implicit free list
- Block headers and footers
- Block splitting
- Bidirectional coalescing
- Reuse of freed blocks

```
+--------+-----------+--------+
| Header | Payload   | Footer |
+--------+-----------+--------+
```

Implemented Features:
✔ First-fit allocation
✔ Block splitting
✔ Boundary tags
✔ Forward coalescing
✔ Backward coalescing
✔ Internal fragmentation reduction
✔ External fragmentation reduction

Planned Features:
□ Alignment support
□ Explicit free list
□ Segregated free lists
□ mmap-backed heap
□ Allocator statistics
