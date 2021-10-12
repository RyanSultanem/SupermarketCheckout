#pragma once

#include "DiscountManager.hpp"
#include "ProductCatalog.hpp"
#include "ProductCatalog.fwd.hpp"
#include "Receipt.hpp"

#include <vector>

class Supermarket
{
public:
	explicit Supermarket(const std::vector<DiscountStrategyInfo> & discountStrategyInfos);

	const ProductCatalog & productCatalog() const;
	void fillProducts(const ProductCatalogFiller & filler);

	Receipt checkout(const ProductsCount & products);

private:
	ProductCatalog m_catalog;
	DiscountManager m_discountManager;

	std::vector<Receipt> m_receiptHistory;

private:
	void bookReceit(const Receipt & receipt);
	void removeProductsFromCatalog(const ProductsCount & products);
};

