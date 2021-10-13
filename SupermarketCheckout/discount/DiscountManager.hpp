#pragma once

#include "DiscountStrategy.hpp"
#include "../product/Product.hpp"

namespace supermarket {

/// <summary>
/// The main entry point of the discounting logic.
/// For now simply filters out the products eligible for discount, 
/// and delegates to the discount strategy to compute the discounted items result. 
/// </summary>
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
