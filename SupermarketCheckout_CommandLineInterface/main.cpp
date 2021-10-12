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
	std::cout << "1. Default Values (No choice interaction)" << std::endl;
	std::cout << "2. Manual Input (Interactive choices in CLI)" << std::endl;
	std::cout << "3. File Input (Interactive choices via File input)" << std::endl;

	int modeChoice = read<int>(std::cin);
	std::cout << std::endl;

	return static_cast<InteractionMode>(modeChoice);
}

static bool getYesNoChoice(const std::string & message)
{
	std::cout << message << std::endl;
	std::cout << "1. Yes" << std::endl;
	std::cout << "2. No" << std::endl;

	return read<int>(std::cin) == 1;
}

int main()
{
	std::unique_ptr<InteractionHelper> interaction = constructInteractionHelper(readInteractionModeChoice());

	// Consutrct Supermarket
	supermarket::Supermarket supermarket = interaction->constructSupermarket();

	// Print Catalog choices
	print(supermarket.productCatalog(), std::cout);

	// Decide to buy items or not
	bool buyItems = getYesNoChoice("Buy Items ?");
	std::cout << std::endl;
	while (buyItems)
	{
		// Consutrct Order based on supermarket catalog, and print it
		supermarket::ProductsCount order = interaction->constructCustomerOrder(supermarket.productCatalog());
		std::cout << "Chosen Products:" << std::endl;
		print(order, std::cout);

		// Decide to checkout or not
		int checkoutChoice = getYesNoChoice("Checkout ?");
		std::cout << std::endl;

		if (checkoutChoice == 1)
		{
			// Checkout and Get the receipt
			supermarket::Receipt receipt = supermarket.checkout(order);
			
			// Print Receipt on console
			print(receipt, std::cout);

			// Print and append Receipt in the ouput file
			std::string outputFIleName("ressources/ReceiptOutput.txt");
			std::ofstream fileStream;
			fileStream.open(outputFIleName, std::ios_base::app);
			print(receipt, fileStream);
			fileStream.close();
		}

		// Print Catalog choices
		print(supermarket.productCatalog(), std::cout);

		// Decide to buy items or not
		buyItems = getYesNoChoice("Buy More Items ?");
	}
	return 0;
}