#include "crawler/crawler.h"
#include <iostream>

int main() {
    
    unsigned int num_threads = 4;
    if (num_threads == 0) num_threads = 4;

    std::cout << "Starting indexer with " << num_threads << " threads." << std::endl;

    Crawler crawler(num_threads, "search_engine.db");

    crawler.start("https://www.vlib.org/");

    std::cout << "\nIndexing finished." << std::endl;
    std::cout << "Total unique pages indexed: " << crawler.get_visited_size() << std::endl;

    return 0;
}