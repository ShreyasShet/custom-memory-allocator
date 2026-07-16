# custom-memory-allocator

## Project Overview:
Custom memory allocator written in C to explore
memory management techniques used by malloc.

## Block Layout
```
+--------+-----------+--------+
| Header | Payload   | Footer |
+--------+-----------+--------+
```

## Allocation Overview
```
+--------+--------+--------+--------+-----------+--------+--------+--------+
|Padding |  Prologue Block | Header | Payload   | Footer |........|Epilogue|
+--------+--------+--------+--------+-----------+--------+--------+--------+
                           ^                                      ^
                        heap_start                             heap_end
```
- Padding implies skipping 8B of heap to keep the payload aligned
- Prologue Block(header + footer) and Epilogue(Header) are always allocated when heap is initialized and act as boundaries for allocation

## Implemented Features

- [x] First-fit allocation
- [x] Block splitting
- [x] Boundary tags
- [x] Forward coalescing
- [x] Backward coalescing
- [x] Internal fragmentation reduction
- [x] External fragmentation reduction
- [x] Alignment Support
- [x] Explicit free list

## Planned Features

- [ ] Segregated free lists
- [ ] mmap-backed heap
- [ ] Allocator statistics
