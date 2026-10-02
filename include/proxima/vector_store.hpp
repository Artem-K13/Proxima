#pragma once

#include "types.hpp"
#include <vector>
#include <utility>

namespace proxima {

    class VectorStore {
    public:
        // Добавить вектор в хранилище
        void add(VectorId id, const Vector& vec);

        // Найти top_k ближайших соседей к запросу
        std::vector<SearchResult> search(const Vector& query, int top_k) const;

        // Получить количество векторов в хранилище
        size_t size() const;

    private:
        struct VectorRecord {
            VectorId id;
            Vector data;
        };

        std::vector<VectorRecord> store_;

        // Вычислить косинусное сходство
        float cosine_similarity(const Vector& a, const Vector& b) const;
    };

} // namespace proxima