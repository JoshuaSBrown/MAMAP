
#include "mamap/arguments/argumentswitch.hpp"
#include "mamap/arguments/properties/propertyswitch.hpp"
#include <iostream>

using namespace mamap;
using namespace std;

ArgumentSwitch::ArgumentSwitch(void) { 
  propobjs_.emplace_back(new PropertySwitch);
}

bool ArgumentSwitch::positive(string val) const {
  if (val.compare("ON") == 0 || val.compare("TRUE") == 0 ||
      val.compare("1") == 0) {
    return true;
  } else if (val.compare("OFF") == 0 || val.compare("FALSE") == 0 ||
             val.compare("0") == 0) {
    return false;
  }
  throw invalid_argument("Argument value is unrecognized " + val);
}
