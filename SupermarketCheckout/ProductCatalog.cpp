#include "ProductCatalog.hpp"

#include "Product.hpp"
#include "Utility.hpp"

namespace supermarket {

bool ProductCatalog::hasProducts(const ProductsCount & products) const
{
	return utility::mapContainsOtherMap(m_productsCount, products);
}

bool ProductCatalog::removeProducts(const ProductsCount & products)
{
	return utility::mapRemoveOtherMap(m_productsCount, products);
}

bool ProductCatalog::removeProduct(const Product & product, int count)
{
	auto it = m_productsCount.find(product);

	if (it == end() || it->second == 0 || it->second < count)
		return false;
	
	it->second -= count;
	return true;
}

void ProductCatalog::addProducts(const ProductsCount & products)
{
	for (auto & product : products)
		addProduct(product.first, product.second);
}

void ProductCatalog::addProduct(const Product & product, int count)
{
	m_productsCount[product] += count;
}

int ProductCatalog::procutCount(const Product & product) const
{
	auto it = m_productsCount.find(product);
	
	return it != end() ? it->second : 0;
}

ProductCatalogCIterator ProductCatalog::begin() const
{
	return m_productsCount.begin();
}

ProductCatalogCIterator ProductCatalog::end() const
{
	return m_productsCount.end();
}

} // namespace supermarket