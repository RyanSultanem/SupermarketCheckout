#pragma once

#include "InteractionHelper.hpp"

class CLIInputInteraction : public InteractionHelper
{
public:
	Supermarket constructSupermarket() const;
	ProductsCount constructCustomerOrder(const ProductCatalog & productCatalog) const;
};

