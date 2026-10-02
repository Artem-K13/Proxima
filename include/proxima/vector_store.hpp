#pragma once

#include "types.hpp"
#include <vector>
#include <utility>

namespace proxima {

    class VectorStore {
    public:
        void add(VectorId id, const Vector& vec);

        std::vector<SearchResult> search(const Vector& query, int top_k) const;

        size_t size() const;

    private:
        struct VectorRecord {
            VectorId id;
            Vector data;
        };

        std::vector<VectorRecord> store_;

        float cosine_similarity(const Vector& a, const Vector& b) const;
    };

} // namespace proxima