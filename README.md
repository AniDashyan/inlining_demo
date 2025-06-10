# Function Inlining Performance Demo

## Overview

A simple C++ demonstration that compares the performance impact of function inlining. The program benchmarks two identical computational functions - one forced to remain non-inlined and another forced to be inlined - to measure the performance difference caused by function call overhead.

## Build & Run

```bash
git clone https://github.com/AniDashyan/inlining_demo
cd inlining_demo
cmake -S . -B build
cmake --build build --config Release
build/inlining_demo
```

## Example Output

```
Regular: 0.0452s
Inline : 0.0321s
Improvement: 29.0%
```

## Explanation

The program demonstrates function inlining by comparing two versions of the same computational logic:

- **Regular functions**: Use `__attribute__((noinline))` to prevent inlining, forcing actual function calls
- **Inline functions**: Use `__attribute__((always_inline))` to guarantee inlining, eliminating function call overhead

Each version performs the same computation (100,000 elements × 100 iterations), but the inline version typically shows 20-40% performance improvement due to:

1. **Eliminated function call overhead**: No stack frame setup/teardown
2. **Better compiler optimization**: Inlined code can be optimized in context
3. **Reduced instruction cache misses**: Less jumping between memory locations
