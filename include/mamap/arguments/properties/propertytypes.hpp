
#ifndef _MAMAP_PROPERTY_TYPES_HPP
#define _MAMAP_PROPERTY_TYPES_HPP

#include <string>

namespace mamap {

  enum class PropertyType {
    UNKNOWN,
    NUMERIC,
    FILE_EXISTS,
    FILE_EXT,
    SISTER_FILE,
    STRING,
    STRING_CHOICE,
    SWITCH
  };

  std::string operator+(std::string str, const PropertyType prop);

}  // namespace mamap
#endif  // _MAMAP_PROPERTY_TYPES_HPP
