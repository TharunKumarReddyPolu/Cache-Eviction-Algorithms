from collections import OrderedDict

class LRUCache:
    def __init__(self, capacity: int):
        """
        Initialize the LRU cache with a given capacity.
        :param capacity: int - maximum number of items the cache can hold
        """
        self.cache = OrderedDict()  # Use OrderedDict to maintain the order of items
        self.capacity = capacity    # Set the maximum capacity of the cache

    def get(self, key: int) -> int:
        """
        Retrieve an item from the cache.
        :param key: int - key of the item to retrieve
        :return: int - value of the item if found, else -1
        """
        if key not in self.cache:
            # If the key is not in the cache, return -1
            return -1
        else:
            # If the key is in the cache, move it to the end to show that it was recently used
            self.cache.move_to_end(key) # move_to_end() is an inbuilt function in OrderedDict
            # Return the value associated with the key
            return self.cache[key]

    def put(self, key: int, value: int) -> None:
        """
        Add or update an item in the cache.
        :param key: int - key of the item
        :param value: int - value of the item
        """
        if key in self.cache:
            # If the key is already in the cache, move it to the end to show that it was recently used
            self.cache.move_to_end(key)
        # Insert or update the key-value pair in the cache
        self.cache[key] = value
        if len(self.cache) > self.capacity:
            # If the cache exceeds its capacity, remove the first item (the least recently used item)
            self.cache.popitem(last=False)

if __name__ == "__main__":
    # Create an LRUCache with capacity 2
    lru_cache = LRUCache(2)
    
    # Add some items to the cache
    lru_cache.put(1, 1)
    lru_cache.put(2, 2)
    
    # Retrieve item with key 1 (should return 1)
    print(lru_cache.get(1))  # Output: 1
    
    # Add another item to the cache, causing the cache to evict the least recently used item (key 2)
    lru_cache.put(3, 3)  # Evicts key 2
    
    # Attempt to retrieve item with key 2 (should return -1 as it was evicted)
    print(lru_cache.get(2))  # Output: -1
    
    # Add another item to the cache, causing the cache to evict the least recently used item (key 1)
    lru_cache.put(4, 4)  # Evicts key 1
    
    # Attempt to retrieve item with key 1 (should return -1 as it was evicted)
    print(lru_cache.get(1))  # Output: -1
    
    # Retrieve item with key 3 (should return 3)
    print(lru_cache.get(3))  # Output: 3
    
    # Retrieve item with key 4 (should return 4)
    print(lru_cache.get(4))  # Output: 4
