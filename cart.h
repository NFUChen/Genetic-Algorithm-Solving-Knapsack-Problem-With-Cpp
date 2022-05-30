#ifndef CART_H
#define CART_H
#include <iostream>
#include <cmath>
#include <assert.h>
#include "PyDataType/list.h"
#include "product.h"
#include "random_number_generator.h"
class Cart
{
private:
    double mutable m_fitness = -1.0;

    List<int> m_chromosome;
    List<int> initialize_chromosome()
    {
        List<int> chromosome;

        while (chromosome.length() != m_products.length())
        {
            double random_val = uniform_random<double>(0, 1);
            if (random_val > 0.5)
            {
                chromosome.append(1);
            }
            else
            {
                chromosome.append(0);
            }
        }

        return chromosome;
    }
    Cart create_next_generation_child_with_new_chromose(const List<int> &new_chromosome)
    {
        Cart next_generate_child(m_products, m_space_limit, m_generation + 1);
        next_generate_child.set_chromosome(new_chromosome);

        return next_generate_child;
    }
    void set_chromosome(const List<int> &new_chromosome)
    {
        m_chromosome = new_chromosome;
    }
    void mutate_a_gene_in_chromosome(int mutated_bit_idx)
    {
        int current_bit = m_chromosome[mutated_bit_idx];
        int new_bit;
        if (current_bit == 1)
            new_bit = 0;
        else if (current_bit == 0)
            new_bit = 1;

        m_chromosome[mutated_bit_idx] = new_bit;
    }

public:
    List<Product> m_products;
    double m_space_limit;
    int m_generation;

    Cart()
    {
    }
    Cart(const List<Product> &products, double space_limit, int generation = 0)
        : m_products(products), m_space_limit(space_limit), m_generation(generation)
    {
        m_chromosome = initialize_chromosome();
        update_fitness();
    }
    void update_fitness() const
    {
        double total_space_used = 0.0;
        double total_score = 0.0;
        for (int idx = 0; idx <= m_products.length() - 1; idx++)
        {
            int gene = m_chromosome[idx];
            Product current_product = m_products[idx];

            if (gene == 1)
            {
                total_space_used += current_product.m_space;
                if (total_space_used > m_space_limit)
                {
                    m_fitness = 0.0;
                    return;
                }
                total_score += current_product.m_price;
            }
        }
        m_fitness = total_score;
    }

    double fitness() const
    {
        return m_fitness;
    }
    List<Product> selected_products()
    {
        List<Product> selected_products_list;
        for (int idx = 0; idx <= m_products.length() - 1; idx++)
        {
            int gene = m_chromosome[idx];
            Product current_product = m_products[idx];

            if (gene == 1)
            {
                selected_products_list.append(current_product);
            }
        }
        return selected_products_list;
    };

    List<Cart> crossover(const Cart &_other_cart)
    {
        assert(m_chromosome.length() != 0);
        assert(_other_cart.m_chromosome.length() != 0);

        int cutoff_point = floor(uniform_random<double>(0, 1) * m_chromosome.length());

        List<int> self_genes_x = m_chromosome.slice(0, cutoff_point);
        List<int> self_genes_y = m_chromosome.slice(cutoff_point);

        List<int> other_genes_x = _other_cart.m_chromosome.slice(0, cutoff_point);
        List<int> other_genes_y = _other_cart.m_chromosome.slice(cutoff_point);

        List<int> child_x_chromosome = self_genes_x + other_genes_y;
        List<int> child_y_chromosome = other_genes_x + self_genes_y;

        Cart child_x = create_next_generation_child_with_new_chromose(child_x_chromosome);
        Cart child_y = create_next_generation_child_with_new_chromose(child_y_chromosome);

        List<Cart> children = {child_x, child_y};

        return children;
    }

    Cart &mutate(double mutation_rate)
    {
        for (int idx = 0; idx <= m_chromosome.length() - 1; idx++)
        {
            double mutation_prob = uniform_random<double>(0, 1);
            if (mutation_prob > mutation_rate)
            {
                mutate_a_gene_in_chromosome(idx);
            }
            update_fitness();
        }

        return *this;
    }

    bool operator==(const Cart &_other_cart) const
    {
        return (this->fitness() == _other_cart.fitness());
    }
    bool operator!=(const Cart &_other_cart) const
    {
        return (this->fitness() != _other_cart.fitness());
    }

    bool operator<(const Cart &_other_cart) const
    {
        return (this->fitness() < _other_cart.fitness());
    }
    bool operator>(const Cart &_other_cart) const
    {
        return (this->fitness() > _other_cart.fitness());
    }

    friend std::ostream &operator<<(std::ostream &stream, const Cart &cart)
    {
        for (const Product &product : cart.m_products.values())
        {
            stream << product << "\n";
        }
        stream << "--------------------------\n";
        stream << cart.m_chromosome << "\n";
        stream << "Current Generation: " << cart.m_generation << "\n";
        stream << "Fitness: " << cart.fitness() << "\n";

        return stream;
    }
};

#endif