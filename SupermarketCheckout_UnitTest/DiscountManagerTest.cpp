#include "pch.h"

#include "../SupermarketCheckout/DiscountManager.hpp"

namespace supermarket {

TEST(DiscountManager, Simple_OnlyElligibleProducts)
{
	Product p1("P1", 1., true);
	
	ProductsCount products;
	products[p1] = 3;

	DiscountManager manager;
	manager.addDiscountStrategy(DiscountStrategyType::IdenticalItems, 2);

	ProductsCount discountedProducts = manager.computeDiscount(products);

	EXPECT_EQ(discountedProducts.size(), 1);
	EXPECT_EQ(discountedProducts[p1], 1);
}

TEST(DiscountManager, Simple_OnlyNonElligibleProducts)
{
	Product p1("P1", 1., false);

	ProductsCount products;
	products[p1] = 3;

	DiscountManager manager;
	manager.addDiscountStrategy(DiscountStrategyType::IdenticalItems, 2);

	ProductsCount discountedProducts = manager.computeDiscount(products);

	EXPECT_EQ(discountedProducts.size(), 0);
}

TEST(DiscountManager, OnlyAffectElligibleProducts)
{
	Product p1("P1", 1., true);
	Product p2("P2", 2., false);

	ProductsCount products;
	products[p1] = 3;
	products[p2] = 3;

	DiscountManager manager;
	manager.addDiscountStrategy(DiscountStrategyType::IdenticalItems, 2);

	ProductsCount discountedProducts = manager.computeDiscount(products);

	EXPECT_EQ(discountedProducts.size(), 1);
	EXPECT_EQ(discountedProducts[p1], 1);
}

} // namespace supermarket