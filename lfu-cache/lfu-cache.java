import java.util.HashMap;
import java.util.LinkedHashSet;

class LFUCache {
    // Node class to store key-value pairs along with their frequency
    class Node {
        int key, value, freq;

        Node(int key, int value) {
            this.key = key;
            this.value = value;
            this.freq = 1;
        }
    }

    // Maximum capacity of the cache
    private final int capacity;
    // HashMap to store key to node mappings
    private final HashMap<Integer, Node> cache;
    // HashMap to store frequency to keys mappings
    private final HashMap<Integer, LinkedHashSet<Node>> freqMap;
    // Variable to keep track of the minimum frequency
    private int minFreq;

    // Constructor to initialize the cache
    public LFUCache(int capacity) {
        this.capacity = capacity;
        this.cache = new HashMap<>();
        this.freqMap = new HashMap<>();
        this.minFreq = 0;
    }

    // Method to get the value of a key if it exists in the cache
    public int get(int key) {
        if (!cache.containsKey(key)) {
            return -1;
        }

        // Get the node from the cache
        Node node = cache.get(key);
        // Update the frequency of the node
        updateFreq(node);
        return node.value;
    }

    // Method to put a key-value pair into the cache
    public void put(int key, int value) {
        if (capacity == 0) return;

        if (cache.containsKey(key)) {
            // Update the value of the existing node
            Node node = cache.get(key);
            node.value = value;
            updateFreq(node);
        } else {
            // Evict the least frequently used node if the cache is full
            if (cache.size() >= capacity) {
                evict();
            }

            // Create a new node and add it to the cache
            Node node = new Node(key, value);
            cache.put(key, node);
            freqMap.computeIfAbsent(1, k -> new LinkedHashSet<>()).add(node);
            minFreq = 1;
        }
    }

    // Method to update the frequency of a node
    private void updateFreq(Node node) {
        // Remove the node from the current frequency list
        int freq = node.freq;
        freqMap.get(freq).remove(node);
        if (freqMap.get(freq).isEmpty()) {
            freqMap.remove(freq);
            if (minFreq == freq) {
                minFreq++;
            }
        }

        // Increment the frequency and add the node to the new frequency list
        node.freq++;
        freqMap.computeIfAbsent(node.freq, k -> new LinkedHashSet<>()).add(node);
    }

    // Method to evict the least frequently used node
    private void evict() {
        // Get the list of nodes with the minimum frequency
        LinkedHashSet<Node> nodes = freqMap.get(minFreq);
        // Remove the first node from the list
        Node node = nodes.iterator().next();
        nodes.remove(node);
        if (nodes.isEmpty()) {
            freqMap.remove(minFreq);
        }
        // Remove the node from the cache
        cache.remove(node.key);
    }

    // Example usage
    public static void main(String[] args) {
        LFUCache lfuCache = new LFUCache(2);

        lfuCache.put(1, 1);
        lfuCache.put(2, 2);
        System.out.println(lfuCache.get(1));  // Returns 1

        lfuCache.put(3, 3);  // Evicts key 2
        System.out.println(lfuCache.get(2));  // Returns -1 (not found)

        lfuCache.put(4, 4);  // Evicts key 1
        System.out.println(lfuCache.get(1));  // Returns -1 (not found)
        System.out.println(lfuCache.get(3));  // Returns 3
        System.out.println(lfuCache.get(4));  // Returns 4
    }
}
