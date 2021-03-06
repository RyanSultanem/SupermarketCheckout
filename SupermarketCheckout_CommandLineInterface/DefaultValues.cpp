#include "DefaultValues.hpp"

#include "../SupermarketCheckout/product/ProductCatalogFiller.hpp"

class DefaultProductCatalogFiller : public supermarket::ProductCatalogFiller
{
public:
	void fillProductCatalog(supermarket::ProductCatalog & producCatalog) const override
	{
		producCatalog.addProduct(supermarket::Product("DefaultProduct1", 1., true), 10);
		producCatalog.addProduct(supermarket::Product("DefaultProduct2", 2., true), 8);
		producCatalog.addProduct(supermarket::Product("DefaultProduct3", 3., false), 6);
		producCatalog.addProduct(supermarket::Product("DefaultProduct4", 4., true), 4);
		producCatalog.addProduct(supermarket::Product("DefaultProduct5", 5., true), 2);
	}
};

supermarket::Supermarket constructDefaultSupermarket()
{
	std::vector<supermarket::DiscountStrategyInfo> strategyInfos;
	strategyInfos.push_back({ supermarket::DiscountStrategyType::IdenticalItems, 3 });
	strategyInfos.push_back({ supermarket::DiscountStrategyType::ItemCount, 3 });

	supermarket::Supermarket supermarket(strategyInfos);
	supermarket.fillProducts(DefaultProductCatalogFiller());

	return supermarket;
}