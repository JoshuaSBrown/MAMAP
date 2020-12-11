
#include "mamap/arguments/argumentfile.hpp"
#include "mamap/arguments/properties/propertyfileexist.hpp"
#include "mamap/arguments/properties/propertyfileext.hpp"
#include "mamap/arguments/properties/propertysisterfile.hpp"
#include <iostream>

using namespace mamap;
using namespace std;

ArgumentFile::ArgumentFile(void) { 
  propobjs_.emplace_back(new PropertyFileExist());
  propobjs_.emplace_back(new PropertyFileExt());
  propobjs_.emplace_back(new PropertySisterFile());

}
