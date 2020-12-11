
#ifndef _MAMAP_PROPERTY_OPTIONS_HPP
#define _MAMAP_PROPERTY_OPTIONS_HPP

#include <iostream>
#include <string>

namespace mamap {

enum class Option {
  NO_OPTIONS,
  MIN,
  MAX,
  MIN_LENGTH,
  MAX_LENGTH,
  MUST_EXIST,
  DOES_EXIST,
  ALLOWED_VALUES,
  ENFORCED,
  FILE_NAME,
  FILE_PATH,
  FILE_PATH_NAME,
  VALUE,
  DEFAULT
};

std::ostream& operator<<(std::ostream& out, const Option option);

std::string operator+(std::string str, const Option option);

}  // namespace mamap
#endif  // _MAMAP_PROPERTY_OPTIONS_HPP
