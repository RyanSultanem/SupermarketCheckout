#include "DiscountStrategy.hpp"
#include "Utility.hpp"


DiscountIdenticalItem::DiscountIdenticalItem(int identicalItemCountThreshold)
	: m_identicalItemCountThreshold(identicalItemCountThreshold)
{}

DiscountResults DiscountIdenticalItem::computeDiscounts(const ProductsCount & discountableProducts) const
{
	ProductsCount discountedProducts;
	ProductsCount remainingProductsAvailableForDiscounts = discountableProducts;

	for (auto & productCount : discountableProducts)
	{
		int freeItemCount = productCount.second / m_identicalItemCountThreshold;
		if (freeItemCount > 0)
		{
			discountedProducts[productCount.first] = freeItemCount;
			remainingProductsAvailableForDiscounts[productCount.first] -= freeItemCount * m_identicalItemCountThreshold;
		}
	}

	DiscountResults discountResult;
	discountResult.discountedProducts = discountedProducts;
	discountResult.remainingProductsAvailableForDiscount = remainingProductsAvailableForDiscounts;
	return discountResult;
}

DiscountItemCount::DiscountItemCount(int itemCountThreshlod)
	: m_itemCountThreshlod(itemCountThreshlod)
{
}

struct ProductPriceComparator
{
	bool operator()(const Product & p1, const Product & p2) const
	{
		return p1.unitPrice() < p2.unitPrice();
	}
};

typedef std::map<Product, int, ProductPriceComparator> ProductsCountSortedByPrice;

DiscountResults DiscountItemCount::computeDiscounts(const ProductsCount & discountableProducts) const
{
	int numberOfProducts = utility::mapItemCount(discountableProducts);
	int numberOfFreeProducts = numberOfProducts / m_itemCountThreshlod;
	int numberOfProductsUsedForDiscountComputation = (numberOfFreeProducts * m_itemCountThreshlod) - numberOfFreeProducts;

	ProductsCountSortedByPrice sortedDiscoutableProducts = utility::constructSortedMap<ProductPriceComparator>(discountableProducts);
	
	// Remove most expensive products as they have been used for discounts
	auto itMax = sortedDiscoutableProducts.rbegin();
	ProductsCount remainingProductsForDiscounts = discountableProducts;
	while (numberOfProductsUsedForDiscountComputation != 0)
	{
		const Product & product = itMax->first;
		int productCount = itMax->second;

		int productCountToRemove = std::min(numberOfProductsUsedForDiscountComputation, productCount);

		remainingProductsForDiscounts[product] -= productCountToRemove;
		numberOfProductsUsedForDiscountComputation -= productCountToRemove;

		itMax++;
	}

	// Choose least expensive products for discounted Products and remove from remaining list
	ProductsCount discountProducts;
	auto itMin = sortedDiscoutableProducts.begin();
	while (numberOfFreeProducts != 0)
	{
		const Product & product = itMin->first;
		int productCount = itMin->second;

		int freeProductCount = std::min(numberOfFreeProducts, productCount);
		discountProducts[product] += freeProductCount;

		remainingProductsForDiscounts[product] -= freeProductCount;
		numberOfFreeProducts -= freeProductCount;

		itMin++;
	}

	DiscountResults discountResult;
	discountResult.discountedProducts = discountProducts;
	discountResult.remainingProductsAvailableForDiscount = remainingProductsForDiscounts;
	return discountResult;
}

static std::unique_ptr<DiscountStrategy> constructDiscountStrategyFromType(DiscountStrategyType strategy, int threshold)
{
	switch (strategy)
	{
	case DiscountStrategyType::IdenticalItems: return std::make_unique<DiscountIdenticalItem>(threshold);
	case DiscountStrategyType::ItemCount: return std::make_unique<DiscountItemCount>(threshold);

	default: return std::make_unique<DiscountIdenticalItem>(threshold);
	}
}

void DiscountComposite::addStrategy(DiscountStrategyType strategyType, int threshold)
{
	m_discountStrategies[strategyType] = constructDiscountStrategyFromType(strategyType, threshold);
}

DiscountResults DiscountComposite::computeDiscounts(const ProductsCount & discountableProducts) const
{
	ProductsCount totalDiscountedProducts;
	ProductsCount remainingDiscountableProducts = discountableProducts;

	for (auto & discountStrategy : m_discountStrategies)
	{
		DiscountResults innerDiscountsResult = discountStrategy.second->computeDiscounts(remainingDiscountableProducts);
		utility::mergeMaps(totalDiscountedProducts, innerDiscountsResult.discountedProducts);

		remainingDiscountableProducts = innerDiscountsResult.remainingProductsAvailableForDiscount;
	}

	DiscountResults totalDiscountResult;
	totalDiscountResult.discountedProducts = totalDiscountedProducts;
	totalDiscountResult.remainingProductsAvailableForDiscount = remainingDiscountableProducts;
	return totalDiscountResult;
}
