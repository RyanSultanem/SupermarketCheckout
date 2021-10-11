#include "InputInteraction.hpp"

#include "../SupermarketCheckout/ProductCatalogFiller.hpp"

#include "DefaultValues.hpp"
#include "Utility.hpp"

#include <iostream>
#include <string>

class InputProducCatalogFiller : public ProductCatalogFiller
{
public:
	InputProducCatalogFiller(std::istream & in)
		: m_in(in)
	{}

	void fillProductCatalog(ProductCatalog & producCatalog) const override
	{
		bool add = getAddShoice();
		while (add)
		{
			std::cout << "ProductName \t UnitPrice \t ElligibleForDiscount(Y/N) \t ItemCount" << std::endl;
			std::string productName = read<std::string>(m_in);
			double unitPrice = read<double>(m_in);
			char elligibleForDiscountCharYN = read<char>(m_in);
			bool elligibleForDiscount = (elligibleForDiscountCharYN == 'Y');
			int unitCount = read<int>(m_in);

			producCatalog.addProduct(Product(productName, unitPrice, elligibleForDiscount), unitCount);

			add = getAddShoice();
		}
		std::cout << std::endl;
	}

private:
	std::istream & m_in;

	bool getAddShoice() const
	{
		std::cout << "Choose:" << std::endl;
		std::cout << "1. Add" << std::endl;
		std::cout << "2. Stop" << std::endl;

		return read<int>(m_in) == 1;
	}
};

static Supermarket constructCustomizedSupermarket(std::istream & in)
{
	std::vector<DiscountStrategyInfo> strategyInfos;
	strategyInfos.push_back({ DiscountStrategyType::IdenticalItems, 3 });
	strategyInfos.push_back({ DiscountStrategyType::ItemCount,3 });

	Supermarket supermarket(strategyInfos);
	supermarket.fillProducts(InputProducCatalogFiller(in));

	return supermarket;
}

Supermarket CLIInputInteraction::constructSupermarket() const
{
	std::cout << "Supermarket Initialization" << std::endl;
	std::cout << "1. Default Supermarket" << std::endl;
	std::cout << "2. Customize Supermarket" << std::endl;

	int choice = read<int>(std::cin);

	if (choice == 2)
	{
		std::cout << "Enter Products information" << std::endl;
		return constructCustomizedSupermarket(std::cin);
	}
		
	return constructDefaultSupermarket();
}

ProductsCount CLIInputInteraction::constructCustomerOrder(const ProductCatalog & productCatalog) const
{
	int counter = 0;
	std::unordered_map<int, Product> choicesMap;
	for (auto & productCount : productCatalog)
	{
		int id = counter + 1;
		const Product & product = productCount.first;
		choicesMap[id] = product;

		std::cout << id << ". "
			<< "Product: " << product.name() << "\t\t"
			<< "Unit Price: " << product.unitPrice() << "\t\t"
			<< "Discount Elligible: " << std::string(product.qualifyForDiscount() ? "Yes" : "No") << "\t\t"
			<< "Product Count: " << productCount.second << "\t\t"
			<< std::endl;
		counter++;
	}

	std::cout << "Choose: ProductId Count  (Type 0 to stop)." << std::endl;

	ProductsCount order;
	int itemChoice = read<int>(std::cin);
	while (itemChoice != 0 || itemChoice >= choicesMap.size())
	{
		int itemCount = read<int>(std::cin);
		order[choicesMap[itemChoice]] += itemCount;

		itemChoice = read<int>(std::cin);
	}

	return order;
}
