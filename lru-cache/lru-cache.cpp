#include <iostream>
#include <unordered_map>

class Node {
public:
    int key;
    int value;
    Node* prev;
    Node* next;
    Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    int capacity;
    std::unordered_map<int, Node*> cache;
    Node* head;
    Node* tail;

    // Add a node to the front (right after head)
    void addNode(Node* node) {
        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
    }

    // Remove an existing node from the linked list
    void removeNode(Node* node) {
        Node* prev = node->prev;
        Node* next = node->next;
        prev->next = next;
        next->prev = prev;
    }

    // Move a node to the front (right after head)
    void moveToHead(Node* node) {
        removeNode(node);
        addNode(node);
    }

    // Pop the tail (remove the least recently used node)
    Node* popTail() {
        Node* res = tail->prev;
        removeNode(res);
        return res;
    }

public:
    LRUCache(int capacity) : capacity(capacity) {
        head = new Node(0, 0);
        tail = new Node(0, 0);
        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        if (cache.find(key) == cache.end()) {
            return -1;
        } else {
            Node* node = cache[key];
            moveToHead(node);
            return node->value;
        }
    }

    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            Node* node = cache[key];
            node->value = value;
            moveToHead(node);
        } else {
            Node* node = new Node(key, value);
            cache[key] = node;
            addNode(node);

            if (cache.size() > capacity) {
                Node* tail = popTail();
                cache.erase(tail->key);
                delete tail;
            }
        }
    }

    ~LRUCache() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
};

// Example Usage
int main() {
    LRUCache lruCache(2);

    lruCache.put(1, 1);
    lruCache.put(2, 2);
    std::cout << lruCache.get(1) << std::endl;  // Returns 1

    lruCache.put(3, 3);  // Evicts key 2
    std::cout << lruCache.get(2) << std::endl;  // Returns -1 (not found)

    lruCache.put(4, 4);  // Evicts key 1
    std::cout << lruCache.get(1) << std::endl;  // Returns -1 (not found)
    std::cout << lruCache.get(3) << std::endl;  // Returns 3
    std::cout << lruCache.get(4) << std::endl;  // Returns 4

    return 0;
}