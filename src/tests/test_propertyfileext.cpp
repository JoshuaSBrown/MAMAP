
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "arguments/properties/propertyfileext.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace mamap;
using namespace std;

TEST_CASE("Property File Extension","[unit]") {

  cerr << "Testing: PropertyFileExt" << endl;
  cerr << "Testing: constructor" << endl;
  {
    PropertyFileExt propFileExt1("*");
    PropertyFileExt propFileExt2("");
    PropertyFileExt propFileExt3(".jpg");
    CHECK_THROWS(PropertyFileExt("ffda.fd"));
    set<string> exts = {".png", ".gjf"};
    PropertyFileExt propFileExt5(exts);
  }

  cerr << "Testing: getPropertyName" << endl;
  {
    PropertyFileExt propFileExt;
    PropertyType type = propFileExt.getPropertyType();
    REQUIRE(type == PropertyType::FILE_EXT);
  }

  cerr << "Testing: getPropertyOptions" << endl;
  {

    PropertyFileExt propFileExt;
    auto options = propFileExt.getPropertyOptions();
    Option opt = options.at(0);
    REQUIRE(opt == Option::ALLOWED_VALUES);
  }

  cerr << "Testing: propValid" << endl;
  {
    PropertyFileExt propFileExt(".jpg");
    CHECK(propFileExt.propValid("dir/file.jpg"));
    CHECK_THROWS(propFileExt.propValid("dir/file.jp"));

    PropertyFileExt propFileExt2("*");
    CHECK(propFileExt2.propValid("dir/file.jpg"));
    CHECK(propFileExt2.propValid("dir/file.jp"));

    set<string> exts = {".png", ".gjf"};
    PropertyFileExt propFileExt3(exts);
    CHECK(propFileExt3.propValid("Dir2/Path/File.png"));
    CHECK(propFileExt3.propValid("Dir2/Path/File.gjf"));
    CHECK_THROWS(propFileExt3.propValid("dir/file.com"));
  }
}
