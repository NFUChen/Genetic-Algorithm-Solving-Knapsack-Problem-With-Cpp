#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <stdexcept>
#include <initializer_list>

template <class K, class V>
class Dict
{
private:
    std::unordered_map<K, V> m_map;
    std::vector<K> m_key_vecotr;
    std::vector<V> m_value_vecotr;

    void __raise_key_not_exist_error__(const K &key) const
    {
        if (!m_map.count(key))
        {
            throw std::invalid_argument("Key not in Dict");
        }
    }

public:
    // ----------------constructor----------------------
    Dict()
    {
    }
    Dict(const std::initializer_list<std::pair<const K, V> > &init)
        : m_map(init)
    {
    }
    Dict(const std::unordered_map<K, V> &map)
    {
        m_map = map;
    }
    // -------------------------------------------------

    bool is_contains(const K &key) const
    {
        return (m_map.count(key));
    }

    int size() const
    {
        return m_map.size();
    }

    void clear()
    {
        m_map.clear();
    }

    Dict<K, V> copy() const
    {
        Dict<K, V> copy_dict(m_map);

        return copy_dict;
    }

    V pop(const K &key)
    {

        __raise_key_not_exist_error__(key);

        V popped_value = m_map[key];
        m_map.erase(key);

        return popped_value;
    }
    V pop(const K &key, const V &default_value)
    {

        if (!m_map.count(key))
        {
            return default_value;
        }
    }

    void update(const Dict<K, V> &_other_dict)
    {
        for (const auto &[key, value] : _other_dict.items())
        {
            m_map[key] = value;
        }
    }

    V setdefault(const K &key)
    {
        // The setdefault() method returns the value of the item with the specified key.
        // If the key does not exist, insert the key, with the specified value
        return m_map[key];
    }
    V setdefault(const K &key, const V &default_value)
    {
        // The setdefault() method returns the value of the item with the specified key.
        // If the key does not exist, insert the key, with the specified value
        if (!m_map.count(key))
        {
            m_map[key] = default_value;
            return default_value;
        }

        return default_value;
    }

    void set(const K &key, const V &value)
    {
        m_map[key] = value;
    }
    V &get(const K &key) // setter
    {
        __raise_key_not_exist_error__(key);
        return m_map[key];
    }
    const V &get(const K &key) const
    {
        __raise_key_not_exist_error__(key);
        return m_map[key];
    }

    V &operator[](const K &key)
    // setter and getter, only with key that is non-exist, may result in undefined behaviour e.g., dict[non_existent_key]
    {
        return m_map[key];
    }

    const V &operator[](const K &key) const
    // setter and getter, only with key that is non-exist, may result in undefined behaviour e.g., dict[non_existent_key]
    {
        return m_map.at(key);
    }

    bool operator==(const Dict<K, V> &_other_dict) const
    {
        if (m_map.size() != _other_dict.m_map.size())
        {
            return false;
        }

        for (const auto &[key, value] : _other_dict.items())
        {
            if (!(m_map[key] == value))
            {
                return false;
            }

            if (!(m_map.count(key)))
            {
                return false;
            }
        }
        return true;
    }
    std::vector<V> values() const // for iteration
    {
        std::vector<V> value_vector;
        for (const auto &[_, value] : m_map)
        {
            value_vector.push_back(value);
        }

        return value_vector;
    }

    std::vector<K> keys() const // for iteration
    {
        std::vector<K> key_vector;
        for (const auto &[key, _] : m_map)
        {
            key_vector.push_back(key);
        }

        return key_vector;
    }

    const std::unordered_map<K, V> &items() const // for iteration
    {
        return m_map;
    }

    friend std::ostream &operator<<(std::ostream &stream, const Dict<K, V> &dict)
    {
        stream << "{";
        int idx = 0;
        for (const auto &[key, value] : dict.m_map)
        {
            stream << key << " : " << value;
            if (idx == dict.size() - 1)
            {
                continue;
            }
            idx += 1;

            stream << ", ";
        }

        stream << "}";

        return stream;
    }
};

#endif