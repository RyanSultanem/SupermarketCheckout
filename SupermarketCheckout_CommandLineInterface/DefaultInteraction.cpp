#include "DefaultInteraction.hpp"
#include "DefaultValues.hpp"

supermarket::Supermarket DefaultInteraction::constructSupermarket() const
{
	return constructDefaultSupermarket();
}

supermarket::ProductsCount DefaultInteraction::constructCustomerOrder(const supermarket::ProductCatalog & productCatalog) const
{
	supermarket::ProductsCount order;

	// Default interaction to always pick half of the items
	for (auto & productCount : productCatalog)
		order[productCount.first] += productCount.second / 2;

	return order;
}
