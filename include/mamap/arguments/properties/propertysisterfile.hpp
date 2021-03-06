
#ifndef _MAMAP_PROPERTY_SISTER_FILE_HPP
#define _MAMAP_PROPERTY_SISTER_FILE_HPP

#include "propertyobject.hpp"
#include <vector>

namespace mamap {

class PropertySisterFile
    : public PropertyObject {
 private:
  bool fileExist(const std::string &) const;
  void extSupported(const std::string &) const;
  void checkExt(const std::string &) const;

  virtual PropertyType getPropertyType_(void) const noexcept final {
    return PropertyType::SISTER_FILE;
  }

 public:

  PropertySisterFile(void);

  virtual bool propValid(const std::any &fileNamePath) final;

};

}  // namespace mamap
#endif  // _MAMAP_PROPERTY_SISTER_FILE_HPP
