#pragma once

//
//  open_closed.cpp
//  DesignPatterns
//
//  Created by Nicolás Cárdenas on 15/02/24.
//

#include <iostream>
#include <vector>
#include <string>

enum class Color { green, blue, black };
enum class Size { small, medium, large };
struct Product {
    std::string name;
    Color color;
    Size size;
};

template <typename T>
struct Specification {
    virtual bool isSatisfied(T* item) = 0;
};

template <typename T>
struct Filter {
    virtual std::vector<T*> filter(std::vector<T*> items, Specification<T>& spec) = 0;
};

struct ProductFilter: Filter<Product> {
    std::vector<Product*> filter(std::vector<Product*> items, Specification<Product>& spec) override {
        std::vector<Product*> result;
        for (Product* product: items) {
            if (spec.isSatisfied(product)) {
                result.push_back(product);
            }
        }
        return result;
    }
};

struct ProductColorSpecification: Specification<Product> {
    Color color;
    
    ProductColorSpecification(Color color) : color(color) {}
    
    bool isSatisfied(Product* product) override {
        return product->color == color;
    };
};


int openClosedMain() {
    Product* first = new Product{"First", Color::black, Size::small};
    Product* second = new Product{"Second", Color::blue, Size::medium};
    Product* third = new Product{"Third", Color::green, Size::medium};
    std::vector<Product*> products = { first, second, third };
    ProductColorSpecification spec = ProductColorSpecification{Color::green};
    std::vector<Product*> filtered = ProductFilter{}.filter(products, spec);
    for (Product* product: filtered) {
        std::cout << product->name << std::endl;
    }
    return 0;
}

