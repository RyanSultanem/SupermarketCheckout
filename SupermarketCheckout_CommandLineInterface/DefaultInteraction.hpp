#pragma once

#include "InteractionHelper.hpp"

class DefaultInteraction : public InteractionHelper
{
public:
	supermarket::Supermarket constructSupermarket() const;
	supermarket::ProductsCount constructCustomerOrder(const supermarket::ProductCatalog & productCatalog) const;
};

