#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

namespace proxima {

// Структура для хранения вектора и его уникального ID
struct VectorRecord {
    int id;
    std::vector<float> data;
};

// Ядро движка: хранилище и поиск
class VectorStore {
private:
    std::vector<VectorRecord> store_;

    // Вычисляем косинусное сходство (от -1.0 до 1.0, где 1.0 = полная идентичность)
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
    // Добавление нового вектора в хранилище
    void add(int id, const std::vector<float>& vec) {
        store_.push_back({id, vec});
    }

    // Поиск top_k ближайших соседей к запросу
    std::vector<std::pair<int, float>> search(const std::vector<float>& query, int top_k) const {
        std::vector<std::pair<int, float>> results;
        results.reserve(store_.size()); // Оптимизация: сразу резервируем память

        for (const auto& record : store_) {
            float sim = cosine_similarity(query, record.data);
            results.push_back({record.id, sim});
        }

        // Сортируем по убыванию сходства (от наиболее похожего к наименее)
        std::sort(results.begin(), results.end(),
                  [](const auto& a, const auto& b) { return a.second > b.second; });

        // Оставляем только top_k результатов
        if (results.size() > static_cast<size_t>(top_k)) {
            results.resize(top_k);
        }

        return results;
    }

    // Полезная утилита: узнать количество векторов в хранилище
    size_t size() const {
        return store_.size();
    }
};

} // namespace proxima

int main() {
    proxima::VectorStore store;

    // Добавляем тестовые данные (эмбеддинги)
    store.add(1, {1.0f, 0.0f, 0.0f}); // Документ 1: "Яблоки"
    store.add(2, {0.0f, 1.0f, 0.0f}); // Документ 2: "Бананы"
    store.add(3, {0.9f, 0.1f, 0.0f}); // Документ 3: "Фрукты" (похож на яблоки)
    store.add(4, {0.0f, 0.0f, 1.0f}); // Документ 4: "Автомобили"

    // Поисковый запрос: "Что-то среднее между яблоками и бананами"
    std::vector<float> query = {0.7f, 0.3f, 0.0f};

    std::cout << "=== Proxima Vector Search Engine ===\n";
    std::cout << "Vectors in store: " << store.size() << "\n";
    std::cout << "Searching for nearest neighbors...\n\n";

    // Ищем топ-3 наиболее похожих вектора
    auto results = store.search(query, 3);

    for (const auto& [id, score] : results) {
        std::cout << "ID: " << id << " | Similarity Score: " << score << "\n";
    }

    return 0;
}