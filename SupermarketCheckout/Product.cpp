#include "Product.hpp"

const std::string & Product::name() const
{
	return m_name;
}

double Product::unitPrice() const
{
	return m_unitPrice;
}

bool Product::qualifyForDiscount() const
{
	return m_qualifyForDiscount;
}

bool Product::operator==(const Product & other) const
{
	return m_name == other.m_name
		&& m_unitPrice == other.m_unitPrice
		&& m_qualifyForDiscount == other.m_qualifyForDiscount;
}
