#include <iostream>
#include <unordered_map>
#include <queue>

class FIFOCache {
public:
    // Constructor to initialize the cache with a given capacity
    FIFOCache(int capacity) : capacity_(capacity) {}

    // Method to retrieve an item from the cache
    int get(int key) {
        // Check if the key is in the cache
        if (cache_.find(key) == cache_.end()) {
            return -1; // Return -1 if the key is not found
        }
        return cache_[key]; // Return the value if the key is found
    }

    // Method to add or update an item in the cache
    void put(int key, int value) {
        // If the key is already in the cache, just update the value
        if (cache_.find(key) != cache_.end()) {
            cache_[key] = value;
            return;
        }

        // If the cache is full, evict the oldest item
        if (cache_.size() >= capacity_) {
            int oldest_key = order_.front(); // Get the oldest key
            order_.pop(); // Remove the oldest key from the queue
            cache_.erase(oldest_key); // Remove the oldest key from the cache
        }

        // Add the new key-value pair to the cache
        cache_[key] = value;
        order_.push(key); // Add the new key to the end of the queue
    }

private:
    int capacity_; // The maximum capacity of the cache
    std::unordered_map<int, int> cache_; // The cache storage
    std::queue<int> order_; // The order of keys (FIFO)
};

// Example Usage
int main() {
    FIFOCache fifo_cache(2);
    
    fifo_cache.put(1, 1);
    fifo_cache.put(2, 2);
    std::cout << fifo_cache.get(1) << std::endl; // Returns 1
    
    fifo_cache.put(3, 3); // Evicts key 2
    std::cout << fifo_cache.get(2) << std::endl; // Returns -1 (not found)
    
    fifo_cache.put(4, 4); // Evicts key 1
    std::cout << fifo_cache.get(1) << std::endl; // Returns -1 (not found)
    std::cout << fifo_cache.get(3) << std::endl; // Returns 3
    std::cout << fifo_cache.get(4) << std::endl; // Returns 4

    return 0;
}