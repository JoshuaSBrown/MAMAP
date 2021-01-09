
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "mamap/arguments/argumentnumerical.hpp"
#include <limits>

using namespace mamap;
using namespace std;

TEST_CASE("Argument Numerical","[unit]"){

  cerr << "Testing: argumentnumerical" << endl;
  cerr << "Testing: constructor" << endl;
  { ArgumentNumerical argNumerical; }
}

TEST_CASE("Argument Numerical Testing: getArgumentType","[unit]"){
  ArgumentNumerical argNumerical;
  CHECK(argNumerical.getArgumentType() == ArgumentType::NUMERIC);
}

TEST_CASE("Argument Numerical Testing: getProperties","[unit]"){
  ArgumentNumerical argNumerical;
  auto props = argNumerical.getProperties();

  bool numer_prop;
  for (auto prop : props) {
    if (prop == PropertyType::NUMERIC) {
      numer_prop = true;
    }
  }
  CHECK(numer_prop);
}

TEST_CASE("Argument Numerical Testing: getPropertyOptions","[unit]"){
  ArgumentNumerical argNumerical;
  auto prop_opts = argNumerical.getPropertyOptions();

  bool opt_min = false;
  bool opt_max = false;

  for (auto opt : prop_opts) {
    if (opt == Option::MIN) {
      opt_min = true;
    }
    if (opt == Option::MAX) {
      opt_max = true;
    }
  }
  CHECK(opt_min);
  CHECK(opt_max);
}

TEST_CASE("Argument Numerical Testing: getArgPropertyValues","[unit]"){
  ArgumentNumerical argNumerical;
  auto prop_values = argNumerical.getPropertyValues();

  bool opt_min = false;
  bool opt_max = false;

  for (auto val : prop_values[PropertyType::NUMERIC]) {
    if (val.first == Option::MIN) {
      opt_min = true;
      CHECK( std::any_cast<double>(val.second) == Approx(numeric_limits<double>::lowest()) );
    }
    if (val.first == Option::MAX) {
      opt_max = true;
      CHECK( std::any_cast<double>(val.second) == Approx(numeric_limits<double>::max()) );
    }
  }
  CHECK(opt_min);
  CHECK(opt_max);
}
