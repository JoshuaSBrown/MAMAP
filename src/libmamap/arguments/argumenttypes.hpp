
#ifndef _MAMAP_ARGUMENTTYPE_HPP
#define _MAMAP_ARGUMENTTYPE_HPP

#include <string>

namespace mamap {

  enum class ArgumentType {
    NUMERIC,
    FILES,
    STRING,
    SWITCH
  };

  std::string operator+(std::string str, const ArgumentType arg);
}  // namespace mamap
#endif  // _MAMAP_ARGUMENTTYPE_HPP
