#include "Receipt.hpp"

#include <numeric>

namespace supermarket {

double ReceiptItem::computeTotal() const
{
    return m_unitPrice * m_itemCount;
}

const std::vector<ReceiptItem> Receipt::getItems() const
{
    return m_items;
}

const std::vector<ReceiptItem> Receipt::getItemsDiscounted() const
{
    return m_itemsDiscounted;
}

void Receipt::addItems(const std::vector<ReceiptItem> & items)
{
    m_items.insert(m_items.end(), items.begin(), items.end());
}

void Receipt::addItemsDiscounted(const std::vector<ReceiptItem> & itemsDiscounted)
{
    // To ensure allignement, always add the complement of the discounted element.
    addItems(itemsDiscounted);
    m_itemsDiscounted.insert(m_itemsDiscounted.end(), itemsDiscounted.begin(), itemsDiscounted.end());
}

static double computeReceiptItemsTotal(const std::vector<ReceiptItem> & receiptItems)
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