#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <set>

template <typename T>
std::ostream &operator<<(std::ostream &stream, const std::vector<T> &vector)
{
    stream << "[";

    for (const auto &val : vector)
    {

        stream << val << ", ";
    }

    stream << "]";

    return stream;
}

template <typename K, typename V>
std::ostream &operator<<(std::ostream &stream, const std::map<K, V> &map)
{
    stream << "{";

    for (const auto &[key, value] : map)
    {

        stream << key << " : " << value << ", ";
    }

    stream << "}";

    return stream;
}

template <typename T>
std::ostream &operator<<(std::ostream &stream, const std::set<T> &set)
{
    stream << "{";

    for (const auto &value : set)
    {

        stream << value << ", ";
    }

    stream << "}";

    return stream;
}
