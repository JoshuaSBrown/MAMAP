
#ifndef _MAMAP_ARGUMENT_DOUBLE_HPP
#define _MAMAP_ARGUMENT_DOUBLE_HPP

#include "argumentobject.hpp"
#include <set>

namespace mamap {

class ArgumentNumerical : public ArgumentObject {
 private:
  std::string getName_(void) const { return "ARGUMENT_DOUBLE"; }
  void registerProperties_(void);

 public:

  virtual ArgumentType getArgumentType(void) const noexcept final 
  { return ArgumentType::NUMERICAL; }

  virtual std::type_index getValueType(void) const noexcept final {
    return typeid(double);
  }

  ArgumentNumerical(void);
};

}  // namespace mamap
#endif  // _MAMAP_ARGUMENT_DOUBLE_HPP
