#include "DefaultInteraction.hpp"
#include "DefaultValues.hpp"

Supermarket DefaultInteraction::constructSupermarket() const
{
	return constructDefaultSupermarket();
}

ProductsCount DefaultInteraction::constructCustomerOrder(const ProductCatalog & productCatalog) const
{
	ProductsCount order;

	// Default interaction to always pick half of the items
	for (auto & productCount : productCatalog)
		order[productCount.first] += productCount.second / 2;

	return order;
}
