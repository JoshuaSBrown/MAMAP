#include "propertytypes.hpp"

namespace mamap {
  std::string operator+(std::string str, const PropertyType prop) {
    if( prop == PropertyType::UNKNOWN) {
      return str + std::string("UNKNOWN");
    } else if(prop == PropertyType::NUMERIC) {
      return str + std::string("NUMERIC");
    } else if(prop == PropertyType::FILE_EXISTS) {
      return str + std::string("FILE_EXISTS");
    } else if(prop == PropertyType::FILE_EXT) {
      return str + std::string("FILE_EXT");
    } else if(prop == PropertyType::SISTER_FILE) {
      return str + std::string("SISTER_FILE");
    } else if(prop == PropertyType::STRING) {
      return str + std::string("STRING");
    } else if(prop == PropertyType::STRING_CHOICE) {
      return str + std::string("SWITCH");
    }
    return str;
  } 
}
