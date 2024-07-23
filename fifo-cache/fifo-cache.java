import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map;
import java.util.Queue;

public class FIFOCache<K, V> {
    private final int capacity; // Maximum capacity of the cache
    private final Map<K, V> cacheMap; // HashMap to store key-value pairs
    private final Queue<K> orderQueue; // Queue to maintain the order of insertion

    public FIFOCache(int capacity) {
        this.capacity = capacity;
        this.cacheMap = new HashMap<>();
        this.orderQueue = new LinkedList<>();
    }

    public V get(K key) {
        // Retrieve the value from the cache
        return cacheMap.get(key);
    }

    public void put(K key, V value) {
        if (cacheMap.size() >= capacity) {
            // Evict the oldest item (first inserted item) if the cache is full
            K oldestKey = orderQueue.poll();
            if (oldestKey != null) {
                cacheMap.remove(oldestKey);
            }
        }
        // Add the new key-value pair to the cache
        cacheMap.put(key, value);
        // Add the key to the order queue
        orderQueue.offer(key);
    }

    public static void main(String[] args) {
        FIFOCache<Integer, String> fifoCache = new FIFOCache<>(2);
        
        fifoCache.put(1, "one");
        fifoCache.put(2, "two");
        System.out.println(fifoCache.get(1));  // Output: one
        
        fifoCache.put(3, "three");  // Evicts key 1
        System.out.println(fifoCache.get(1));  // Output: null
        System.out.println(fifoCache.get(2));  // Output: two
        
        fifoCache.put(4, "four");  // Evicts key 2
        System.out.println(fifoCache.get(2));  // Output: null
        System.out.println(fifoCache.get(3));  // Output: three
        System.out.println(fifoCache.get(4));  // Output: four
    }
}