
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "arguments/properties/propertystringchoice.hpp"
#include <cassert>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace mamap;
using namespace std;

TEST_CASE("Property String Choice","[unit]") {
  { PropertyStringChoice propStrChoice; }
}

TEST_CASE("getPropertyType","[unit]") { 
  PropertyStringChoice propStrChoice;
  PropertyType type = propStrChoice.getPropertyType();
  REQUIRE(type == PropertyType::STRING_CHOICE);
}

TEST_CASE("getPropertyOptions","[unit]") { 

  PropertyStringChoice propStrChoice;
  auto options = propStrChoice.getPropertyOptions();

  bool choice_enforced = false;
  bool str_choices = false;

  for (auto opt : options) {
    if (opt == Option::ENFORCED) {
      choice_enforced = true;
    }
    if (opt == Option::ALLOWED_VALUES) {
      str_choices = true;
    }
  }
  REQUIRE(choice_enforced);
  REQUIRE(str_choices);
}

TEST_CASE("getPropOption","[unit]"){ 
  PropertyStringChoice propStrChoice;

  set<string> choice_enforced =
    propStrChoice.getPropOption<set<string>>(Option::ENFORCED);
  set<string> choices = propStrChoice.getPropOption<set<string>>(Option::ALLOWED_VALUES);

  string enforced = *(choice_enforced.begin());
 
  std::cout << "Enforced " << enforced << std::endl; 
  //REQUIRE(enforced == false);
}

TEST_CASE("setPropOption", "[unit]"){
  PropertyStringChoice propStrChoice;

  std::cout << "1a" << std::endl;
  propStrChoice.setPropOption(Option::ENFORCED, std::string("true"));
  set<string> choices{"true", "false"};
  for ( string test : choices ) {
    std::cout << "Order of set " << test << std::endl;
  }
  std::cout << "2a" << std::endl;
  propStrChoice.setPropOption(Option::ALLOWED_VALUES, choices);

  string choice = "true";
  std::cout << "3a" << std::endl;
  propStrChoice.propValid(choice);
  choice = "false";
  propStrChoice.propValid(choice);

  choice = "blah";
  REQUIRE_THROWS(propStrChoice.propValid(choice));

  set<string> allowed_choices = propStrChoice.getPropOption<set<string>>(Option::ALLOWED_VALUES);
  set<string> choice_on =
    propStrChoice.getPropOption<set<string>>(Option::ALLOWED_VALUES);

  bool false_str = false;
  bool true_str = false;
  for (auto item : allowed_choices) {
    if (item.compare("false") == 0) false_str = true;
    if (item.compare("true") == 0) true_str = true;
  }
  REQUIRE(false_str);
  REQUIRE(true_str);

  string on = *(choice_on.begin());
  std::cout << "on " << on << std::endl;
  REQUIRE(on == "false");
}
