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

// These values should be ordered by priority to ensure DiscountComposite application order from lowest to highest
enum class DiscountStrategyType
{
	IdenticalItems,
	ItemCount
};

typedef std::pair<DiscountStrategyType, int> DiscountStrategyInfo;

class DiscountStrategy
{
public:
	virtual DiscountResults computeDiscounts(const ProductsCount & discountableProducts) const = 0;

	virtual ~DiscountStrategy() = default;
};

class DiscountComposite : public DiscountStrategy
{
public:
	DiscountComposite() = default;

	DiscountResults computeDiscounts(const ProductsCount & discountableProducts) const override;

	void addStrategy(DiscountStrategyType strategyType, int threshold);

private:
	std::map<DiscountStrategyType, std::unique_ptr<DiscountStrategy>> m_discountStrategies;
};

class DiscountIdenticalItem : public DiscountStrategy
{
public:
	explicit DiscountIdenticalItem(int identicalItemCountThreshold);

	DiscountResults computeDiscounts(const ProductsCount & discountableProducts) const override;

private:
	int m_identicalItemCountThreshold = 0;
};

class DiscountItemCount : public DiscountStrategy
{
public:
	explicit DiscountItemCount(int itemCountThreshlod);

	DiscountResults computeDiscounts(const ProductsCount & discountableProducts) const override;

private:
	int m_itemCountThreshlod;
};

} // namespace supermarket