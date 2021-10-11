#pragma once

#include "ProductCatalog.fwd.hpp"

class ProductCatalogFiller
{
public:
	virtual void fillProductCatalog(ProductCatalog & producCatalog) const = 0;
};