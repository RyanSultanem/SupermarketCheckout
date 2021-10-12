#include "InputInteraction.hpp"

#include "../SupermarketCheckout/product/ProductCatalogFiller.hpp"

#include "DefaultValues.hpp"
#include "Utility.hpp"

#include <fstream>
#include <iostream>
#include <istream>
#include <string>

class InputProducCatalogFiller : public supermarket::ProductCatalogFiller
{
public:
	InputProducCatalogFiller(std::istream & in)
		: m_in(in)
	{}

	void fillProductCatalog(supermarket::ProductCatalog & producCatalog) const override
	{
		int numberOfItemsToAdd = read<int>(m_in);
		while (numberOfItemsToAdd > 0)
		{
			std::string productName = read<std::string>(m_in);
			double unitPrice = read<double>(m_in);
			char elligibleForDiscountCharYN = read<char>(m_in);
			bool elligibleForDiscount = (elligibleForDiscountCharYN == 'Y');
			int unitCount = read<int>(m_in);

			producCatalog.addProduct(supermarket::Product(productName, unitPrice, elligibleForDiscount), unitCount);

			numberOfItemsToAdd--;
		}
	}

private:
	std::istream & m_in;
};

static supermarket::Supermarket constructCustomizedSupermarket(std::istream & in)
{
	std::vector<supermarket::DiscountStrategyInfo> strategyInfos;
	strategyInfos.push_back({ supermarket::DiscountStrategyType::IdenticalItems, 3 });
	strategyInfos.push_back({ supermarket::DiscountStrategyType::ItemCount,3 });

	supermarket::Supermarket supermarket(strategyInfos);
	supermarket.fillProducts(InputProducCatalogFiller(in));

	return supermarket;
}

supermarket::Supermarket CLIInputInteraction::constructSupermarket() const
{
	std::cout << "Supermarket Initialization" << std::endl;
	std::cout << "1. Default Supermarket" << std::endl;
	std::cout << "2. Customize Supermarket" << std::endl;

	int choice = read<int>(std::cin);
	std::cout << std::endl;

	if (choice == 2)
	{
		std::cout << "Products information Format:" << std::endl;
		std::cout << "ProductName \t UnitPrice \t ElligibleForDiscount(Y/N) \t ItemCount" << std::endl;
		std::cout << "Enter number of products to add with their quantity, then enter the products: ";

		return constructCustomizedSupermarket(std::cin);
	}
		
	return constructDefaultSupermarket();
}

static supermarket::ProductsCount constructCustomerOrderFromInputStream(const supermarket::ProductCatalog & productCatalog, std::istream & in)
{
	int counter = 0;
	std::unordered_map<int, supermarket::Product> choicesMap;
	for (auto & productCount : productCatalog)
	{
		choicesMap[counter + 1] = productCount.first;
		counter++;
	}

	int numberOfProductsToBuy = read<int>(in);
	supermarket::ProductsCount order;

	while (numberOfProductsToBuy)
	{
		int itemChoice = read<int>(in);
		int itemCount = read<int>(in);
		order[choicesMap.at(itemChoice)] += itemCount;

		numberOfProductsToBuy--;
	}

	return order;
}

supermarket::ProductsCount CLIInputInteraction::constructCustomerOrder(const supermarket::ProductCatalog & productCatalog) const
{	
	std::cout << "Product Choice Format: ProductId Count" << std::endl;
	std::cout << "Enter the number of product, then the product input format: ";
	
	return constructCustomerOrderFromInputStream(productCatalog, std::cin);
}

supermarket::Supermarket FileInputInteraction::constructSupermarket() const
{
	std::cout << "Supermarket Initialization" << std::endl;
	std::cout << "1. Default Supermarket" << std::endl;
	std::cout << "2. File Input" << std::endl;

	int choice = read<int>(std::cin);
	std::cout << std::endl;

	if (choice == 2)
	{
		std::cout << "Products information Format:" << std::endl 
				  << "ProductName \t UnitPrice \t ElligibleForDiscount(Y/N) \t ItemCount" << std::endl
				  << "Fill the file with the number of products on the first line." << std::endl
				  << "Followed by a line for each product with the product format." << std::endl;
				  
		std::cout << "Enter the filename (E.g. SupermarketProductCatalogInput.txt): ";
		std::string fileName = "ressources/" + read<std::string>(std::cin);
		std::cout << std::endl;

		std::ifstream inFile(fileName);
		supermarket::Supermarket supermarket = constructCustomizedSupermarket(inFile);
		
		return supermarket;
	}

	return constructDefaultSupermarket();
}

supermarket::ProductsCount FileInputInteraction::constructCustomerOrder(const supermarket::ProductCatalog & productCatalog) const
{
	std::cout << "Product Choice Format: ProductId Count" << std::endl;
	std::cout << "Enter the number of product, then one line with the product choice format for each product." << std::endl;

	std::cout << "Enter the input file name (E.g. CustomerOrderInput.txt): ";
	std::string inputFileName = "ressources/" + read<std::string>(std::cin);
	std::cout << std::endl;

	std::ifstream inFile(inputFileName);
	return constructCustomerOrderFromInputStream(productCatalog, inFile);
}
