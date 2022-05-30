#ifndef LIST_H
#define LIST_H
#include <iostream>
#include <initializer_list>
#include <vector>
#include <set>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <functional>
#include <type_traits>
#include "dictionary.h"
#include "set.h"

static int copied_time = 0;

template <class T>
class List
{
private:
    std::vector<T> m_vector;

    void __throw_out_of_range_error__(const std::vector<T> &vector, const int &idx) const
    {
        if (idx > vector.size() - 1)
        {
            throw std::out_of_range("List index out of bound");
        }
    }

    T &__setitem__(const int &idx)
    {

        if (idx < 0)
        {
            int negate_idx = (idx * -1);
            __throw_out_of_range_error__(m_vector, negate_idx);
            return m_vector.at(m_vector.size() - negate_idx); // list[-1] -> m_vector.back()
        }

        __throw_out_of_range_error__(m_vector, idx);

        return m_vector.at(idx);
    }
    const T &__getitem__(const int &idx) const
    {

        if (idx < 0)
        {
            int negate_idx = (idx * -1);
            __throw_out_of_range_error__(m_vector, negate_idx);
            return m_vector.at(m_vector.size() - negate_idx); // list[-1] -> m_vector.back()
        }

        __throw_out_of_range_error__(m_vector, idx);

        return m_vector.at(idx);
    }

public:
    // ----------------constructor----------------------
    List()
    {
    }
    List(const std::initializer_list<T> &init)
        : m_vector(init)
    {
    }
    List(const std::vector<T> &vector)
        : m_vector(vector)
    {
    }
    List(const std::set<T> &set)
    {
        for (const T &value : set)
        {
            m_vector.push_back(value);
        }
    }
    // -------------------------------------------------

    List<T> copy() const
    {

        List<T> copy_list(m_vector);

        return copy_list;
    }
    void clear()
    {
        m_vector.clear();
    }

    void append(const T &value)
    {

        m_vector.push_back(value);
    }

    void extend(const List<T> &_other_list)
    {

        for (const T &value : _other_list.values())
        {
            m_vector.push_back(value);
        }
    }

    void insert(const int &index, const T &value)
    {
        m_vector.insert(m_vector.begin() + index, value);
    }

    void remove_value_along_with_duplicates(const T &value)
    {
        bool is_value_exist = false;
        int value_count = this->count(value);

        while (value_count != 0)
        {
            for (int idx = 0; idx <= m_vector.size() - 1; idx++)
            {
                if (m_vector.at(idx) == value)
                {
                    is_value_exist = true;
                    m_vector.erase(m_vector.begin() + idx);
                    value_count -= 1;
                    break;
                }
            }
        }

        if (!is_value_exist)
        {
            throw std::invalid_argument("value not in list");
        }
    }

    void remove(const T &value)
    {
        bool is_value_exist = false;

        for (int idx = 0; idx <= m_vector.size() - 1; idx++)
        {
            if (m_vector.at(idx) == value)
            {
                is_value_exist = true;
                m_vector.erase(m_vector.begin() + idx);
                return; // only removes the first matching value.
            }
        }

        if (!is_value_exist)
        {
            throw std::invalid_argument("value not in list");
        }
    }

    int index(const T &searched_value, int start = -1, int end = -1) const
    {

        if (start == -1)
        {
            start = 0;
        }
        if (end == -1)
        {
            end = m_vector.size() - 1;
        }

        for (int idx = start; idx <= end; idx++)
        {
            if (m_vector.at(idx) == searched_value)
            {
                return idx;
            }
        }

        throw std::invalid_argument("value not found");
    }

    T pop(int idx = -1)
    {
        if (idx == -1)
        {
            T popped_value = m_vector.at(m_vector.size() - 1);
            m_vector.erase(m_vector.end() - 1);
            return popped_value;
        }

        T popped_value = m_vector.at(idx);
        m_vector.erase(m_vector.begin() + idx);
        return popped_value;
    }

    List<T> slice(const int &begin_idx = -1, int end_idx = -1) const
    {
        // e.g. [1,2,3,4,5].slice() -> [1,2,3,4,5]
        // e.g. [1,2,3,4,5].slice(1, 4) -> [2,3,4]
        if (begin_idx == -1 && end_idx == -1)
        {
            return this->copy();
        }

        if (end_idx == -1)
        {
            end_idx = m_vector.size();
        }
        std::vector<T> sliced_vector;
        for (int idx = begin_idx; idx < end_idx; idx++)
        {
            sliced_vector.push_back(m_vector.at(idx));
        }

        List<T> sliced_list(sliced_vector);

        return sliced_list;
    }
    List<std::string> map_to_string()
    {
        static_assert(std::is_arithmetic_v<T>, "Integral or floating types required");
        List<std::string> string_list;
        for (const auto &value : m_vector)
        {

            string_list.append(std::to_string(value));
        }

        return string_list;
    }

    std::string join(const std::string &delimeter) const
    {
        static_assert(std::is_arithmetic_v<T>, "Integral or floating types required");
        std::string repr_ = "";
        std::string joined_string;
        int idx = 0;
        for (const auto &value : m_vector)
        {
            if (idx == m_vector.size() - 1)
            {
                continue;
            }
            idx += 1;

            joined_string = std::to_string(value) + delimeter;

            repr_ += joined_string;
        }

        return repr_;
    }

    int length() const
    {
        return m_vector.size();
    }

    bool is_contains(const T &value) const
    {
        return (std::find(m_vector.begin(), m_vector.end(), value) != m_vector.end());
    }

    void sort()
    {
        std::sort(m_vector.begin(), m_vector.end());
    }
    void sort(const std::function<bool(const T &list_x, const T &list_y)> &compare_func)
    {
        std::sort(m_vector.begin(), m_vector.end(), compare_func);
    }

    void reverse()
    {
        std::reverse(m_vector.begin(), m_vector.end());
    }

    int count(const T &value) const
    {
        long int count = 0;
        for (const T &val : m_vector)
        {
            if (val == value)
            {
                count += 1;
            }
        }

        return count;
    }
    bool is_all(const T &checked_value)
    {
        int count = 0;
        for (const T &value : m_vector)
        {
            if (value == checked_value)
            {
                count += 1;
            }
        }

        return (count == m_vector.size());
    }

    T &operator[](const int &idx) // setter
    {

        return this->__setitem__(idx);
    }
    const T &operator[](const int &idx) const
    {

        return this->__getitem__(idx);
    }
    List<T> operator+(const List<T> &_other_list) const
    {
        List<T> copy_list = this->copy();
        copy_list.extend(_other_list);

        return copy_list;
    }

    bool operator==(const List<T> &_other_list) const
    {
        if (m_vector.size() != _other_list.m_vector.size())
        {
            return false;
        }

        for (int idx = 0; idx <= m_vector.size() - 1; idx++)
        {
            if (m_vector.at(idx) != _other_list.m_vector.at(idx))
            {
                return false;
            }
        }
        return true;
    }

    std::vector<T> &values() // for iteration
    {
        return m_vector;
    }
    const std::vector<T> &values() const // for const value iteration
    {
        return m_vector;
    }
    friend std::ostream &operator<<(std::ostream &stream, const List &list)
    {

        stream << "[ ";
        int idx = 0;
        for (const auto &value : list.m_vector)
        {
            stream << " " << value;
            if (idx == list.length() - 1)
            {
                continue;
            }
            stream << ", ";
            idx += 1;
        }

        stream << " ]";
        return stream;
    }
};

#endif