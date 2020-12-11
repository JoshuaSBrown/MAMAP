
#ifndef _MAMAP_ARGUMENT_FILE_HPP
#define _MAMAP_ARGUMENT_FILE_HPP

#include "argumentobject.hpp"
#include <set>

namespace mamap {

class ArgumentFile : public ArgumentObject {

 public:

  virtual ArgumentType getArgumentType(void) const noexcept final {
    return ArgumentType::FILES;
  }

  virtual std::type_index getValueType(void) const noexcept final { 
    return typeid(std::string);
  }

  ArgumentFile(void);
};

}  // namespace mamap

#endif  // _MAMAP_ARGUMENT_FILE_HPP
