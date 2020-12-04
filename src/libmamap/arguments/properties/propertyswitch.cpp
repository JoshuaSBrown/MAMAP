
#include "propertyswitch.hpp"
#include "string_support.hpp"

#include <limits>

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
      std::string value;
      if ( val.type() == typeid(std::string) ) {
        value = std::any_cast<std::string>(val);
      } else if ( val.type() == typeid(const char *) ) {
        value = string(std::any_cast<const char *>(val));
      }
      if( to_upper(value) == "TRUE" ) {
        return true; 
      } else if( to_upper(value) == "FALSE") {
        return false;
      }else if ( value == "0" ) {
        return false;
      }else if ( value == "1" ) {
        return true;
      } else if ( to_upper(value) == "ON") {
        return true;
      } else if ( to_upper(value) == "OFF") {
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

  PropertySwitch::PropertySwitch() { 

    default_option_type_.insert(std::pair<Option, type_index>(Option::DEFAULT, type_index(typeid(bool))));

    str_convert_[Option::DEFAULT] = &mamap::getStrDefaultBool_;
    bool_convert_[Option::DEFAULT] = &mamap::getBoolDefaultBool_;
    int_convert_[Option::DEFAULT] = &mamap::getIntDefaultBool_;

    str_convert_to_default_[Option::DEFAULT] = &mamap::convertStrToDefault_;
    bool_convert_to_default_[Option::DEFAULT] = &mamap::convertBoolToDefault_;
    int_convert_to_default_[Option::DEFAULT] = &mamap::convertIntToDefault_;
    // Set defaults
    setPropOption_(Option::DEFAULT, bool(false)); 
  }

  void PropertySwitch::switchValid(int val) const {
    if (val < 0 || val > 1) {
      string err =
        "Switches are only allowed to be on or off. By default they "
        "are set to off. An integer may be provided to the switch to "
        "toggle the behavior, however the integer is only allowed to "
        "be a 1 or a 0 you have provided a " +
        to_string(val);
      throw invalid_argument(err);
    }
  }

  void PropertySwitch::switchValid(std::string val) const {
    if (val.compare("0") != 0 && val.compare("1") != 0 &&
        val.compare("ON") != 0 && val.compare("OFF") != 0 &&
        val.compare("TRUE") != 0 && val.compare("FALSE") != 0) {
      string err =
        "Switches are only allowed to be on or off. By default they "
        "are set to off. A string may be provided to the switch to "
        "toggle the behavior, however the string is only allowed to "
        "be a TRUE/FALSE/ON/OFF you have provided a " +
        val;
      throw invalid_argument(err);
    }
  }

  bool PropertySwitch::propValid(const std::any & value) {
    if( value.type() == typeid(int)){
      int int_val = any_cast<int>(value);
      switchValid(int_val); 
    }else if(value.type() == typeid(std::string)){
      std::string str_val = any_cast<std::string>(value);
      switchValid(str_val); 
    }else if(value.type() == typeid(const char *)){
      std::string str_val = string(any_cast<const char *>(value));
      switchValid(str_val);
    }else if(value.type() == typeid(char *)){
      std::string str_val = string(any_cast<char *>(value));
      switchValid(str_val);
    }else if(value.type() != typeid(bool)) {
      throw invalid_argument("Unrecognized type passed to switch, only recognizes"
          " int, string and bool types");
    }
    return true;
  }
} // namespace mamap
