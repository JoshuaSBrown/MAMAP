
#ifndef _MAMAP_PROPERTY_FILEEXT_HPP
#define _MAMAP_PROPERTY_FILEEXT_HPP

#include "propertyobject.hpp"
#include <set>

namespace mamap {

class PropertyFileExt
    : public PropertyObject {
 private:
  void checkExt(const std::string &) const;
  void extSupported(const std::string &) const;
  std::vector<std::string> getOpts_(void) const;

  virtual PropertyType getPropertyType_(void) const noexcept final {
    return PropertyType::FILE_EXT;
  }

 public:
  PropertyFileExt(void);

  explicit PropertyFileExt(std::string ext);
  PropertyFileExt(std::set<std::string> exts);

  virtual bool propValid(const std::any &fileNamePath) final;
  void setPropOption(Option option, std::string var);
  void setPropOption(Option option, std::set<std::string> var);
};

}  // namespace mamap
#endif  // _MAMAP_PROPERTY_FILEEXT_HPP
