
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "arguments/properties/propertystring.hpp"
#include <cassert>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

using namespace mamap;
using namespace std;

TEST_CASE("Property String","[unit]") {

  cerr << "Testing: PropertyString" << endl;
  cerr << "Testing: constructor" << endl;
  { PropertyString propString; }

  cerr << "Testing: getPropertyName" << endl;
  {
    PropertyString propString;
    std::cout << __LINE__ << std::endl;
    PropertyType type = propString.getPropertyType();
    std::cout << __LINE__ << std::endl;
    REQUIRE(type == PropertyType::STRING);
  }

  cerr << "Testing: getPropertyOptions" << endl;
  {

    PropertyString propString;
    std::cout << __LINE__ << std::endl;
    auto options = propString.getPropertyOptions();
    std::cout << __LINE__ << std::endl;
    Option opt = options.at(0);
    std::cout << __LINE__ << std::endl;
    REQUIRE(opt == Option::MIN_LENGTH);
    opt = options.at(1);
    REQUIRE(opt == Option::MAX_LENGTH);
  }

  cerr << "Testing: propValid" << endl;
  {
    PropertyString propString;
    bool valid = propString.propValid("Hello");
    REQUIRE(valid);
  }

  cerr << "Testing: setPropOption" << endl;
  {
    PropertyString propString;
    size_t val = 3;
    std::cout << "1" << std::endl;
    propString.setPropOption(Option::MAX_LENGTH, val);
    std::cout << "2" << std::endl;
    propString.propValid("");
    std::cout << "3" << std::endl;
    CHECK_THROWS(propString.propValid("Hello"));
    
    val = 4;
    CHECK_THROWS(propString.setPropOption(Option::MAX, val));
  }
}
