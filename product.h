#ifndef PRODUCT_H
#define PRODUCT_H
#include <iostream>
#include <string>
#include "PyDataType/list.h"
class Product
{
public:
    std::string m_name;
    double m_space;
    double m_price;
    Product(std::string name, double space, double price)
        : m_name(name), m_space(space), m_price(price)
    {
    }

    static List<Product> get_all_products()
    {
        Product p1("Refrigerator A", 0.751, 999.90);
        Product p2("Cell phone", 0.00000899, 2199.12);
        Product p3("TV 55", 0.400, 4346.99);
        Product p4("TV 50' ", 0.290, 3999.90);
        Product p5("TV 42' ", 0.200, 2999.00);
        Product p6("Notebook A", 0.00350, 2499.90);
        Product p7("Ventilator", 0.496, 199.90);
        Product p8("Microwave A", 0.0424, 308.66);
        Product p9("Microwave B", 0.0544, 429.90);
        Product p10("Microwave C", 0.0319, 299.29);
        Product p11("Refrigerator B", 0.635, 849.00);
        Product p12("Refrigerator C", 0.870, 1199.89);
        Product p13("Notebook B", 0.498, 1999.90);
        Product p14("Notebook C", 0.527, 3999.00);
        List<Product> products = {p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14};

        return products;
    }

    bool operator==(const Product &_other_product)
    {
        return (m_name == _other_product.m_name && m_price == _other_product.m_price && m_space == _other_product.m_space);
    }

    friend std::ostream &operator<<(std::ostream &stream, const Product &product)
    {
        stream << product.m_name << " - " << product.m_price << " - " << product.m_space;

        return stream;
    }

    std::string to_string() const
    {
        std::string repr_;
        repr_ = m_name + std::to_string(m_price) + std::to_string(m_space);
        return repr_;
    }
};

#endif