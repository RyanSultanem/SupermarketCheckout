#include "pch.h"

#include "../SupermarketCheckout/Product.hpp"
#include "../SupermarketCheckout/DiscountStrategy.hpp"

namespace supermarket {

TEST(DiscountIdenticalProducts, BasicTest)
{
	Product p1("P1", 1., true);
	Product p2("P2", 2., true);
	
	ProductsCount products;
	products[p1] = 5;
	products[p2] = 2;

	DiscountIdenticalItem discount(3);
	DiscountResults discountResult = discount.computeDiscounts(products);
	ProductsCount discountedProducts = discountResult.discountedProducts;

	EXPECT_EQ(discountedProducts.size(), 1);
	EXPECT_EQ(discountedProducts[p1], 1);
}

TEST(DiscountIdenticalProducts, NoDiscount)
{
	Product p1("P1", 1., true);
	Product p2("P2", 2., true);

	ProductsCount products;
	products[p1] = 3;
	products[p2] = 2;

	DiscountIdenticalItem discount(5);
	DiscountResults discountResult = discount.computeDiscounts(products);
	ProductsCount discountedProducts = discountResult.discountedProducts;

	EXPECT_EQ(discountedProducts.size(), 0);
}

TEST(DiscountIdenticalProducts, SameDiscountAppliedTwiceOnSameProduct)
{
	Product p1("P1", 1., true);

	ProductsCount products;
	products[p1] = 5;

	DiscountIdenticalItem discount(2);
	DiscountResults discountResult = discount.computeDiscounts(products);
	ProductsCount discountedProducts = discountResult.discountedProducts;

	EXPECT_EQ(discountedProducts.size(), 1);
	EXPECT_EQ(discountedProducts[p1], 2);
}

TEST(DiscountIdenticalProducts, AppliedOnTwoDifferentProducts)
{
	Product p1("P1", 1., true);
	Product p2("P2", 2., true);

	ProductsCount products;
	products[p1] = 5;
	products[p2] = 2;

	DiscountIdenticalItem discount(2);
	DiscountResults discountResult = discount.computeDiscounts(products);
	ProductsCount discountedProducts = discountResult.discountedProducts;

	EXPECT_EQ(discountedProducts.size(), 2);
	EXPECT_EQ(discountedProducts[p1], 2);
	EXPECT_EQ(discountedProducts[p2], 1);
}

TEST(DiscountBasedOnItemCount, BasicTest)
{
	Product p1("P1", 4., true);
	Product p2("P2", 2., true);
	Product p3("P3", 3., true);

	ProductsCount products;
	products[p1] = 1;
	products[p2] = 1;
	products[p3] = 1;

	DiscountItemCount discount(3);
	DiscountResults discountResult = discount.computeDiscounts(products);
	ProductsCount discountedProducts = discountResult.discountedProducts;

	EXPECT_EQ(discountedProducts.size(), 1);
	EXPECT_EQ(discountedProducts[p2], 1);
}

TEST(DiscountBasedOnItemCount, NoDiscount)
{
	Product p1("P1", 4., true);
	Product p2("P2", 2., true);

	ProductsCount products;
	products[p1] = 1;
	products[p2] = 1;

	DiscountItemCount discount(3);
	DiscountResults discountResult = discount.computeDiscounts(products);
	ProductsCount discountedProducts = discountResult.discountedProducts;

	EXPECT_EQ(discountedProducts.size(), 0);
}

TEST(DiscountBasedOnItemCount, DiscountAppliedTwice)
{
	Product p1("P1", 4., true);
	Product p2("P2", 2., true);
	Product p3("P3", 3., true);

	ProductsCount products;
	products[p1] = 3;
	products[p2] = 1;
	products[p3] = 4;

	DiscountItemCount discount(3);
	DiscountResults discountResult = discount.computeDiscounts(products);
	ProductsCount discountedProducts = discountResult.discountedProducts;

	EXPECT_EQ(discountedProducts.size(), 2);
	EXPECT_EQ(discountedProducts[p2], 1);
	EXPECT_EQ(discountedProducts[p3], 1);
}

TEST(DiscountComposite, Basic_IdenticalItems_and_ItemCount)
{
	Product p1("P1", 1., true);
	Product p2("P2", 2., true);
	Product p3("P3", 3., true);

	ProductsCount products;
	products[p1] = 2;
	products[p2] = 3;
	products[p3] = 1;
	
	DiscountComposite discount;
	discount.addStrategy(DiscountStrategyType::IdenticalItems, 3);
	discount.addStrategy(DiscountStrategyType::ItemCount, 3);

	DiscountResults discountResult = discount.computeDiscounts(products);
	ProductsCount discountedProducts = discountResult.discountedProducts;

	EXPECT_EQ(discountedProducts.size(), 2);
	EXPECT_EQ(discountedProducts[p1], 1);
	EXPECT_EQ(discountedProducts[p2], 1);
}

TEST(DiscountComposite, EmptyDiscountComposite)
{
	Product p1("P1", 1., true);
	ProductsCount products;
	products[p1] = 2;

	DiscountComposite discount;
	DiscountResults discountResult = discount.computeDiscounts(products);
	ProductsCount discountedProducts = discountResult.discountedProducts;

	EXPECT_EQ(discountedProducts.size(), 0);
}

TEST(DiscountComposite, IdenticalItemsAppliedTwice_and_ItemCountAppliedTwice)
{
	Product p1("P1", 1., true);
	Product p2("P2", 2., true);
	Product p3("P3", 3., true);
	Product p4("P4", 4., true);
	Product p5("P5", 5., true);
	Product p6("P6", 6., true);

	ProductsCount products;
	products[p1] = 3;
	products[p2] = 1;
	products[p3] = 2;
	products[p4] = 1;
	products[p5] = 2;
	products[p6] = 3;

	DiscountComposite discount;
	discount.addStrategy(DiscountStrategyType::ItemCount, 3);
	discount.addStrategy(DiscountStrategyType::IdenticalItems, 3);

	DiscountResults discountResult = discount.computeDiscounts(products);
	ProductsCount discountedProducts = discountResult.discountedProducts;

	EXPECT_EQ(discountedProducts.size(), 4);
	EXPECT_EQ(discountedProducts[p1], 1);
	EXPECT_EQ(discountedProducts[p2], 1);
	EXPECT_EQ(discountedProducts[p3], 1);
	EXPECT_EQ(discountedProducts[p6], 1);
}

TEST(DiscountComposite, IdenticalItems_and_ItemCount_SameProductUsedInBoth)
{
	Product p1("P1", 1., true);
	Product p2("P2", 2., true);

	ProductsCount products;
	products[p1] = 7;
	products[p2] = 2;

	DiscountComposite discount;
	discount.addStrategy(DiscountStrategyType::ItemCount, 3);
	discount.addStrategy(DiscountStrategyType::IdenticalItems, 3);

	DiscountResults discountResult = discount.computeDiscounts(products);
	ProductsCount discountedProducts = discountResult.discountedProducts;

	EXPECT_EQ(discountedProducts.size(), 1);
	EXPECT_EQ(discountedProducts[p1], 3);
}

TEST(DiscountComposite, IdenticalItems_and_ItemCount_OnlyOneApplied)
{
	Product p1("P1", 1., true);
	Product p2("P2", 2., true);

	ProductsCount products;
	products[p1] = 4;
	products[p2] = 1;

	DiscountComposite discount;
	discount.addStrategy(DiscountStrategyType::ItemCount, 3);
	discount.addStrategy(DiscountStrategyType::IdenticalItems, 3);

	DiscountResults discountResult = discount.computeDiscounts(products);
	ProductsCount discountedProducts = discountResult.discountedProducts;

	EXPECT_EQ(discountedProducts.size(), 1);
	EXPECT_EQ(discountedProducts[p1], 1);
}

TEST(DiscountComposite, IdenticalItems_Only_ThroughComposite)
{
	Product p1("P1", 1., true);
	Product p2("P2", 2., true);

	ProductsCount products;
	products[p1] = 4;
	products[p2] = 1;

	DiscountComposite discount;
	discount.addStrategy(DiscountStrategyType::IdenticalItems, 3);

	DiscountResults discountResult = discount.computeDiscounts(products);
	ProductsCount discountedProducts = discountResult.discountedProducts;

	EXPECT_EQ(discountedProducts.size(), 1);
	EXPECT_EQ(discountedProducts[p1], 1);
}

TEST(DiscountComposite, IdenticalItems_throughComposite)
{
	Product p1("P1", 1., true);
	Product p2("P2", 2., true);

	ProductsCount products;
	products[p1] = 3;
	products[p2] = 3;

	DiscountComposite discount;
	discount.addStrategy(DiscountStrategyType::IdenticalItems, 3);
	
	DiscountResults discountResult = discount.computeDiscounts(products);
	ProductsCount discountedProducts = discountResult.discountedProducts;

	EXPECT_EQ(discountedProducts.size(), 2);
	EXPECT_EQ(discountedProducts[p1], 1);
	EXPECT_EQ(discountedProducts[p2], 1);
}

TEST(DiscountComposite, EmptyProducts)
{
	ProductsCount products;
	DiscountComposite discount;
	discount.addStrategy(DiscountStrategyType::IdenticalItems, 3);
	discount.addStrategy(DiscountStrategyType::ItemCount, 3);

	DiscountResults discountResult = discount.computeDiscounts(products);
	ProductsCount discountedProducts = discountResult.discountedProducts;

	EXPECT_EQ(discountedProducts.size(), 0);
}

} // namespace supermarket