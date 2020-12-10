
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "arguments/argumentstring.hpp"
#include <limits>

using namespace mamap;
using namespace std;

TEST_CASE("Argument String","[unit]"){

  cerr << "Testing: argumentstring" << endl;
  cerr << "Testing: constructor" << endl;
  { ArgumentString argString; }

  cerr << "Testing: getArgumentName" << endl;
  {
    ArgumentString argString;
    CHECK(argString.getArgumentType() == ArgumentType::STRING);
  }

  cerr << "Testing: getProperties" << endl;
  {
    ArgumentString argString;
    auto props = argString.getProperties();

    bool string_prop = false;
    bool string_choice = false;

    for (auto prop : props) {
      if (prop == PropertyType::STRING) {
        string_prop = true;
      }
      if (prop == PropertyType::STRING_CHOICE) {
        string_choice = true;
      }
    }
    CHECK(string_prop);
    CHECK(string_choice);
  }

  cerr << "Testing: getPropertyOptions" << endl;
  {
    ArgumentString argString;
    auto prop_opts = argString.getPropertyOptions();

    bool opt_min = false;
    bool opt_max = false;
    bool opt_enforced = false;
    bool opt_choices = false;

    for (auto opt : prop_opts) {
      if (opt == Option::MIN_LENGTH) {
        opt_min = true;
      }
      if (opt == Option::MAX_LENGTH) {
        opt_max = true;
      }
      if (opt == Option::ENFORCED) {
        opt_enforced = true;
      }
      if (opt == Option::ALLOWED_VALUES) {
        opt_choices = true;
      }
    }

    CHECK(opt_min);
    CHECK(opt_max);
    CHECK(opt_enforced);
    CHECK(opt_choices);
  }

  cerr << "Testing: getArgPropertyValues" << endl;
  {
    ArgumentString argString;
    auto prop_values = argString.getPropertyValues();

    bool opt_min = false;
    bool opt_max = false;
    bool opt_enforced = false;
    bool opt_choices = false;

    bool opt_min_val = false;
    bool opt_max_val = false;
    bool opt_enforced_val = false;
    bool opt_choices_val = false;

    for (auto val : prop_values) {
      auto prop_type = val.first;
      for ( auto opt_val : val.second ) {
        auto opt_type = opt_val.first;
          if (opt_type == Option::MIN_LENGTH) {
            opt_min = true;
            if (argString.getPropertyValues<size_t>(prop_type,opt_type) == 0) {
              opt_min_val = true;
            }
          }
        if (opt_type == Option::MAX_LENGTH) {
          opt_max = true;
          if (argString.getPropertyValues<size_t>(prop_type,opt_type) > 10000) {
            opt_max_val = true;
          }
        }
        if (opt_type == Option::ENFORCED) {
          opt_enforced = true;
          if (argString.getPropertyValues<bool>(prop_type,opt_type) == false) {
            opt_enforced_val = true;
          }
        }
        if (opt_type == Option::ALLOWED_VALUES) {
          opt_choices = true;
          if (argString.getPropertyValues<std::string>(prop_type,opt_type) == "NOT_DEFINED") {
            opt_choices_val = true;
          }
        }
      }
    }

    CHECK(opt_min);
    CHECK(opt_max);
    CHECK(opt_min_val);
    CHECK(opt_max_val);
    CHECK(opt_enforced);
    CHECK(opt_choices);
    CHECK(opt_enforced_val);
    CHECK(opt_choices_val);
  }
}
