#pragma once

#include "Product.hpp"
#include "Receipt.hpp"

Receipt constructReceiptFromProducts(const ProductsCount & products, const ProductsCount & discountedProducts);