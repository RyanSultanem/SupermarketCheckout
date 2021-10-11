#pragma once

#include "InteractionHelper.hpp"

class DefaultInteraction : public InteractionHelper
{
public:
	Supermarket constructSupermarket() const;
	ProductsCount constructCustomerOrder(const ProductCatalog & productCatalog) const;
};

