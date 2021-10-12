#include "Printer.hpp"

void print(const supermarket::ProductsCount & products, std::ostream & out)
{
	for (auto& product : products)
		out << product.first.name() << "\t" << product.second << std::endl;
	out << std::endl;
}

static void print(const supermarket::ReceiptItem & item, std::ostream & out)
{
	out << item.productName() << "\t" << "UP: " << item.unitPrice() << "\t" << "#: " << item.itemCount() << "\t" << "T: " << item.computeTotal() << std::endl;
}

void print(const supermarket::Receipt & receipt, std::ostream & out)
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