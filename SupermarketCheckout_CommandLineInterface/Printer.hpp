#pragma once

#include "../SupermarketCheckout/product/Product.hpp"
#include "../SupermarketCheckout/product/ProductCatalog.fwd.hpp"
#include "../SupermarketCheckout/Receipt.hpp"

#include <ostream>

void print(const supermarket::ProductCatalog & productCatalog, std::ostream & out);
void print(const supermarket::ProductsCount & products, std::ostream & out);
void print(const supermarket::Receipt & receipt, std::ostream& out);