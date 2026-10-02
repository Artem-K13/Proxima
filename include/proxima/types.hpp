#pragma once

#include <vector>
#include <cstdint>

namespace proxima {

    // Тип для ID вектора
    using VectorId = int64_t;

    // Тип для значений в векторе
    using ValueType = float;

    // Сам вектор (массив float)
    using Vector = std::vector<ValueType>;

    // Результат поиска: ID вектора и его сходство с запросом
    struct SearchResult {
        VectorId id;
        float similarity;
    };

} // namespace proxima