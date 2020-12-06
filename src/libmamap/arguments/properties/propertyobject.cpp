#include "propertyobject.hpp"

namespace mamap {

  std::any all_convert_(Option option,std::map<Option, std::any> options) {
    std::cout << "grabbing option in all_convert" << std::endl;
    if( options.count(option)==0 ) {
      std::string err = "Error option is not available for property, Option: " + option; 
      throw std::runtime_error(err);
    }
    return options.at(option);
  }

  std::ostream& operator<<(std::ostream& out, const Option option){
    if( option == Option::NO_OPTIONS) {
      return out << std::string("NO_OPTIONS");
    } else if(option == Option::MIN) {
      return out << std::string("MIN");
    }  else if(option == Option::MAX) {
      return out << std::string("MAX");
    }  else if(option == Option::MIN_LENGTH) {
      return out << std::string("MIN_LENGTH");
    }  else if(option == Option::MAX_LENGTH) {
      return out << std::string("MAX_LENGTH");
    }  else if(option == Option::MUST_EXIST) {
      return out << std::string("MUST_EXIST");
    }  else if(option == Option::DOES_EXIST) {
      return out << std::string("DOES_EXIST");
    }  else if(option == Option::ALLOWED_VALUES) {
      return out << std::string("ALLOWED_VALUES");
    }  else if(option == Option::ENFORCED) {
      return out << std::string("ENFORCED");
    }  else if(option == Option::FILE_NAME) {
      return out << std::string("FILE_NAME");
    }  else if(option == Option::FILE_PATH) {
      return out << std::string("FILE_PATH");
    }  else if(option == Option::FILE_PATH_NAME) {
      return out << std::string("FILE_PATH_NAME");
    }  else if(option == Option::VALUE) {
      return out << std::string("VALUE");
    }  else if(option == Option::DEFAULT) {
      return out << std::string("DEFAULT");
    }
    return out;
  }

  std::string operator+(std::string str, const Option option) {
    if( option == Option::NO_OPTIONS) {
      return str + std::string("NO_OPTIONS");
    } else if(option == Option::MIN) {
      return str + std::string("MIN");
    }  else if(option == Option::MAX) {
      return str + std::string("MAX");
    }  else if(option == Option::MIN_LENGTH) {
      return str + std::string("MIN_LENGTH");
    }  else if(option == Option::MAX_LENGTH) {
      return str + std::string("MAX_LENGTH");
    }  else if(option == Option::MUST_EXIST) {
      return str + std::string("MUST_EXIST");
    }  else if(option == Option::DOES_EXIST) {
      return str + std::string("DOES_EXIST");
    }  else if(option == Option::ALLOWED_VALUES) {
      return str + std::string("ALLOWED_VALUES");
    }  else if(option == Option::ENFORCED) {
      return str + std::string("ENFORCED");
    }  else if(option == Option::FILE_NAME) {
      return str + std::string("FILE_NAME");
    }  else if(option == Option::FILE_PATH) {
      return str + std::string("FILE_PATH");
    }  else if(option == Option::FILE_PATH_NAME) {
      return str + std::string("FILE_PATH_NAME");
    }  else if(option == Option::VALUE) {
      return str + std::string("VALUE");
    }  else if(option == Option::DEFAULT) {
      return str + std::string("DEFAULT");
    }
    return str;
  }

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
