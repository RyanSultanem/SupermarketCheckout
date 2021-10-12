#pragma once

#include "../SupermarketCheckout/product/Product.hpp"
#include "../SupermarketCheckout/Receipt.hpp"

#include <ostream>

void print(const supermarket::ProductsCount & products);
void print(const supermarket::Receipt & receipt, std::ostream& out);