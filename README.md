# Proxima

**High-performance embedded vector search engine in C++20**

Proxima is a lightweight, fast library for approximate nearest neighbor (ANN) search. It stores multi-dimensional vectors and finds the most similar ones using cosine similarity.

## Features

- Pure C++20, no external dependencies
- Fast brute-force search (baseline implementation)
- Cosine similarity metric
- Simple, clean API
- Modern C++ features (concepts, ranges)

## Quick Start

    #include "proxima.h"
    proxima::VectorStore store;
    store.add(1, {1.0f, 0.0f, 0.0f});
    auto results = store.search({0.9f, 0.1f, 0.0f}, 2);

## Building

    mkdir build && cd build
    cmake ..
    cmake --build .

## Requirements

- C++20 compatible compiler (GCC 10+, Clang 12+, MSVC 19.28+)
- CMake 3.20+

## Roadmap

- [ ] SIMD optimization (AVX2)
- [ ] HNSW index for fast approximate search
- [ ] Persistence (save/load to disk)
- [ ] Python bindings
- [ ] Concepts for vector types

## License

MIT