#pragma once

#include "ProductCatalog.fwd.hpp"

namespace supermarket {

class ProductCatalogFiller
{
public:
	virtual void fillProductCatalog(ProductCatalog & producCatalog) const = 0;
};

} // namespace supermarket