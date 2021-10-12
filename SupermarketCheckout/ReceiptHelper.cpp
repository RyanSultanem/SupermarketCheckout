#include "ReceiptHelper.hpp"

#include "Utility.hpp"

#include <algorithm>
#include <iterator>
#include <vector>

namespace supermarket {

static std::vector<ReceiptItem> constructReceiptItemList(const ProductsCount & products)
{
    std::vector<ReceiptItem> receiptItems;
    receiptItems.reserve(products.size());

    std::transform(products.begin(), products.end(), std::back_inserter(receiptItems),
        [](const std::pair<Product, int> productCount)
        {
            const Product & product = productCount.first;
            return ReceiptItem(product.name(), productCount.second, product.unitPrice());
        });

    return receiptItems;
}

Receipt constructReceiptFromProducts(const ProductsCount & products, const ProductsCount & discountedProducts)
{
    ProductsCount nonDiscountedProducts = products;
    utility::mapRemoveOtherMap(nonDiscountedProducts, discountedProducts);

    Receipt receipt;

    receipt.addItems(constructReceiptItemList(nonDiscountedProducts));
    receipt.addItemsDiscounted(constructReceiptItemList(discountedProducts));

    return receipt;
}

} // namespace supermarket