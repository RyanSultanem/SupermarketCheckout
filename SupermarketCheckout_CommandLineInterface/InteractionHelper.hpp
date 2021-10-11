#pragma once

#include "../SupermarketCheckout/Supermarket.hpp"

#include <memory>

enum class InteractionMode
{
	Default = 1,
	Custmoize = 2,
	File = 3
};

class InteractionHelper
{
public:
	virtual Supermarket constructSupermarket() const = 0;
	virtual ProductsCount constructCustomerOrder(const ProductCatalog & productCatalog) const = 0;

	virtual ~InteractionHelper() = default;
};

std::unique_ptr<InteractionHelper> constructInteractionHelper(InteractionMode interactionMode);