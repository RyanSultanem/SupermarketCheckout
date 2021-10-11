#pragma once

#include <vector>
#include <string>

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

private:
	std::string m_productName;
	int m_itemCount = 0;
	double m_unitPrice = 0.;
};

typedef std::vector<ReceiptItem>::const_iterator ReceiptItemCIterator;

class Receipt
{
public:
	Receipt() = default;

	const std::vector<ReceiptItem> getItems() const;
	const std::vector<ReceiptItem> getItemsDiscounted() const;

	void addItems(const std::vector<ReceiptItem> & items);
	void addItemsDiscounted(const std::vector<ReceiptItem> & itemsDiscounted);

	double computeTotal() const;
	double computeTotalDiscount() const;
	double computeTotalUndiscounted() const;

private:
	std::vector<ReceiptItem> m_items;
	std::vector<ReceiptItem> m_itemsDiscounted;
};

