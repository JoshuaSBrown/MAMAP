
#include "propertyfileexist.hpp"
#include "string_support.hpp"
#include <stdexcept>
#include <sys/stat.h>

using namespace std;

namespace mamap {

  namespace {

    std::string getStrDefaultBool_(Option option, std::map<Option, std::any> options_){
      bool val = std::any_cast<bool>(options_.at(option));
      if( val ) return string("true");
      return string("false");
    }

    bool getBoolDefaultBool_(Option option, std::map<Option, std::any> options_){
      return std::any_cast<bool>(options_.at(option));
    }

    int getIntDefaultBool_(Option option, std::map<Option, std::any> options_) {
      bool val = std::any_cast<bool>(options_.at(option));
      if( val ) return 1;
      return 0;
    }

    std::any convertStrToDefault_(Option option, std::map<Option, std::any> options_, std::any val){
      std::string value = std::any_cast<std::string>(val);
      if( to_upper(value) == "TRUE" ) {
        return true; 
      } else if( to_upper(value) == "FALSE") {
        return false;
      } else {
        throw std::runtime_error("Cannot convert string to bool time.");
      }
    }
    std::any convertBoolToDefault_(Option option, std::map<Option, std::any> options_, std::any val){
      return val;
    }
    std::any convertIntToDefault_(Option option, std::map<Option, std::any> options_, std::any val){

      int value = std::any_cast<int>(val);
      if ( value == 0 ) return false;
      return true;
    }

  }

  PropertyFileExist::PropertyFileExist(void) {

    default_option_type_.insert(std::pair<Option, type_index>(Option::MUST_EXIST, type_index(typeid(bool))));
    default_option_type_.insert(std::pair<Option, type_index>(Option::DOES_EXIST, type_index(typeid(bool))));

    allowed_option_types_[Option::MUST_EXIST].push_back(type_index(typeid(bool)));
    allowed_option_types_[Option::MUST_EXIST].push_back(type_index(typeid(std::string)));
    allowed_option_types_[Option::MUST_EXIST].push_back(type_index(typeid(int)));

    allowed_option_types_[Option::DOES_EXIST].push_back(type_index(typeid(bool)));
    allowed_option_types_[Option::DOES_EXIST].push_back(type_index(typeid(std::string)));
    allowed_option_types_[Option::DOES_EXIST].push_back(type_index(typeid(int)));

    str_convert_[Option::MUST_EXIST] = &mamap::getStrDefaultBool_;
    bool_convert_[Option::MUST_EXIST] = &mamap::getBoolDefaultBool_;
    int_convert_[Option::MUST_EXIST] = &mamap::getIntDefaultBool_;

    str_convert_[Option::DOES_EXIST] = &mamap::getStrDefaultBool_;
    bool_convert_[Option::DOES_EXIST] = &mamap::getBoolDefaultBool_;
    int_convert_[Option::DOES_EXIST] = &mamap::getIntDefaultBool_;

    str_convert_to_default_[Option::MUST_EXIST] = &mamap::convertStrToDefault_;
    bool_convert_to_default_[Option::MUST_EXIST] = &mamap::convertBoolToDefault_;
    int_convert_to_default_[Option::MUST_EXIST] = &mamap::convertIntToDefault_;

    str_convert_to_default_[Option::DOES_EXIST] = &mamap::convertStrToDefault_;
    bool_convert_to_default_[Option::DOES_EXIST] = &mamap::convertBoolToDefault_;
    int_convert_to_default_[Option::DOES_EXIST] = &mamap::convertIntToDefault_;

    //  Defaults
    setPropOption_(Option::MUST_EXIST, bool(false));
    setPropOption_(Option::DOES_EXIST, bool(false));
  }

  PropertyFileExist::PropertyFileExist(bool fileMustExist) : PropertyFileExist() {
    setPropOption_(Option::MUST_EXIST, fileMustExist);
  }

  bool PropertyFileExist::fileExist(const string& fileNamePath) const {
    struct stat buf;
    return (stat(fileNamePath.c_str(), &buf) == 0);
  }

  bool PropertyFileExist::propValid(const std::any& fileNamePath) {
    std::string file_name_path;
    if ( fileNamePath.type() == typeid(char *) ) {
      file_name_path = std::string(std::any_cast<char *>(fileNamePath));
    } else if ( fileNamePath.type() == typeid(const char *) ) {
      file_name_path = std::string(std::any_cast<const char *>(fileNamePath));
    } else {
      file_name_path = std::any_cast<std::string>(fileNamePath);
    } 
    bool must_exist = any_cast<bool>(options_[Option::MUST_EXIST]);
    if (must_exist) {
      if (!fileExist(file_name_path)) {
        string err = "" + file_name_path + " does not exist";
        throw invalid_argument(err);
      }
      setPropOption_(Option::DOES_EXIST, bool(true));
    } else {
      if (fileExist(file_name_path)) {
        setPropOption_(Option::DOES_EXIST, bool(true));
      }
    }
    return true;
  }

  void PropertyFileExist::postCheck(void) const {
    auto must_exist = getPropOption<bool>(Option::MUST_EXIST);
    auto exist = getPropOption<bool>(Option::DOES_EXIST);
    if (must_exist && exist == 0) {
      throw runtime_error("A necessary file is missing!");
    }
  }

} // namespace mamap
