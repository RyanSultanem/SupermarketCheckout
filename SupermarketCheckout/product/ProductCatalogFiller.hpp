#pragma once

#include "ProductCatalog.fwd.hpp"

namespace supermarket {

/// <summary>
/// An interface that exposes a product catalog to be filled. 
/// </summary>
class ProductCatalogFiller
{
public:
	virtual void fillProductCatalog(ProductCatalog & producCatalog) const = 0;
};

} // namespace supermarket