#pragma once

#include <string>
#include <unordered_map>

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

typedef std::unordered_map<Product, int> ProductsCount;

namespace std {

template<>
struct hash<Product>
{
	std::size_t operator()(const Product & product) const
	{
		return (hash<string>()(product.name())
			 + hash<double>()(product.unitPrice())
			 + product.qualifyForDiscount() ? 1 : -1);
	}
};

} // namespace std
