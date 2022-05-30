#ifndef SET_H
#define SET_H

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <initializer_list>
#include "list.h"
template <class T>
class Set
{
private:
  std::set<T> m_set;

public:
  // ----------------constructor----------------------
  Set()
  {
  }

  Set(const std::vector<T> &vector)
  {
    for (const T &value : vector)
    {
      m_set.insert(value);
    }
  }
  Set(const std::set<T> &set)
      : m_set(set)
  {
  }
  Set(const std::initializer_list<T> &init)
      : m_set(init)
  {
  }
  // -------------------------------------------------

  int size() const
  {

    return m_set.size();
  }
  Set<T> copy() const
  {
    Set<T> copy_set(m_set);

    return copy_set;
  }

  bool is_contains(const T &value) const
  {
    return (m_set.find(value) != m_set.end());
  }

  void add(const T &value)
  {
    m_set.insert(value);
  }

  void remove(const T &value)
  {
    if (!this->is_contains(value)) // not found
    {
      std::string error_msg = std::to_string(value) + " not in set";
      throw std::invalid_argument(error_msg);
    }

    m_set.erase(value);
  }

  void discard(const T &value)
  {
    m_set.erase(value);
  }

  void clear()
  {
    m_set.clear();
  }

  void update(const Set<T> &_other_set)
  // The update() method updates the current set, by adding items from another set (or any other iterable).
  // If an item is present in both sets,
  // only one appearance of this item will be present in the updated set.
  {
    for (const T &value : _other_set)
    {
      m_set.insert(value);
    }
  }

  Set<T> union_with(const Set<T> &_other_set) const
  {
    Set<T> union_set;
    for (const T &value : m_set)
    {
      union_set.add(value);
    }
    for (const T &value : _other_set.values())
    {
      union_set.add(value);
    }
    return union_set;
  }

  Set<T> difference_with(const Set<T> &_other_set) const
  {
    Set<T> difference_set(m_set);
    for (const T &value : _other_set.values())
    {
      if (difference_set.is_contains(value)) // if find
      {
        difference_set.remove(value);
      }
    }

    return difference_set;
  }
  Set<T> intersection_with(const Set<T> &_other_set) const
  {
    Set<T> intersection_set;
    for (const T &self_value : m_set)
    {
      if (_other_set.is_contains(self_value))
      {
        intersection_set.add(self_value);
      }
    }

    return intersection_set;
  }

  std::set<T> &values() // for iteration
  {
    return m_set;
  }
  const std::set<T> &values() const // for const value iteration
  {
    return m_set;
  }

  friend std::ostream &operator<<(std::ostream &stream, const Set<T> &set)
  {
    stream << "{";

    for (const T &value : set.m_set)
    {

      stream << value << ", ";
    }

    stream << "}";

    return stream;
  }
};

#endif