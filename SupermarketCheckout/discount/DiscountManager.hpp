#pragma once

#include "../product/Product.hpp"
#include "DiscountStrategy.hpp"

namespace supermarket {

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
