#pragma once

#include <functional>

template<typename K, typename V>
class Entry
{
private:
	size_t m_hashCode;

	K m_key;
	V m_value;

	Entry<K, V>* m_next;
public:
	Entry(const K& key, const V& value) : m_key(key), m_value(value), m_next(nullptr)
	{
		std::hash<K> hasher;
		m_hashCode = hasher(key);
	}

	inline size_t GetHashCode() { return m_hashCode; }

	inline const K& GetKey()   { return m_key;   }
	inline       V& GetValue() { return m_value; }

	inline Entry<K, V>* GetNext() { return m_next; }

	inline void SetValue(const V& value) { m_value = value; }

	inline void SetNext(Entry<K, V>* next) { m_next = next; }
};

template<typename K, typename V>
class KeyCollection;

template<typename K, typename V>
class ValueCollection;

template<typename K, typename V>
class EntryCollection;

template<typename K, typename V>
class HashMap
{
private:
	Entry<K, V>** m_buckets;
	size_t        m_capacity;
	size_t        m_count;

	float  m_loadFactor;
	size_t m_maxCount;

	bool         PlaceInBucket(Entry<K, V>** bucket, const K& key, const V& value);
	Entry<K, V>* GetFromBucket(Entry<K, V>** bucket, const K& key);
	bool         RemoveFromBucket(Entry<K, V>** bucket, const K& key);

	Entry<K, V>** GetBucket(const K& key);

	void Reallocate();
public:
	HashMap(size_t initialCapacity = 16, float loadFactor = 0.75f) : 
		m_buckets(new Entry<K, V>*[initialCapacity]), 
		m_capacity(initialCapacity), 
		m_count(0),
		m_loadFactor(loadFactor),
		m_maxCount(loadFactor * initialCapacity) 
	{
		for(size_t i = 0; i < m_capacity; i++)
			m_buckets[i] = nullptr;
	}

	~HashMap()
	{
		Clear();
		delete[] m_buckets;
	}

	inline size_t Count() { return m_count; }

	V& operator[](const K& key);

	bool Place(const K& key, const V& value);
	bool Remove(const K& key);

	void Clear();

	KeyCollection<K, V>   GetKeys();
	ValueCollection<K, V> GetValues();

	EntryCollection<K, V> GetEntries();
};

template<typename K, typename V>
class HashIterator
{
private:
	Entry<K, V>** m_buckets;
	size_t        m_capacity;

	size_t       m_bucketIndex;
	Entry<K, V>* m_currEntry;
public:
	HashIterator() : m_currEntry(nullptr), m_bucketIndex(0) {}

	HashIterator(Entry<K, V>** buckets, size_t capacity) : m_buckets(buckets), m_capacity(capacity) 
	{
		m_bucketIndex = 0;
		m_currEntry   = m_buckets[m_bucketIndex];
		while(m_currEntry == nullptr)
		{
			m_bucketIndex++;
			if(m_bucketIndex >= m_capacity)
				break;

			m_currEntry = m_buckets[m_bucketIndex];
		}
	}

	HashIterator& operator++()
	{
		m_currEntry = m_currEntry->GetNext();
		while(m_currEntry == nullptr)
		{
			m_bucketIndex++;
			if(m_bucketIndex >= m_capacity)
				break;

			m_currEntry = m_buckets[m_bucketIndex];
		}

		return *this;
	}

	Entry<K, V>* GetCurrentEntry() { return m_currEntry; }

	HashIterator& operator++(int)
	{
		HashIterator result = *this;
		++(*this);
		return result;
	}

	bool operator==(const HashIterator& other)
	{
		return m_currEntry == other.m_currEntry;
	}

	bool operator!=(const HashIterator& other)
	{
		return !(*this == other);
	}
};

template<typename K, typename V>
class KeyIterator : public HashIterator<K, V>
{
public:
	KeyIterator()                                       : HashIterator<K, V>()                  {}
	KeyIterator(Entry<K, V>** buckets, size_t capacity) : HashIterator<K, V>(buckets, capacity) {}

	K* operator->()
	{
		Entry<K, V>* currEntry = GetCurrentEntry();
		return &currEntry->GetKey();
	}

	const K& operator*()
	{
		Entry<K, V>* currEntry = GetCurrentEntry();
		return currEntry->GetKey();
	}
};

template<typename K, typename V>
class ValueIterator : public HashIterator<K, V>
{
public:
	ValueIterator() : HashIterator<K, V>() {}
	ValueIterator(Entry<K, V>** buckets, size_t capacity) : HashIterator<K, V>(buckets, capacity) {}

	V* operator->()
	{
		Entry<K, V>* currEntry = GetCurrentEntry();
		return &currEntry->GetValue();
	}

	V& operator*()
	{
		Entry<K, V>* currEntry = GetCurrentEntry();
		return currEntry->GetValue();
	}
};

template<typename K, typename V>
class EntryIterator : public HashIterator<K, V>
{
public:
	EntryIterator() : HashIterator<K, V>() {}
	EntryIterator(Entry<K, V>** buckets, size_t capacity) : HashIterator<K, V>(buckets, capacity) {}

	Entry<K, V>* operator->()
	{
		Entry<K, V>* currEntry = GetCurrentEntry();
		return currEntry;
	}

	Entry<K, V>& operator*()
	{
		Entry<K, V>* currEntry = GetCurrentEntry();
		return *currEntry;
	}
};

template<typename K, typename V>
class KeyCollection
{
private:
	Entry<K, V>** m_buckets;
	size_t        m_capacity;
public:
	KeyCollection(Entry<K, V>** buckets, size_t capacity) : m_buckets(buckets), m_capacity(capacity) {}

	KeyIterator<K, V> begin() { return KeyIterator<K, V>(m_buckets, m_capacity); }
	KeyIterator<K, V> end()   { return KeyIterator<K, V>();                      }
};

template<typename K, typename V>
class ValueCollection
{
private:
	Entry<K, V>** m_buckets;
	size_t        m_capacity;
public:
	ValueCollection(Entry<K, V>** buckets, size_t capacity) : m_buckets(buckets), m_capacity(capacity) {}

	ValueIterator<K, V> begin() { return ValueIterator<K, V>(m_buckets, m_capacity); }
	ValueIterator<K, V> end()   { return ValueIterator<K, V>();                      }
};

template<typename K, typename V>
class EntryCollection
{
private:
	Entry<K, V>** m_buckets;
	size_t        m_capacity;
public:
	EntryCollection(Entry<K, V>** buckets, size_t capacity) : m_buckets(buckets), m_capacity(capacity) {}

	EntryIterator<K, V> begin() { return EntryIterator<K, V>(m_buckets, m_capacity); }
	EntryIterator<K, V> end()   { return EntryIterator<K, V>();                      }
};

template<typename K, typename V>
KeyCollection<K, V> HashMap<K, V>::GetKeys()
{
	return KeyCollection<K, V>(m_buckets, m_capacity);
}

template<typename K, typename V>
ValueCollection<K, V> HashMap<K, V>::GetValues()
{
	return ValueCollection<K, V>(m_buckets, m_capacity);
}

template<typename K, typename V>
EntryCollection<K, V> HashMap<K, V>::GetEntries()
{
	return EntryCollection<K, V>(m_buckets, m_capacity);
}

template<typename K, typename V>
bool HashMap<K, V>::PlaceInBucket(Entry<K, V>** bucket, const K& key, const V& value)
{
	Entry<K, V>* lastEntry = nullptr;
	Entry<K, V>* currEntry = *bucket;

	std::hash<K> hasher;
	size_t keyHash = hasher(key);

	while(currEntry != nullptr)
	{
		if(currEntry->GetHashCode() == keyHash)
		{ 
			if(currEntry->GetKey() == key)
			{
				currEntry->SetValue(value);
				return true;
			}
		}
		lastEntry = currEntry;
		currEntry = currEntry->GetNext();
	}

	Entry<K, V>* newEntry = new Entry<K, V>(key, value);
	if(lastEntry == nullptr)
		*bucket = newEntry;
	else
		lastEntry->SetNext(newEntry);
	
	m_count++;

	if(m_count > m_maxCount)
		Reallocate();

	return false;
}

template<typename K, typename V>
Entry<K, V>* HashMap<K, V>::GetFromBucket(Entry<K, V>** bucket, const K& key)
{
	Entry<K, V>* currEntry = *bucket;

	std::hash<K> hasher;
	size_t keyHash = hasher(key);

	while(currEntry != nullptr)
	{
		if(currEntry->GetHashCode() == keyHash)
		{
			if(currEntry->GetKey() == key)
				return currEntry;
		}
		currEntry = currEntry->GetNext();
	}

	return nullptr;
}

template<typename K, typename V>
bool HashMap<K, V>::RemoveFromBucket(Entry<K, V>** bucket, const K& key)
{
	Entry<K, V>* lastEntry = nullptr;
	Entry<K, V>* currEntry = *bucket;

	std::hash<K> hasher;
	size_t keyHash = hasher(key);

	while(currEntry != nullptr)
	{
		if(currEntry->GetHashCode() == keyHash)
		{
			if(currEntry->GetKey() == key)
			{
				if(lastEntry == nullptr)
					*bucket = currEntry->GetNext();
				else
					lastEntry->SetNext(currEntry->GetNext());

				delete currEntry;
				m_count--;
				return true;
			}
		}
		lastEntry = currEntry;
		currEntry = currEntry->GetNext();
	}

	return false;
}

template<typename K, typename V>
Entry<K, V>** HashMap<K, V>::GetBucket(const K& key)
{
	std::hash<K> hasher;
	size_t keyHash = hasher(key);
	size_t index   = keyHash % m_capacity;
	return &m_buckets[index];
}

template<typename K, typename V>
void HashMap<K, V>::Reallocate()
{
	Entry<K, V>** newBuckets = new Entry<K, V>*[m_capacity * 2];

	for(size_t i = 0; i < m_capacity * 2; i++)
		newBuckets[i] = nullptr;

	Entry<K, V>** oldBuckets = m_buckets;
	m_buckets = newBuckets;
	m_capacity *= 2;
	m_maxCount = m_loadFactor * m_capacity;
	m_count = 0;
	for(size_t i = 0; i < m_capacity / 2; i++)
	{
		Entry<K, V>* currEntry = oldBuckets[i];
		while(currEntry != nullptr)
		{
			Entry<K, V>* entryToDelete = currEntry;
			PlaceInBucket(GetBucket(currEntry->GetKey()), currEntry->GetKey(), currEntry->GetValue());
			currEntry = currEntry->GetNext();
			delete entryToDelete;
		}
	}

	delete[] oldBuckets;
}

template<typename K, typename V>
bool HashMap<K, V>::Place(const K& key, const V& value)
{
	return PlaceInBucket(GetBucket(key), key, value);
}

template<typename K, typename V>
bool HashMap<K, V>::Remove(const K& key)
{
	return RemoveFromBucket(GetBucket(key), key);
}

template<typename K, typename V>
V& HashMap<K, V>::operator[](const K& key)
{
	Entry<K, V>* foundEntry = GetFromBucket(GetBucket(key), key);
	if(foundEntry == nullptr)
	{
		V value;
		PlaceInBucket(GetBucket(key), key, value);
		foundEntry = GetFromBucket(GetBucket(key), key);
	}
	return foundEntry->GetValue();
}

template<typename K, typename V>
void HashMap<K, V>::Clear()
{
	for(size_t i = 0; i < m_capacity; i++)
	{
		Entry<K, V>* currEntry = m_buckets[i];
		while(currEntry != nullptr)
		{
			Entry<K, V>* entryToDelete = currEntry;
			currEntry = currEntry->GetNext();
			delete entryToDelete;
		}
		m_buckets[i] = nullptr;
	}
	m_count = 0;
}