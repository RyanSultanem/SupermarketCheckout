#include "ReceiptHelper.hpp"

#include "Utility.hpp"

namespace supermarket {

static std::unordered_set<ReceiptItem> constructReceiptItemList(const ProductsCount & products)
{
    std::unordered_set<ReceiptItem> receiptItems;
    receiptItems.reserve(products.size());

    for (auto & productCount : products)
    {
        const Product & product = productCount.first;
        receiptItems.insert(ReceiptItem(product.name(), productCount.second, product.unitPrice()));
    }

    return receiptItems;
}

Receipt constructReceiptFromProducts(const ProductsCount & products, const ProductsCount & discountedProducts)
{
    ProductsCount nonDiscountedProducts = products;
    utility::mapRemoveOtherMap(nonDiscountedProducts, discountedProducts);

    Receipt receipt;

    receipt.addItemsUndiscounted(constructReceiptItemList(nonDiscountedProducts));
    receipt.addItemsDiscounted(constructReceiptItemList(discountedProducts));

    return receipt;
}

} // namespace supermarket