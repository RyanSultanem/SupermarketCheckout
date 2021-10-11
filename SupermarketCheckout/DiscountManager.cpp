#include "DiscountManager.hpp"

#include "DiscountStrategy.hpp"

void DiscountManager::addDiscountStrategy(DiscountStrategyType strategyType, int threshold)
{
	m_mainDiscountStrategy.addStrategy(strategyType, threshold);
}

static ProductsCount constructDiscountableProducts(const ProductsCount & products)
{
	ProductsCount discountableProducts;

	for (auto & product : products)
	{
		if (product.first.qualifyForDiscount())
			discountableProducts[product.first] = product.second;
	}

	return discountableProducts;
}

ProductsCount DiscountManager::computeDiscount(const ProductsCount & products)
{
	ProductsCount discountableProducts = constructDiscountableProducts(products);
	return m_mainDiscountStrategy.computeDiscounts(discountableProducts).discountedProducts;
}
