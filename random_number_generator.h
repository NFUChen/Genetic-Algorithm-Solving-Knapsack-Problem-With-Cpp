#pragma once
#include <random>
// Construct a global Mersenne Twister to re-use
// Use a temporary random_device to generate a single seed
static std::mt19937 mersenneEngine(std::random_device{}());

template <typename IntType>
IntType uniform_random_int(IntType a, IntType b)
{
    std::uniform_int_distribution<IntType> dist(a, b);
    return dist(mersenneEngine);
}

template <typename T>
T uniform_random(T lowerbound, T upperbound)
{
    std::uniform_real_distribution<T> dist(lowerbound, upperbound);
    return dist(mersenneEngine);
}
