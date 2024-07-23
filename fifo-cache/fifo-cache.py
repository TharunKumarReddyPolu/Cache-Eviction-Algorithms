from collections import deque, defaultdict

class FIFOCache:
    def __init__(self, capacity: int):
        """
        Initialize the FIFO cache with a given capacity.
        :param capacity: int - maximum number of items the cache can hold
        """
        self.cache = {}
        self.capacity = capacity
        self.order = deque()

    def get(self, key: int) -> int:
        """
        Retrieve an item from the cache.
        :param key: int - key of the item to retrieve
        :return: int - value of the item if found, else -1
        """
        return self.cache.get(key, -1)

    def put(self, key: int, value: int) -> None:
        """
        Add or update an item in the cache.
        :param key: int - key of the item
        :param value: int - value of the item
        """
        if key not in self.cache:
            if len(self.cache) >= self.capacity:
                # Remove the oldest item from the cache
                oldest_key = self.order.popleft()
                del self.cache[oldest_key]
            # Add the new item to the cache
            self.cache[key] = value
            self.order.append(key)
        else:
            # Update the value if the key already exists in the cache
            self.cache[key] = value

# Example Usage
if __name__ == "__main__":
    fifo_cache = FIFOCache(2)
    
    fifo_cache.put(1, 1)
    fifo_cache.put(2, 2)
    print(fifo_cache.get(1))  # Returns 1
    
    fifo_cache.put(3, 3)  # Evicts key 1
    print(fifo_cache.get(1))  # Returns -1 (not found)
    print(fifo_cache.get(2))  # Returns 2
    print(fifo_cache.get(3))  # Returns 3
    
    fifo_cache.put(4, 4)  # Evicts key 2
    print(fifo_cache.get(2))  # Returns -1 (not found)
    print(fifo_cache.get(3))  # Returns 3
    print(fifo_cache.get(4))  # Returns 4
