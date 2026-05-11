# Cache Memory Simulator

A C++ implementation of a CPU cache memory simulator that demonstrates how cache replacement policies work. Supports **LRU (Least Recently Used)** and **FIFO (First In First Out)** replacement policies with real-time cache state visualization.

---

## What is Cache Memory?

Cache memory sits between the CPU and main memory. It stores recently or frequently accessed data so the CPU doesn't have to fetch it from slow main memory every time.

- **Cache Hit** → Data found in cache → served immediately (fast)
- **Cache Miss** → Data not in cache → fetched from main memory → loaded into cache (slow)

When the cache is full and a miss occurs, a **replacement policy** decides which existing block to evict to make room for the new one. Different policies make different tradeoffs — this simulator lets you observe and compare them.

---

## Features

- LRU and FIFO replacement policies
- Real-time cache state display after every memory access
- Hit/Miss tracking with final statistics
- Hit rate and miss rate percentage at the end
- Clean class-based C++ implementation

---

## Replacement Policies Implemented

### LRU — Least Recently Used
Evicts the block that was accessed **least recently**. Maintains a usage order — on every hit, the accessed block moves to the front. The back of the list is always the eviction candidate.

```
Cache size: 3, Access: 1 2 3 1

Access 1 -> MISS | Cache: [1]
Access 2 -> MISS | Cache: [2, 1]
Access 3 -> MISS | Cache: [3, 2, 1]
Access 1 -> HIT  | Cache: [1, 3, 2]   ← 1 moved to front
```

### FIFO — First In First Out
Evicts the block that was loaded into cache **first**, regardless of how recently it was used. Order never changes on a hit.

```
Cache size: 3, Access: 1 2 3 1

Access 1 -> MISS | Cache: [1]
Access 2 -> MISS | Cache: [1, 2]
Access 3 -> MISS | Cache: [1, 2, 3]
Access 1 -> HIT  | Cache: [1, 2, 3]   ← order unchanged
```

---

## How to Compile & Run

### Requirements
- g++ compiler (C++11 or later)

### compile
```bash
g++ CacheMemory.cpp -o CacheMemory
```

### Run
```bash
./CacheMemory          # Linux/Mac
.\CacheMemory          # Windows PowerShell
```

---

## Sample Output

```
Enter cache size: 4
Choose policy (LRU/FIFO): LRU

Memory Access Sequence:
Accessing 1 -> MISS | Cache: [1]
Accessing 2 -> MISS | Cache: [2, 1]
Accessing 3 -> MISS | Cache: [3, 2, 1]
Accessing 4 -> MISS | Cache: [4, 3, 2, 1]
Accessing 1 -> HIT  | Cache: [1, 4, 3, 2]
Accessing 2 -> HIT  | Cache: [2, 1, 4, 3]
Accessing 5 -> MISS | Cache: [5, 2, 1, 4]
Accessing 1 -> HIT  | Cache: [1, 5, 2, 4]
Accessing 2 -> HIT  | Cache: [2, 1, 5, 4]
Accessing 3 -> MISS | Cache: [3, 2, 1, 5]
Accessing 4 -> MISS | Cache: [4, 3, 2, 1]
Accessing 5 -> MISS | Cache: [5, 4, 3, 2]

--- Cache Statistics ---
Total Accesses: 12
Hits: 4
Misses: 8
Hit Rate: 33.3333%
Miss Rate: 66.6667%
```

---

## LRU vs FIFO Comparison

Same access sequence `{1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5}` with cache size 4:

| Policy | Hits | Misses | Hit Rate |
|--------|------|--------|----------|
| LRU    | 4    | 8      | 33.33%   |
| FIFO   | 2    | 10     | 16.67%   |

LRU outperforms FIFO here because the access pattern has **temporal locality** — recently accessed blocks (1, 2) get accessed again soon. LRU keeps them; FIFO may evict them based on arrival order regardless of recency.

---

## Data Structures Used

| Structure | Purpose |
|-----------|---------|
| `std::list` | LRU order tracking — O(1) insert/remove at front and back |
| `std::queue` | FIFO order tracking — natural first-in-first-out |
| `std::unordered_set` | O(1) cache lookup for both policies |

Both policies use a **set + list/queue pair**: the set for fast hit/miss detection, the list/queue for eviction order.

---

## Known Limitations & Future Improvements

- Current DFT implementation is O(n²) — real systems use FFT which is O(n log n)
- Access sequence is hardcoded — future version will accept user input
- Write policies (write-through, write-back) not yet implemented
- Could add MRU (Most Recently Used) and Random replacement policies
- No associativity (direct-mapped only) — set-associative cache is a natural next step

---

## Concepts Covered

- Cache memory hierarchy
- Cache hit and miss behavior
- Replacement policy tradeoffs (recency vs arrival order)
- Temporal locality in memory access patterns
- Data structure selection based on algorithmic requirements

---

## Author

**Drishti Tripathi**   
[GitHub](https://github.com/DrishtiTripathi2230)
