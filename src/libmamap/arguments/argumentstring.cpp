
#include "argumentstring.hpp"
#include "properties/propertystring.hpp"
#include "properties/propertystringchoice.hpp"
#include <iostream>

using namespace mamap;
using namespace std;

ArgumentString::ArgumentString(void) { 
  propobjs_.emplace_back(new PropertyString);
  propobjs_.emplace_back(new PropertyStringChoice);
}
