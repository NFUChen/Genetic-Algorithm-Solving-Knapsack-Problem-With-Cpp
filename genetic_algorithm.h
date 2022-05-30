#ifndef GENETICALGORITHM_H
#define GENETICALGORITHM_H
#include <iostream>
#include <cmath>
#include "PyDataType/list.h"
#include "product.h"
#include "cart.h"

template <typename T>
T &choose_max(T &x, T &y)
{
    if (x > y)
        return x;

    return y;
}

class GeneticAlgorithm
{
private:
    void intialize_population()
    {
        while (m_current_population.length() < m_population_size)
        {
            Cart one_solution = Cart(m_available_products, m_space_limit);
            m_current_population.append(one_solution);
        }
        m_current_population.sort();
        m_current_best_solution = m_current_population[-1];
        m_global_best_solution = m_current_best_solution;
    }

    double get_total_fitness_of_population()
    {
        double total_fitness = 0;
        for (const Cart &cart : m_current_population.values())
        {
            total_fitness += cart.fitness();
        }
        return total_fitness;
    }

    Cart select_a_parent()
    {
        double total_fitness = get_total_fitness_of_population();

        if (total_fitness == 0)
        {
            Cart random_parent = randomly_select_a_parent();
            return random_parent;
        }

        double random_val = uniform_random<double>(0, 1);
        double check_sum = 0;
        int selected_idx = 0;
        while (check_sum < (random_val * total_fitness) && selected_idx <= (m_population_size - 1))
        {
            check_sum += m_current_population[selected_idx].fitness();
            selected_idx += 1;
        }

        return m_current_population[selected_idx - 1];
    }
    Cart randomly_select_a_parent()
    {
        int random_idx = floor(uniform_random<double>(0, 1) * m_current_population.length());

        return m_current_population[random_idx];
    }

    List<Cart> crossover_two_parents()
    {
        Cart parent_x = select_a_parent();
        Cart parent_y = select_a_parent();

        List<Cart> children = parent_x.crossover(parent_y);

        return children;
    }

    List<Cart> mutate_two_children(List<Cart> children)
    {
        for (Cart &cart : children.values())
        {
            cart.mutate(m_mutation_prob);
        }

        return children;
    }
    void update_population_info(List<Cart> &new_population)
    {
        m_current_population = new_population;
        m_current_population.sort();
        m_current_best_solution = m_current_population[-1];
        m_global_best_solution = choose_max(m_global_best_solution, m_current_best_solution);
    }

    void visualize_current_generation()
    {
        std::cout << "Generation: " << m_current_generation << "\n"
                  << m_current_population << "\n"
                  << "Best Solution: "
                  << "\n"
                  << m_current_best_solution << "\n";
    }

public:
    int m_population_size;
    double m_mutation_prob;
    int m_number_of_generation;
    List<Product> m_available_products;
    double m_space_limit;

    List<Cart> m_current_population;
    int m_current_generation = 0;
    Cart m_current_best_solution;
    Cart m_global_best_solution;
    GeneticAlgorithm(int population_size, double mutation_prob, int number_of_generation, List<Product> available_products, double space_limit)
        : m_population_size(population_size),
          m_mutation_prob(mutation_prob),
          m_number_of_generation(number_of_generation),
          m_available_products(available_products),
          m_space_limit(space_limit)
    {
    }

    void solve()
    {
        intialize_population();
        visualize_current_generation();
        m_current_generation = 1;

        for (int generation = 0; generation < m_number_of_generation; generation++)
        {
            List<Cart> new_population;
            while (new_population.length() < m_population_size)
            {
                List<Cart> children = crossover_two_parents();
                List<Cart> mutated_children = mutate_two_children(children);
                new_population.extend(mutated_children);
            }
            update_population_info(new_population);
            visualize_current_generation();

            m_current_generation += 1;
        }
    }
};

#endif