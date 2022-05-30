#include <iostream>
#include "cart.h"
#include "product.h"
#include "PyDataType/list.h"
#include "PyDataType/dictionary.h"
#include "genetic_algorithm.h"
using std::cout;
using std::endl;

int main()
{
    // GeneticAlgorithm(int population_size, double mutation_prob, int number_of_generation, List<Product> available_products)
    List<Product> products = Product::get_all_products();

    GeneticAlgorithm ga(300, 0.01, 500, products, 2.5);
    ga.solve();

    std::cout << ga.m_global_best_solution << std::endl;
}