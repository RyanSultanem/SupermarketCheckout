#include "Receipt.hpp"

#include <numeric>

namespace supermarket {

double ReceiptItem::computeTotal() const
{
    return m_unitPrice * m_itemCount;
}

bool ReceiptItem::operator==(const ReceiptItem & other) const
{
    // Item count left out on purpose, part of the output.
    return m_productName == other.m_productName
        && m_unitPrice == other.m_unitPrice;
}

const std::unordered_set<ReceiptItem> Receipt::getItems() const
{
    return m_items;
}

const std::unordered_set<ReceiptItem> Receipt::getItemsDiscounted() const
{
    return m_itemsDiscounted;
}

static void addItemsInternal(std::unordered_set<ReceiptItem> & items, const std::unordered_set<ReceiptItem> & itemsToAdd)
{
    for (const ReceiptItem & itemToAdd : itemsToAdd)
    {
        auto it = items.find(itemToAdd);

        if (it == items.end())
        {
            items.insert(itemToAdd);
        }
        else
        {
            // In order not to have repeated items of the same product, we add up the counts
            const ReceiptItem & currentItem = *it;
            int newCount = currentItem.itemCount() + itemToAdd.itemCount();

            ReceiptItem newReceiptItem(currentItem.productName(), newCount, currentItem.unitPrice());
            // remove old receiptItem and add the new one
            items.erase(itemToAdd);
            items.insert(newReceiptItem);
        }
    }
}

void Receipt::addItemsUndiscounted(const std::unordered_set<ReceiptItem> & items)
{
    addItemsInternal(m_items, items);
}

void Receipt::addItemsDiscounted(const std::unordered_set<ReceiptItem> & itemsDiscounted)
{
    // To ensure allignement, always add the complement of the discounted element.
    addItemsInternal(m_items, itemsDiscounted);
    addItemsInternal(m_itemsDiscounted, itemsDiscounted);
}

static double computeReceiptItemsTotal(const std::unordered_set<ReceiptItem> & receiptItems)
{
    return std::accumulate(receiptItems.begin(), receiptItems.end(), 0.,
        [](double sum, const ReceiptItem & item)
        {
            return sum + item.computeTotal();
        });
}

double Receipt::computeTotal() const
{
    return computeTotalUndiscounted() - computeTotalDiscount();
}

double Receipt::computeTotalDiscount() const
{
    return computeReceiptItemsTotal(m_itemsDiscounted);
}

double Receipt::computeTotalUndiscounted() const
{
    return computeReceiptItemsTotal(m_items);
}

} // namespace supermarket