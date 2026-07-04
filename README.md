# custom-memory-allocator

## Project Overview:
Custom memory allocator written in C to explore
memory management techniques used by malloc.

Current implementation includes:
- Implicit free list
- Block headers and footers
- Block splitting
- Bidirectional coalescing
- Reuse of freed blocks

## Memory Layout
```
+--------+-----------+--------+
| Header | Payload   | Footer |
+--------+-----------+--------+
```

## Implemented Features

- [x] First-fit allocation
- [x] Block splitting
- [x] Boundary tags
- [x] Forward coalescing
- [x] Backward coalescing
- [x] Internal fragmentation reduction
- [x] External fragmentation reduction

## Planned Features

- [ ] Alignment support
- [ ] Explicit free list
- [ ] Segregated free lists
- [ ] mmap-backed heap
- [ ] Allocator statistics
