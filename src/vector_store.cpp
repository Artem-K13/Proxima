#include "proxima/vector_store.hpp"
#include <iostream>

int main() {
    proxima::VectorStore store;

    // Добавляем тестовые данные
    store.add(1, {1.0f, 0.0f, 0.0f});
    store.add(2, {0.0f, 1.0f, 0.0f});
    store.add(3, {0.9f, 0.1f, 0.0f});
    store.add(4, {0.0f, 0.0f, 1.0f});

    // Поисковый запрос
    proxima::Vector query = {0.7f, 0.3f, 0.0f};

    std::cout << "=== Proxima Vector Search Engine ===\n";
    std::cout << "Vectors in store: " << store.size() << "\n";
    std::cout << "Searching for nearest neighbors...\n\n";

    // Ищем топ-3
    auto results = store.search(query, 3);

    for (const auto& result : results) {
        std::cout << "ID: " << result.id
                  << " | Similarity: " << result.similarity << "\n";
    }

    return 0;
}