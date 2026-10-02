#pragma once

#include <vector>
#include <cstdint>

namespace proxima {

    using VectorId = int64_t;

    using ValueType = float;

    using Vector = std::vector<ValueType>;

    struct SearchResult {
        VectorId id;
        float similarity;
    };

} // namespace proxima