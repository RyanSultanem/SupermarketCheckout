#include "pch.h"

#include "../SupermarketCheckout/ProductCatalog.hpp"

namespace supermarket {

TEST(ProductCatalog, AddingItems)
{
	Product p1("P1", 1., true);
	Product p2("P2", 2., false);

	ProductCatalog catalog;

	catalog.addProduct(p1, 5);
	catalog.addProduct(p2, 3);
	catalog.addProduct(p2, 3);

	auto itBegin = catalog.begin();
	auto itEnd = catalog.end();

	EXPECT_EQ(std::distance(itBegin, itEnd), 2);
	EXPECT_EQ(catalog.procutCount(p1), 5);
	EXPECT_EQ(catalog.procutCount(p2), 6);
}

TEST(ProductCatalog, RemovingItems)
{
	Product p1("P1", 1., true);
	Product p2("P2", 2., false);
	Product p3("P3", 3., true);

	ProductCatalog catalog;

	catalog.addProduct(p1, 5);
	catalog.addProduct(p2, 6);

	bool result1 = catalog.removeProduct(p1, 3);
	bool result2 = catalog.removeProduct(p2, 4);
	bool result3 = catalog.removeProduct(p2, 3);
	bool result4 = catalog.removeProduct(p3, 1);

	EXPECT_TRUE(result1);
	EXPECT_TRUE(result2);
	EXPECT_FALSE(result3);
	EXPECT_FALSE(result4);

	EXPECT_EQ(catalog.procutCount(p1), 2);
	EXPECT_EQ(catalog.procutCount(p2), 2);
}

} // namespace supermarket