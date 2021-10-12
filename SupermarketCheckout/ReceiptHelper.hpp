#pragma once

#include "Product.hpp"
#include "Receipt.hpp"

namespace supermarket {

Receipt constructReceiptFromProducts(const ProductsCount & products, const ProductsCount & discountedProducts);

} // namespace supermarket