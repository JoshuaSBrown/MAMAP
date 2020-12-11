#include "mamap/arguments/properties/propertyobject.hpp"

namespace mamap {

std::any all_convert_(Option option,std::map<Option, std::any> options) {
  return options.at(option);
}

}
