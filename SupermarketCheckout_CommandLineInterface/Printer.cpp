#include "Printer.hpp"

#include "../SupermarketCheckout/product/ProductCatalog.hpp"

void print(const supermarket::ProductsCount & products, std::ostream & out)
{
	for (auto& product : products)
		out << product.first.name() << "\t" << product.second << std::endl;
	out << std::endl;
}

void print(const supermarket::ProductCatalog & productCatalog, std::ostream & out)
{
	out << "Product Catalog:" << std::endl;
	int count = 0;
	for (auto & productCount : productCatalog)
	{
		const supermarket::Product & product = productCount.first;
		out << count + 1 << ". "
			<< "Product: " << product.name() << "\t\t"
			<< "Unit Price: " << product.unitPrice() << "\t\t"
			<< "Discount Elligible: " << std::string(product.qualifyForDiscount() ? "Yes" : "No") << "\t\t"
			<< "Product Count: " << productCount.second << "\t\t"
			<< std::endl;
		count++;
	}
	out << std::endl;
}

static void print(const supermarket::ReceiptItem & item, std::ostream & out)
{
	out << item.productName() << "\t" << "UP: " << item.unitPrice() << "\t" << "#: " << item.itemCount() << "\t" << "T: " << item.computeTotal() << std::endl;
}

void print(const supermarket::Receipt & receipt, std::ostream & out)
{
	out << "======================================" << std::endl;
	out << "Receipt:" << std::endl << std::endl;

	out << "All Items:" << std::endl;
	for (auto & item : receipt.getItems())
		print(item, out);
	out << "Undiscounted Total: " << receipt.computeTotalUndiscounted() << std::endl << std::endl;

	out << "Discounted Items:" << std::endl;
	for (auto & item : receipt.getItemsDiscounted())
		print(item, out);
	out << "Discounted Total: " << receipt.computeTotalDiscount() << std::endl << std::endl;

	out << "Total: " << receipt.computeTotal() << std::endl;
	out << "======================================" << std::endl << std::endl;
}