
#ifndef _MAMAP_PROPERTY_STRING_HPP
#define _MAMAP_PROPERTY_STRING_HPP

#include "propertyobject.hpp"

namespace mamap {

class PropertyString : public PropertyObject {

  private: 
    virtual PropertyType getPropertyType_(void) const noexcept final {
      return PropertyType::STRING;
    }

 public:
  PropertyString(void);

  virtual bool propValid(const std::any& val) final;
};

}  // namespace mamap
#endif  // _MAMAP_PROPERTY_STRING_HPP
