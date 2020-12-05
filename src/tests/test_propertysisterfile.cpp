
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "arguments/properties/propertysisterfile.hpp"
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace mamap;
using namespace std;

TEST_CASE("Property Sister File","[unit]") {
  fstream fs;
  fs.open("testfile.pun", ios::out);
  fs.close();

  cerr << "Testing: PropertySisterFile" << endl;
  cerr << "Testing: constructor" << endl;
  { PropertySisterFile propSisterFile1; }

  cerr << "Testing: getPropertyName" << endl;
  {
    PropertySisterFile propSisterFile;
    PropertyType type = propSisterFile.getPropertyType();
    CHECK(type == PropertyType::SISTER_FILE);
  }

  cerr << "Testing: getPropertyOptions" << endl;
  {

    PropertySisterFile propSisterFile;
    auto options = propSisterFile.getPropertyOptions();

    bool allowed_file = false;
    bool sister_name = false;
    bool sister_path = false;
    bool sister_name_path = false;
    bool sister_exists = false;

    for (auto opt : options) {
      if (opt == Option::ALLOWED_VALUES) {
        allowed_file = true;
      }
      if (opt == Option::FILE_NAME) {
        sister_name = true;
      }
      if (opt == Option::FILE_PATH) {
        sister_path = true;
      }
      if (opt == Option::FILE_PATH_NAME) {
        sister_name_path = true;
      }
      if (opt == Option::DOES_EXIST) {
        sister_exists = true;
      }
    }
    CHECK(allowed_file);
    CHECK(sister_name);
    CHECK(sister_path);
    CHECK(sister_name_path);
    CHECK(sister_exists);
  }

  cerr << "Testing: getPropOption" << endl;
  {
    PropertySisterFile propSisterFile1;

    vector<string> allowed_ext =
        propSisterFile1.getPropOption<vector<string>>(Option::ALLOWED_VALUES);
    vector<string> file_name =
        propSisterFile1.getPropOption<vector<string>>(Option::FILE_NAME);
    vector<string> file_path =
        propSisterFile1.getPropOption<vector<string>>(Option::FILE_PATH);
    vector<string> file_path_name =
        propSisterFile1.getPropOption<vector<string>>(Option::FILE_PATH_NAME);
    vector<bool> fileExist =
        propSisterFile1.getPropOption<vector<bool>>(Option::DOES_EXIST);

    CHECK(allowed_ext.at(0) == "NOT_DEFINED");
    CHECK(file_name.at(0) == "NOT_DEFINED");
    CHECK(file_path.at(0) == "NOT_DEFINED");
    CHECK(file_path_name.at(0) == "NOT_DEFINED");
    CHECK(fileExist.at(0) == false);
  }

  cerr << "Testing: getPropOption" << endl;
  {
    PropertySisterFile propSisterFile1;

    propSisterFile1.setPropOption(Option::ALLOWED_VALUES, ".pun");

    string fileName = "testfile.log";
    propSisterFile1.propValid(fileName);
    vector<string> allowed_ext =
        propSisterFile1.getPropOption<vector<string>>(Option::ALLOWED_VALUES);
    vector<string> file_name =
        propSisterFile1.getPropOption<vector<string>>(Option::FILE_NAME);
    vector<string> file_path =
        propSisterFile1.getPropOption<vector<string>>(Option::FILE_PATH);
    vector<string> file_path_name =
        propSisterFile1.getPropOption<vector<string>>(Option::FILE_PATH_NAME);
    vector<bool> fileExist =
        propSisterFile1.getPropOption<vector<bool>>(Option::DOES_EXIST);

    CHECK(allowed_ext.at(0) == ".pun");

    CHECK(file_name.at(0) == "testfile.pun");
    CHECK(file_path.at(0) == "");
    CHECK(file_path_name.at(0) == "testfile.pun");
    CHECK(fileExist.at(0));
  }
}
