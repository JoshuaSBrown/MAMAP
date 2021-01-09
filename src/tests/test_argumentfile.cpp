
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "mamap/arguments/argumentfile.hpp"

using namespace mamap;
using namespace std;

TEST_CASE("Argument File","[unit]"){

  cerr << "Testing: argumentfile" << endl;
  cerr << "Testing: constructor" << endl;
  { ArgumentFile argFile; }

  cerr << "Testing: getArgumentType" << endl;
  {
    ArgumentFile argFile;
    std::cout << __FILE__ << ":" << __LINE__ << std::endl;
    CHECK(argFile.getArgumentType() == ArgumentType::FILES);
  }

  cerr << "Testing: getProperties" << endl;
  {
    ArgumentFile argFile;
    std::cout << __FILE__ << ":" << __LINE__ << std::endl;
    auto props = argFile.getProperties();

    bool file_exist = false;
    bool file_ext = false;
    bool sister_file = false;

    for (auto prop : props) {
      if (prop == PropertyType::FILE_EXISTS) {
        file_exist = true;
      }
      if (prop == PropertyType::FILE_EXT) {
        file_ext = true;
      }
      if (prop == PropertyType::SISTER_FILE) {
        sister_file = true;
      }
    }
    CHECK(file_exist);
    CHECK(file_ext);
    CHECK(sister_file);
  }

  cerr << "Testing: getPropertyOptions" << endl;
  {
    ArgumentFile argFile;
    std::cout << __FILE__ << ":" << __LINE__ << std::endl;
    auto prop_opts = argFile.getPropertyOptions();

    bool file_must_exist = false;
    int file_does_exist = 0;
    bool sis_file_name = false;
    bool sis_file_path = false;
    bool sis_file_path_name = false;
    int allowed_values = 0;
    for (auto opt : prop_opts) {
      if (opt == Option::ALLOWED_VALUES) {
        allowed_values++;
      }
      if (opt == Option::MUST_EXIST) {
        file_must_exist = true;
      }
      if (opt == Option::DOES_EXIST) {
        file_does_exist++;
      }
      if (opt == Option::FILE_NAME ) {
        sis_file_name = true;
      }
      if (opt == Option::FILE_PATH)  {
        sis_file_path = true;
      }
      if (opt == Option::FILE_PATH_NAME) {
        sis_file_path_name = true;
      }
    }

    CHECK(file_must_exist);
    CHECK(file_does_exist == 2);
    CHECK(sis_file_name);
    CHECK(sis_file_path);
    CHECK(sis_file_path_name);
    CHECK(allowed_values == 2);
  }

  cerr << "Testing: setArgPropertyValues" << endl;
  {
    ArgumentFile argFile;
    std::cout << __FILE__ << ":" << __LINE__ << std::endl;
    auto prop_values = argFile.getPropertyValues();

    std::cout << __FILE__ << ":" << __LINE__ << std::endl;
    bool allowed_ext = false;
    bool allowed_ext_val = false;

    for (auto prop_opt_map : prop_values) {
      if ( prop_opt_map.first == PropertyType::FILE_EXT) {
        auto val = prop_opt_map.second;
        if (val.count(Option::ALLOWED_VALUES)) {
          allowed_ext = true;
    std::cout << __FILE__ << ":" << __LINE__ << std::endl;
    std::cout << "Should be asterix " << argFile.getPropertyValues<string>(PropertyType::FILE_EXT, Option::ALLOWED_VALUES) << std::endl;
          if (argFile.getPropertyValues<string>(PropertyType::FILE_EXT, Option::ALLOWED_VALUES) == "*") {
            allowed_ext_val = true;
          }
        }
      }
    }

    CHECK(allowed_ext);
    CHECK(allowed_ext_val);

    set<string> exts{".pun", ".7", ".orb"};
    std::cout << __FILE__ << ":" << __LINE__ << std::endl;
    argFile.setArgPropertyOpt(PropertyType::FILE_EXT, Option::ALLOWED_VALUES, exts);
    std::cout << __FILE__ << ":" << __LINE__ << std::endl;
    auto str_exts =
        argFile.getPropertyValues<std::set<string>>(PropertyType::FILE_EXT, Option::ALLOWED_VALUES);

    bool pun_ext = false;
    bool fort7_ext = false;
    bool orb_ext = false;
    for ( auto ext : str_exts ) {
      if( ext == ".pun" ) pun_ext = true;
      if( ext == ".7" ) fort7_ext = true;
      if( ext == ".orb" ) orb_ext = true;
    }
    CHECK(pun_ext);
    CHECK(fort7_ext);
    CHECK(orb_ext);
  }

}
