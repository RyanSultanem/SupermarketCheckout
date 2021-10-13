#pragma once

#include <unordered_set>
#include <string>

namespace supermarket {

class ReceiptItem
{
public:
	ReceiptItem(const std::string & productName, int itemCount, double unitPrice)
		: m_productName(productName)
		, m_itemCount(itemCount)
		, m_unitPrice(unitPrice)
	{}

	const std::string & productName() const { return m_productName; }
	int itemCount() const { return m_itemCount; }
	double unitPrice() const { return m_unitPrice; }

	double computeTotal() const;

	bool operator==(const ReceiptItem & other) const;

private:
	std::string m_productName;
	int m_itemCount = 0;
	double m_unitPrice = 0.;
};

} // namespace supermarket

namespace std {

template<>
struct hash<supermarket::ReceiptItem>
{
	std::size_t operator()(const supermarket::ReceiptItem & receiptItem) const
	{
		// Unit count left on purpose, part of the output
		return (hash<string>()(receiptItem.productName())
			+ hash<double>()(receiptItem.unitPrice()));
	}
};

} // namespace std

namespace supermarket {

class Receipt
{
public:
	Receipt() = default;

	// Returns all items, discounted and undiscounted
	const std::unordered_set<ReceiptItem> getItems() const;
	// Return the discounted items
	const std::unordered_set<ReceiptItem> getItemsDiscounted() const;

	// Only add Items that are not discounted
	void addItemsUndiscounted(const std::unordered_set<ReceiptItem> & items);
	// Only add Items that weere discounted
	void addItemsDiscounted(const std::unordered_set<ReceiptItem> & itemsDiscounted);

	double computeTotal() const;
	double computeTotalDiscount() const;
	double computeTotalUndiscounted() const;

private:
	std::unordered_set<ReceiptItem> m_items;
	std::unordered_set<ReceiptItem> m_itemsDiscounted;
};

} // namespace supermarket

