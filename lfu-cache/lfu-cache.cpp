#include <unordered_map>
#include <list>
#include <iostream>

class LFUCache {
private:
    struct CacheNode {
        int key;
        int value;
        int freq;
        CacheNode(int k, int v, int f) : key(k), value(v), freq(f) {}
    };

    int capacity;
    int minFreq;
    std::unordered_map<int, std::list<CacheNode>::iterator> cache;  // Key to node iterator
    std::unordered_map<int, std::list<CacheNode>> freqList;         // Frequency to list of nodes

    void updateFreq(int key) {
        auto node = cache[key];
        int freq = node->freq;
        int value = node->value;

        // Remove node from the current frequency list
        freqList[freq].erase(node);
        if (freqList[freq].empty() && freq == minFreq) {
            freqList.erase(freq);
            minFreq++;
        }

        // Add node to the new frequency list
        freq++;
        freqList[freq].emplace_front(key, value, freq);
        cache[key] = freqList[freq].begin();
    }

public:
    LFUCache(int capacity) : capacity(capacity), minFreq(0) {}

    int get(int key) {
        if (cache.find(key) == cache.end()) {
            return -1;  // Key not found
        }

        // Update frequency
        updateFreq(key);
        return cache[key]->value;
    }

    void put(int key, int value) {
        if (capacity == 0) {
            return;
        }

        if (cache.find(key) != cache.end()) {
            // Update the value and frequency
            cache[key]->value = value;
            updateFreq(key);
        } else {
            if (cache.size() >= capacity) {
                // Evict the least frequently used node
                auto evictNode = freqList[minFreq].back();
                cache.erase(evictNode.key);
                freqList[minFreq].pop_back();
                if (freqList[minFreq].empty()) {
                    freqList.erase(minFreq);
                }
            }

            // Add new node with frequency 1
            minFreq = 1;
            freqList[1].emplace_front(key, value, 1);
            cache[key] = freqList[1].begin();
        }
    }
};

// Example Usage
int main() {
    LFUCache lfuCache(2);

    lfuCache.put(1, 1);
    lfuCache.put(2, 2);
    std::cout << lfuCache.get(1) << std::endl;  // Returns 1

    lfuCache.put(3, 3);  // Evicts key 2
    std::cout << lfuCache.get(2) << std::endl;  // Returns -1 (not found)

    lfuCache.put(4, 4);  // Evicts key 1
    std::cout << lfuCache.get(1) << std::endl;  // Returns -1 (not found)
    std::cout << lfuCache.get(3) << std::endl;  // Returns 3
    std::cout << lfuCache.get(4) << std::endl;  // Returns 4

    return 0;
}