#pragma once

#include "Product.hpp"

#include <unordered_map>

namespace supermarket {

typedef std::unordered_map<Product, int>::const_iterator ProductCatalogCIterator;

class ProductCatalog
{
public:
	ProductCatalog() = default;

	bool hasProducts(const ProductsCount & products) const;
	int procutCount(const Product & product) const;

	bool removeProducts(const ProductsCount & products);
	bool removeProduct(const Product & product, int count);
	void addProducts(const ProductsCount & products);
	void addProduct(const Product & product, int count);

	ProductCatalogCIterator begin() const;
	ProductCatalogCIterator end() const;

private:
	ProductsCount m_productsCount;
};

} // namespace supermarket