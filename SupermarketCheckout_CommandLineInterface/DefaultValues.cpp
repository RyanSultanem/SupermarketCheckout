#include "DefaultValues.hpp"

#include "../SupermarketCheckout/ProductCatalogFiller.hpp"

class DefaultProductCatalogFiller : public ProductCatalogFiller
{
public:
	void fillProductCatalog(ProductCatalog & producCatalog) const override
	{
		producCatalog.addProduct(Product("Product1", 1., true), 10);
		producCatalog.addProduct(Product("Product2", 2., true), 8);
		producCatalog.addProduct(Product("Product3", 3., false), 6);
		producCatalog.addProduct(Product("Product4", 4., true), 4);
		producCatalog.addProduct(Product("Product5", 5., true), 2);
	}
};

Supermarket constructDefaultSupermarket()
{
	std::vector<DiscountStrategyInfo> strategyInfos;
	strategyInfos.push_back({ DiscountStrategyType::IdenticalItems, 3 });
	strategyInfos.push_back({ DiscountStrategyType::ItemCount,3 });

	Supermarket supermarket(strategyInfos);
	supermarket.fillProducts(DefaultProductCatalogFiller());

	return supermarket;
}