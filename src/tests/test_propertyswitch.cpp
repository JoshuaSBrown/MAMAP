
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "arguments/properties/propertyswitch.hpp"
#include <cassert>
#include <exception>
#include <iostream>
#include <string>
#include <vector>

using namespace mamap;
using namespace std;

TEST_CASE("Property Switch","[unit]") {

  cerr << "Testing: PropertySwitch" << endl;
  cerr << "Testing: constructor" << endl;
  { PropertySwitch propSwitch; }

  cerr << "Testing: getPropertyName" << endl;
  {
    PropertySwitch propSwitch;
    PropertyType type = propSwitch.getPropertyType();
    REQUIRE(type == PropertyType::SWITCH);
  }

  cerr << "Testing: getPropertyOptions" << endl;
  {

    PropertySwitch propSwitch;
    auto options = propSwitch.getPropertyOptions();
    Option opt = options.at(0);
    REQUIRE(opt == Option::DEFAULT);
  }

  cerr << "Testing: propValid" << endl;
  {
    PropertySwitch propSwitch;
    CHECK(propSwitch.propValid(0));
    CHECK(propSwitch.propValid(1));
    CHECK(propSwitch.propValid());
    CHECK_THROWS(propSwitch.propValid(-1));
    CHECK_THROWS(propSwitch.propValid(2));
    CHECK(propSwitch.propValid("ON"));
    CHECK(propSwitch.propValid("OFF"));
    CHECK(propSwitch.propValid("TRUE"));
    CHECK(propSwitch.propValid("FALSE"));
    CHECK(propSwitch.propValid("0"));
    CHECK(propSwitch.propValid("1"));
  }

  cerr << "Testing: setPropOption" << endl;
  {
    PropertySwitch propSwitch;
    propSwitch.setPropOption(Option::DEFAULT, "ON");
    propSwitch.setPropOption(Option::DEFAULT, "OFF");
    CHECK(propSwitch.propValid(0));
    CHECK_THROWS(propSwitch.propValid(-1));
  }
}
