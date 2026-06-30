#pragma once

#include <vector>
#include <functional>
#include "ListaDoble.h"
#include "HashNode.h"

template<typename K, typename V>
class HashTable {

public:

    using HashFunction =
        std::function<size_t(const K&)>;

    using EqualFunction =
        std::function<bool(
            const K&,
            const K&
        )>;

private:

    std::vector<ListaDoble<HashNode<K,V>>> buckets;

    size_t capacity;

    size_t currentSize;

    HashFunction hashFunction;

    EqualFunction equalFunction;

public:

    HashTable(
        size_t cap = 101
    );

    bool insert(
        const K&,
        const V&
    );

    bool remove(
        const K&
    );

    V get(
        const K&
    ) const;

    bool contains(
        const K&
    ) const;

    void clear();

    size_t size() const;

    bool empty() const;

};

template<typename K, typename V>
HashTable<K,V>::HashTable(size_t cap)
    :
    buckets(cap),
    capacity(cap),
    currentSize(0)
{

    hashFunction =
        [this](const K& key)
    {
        return std::hash<K>{}(key)
            % capacity;
    };

    equalFunction =
        [](const K& a,
           const K& b)
    {
        return a == b;
    };

}

template<typename K, typename V>
bool HashTable<K,V>::insert(
    const K& key,
    const V& value
)
{
    size_t index =
        hashFunction(key);

    auto& bucket =
        buckets[index];

    auto node =
        bucket.getHead();

    while(node)
    {
        if(equalFunction(
            node->data.key,
            key))
        {
            node->data.value = value;
            return false;
        }

        node = node->next;
    }

    bucket.push_back(
        HashNode<K,V>(
            key,
            value
        )
    );

    currentSize++;

    return true;
}

template<typename K, typename V>
V HashTable<K,V>::get(
    const K& key
) const
{
    size_t index =
        hashFunction(key);

    auto node =
        buckets[index].getHead();

    while(node)
    {
        if(equalFunction(
            node->data.key,
            key))
        {
            return node->data.value;
        }

        node=node->next;
    }

    return nullptr;
}

template<typename K, typename V>
bool HashTable<K,V>::contains(
    const K& key
) const
{
    return get(key)!=nullptr;
}

template<typename K, typename V>
bool HashTable<K, V>::remove(const K& key)
{
    size_t index = hashFunction(key);

    auto& bucket = buckets[index];

    auto node = bucket.getHead();

    while (node)
    {
        if (equalFunction(node->dato.key, key))
        {
            if (node->prev)
                node->prev->next = node->next;
            else
                bucket.getHeadRef() = node->next;

            if (node->next)
                node->next->prev = node->prev;

            delete node;

            currentSize--;

            return true;
        }

        node = node->next;
    }

    return false;
}