#include "../SupermarketCheckout/Supermarket.hpp"

#include "InteractionHelper.hpp"
#include "Utility.hpp"

#include <fstream>
#include <iostream>
#include <String>

void print(const ProductsCount & products)
{
	for (auto & product : products)
		std::cout << product.first.name() << "\t" << product.second << std::endl;
	std::cout << std::endl;
}

void print(const ReceiptItem & item, std::ostream & out)
{
	out << item.productName() << "\t" << "UP: " << item.unitPrice() << "\t" << "#: " << item.itemCount() << "\t" << "T: " << item.computeTotal() << std::endl;
}

void print(const Receipt & receipt, std::ostream & out)
{
	out << "Receipt:" << std::endl << std::endl;

	out << "All Items:" << std::endl;
	for (auto & item : receipt.getItems())
		print(item, out); 
	out << "Undiscounted Total: " << receipt.computeTotalUndiscounted() << std::endl << std::endl;
	
	out << "Discounted Items:" << std::endl;
	for (auto & item : receipt.getItemsDiscounted())
		print(item, out);
	out << "Discounted Total: " << receipt.computeTotalDiscount() << std::endl << std::endl;

	out << "Total: " << receipt.computeTotal() << std::endl << std::endl;
}

static InteractionMode readInteractionModeChoice()
{
	std::cout << "Interaction Mode: " << std::endl;
	std::cout << "1. Default Values" << std::endl;
	std::cout << "2. Customize " << std::endl;

	int modeChoice = read<int>(std::cin);
	std::cout << std::endl;

	return static_cast<InteractionMode>(modeChoice);
}

bool getChoseItemChoice()
{
	std::cout << "Choose:" << std::endl;
	std::cout << "1. Buy Items" << std::endl;
	std::cout << "2. Stop" << std::endl;

	return read<int>(std::cin) == 1;
}

int main()
{
	std::unique_ptr<InteractionHelper> interaction = constructInteractionHelper(readInteractionModeChoice());

	// Consutrct Supermarket
	Supermarket supermarket = interaction->constructSupermarket();

	bool chooseItems = getChoseItemChoice();

	while (chooseItems)
	{
		// Consutrct Order based on supermarket catalog
		const ProductCatalog & productCatalog = supermarket.productCatalog();
		ProductsCount order = interaction->constructCustomerOrder(productCatalog);

		// Print chosen priducts
		std::cout << "Chosen Products:" << std::endl;
		print(order);

		// Decide To checkout or not
		std::cout << "Checkout?" << std::endl;
		std::cout << "1. Yes" << std::endl;
		std::cout << "2. No" << std::endl;

		int checkoutChoice = read<int>(std::cin);
		std::cout << std::endl;

		if (checkoutChoice == 1)
		{
			// Checkout and Get the receipt
			Receipt receipt = supermarket.checkout(order);
			
			// Print Receipt on console
			print(receipt, std::cout);


			// Print and append Receipt in the ouput file
			std::string outputFIleName("ReceiptOutput.txt");
			std::ofstream fileStream;
			fileStream.open(outputFIleName, std::ios_base::app);
			print(receipt, fileStream);
			fileStream.close();
		}

		chooseItems = getChoseItemChoice();
	}
	return 0;
}