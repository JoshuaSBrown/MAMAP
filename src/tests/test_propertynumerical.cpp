
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "arguments/properties/propertynumeric.hpp"
#include <exception>
#include <iostream>
#include <string>
#include <vector>

using namespace mamap;
using namespace std;

TEST_CASE("Property Numerical","[unit]") {

  cerr << "Testing: PropertyNumeric" << endl;
  cerr << "Testing: constructor" << endl;
  { PropertyNumeric propNumerical; }

  cerr << "Testing: getPropertyType" << endl;
  {
    PropertyNumeric propNumerical;
    PropertyType name = propNumerical.getPropertyType();
    CHECK(name == PropertyType::NUMERIC);
  }

  cerr << "Testing: getPropertyOptions" << endl;
  {

    PropertyNumeric propNumerical;
    auto options = propNumerical.getPropertyOptions();
    CHECK(options.at(0) == Option::MIN);
    CHECK(options.at(1) == Option::MAX);
  }

  cerr << "Testing: propValid" << endl;
  {
    PropertyNumeric propNumerical;
    CHECK(propNumerical.propValid(0));
  }

  cerr << "Testing: setPropOption" << endl;
  {
    PropertyNumeric propNumerical;
    propNumerical.setPropOption(Option::MIN, 0);
    propNumerical.propValid(0);
    CHECK_THROWS(propNumerical.propValid(-1));
    // Option is unsupported
    CHECK_THROWS(propNumerical.setPropOption(Option::ENFORCED, 3));
  }
}
