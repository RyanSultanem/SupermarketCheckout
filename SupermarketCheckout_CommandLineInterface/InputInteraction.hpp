#pragma once

#include "InteractionHelper.hpp"

class CLIInputInteraction : public InteractionHelper
{
public:
	supermarket::Supermarket constructSupermarket() const;
	supermarket::ProductsCount constructCustomerOrder(const supermarket::ProductCatalog & productCatalog) const;
};

class FileInputInteraction : public InteractionHelper
{
public:
	supermarket::Supermarket constructSupermarket() const;
	supermarket::ProductsCount constructCustomerOrder(const supermarket::ProductCatalog & productCatalog) const;
};