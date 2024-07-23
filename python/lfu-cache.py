from collections import defaultdict

class LFUCache:
    def __init__(self, capacity: int):
        """
        Initialize the LFU cache with a given capacity.
        :param capacity: int - maximum number of items the cache can hold
        """
        self.capacity = capacity
        self.min_freq = 0
        self.cache = {}  # stores key and (value, frequency) pairs
        self.freq = defaultdict(list)  # stores frequency and list of keys with that frequency
        self.key_freq = {}  # stores key and its frequency

    def _update_freq(self, key):
        """
        Update the frequency of a given key.
        :param key: int - key whose frequency needs to be updated
        """
        freq = self.key_freq[key]
        self.key_freq[key] += 1
        self.freq[freq].remove(key)

        if not self.freq[freq]:
            del self.freq[freq]
            if self.min_freq == freq:
                self.min_freq += 1

        self.freq[freq + 1].append(key)

    def get(self, key: int) -> int:
        """
        Retrieve an item from the cache.
        :param key: int - key of the item to retrieve
        :return: int - value of the item if found, else -1
        """
        if key not in self.cache:
            return -1

        value, _ = self.cache[key]
        self._update_freq(key)
        return value

    def put(self, key: int, value: int) -> None:
        """
        Add or update an item in the cache.
        :param key: int - key of the item
        :param value: int - value of the item
        """
        if self.capacity == 0:
            return

        if key in self.cache:
            self.cache[key] = (value, self.key_freq[key])
            self._update_freq(key)
        else:
            if len(self.cache) >= self.capacity:
                evict_key = self.freq[self.min_freq].pop(0)
                if not self.freq[self.min_freq]:
                    del self.freq[self.min_freq]
                del self.cache[evict_key]
                del self.key_freq[evict_key]

            self.cache[key] = (value, 1)
            self.key_freq[key] = 1
            self.freq[1].append(key)
            self.min_freq = 1

# Example Usage
if __name__ == "__main__":
    lfu_cache = LFUCache(2)
    
    lfu_cache.put(1, 1)
    lfu_cache.put(2, 2)
    print(lfu_cache.get(1))  # Returns 1
    
    lfu_cache.put(3, 3)  # Evicts key 2
    print(lfu_cache.get(2))  # Returns -1 (not found)
    
    lfu_cache.put(4, 4)  # Evicts key 1
    print(lfu_cache.get(1))  # Returns -1 (not found)
    print(lfu_cache.get(3))  # Returns 3
    print(lfu_cache.get(4))  # Returns 4