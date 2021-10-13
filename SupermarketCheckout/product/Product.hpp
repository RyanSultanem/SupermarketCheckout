#pragma once

#include <string>
#include <unordered_map>

namespace supermarket {

/// <summary>
///  A structure containing the product name, the unit price, and whether the product is eligible for discounts or not. 
/// </summary>
class Product
{
public:
	Product() = default;

	Product(const std::string & name, double unitPrice, bool qualifyForDiscount)
		: m_name(name)
		, m_unitPrice(unitPrice)
		, m_qualifyForDiscount(qualifyForDiscount)
	{}

	const std::string & name() const;
	double unitPrice() const;
	bool qualifyForDiscount() const;

	bool operator==(const Product & other) const;

private:
	std::string m_name;
	double m_unitPrice = 0.;
	bool m_qualifyForDiscount = false;
};

/// <summary>
/// ProductsCount:
/// Type definition for an unordered_map of Products to count, marking a group of items of products. It is the main way to group the products in the overall library. 
/// </summary>
typedef std::unordered_map<Product, int> ProductsCount;

} // namespace supermarket

namespace std {

template<>
struct hash<supermarket::Product>
{
	std::size_t operator()(const supermarket::Product & product) const
	{
		return (hash<string>()(product.name())
			 + hash<double>()(product.unitPrice())
			 + product.qualifyForDiscount() ? 1 : -1);
	}
};

} // namespace std

