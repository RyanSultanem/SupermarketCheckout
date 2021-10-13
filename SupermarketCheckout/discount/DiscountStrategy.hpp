#pragma once

#include "../product/Product.hpp"

#include <map>
#include <memory>

namespace supermarket {

struct DiscountResults
{
	ProductsCount discountedProducts;
	ProductsCount remainingProductsAvailableForDiscount;
};

/// <summary>
/// Enum denoting the priority of the appliance of discounting rules, mainly used in DiscountComposite.
/// </summary>
enum class DiscountStrategyType
{
	IdenticalItems,
	ItemCount
};

typedef std::pair<DiscountStrategyType, int> DiscountStrategyInfo;

/// <summary>
/// An interface that applies the discount on a list of products and returns the discounted items.
/// </summary>
class DiscountStrategy
{
public:
	virtual DiscountResults computeDiscounts(const ProductsCount & discountableProducts) const = 0;

	virtual ~DiscountStrategy() = default;
};

/// <summary>
/// A list of discounting strategies to apply on the same set of products, also ensures that the strategies are applied in order.
/// </summary>
class DiscountComposite : public DiscountStrategy
{
public:
	DiscountComposite() = default;

	DiscountResults computeDiscounts(const ProductsCount & discountableProducts) const override;

	void addStrategy(DiscountStrategyType strategyType, int threshold);

private:
	std::map<DiscountStrategyType, std::unique_ptr<DiscountStrategy>> m_discountStrategies;
};

/// <summary>
/// Discount strategy to compute identical item discounting rule.
/// </summary>
class DiscountIdenticalItem : public DiscountStrategy
{
public:
	explicit DiscountIdenticalItem(int identicalItemCountThreshold);

	DiscountResults computeDiscounts(const ProductsCount & discountableProducts) const override;

private:
	int m_identicalItemCountThreshold = 0;
};

/// <summary>
/// Discount strategy to compute the item count discounting rule. 
/// </summary>
class DiscountItemCount : public DiscountStrategy
{
public:
	explicit DiscountItemCount(int itemCountThreshlod);

	DiscountResults computeDiscounts(const ProductsCount & discountableProducts) const override;

private:
	int m_itemCountThreshlod;
};

} // namespace supermarket