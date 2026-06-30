#pragma once

template<typename K, typename V>
struct HashNode {

    K key;
    V value;

    HashNode(
        const K& k,
        const V& v
    )
        : key(k),
          value(v)
    {
    }

};