#pragma once

#include "../SupermarketCheckout/Supermarket.hpp"

#include <memory>

enum class InteractionMode
{
	Default = 1,
	Manual = 2,
	File = 3
};

class InteractionHelper
{
public:
	virtual supermarket::Supermarket constructSupermarket() const = 0;
	virtual supermarket::ProductsCount constructCustomerOrder(const supermarket::ProductCatalog & productCatalog) const = 0;

	virtual ~InteractionHelper() = default;
};

std::unique_ptr<InteractionHelper> constructInteractionHelper(InteractionMode interactionMode);