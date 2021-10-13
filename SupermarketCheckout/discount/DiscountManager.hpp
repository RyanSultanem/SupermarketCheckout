#pragma once

#include "DiscountStrategy.hpp"
#include "../product/Product.hpp"

namespace supermarket {

// Entry point of the discount module
// Filters out the Products that are eligible for discount
// Then compute the discount on the remaining products
class DiscountManager
{
public:
	DiscountManager() = default;
	void addDiscountStrategy(DiscountStrategyType strategyType, int threshold);

	ProductsCount computeDiscount(const ProductsCount & products);

private:
	DiscountComposite m_mainDiscountStrategy;
};

} // namespace supermarket
