#include "pch.h"

#include "../SupermarketCheckout/Receipt.hpp"

#include <vector>

namespace supermarket {

TEST(ReceiptItem, Total)
{
	ReceiptItem item("Item", 3, 5.);

	EXPECT_DOUBLE_EQ(item.computeTotal(), 15.);
}

TEST(Receipt, Empty)
{
	Receipt receipt;

	const std::unordered_set<ReceiptItem> & receiptItems = receipt.getItems();
	const std::unordered_set<ReceiptItem> & receiptItemsDiscounted = receipt.getItemsDiscounted();

	EXPECT_EQ(receiptItems.size(), 0);
	EXPECT_EQ(receiptItemsDiscounted.size(), 0);

	EXPECT_DOUBLE_EQ(receipt.computeTotalUndiscounted(), 0.);
	EXPECT_DOUBLE_EQ(receipt.computeTotalDiscount(), 0.);
	EXPECT_DOUBLE_EQ(receipt.computeTotal(), 0.);
}

TEST(Receipt, Total_Items)
{
	Receipt receipt;

	receipt.addItemsUndiscounted({ ReceiptItem("Item1", 1, 1.5) });
	receipt.addItemsUndiscounted({ ReceiptItem("Item2", 2, 2.5) });

	EXPECT_EQ(receipt.getItems().size(), 2);
	EXPECT_DOUBLE_EQ(receipt.computeTotal(), 6.5);
	EXPECT_DOUBLE_EQ(receipt.computeTotalUndiscounted(), 6.5);
}

TEST(Receipt, Total_ItemsAndItemsDiscounted)
{
	Receipt receipt;

	receipt.addItemsUndiscounted({ ReceiptItem("Item1", 1, 1.5) });

	receipt.addItemsDiscounted({ ReceiptItem("Item2", 2, 2.5) });

	EXPECT_EQ(receipt.getItems().size(), 2);
	EXPECT_EQ(receipt.getItemsDiscounted().size(), 1);

	EXPECT_DOUBLE_EQ(receipt.computeTotal(), 1.5);
	EXPECT_DOUBLE_EQ(receipt.computeTotalUndiscounted(), 6.5);
	EXPECT_DOUBLE_EQ(receipt.computeTotalDiscount(), 5.);
}

} // namespace supermarket