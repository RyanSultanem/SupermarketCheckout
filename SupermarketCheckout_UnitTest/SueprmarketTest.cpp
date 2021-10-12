#include "pch.h"

#include "../SupermarketCheckout/Supermarket.hpp"
#include "../SupermarketCheckout/ProductCatalogFiller.hpp"

namespace supermarket {

struct TestGlobalData
{
	Product p1 = Product("P1", 1., true);
	Product p2 = Product("P2", 2., false);
	Product p3 = Product("P3", 3., false);
	Product p4 = Product("P4", 4., true);
	Product p5 = Product("P5", 5., true);
};

const TestGlobalData data;

class DefaultProductCatalogFiller : public ProductCatalogFiller
{
public:
	void fillProductCatalog(ProductCatalog & producCatalog) const override
	{
		producCatalog.addProduct(data.p1, 10);
		producCatalog.addProduct(data.p2, 10);
		producCatalog.addProduct(data.p3, 10);
		producCatalog.addProduct(data.p4, 10);
		producCatalog.addProduct(data.p5, 10);
	}
};

static Supermarket constructSupermarketTest()
{
	std::vector<DiscountStrategyInfo> strategyInfos;
	strategyInfos.push_back({ DiscountStrategyType::IdenticalItems, 3 });
	strategyInfos.push_back({ DiscountStrategyType::ItemCount,3 });

	Supermarket supermarket(strategyInfos);
	supermarket.fillProducts(DefaultProductCatalogFiller());

	return supermarket; 
}

TEST(Supermarket, OrderProducesReceiptWithTotalAndDiscount)
{
	Supermarket supermarket = constructSupermarketTest();

	ProductsCount order;
	order[data.p1] = 3;
	order[data.p2] = 3;
	order[data.p3] = 1;
	order[data.p4] = 1;
	order[data.p5] = 8;

	Receipt receipt = supermarket.checkout(order);

	// undiscountedTotal = sum(pi, order[pi])
	double undiscountedTotal = (1 * 3.) + (3 * 2.) + (1 * 3.) + (1 * 4.) + (8 * 5.);
	// discounted Items = 1 p1 + 1 p4 + 2 p5
	double discountedTotal = 1. + 4. + (2 * 5.);

	EXPECT_DOUBLE_EQ(receipt.computeTotalUndiscounted(), undiscountedTotal);
	EXPECT_DOUBLE_EQ(receipt.computeTotalDiscount(), discountedTotal);
	EXPECT_DOUBLE_EQ(receipt.computeTotal(), undiscountedTotal - discountedTotal);
}

TEST(Supermarket, OrderNotPresentInSupermarket_EmptyReceipt)
{
	Supermarket supermarket = constructSupermarketTest();

	ProductsCount order;
	order[data.p1] = 5;
	order[data.p2] = 12;

	Receipt receipt = supermarket.checkout(order);

	EXPECT_EQ(receipt.getItems().size(), 0);
	EXPECT_EQ(receipt.computeTotal(), 0);
}

TEST(Supermarket, SameOrderTwice_SecondOrderShouldFail)
{
	Supermarket supermarket = constructSupermarketTest();

	ProductsCount order;
	order[data.p1] = 6;
	order[data.p2] = 6;

	Receipt receipt1 = supermarket.checkout(order);
	Receipt receipt2 = supermarket.checkout(order);

	EXPECT_NE(receipt1.getItems().size(), 0);
	EXPECT_NE(receipt1.computeTotal(), 0);

	EXPECT_EQ(receipt2.getItems().size(), 0);
	EXPECT_EQ(receipt2.computeTotal(), 0);
}

} // namespace supermarket