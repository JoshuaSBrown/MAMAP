
#ifndef _MAMAP_PROPERTY_NUMERIC_HPP
#define _MAMAP_PROPERTY_NUMERIC_HPP

#include "propertyobject.hpp"

#include <any>
#include <limits>

namespace mamap {

class PropertyNumeric : public PropertyObject {

  // Override the setting make sure that a double is passed in as the numeric type
  //virtual void setPropOption_(const Option & option, const std::any & val) final;

  virtual PropertyType getPropertyType_(void) const noexcept final {
    return PropertyType::NUMERIC;
  }

 public:
  PropertyNumeric(void);

  virtual bool propValid(const std::any& value) final;
};

}  // namespace mamap

#endif  // _MAMAP_PROPERTY_NUMERIC_HPP
