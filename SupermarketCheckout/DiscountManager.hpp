#pragma once

#include "Product.hpp"
#include "DiscountStrategy.hpp"

class DiscountManager
{
public:
	DiscountManager() = default;
	void addDiscountStrategy(DiscountStrategyType strategyType, int threshold);

	ProductsCount computeDiscount(const ProductsCount & products);

private:
	DiscountComposite m_mainDiscountStrategy;
};