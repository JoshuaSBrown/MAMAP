
#include "mamap/arguments/argumentnumerical.hpp"
#include "mamap/arguments/properties/propertynumeric.hpp"
#include <iostream>
#include <memory>

using namespace mamap;
using namespace std;

ArgumentNumerical::ArgumentNumerical(void) { 
  propobjs_.emplace_back(new PropertyNumeric());
}

