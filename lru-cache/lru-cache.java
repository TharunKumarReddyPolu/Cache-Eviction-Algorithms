import java.util.LinkedHashMap;
import java.util.Map;

public class LRUCache<K, V> {
    private final int capacity;
    private final LinkedHashMap<K, V> cache;

    // Constructor to initialize the LRU cache with a given capacity
    public LRUCache(int capacity) {
        this.capacity = capacity;

        // Create a LinkedHashMap with access order
        this.cache = new LinkedHashMap<K, V>(capacity, 0.75f, true) {
            // Override removeEldestEntry to evict the least recently used entry
            @Override
            protected boolean removeEldestEntry(Map.Entry<K, V> eldest) {
                return size() > capacity;
            }
        };
    }

    // Retrieve an item from the cache
    public V get(K key) {
        return cache.getOrDefault(key, null);
    }

    // Add or update an item in the cache
    public void put(K key, V value) {
        cache.put(key, value);
    }

    // For debugging: Print the contents of the cache
    public void printCache() {
        System.out.println(cache);
    }

    public static void main(String[] args) {
        LRUCache<Integer, String> lruCache = new LRUCache<>(2);

        lruCache.put(1, "one");
        lruCache.put(2, "two");
        System.out.println(lruCache.get(1));  // Returns "one"
        lruCache.put(3, "three");             // Evicts key 2
        System.out.println(lruCache.get(2));  // Returns null (not found)
        lruCache.put(4, "four");              // Evicts key 1
        System.out.println(lruCache.get(1));  // Returns null (not found)
        System.out.println(lruCache.get(3));  // Returns "three"
        System.out.println(lruCache.get(4));  // Returns "four"

        lruCache.printCache();  // For debugging: Shows the current state of the cache
    }
}