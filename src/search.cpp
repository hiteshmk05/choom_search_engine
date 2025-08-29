#include "search/query_engine.h"
#include <iostream>
#include <string>

int main() {
    Database db("search_engine.db");
    QueryEngine engine(db);

    std::cout << "choom search engine" << std::endl;
    std::cout << "-----------------------" << std::endl;
    std::cout << "enter to search (exit to exit)" << std::endl;

    std::string query_line;
    while (std::cout << "> " && std::getline(std::cin, query_line)) {
        if (query_line == "exit") {
            break;
        }

        std::vector<SearchResult> results = engine.search(query_line);

        if (results.empty()) {
            std::cout << "No results found." << std::endl;
        } else {
            std::cout << "Found " << results.size() << " results:" << std::endl;
            for (const auto& res : results) {
                std::cout << "  - URL: " << res.url << std::endl;
            }
        }
        std::cout << std::endl;
    }

    return 0;
}