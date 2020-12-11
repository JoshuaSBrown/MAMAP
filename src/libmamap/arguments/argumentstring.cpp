
#include "mamap/arguments/argumentstring.hpp"
#include "mamap/arguments/properties/propertystring.hpp"
#include "mamap/arguments/properties/propertystringchoice.hpp"
#include <iostream>

using namespace mamap;
using namespace std;

ArgumentString::ArgumentString(void) { 
  propobjs_.emplace_back(new PropertyString);
  propobjs_.emplace_back(new PropertyStringChoice);
}
