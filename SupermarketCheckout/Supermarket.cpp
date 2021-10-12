#include "Supermarket.hpp"

#include "ProductCatalogFiller.hpp"
#include "Product.hpp"
#include "ReceiptHelper.hpp"

namespace supermarket {

Supermarket::Supermarket(const std::vector<std::pair<DiscountStrategyType, int>> & discountStrategyInfos)
{
    for (auto & discountStrategyInfo : discountStrategyInfos)
        m_discountManager.addDiscountStrategy(discountStrategyInfo.first, discountStrategyInfo.second);
}

Receipt Supermarket::checkout(const ProductsCount & customerItems)
{
    if (!m_catalog.hasProducts(customerItems))
    {
        // Inconsistent Data, should either throw an exception or send an error.
        return Receipt();
    }
    removeProductsFromCatalog(customerItems);

    ProductsCount discountedProducts = m_discountManager.computeDiscount(customerItems);
    Receipt receipt = constructReceiptFromProducts(customerItems, discountedProducts);
    // Save Receipt History
    bookReceit(receipt);

    return receipt;
}

const ProductCatalog & Supermarket::productCatalog() const
{
    return m_catalog;
}

void Supermarket::fillProducts(const ProductCatalogFiller & filler)
{
    filler.fillProductCatalog(m_catalog);
}

void Supermarket::bookReceit(const Receipt & receipt)
{
    m_receiptHistory.push_back(receipt);
}

void Supermarket::removeProductsFromCatalog(const ProductsCount & products)
{
    m_catalog.removeProducts(products);
}

} // namespace supermarket