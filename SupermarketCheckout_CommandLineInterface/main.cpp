#include "../SupermarketCheckout/Supermarket.hpp"

#include "InteractionHelper.hpp"
#include "Printer.hpp"
#include "Utility.hpp"

#include <fstream>
#include <iostream>
#include <String>

static InteractionMode readInteractionModeChoice()
{
	std::cout << "Interaction Mode: " << std::endl;
	std::cout << "1. Default Values" << std::endl;
	std::cout << "2. Customize " << std::endl;

	int modeChoice = read<int>(std::cin);
	std::cout << std::endl;

	return static_cast<InteractionMode>(modeChoice);
}

static bool getChoseItemChoice()
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
	supermarket::Supermarket supermarket = interaction->constructSupermarket();

	bool chooseItems = getChoseItemChoice();
	while (chooseItems)
	{
		// Consutrct Order based on supermarket catalog
		const supermarket::ProductCatalog & productCatalog = supermarket.productCatalog();
		supermarket::ProductsCount order = interaction->constructCustomerOrder(productCatalog);

		// Print chosen priducts
		std::cout << "Chosen Products:" << std::endl;
		print(order);

		// Decide To checkout or not
		int checkoutChoice = getChoseItemChoice();
		std::cout << std::endl;

		if (checkoutChoice == 1)
		{
			// Checkout and Get the receipt
			supermarket::Receipt receipt = supermarket.checkout(order);
			
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