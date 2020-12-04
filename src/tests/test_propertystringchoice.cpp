
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

  // Choice enforced can be returned as bool, an int or a string
  set<string> choice_enforced_str =
    propStrChoice.getPropOption<set<string>>(Option::ENFORCED);
  set<bool> choice_enforced_bool =
    propStrChoice.getPropOption<set<bool>>(Option::ENFORCED);
  set<int> choice_enforced_int =
    propStrChoice.getPropOption<set<int>>(Option::ENFORCED);
  set<string> choices = propStrChoice.getPropOption<set<string>>(Option::ALLOWED_VALUES);

  string enforced_str = *(choice_enforced_str.begin());
  bool enforced_bool = *(choice_enforced_bool.begin());
  int enforced_int = *(choice_enforced_int.begin());
 
  // By default enforced is set to false
  REQUIRE(enforced_str == "false");
  REQUIRE(enforced_bool == false);
  REQUIRE(enforced_int == 0);
  // By default there is a single choice
  REQUIRE(choices.size() == 1);
  // The value is set to "NOT_DEFINED"
  REQUIRE(*choices.begin() == "NOT_DEFINED");
  
}

TEST_CASE("setPropOption", "[unit]"){

  PropertyStringChoice propStrChoice;

  propStrChoice.setPropOption(Option::ENFORCED, std::string("true"));

  // Checking default values
  set<string> choice_enforced_str =
    propStrChoice.getPropOption<set<string>>(Option::ENFORCED);
  set<bool> choice_enforced_bool =
    propStrChoice.getPropOption<set<bool>>(Option::ENFORCED);
  set<int> choice_enforced_int =
    propStrChoice.getPropOption<set<int>>(Option::ENFORCED);

  string enforced_str = *(choice_enforced_str.begin());
  bool enforced_bool = *(choice_enforced_bool.begin());
  int enforced_int = *(choice_enforced_int.begin());
 
  // By default enforced is set to false
  REQUIRE(enforced_str == "true");
  REQUIRE(enforced_bool == true);
  REQUIRE(enforced_int == 1);

  set<string> choices{"true", "false"};
  propStrChoice.setPropOption(Option::ALLOWED_VALUES, choices);

  // true is a valid string choice
  string choice = "true";
  REQUIRE_NOTHROW(propStrChoice.propValid(choice));

  // False is a valid choice should not throw
  choice = "false";
  REQUIRE_NOTHROW(propStrChoice.propValid(choice));

  // blah is not a valid choice
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
  REQUIRE(on == "false");
}
