#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

namespace proxima {

struct VectorRecord {
    int id;
    std::vector<float> data;
};

class VectorStore {
private:
    std::vector<VectorRecord> store_;

    float cosine_similarity(const std::vector<float>& a, const std::vector<float>& b) const {
        if (a.size() != b.size() || a.empty()) return 0.0f;

        float dot = 0.0f, norm_a = 0.0f, norm_b = 0.0f;
        for (size_t i = 0; i < a.size(); ++i) {
            dot += a[i] * b[i];
            norm_a += a[i] * a[i];
            norm_b += b[i] * b[i];
        }

        float denom = std::sqrt(norm_a) * std::sqrt(norm_b);
        return (denom == 0.0f) ? 0.0f : dot / denom;
    }

public:
    void add(int id, const std::vector<float>& vec) {
        store_.push_back({id, vec});
    }

    std::vector<std::pair<int, float>> search(const std::vector<float>& query, int top_k) const {
        std::vector<std::pair<int, float>> results;
        results.reserve(store_.size());

        for (const auto& record : store_) {
            float sim = cosine_similarity(query, record.data);
            results.push_back({record.id, sim});
        }

        std::sort(results.begin(), results.end(),
                  [](const auto& a, const auto& b) { return a.second > b.second; });

        if (results.size() > static_cast<size_t>(top_k)) {
            results.resize(top_k);
        }

        return results;
    }

    size_t size() const {
        return store_.size();
    }
};

} // namespace proxima

int main() {
    proxima::VectorStore store;

    store.add(1, {1.0f, 0.0f, 0.0f});
    store.add(2, {0.0f, 1.0f, 0.0f});
    store.add(3, {0.9f, 0.1f, 0.0f});
    store.add(4, {0.0f, 0.0f, 1.0f});

    std::vector<float> query = {0.7f, 0.3f, 0.0f};

    std::cout << "=== Proxima Vector Search Engine ===\n";
    std::cout << "Vectors in store: " << store.size() << "\n";
    std::cout << "Searching for nearest neighbors...\n\n";

    auto results = store.search(query, 3);

    for (const auto& [id, score] : results) {
        std::cout << "ID: " << id << " | Similarity Score: " << score << "\n";
    }

    return 0;
}