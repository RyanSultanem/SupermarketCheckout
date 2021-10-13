#pragma once

#include "discount/DiscountManager.hpp"
#include "product/ProductCatalog.hpp"
#include "product/ProductCatalog.fwd.hpp"
#include "Receipt.hpp"

#include <vector>

namespace supermarket {

/// <summary>
/// The entry point of the library.
/// This class contains the list of products to be bought.
/// Allows the customer to checkout a list of items and receive a receipt
/// The history of receipt is also stored in the supermarket.
/// Also exposes a method to allow the filling of the products in the supermarket. 
/// </summary>
class Supermarket
{
public:
	explicit Supermarket(const std::vector<DiscountStrategyInfo> & discountStrategyInfos);

	const ProductCatalog & productCatalog() const;
	void fillProducts(const ProductCatalogFiller & filler);

	Receipt checkout(const ProductsCount & products);

	const std::vector<Receipt> & receiptHistory() const;

private:
	ProductCatalog m_catalog;
	DiscountManager m_discountManager;

	std::vector<Receipt> m_receiptHistory;

private:
	void bookReceit(const Receipt & receipt);
	void removeProductsFromCatalog(const ProductsCount & products);
};

} // namespace supermarket