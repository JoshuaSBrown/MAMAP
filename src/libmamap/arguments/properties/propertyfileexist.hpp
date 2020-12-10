
#ifndef _MAMAP_PROPERTY_FILEEXIST_HPP
#define _MAMAP_PROPERTY_FILEEXIST_HPP

#include "propertyobject.hpp"
#include <set>

namespace mamap {

class PropertyFileExist : public PropertyObject {
 private:
  bool fileExist(const std::string &) const;

  virtual PropertyType getPropertyType_() const noexcept final {
    return PropertyType::FILE_EXISTS;
  }

 public:
  explicit PropertyFileExist(void);
  PropertyFileExist(bool fileMustExist);

  virtual bool propValid(const std::any &fileName) final;

  void postCheck(void) const final;
};

}  // namespace mamap

#endif  // _MAMAP_PROPERTY_FILEEXIST_HPP
