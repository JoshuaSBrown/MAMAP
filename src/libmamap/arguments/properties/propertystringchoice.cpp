
#include "mamap/arguments/properties/propertystringchoice.hpp"
#include "mamap/string_support.hpp"
#include <iostream>
#include <set>
#include <stdexcept>
#include <sys/stat.h>
#include <typeinfo>
#include <typeindex>

using namespace std;

namespace mamap {
  namespace {
    std::vector<bool> getVecBoolEnforced_(Option option, std::map<Option, std::any> options_){
      vector<bool> values;
      // Because the default is a set of strings
      set<string> stored_values = std::any_cast<set<string>>(options_.at(option));
      for ( std::string val : stored_values){
        if( to_upper(val) == "TRUE" ) {
          values.push_back(true);
        } else if( to_upper(val) == "FALSE") {
          values.push_back(false);
        }
      } 
      return values;
    }

    // Convert from a set of bools to a set of strings
    std::any convertVecBoolEnforcedToDefault_(std::any val){
      // Because the default is a set of strings
      auto values = std::any_cast<vector<bool>>(val);
      set<string> default_values;
      for ( bool val : values){
        if( val ) {
          default_values.insert("true");
        } else {
          default_values.insert("false");
        }
      } 
      return default_values;
    }

    std::string getStrEnforced_(Option option, std::map<Option, std::any> options_){
      string values;
      // Because the default is a set of strings
      set<string> stored_values = std::any_cast<set<string>>(options_.at(option));
      if ( stored_values.size() != 1) {
        throw std::runtime_error("Cannot convert enforced option to string because more than one value has been specefied");
      } 
      for ( std::string val : stored_values){
        values = val;
      } 
      return values;
    }

    std::any convertStrEnforcedToDefault_(std::any val){
      std::string value;
      if ( val.type() == typeid(std::string) ) {
        value = std::any_cast<std::string>(val);
      } else if ( val.type() == typeid(const char *) ) {
        value = string(std::any_cast<const char *>(val));
      }
      set<string> default_values;
      default_values.insert(value);
      return default_values;
    }

    std::set<string> getSetStrEnforced_(Option option, std::map<Option, std::any> options_){
      // Because the default is a set of strings
      set<string> stored_values = std::any_cast<set<string>>(options_.at(option));
      return stored_values;
    }

    std::any convertSetStrEnforcedToDefault_(std::any val){
      return val;
    }

    std::vector<int> getVecIntEnforced_(Option option, std::map<Option, std::any> options_){
      vector<int> values;
      // Because the default is a set of strings
      set<string> stored_values = std::any_cast<set<string>>(options_.at(option));
      for ( std::string val : stored_values){
        if( to_upper(val) == "TRUE" ) {
          values.push_back(1);
        } else if( to_upper(val) == "FALSE") {
          values.push_back(0);
        }
      } 
      return values;
    }

    std::any convertVecIntEnforcedToDefault_(std::any val){
      vector<int> values = std::any_cast<vector<int>>(val);
      set<string> default_values;
      for ( int val : values){
        if( val == 0) {
          default_values.insert("false");
        } else {
          default_values.insert("true");
        }
      }
      return default_values;
    }

    std::string getStrAllowedValues_(Option option, std::map<Option, std::any> options_){
      // Because the default is a set of strings
      set<string> stored_values = std::any_cast<set<string>>(options_.at(option));

      if ( stored_values.size() > 1 ) {
        throw std::runtime_error("Cannot convert option value to string because there is more than a single value.");
      }
      return *stored_values.begin();
    }

    std::set<string> getSetStrAllowedValues_(Option option, std::map<Option, std::any> options_){
      // Because the default is a set of strings
      set<string> stored_values = std::any_cast<set<string>>(options_.at(option));
      return stored_values;
    }

    std::any convertSetStrAllowedValuesToDefault_(std::any val){
      // Because the default is a set of strings
      return val;
    }

    std::vector<string> getVectorStrAllowedValues_(Option option, std::map<Option, std::any> options_){
      vector<string> values;
      // Because the default is a set of strings
      set<string> stored_values = std::any_cast<set<string>>(options_.at(option));
      for ( string val : stored_values ) {
        values.push_back(val);
      }
      return values;
    }

    std::any convertVectorStrAllowedValuesToDefault_(std::any val){
      // Because the default is a set of strings
      vector<string> values = std::any_cast<vector<string>>(val);
      set<string> default_values;
      for ( string val1 : values ) {
        default_values.insert(val1);
      }
      return default_values;
    }

    std::any convertStrAllowedValuesToDefault_(std::any val){
      // Because the default is a set of strings
      string values = std::any_cast<string>(val);
      set<string> default_values;
      default_values.insert(values);
      std::any converted_val = default_values;
      return converted_val;
    }
  }

  PropertyStringChoice::PropertyStringChoice(void) {

    default_option_type_.insert(std::pair<Option, type_index>(Option::ENFORCED, type_index(typeid(set<string>))));

    allowed_option_types_[Option::ENFORCED].push_back(type_index(typeid(set<string>)));
    allowed_option_types_[Option::ENFORCED].push_back(type_index(typeid(vector<bool>)));
    allowed_option_types_[Option::ENFORCED].push_back(type_index(typeid(vector<int>)));

    str_convert_[Option::ENFORCED] = &mamap::getStrEnforced_;
    vector_bool_convert_[Option::ENFORCED] = &mamap::getVecBoolEnforced_;
    set_str_convert_[Option::ENFORCED] = &mamap::getSetStrEnforced_;
    vector_int_convert_[Option::ENFORCED] = &mamap::getVecIntEnforced_;

    str_convert_to_default_[Option::ENFORCED] = &mamap::convertStrEnforcedToDefault_;
    vector_bool_convert_to_default_[Option::ENFORCED] = &mamap::convertVecBoolEnforcedToDefault_;
    set_str_convert_to_default_[Option::ENFORCED] = &mamap::convertSetStrEnforcedToDefault_;
    vector_int_convert_to_default_[Option::ENFORCED] = &mamap::convertVecIntEnforcedToDefault_;

    default_option_type_.insert(std::pair<Option, type_index>(Option::ALLOWED_VALUES, type_index(typeid(set<string>))));

    allowed_option_types_[Option::ALLOWED_VALUES].push_back(type_index(typeid(set<string>)));
    allowed_option_types_[Option::ALLOWED_VALUES].push_back(type_index(typeid(vector<string>)));

    str_convert_[Option::ALLOWED_VALUES] = &mamap::getStrAllowedValues_;
    set_str_convert_[Option::ALLOWED_VALUES] = &mamap::getSetStrAllowedValues_;
    vector_str_convert_[Option::ALLOWED_VALUES] = &mamap::getVectorStrAllowedValues_;
    
    str_convert_to_default_[Option::ALLOWED_VALUES] = &mamap::convertStrAllowedValuesToDefault_;
    set_str_convert_to_default_[Option::ALLOWED_VALUES] = &mamap::convertSetStrAllowedValuesToDefault_;
    vector_str_convert_to_default_[Option::ALLOWED_VALUES] = &mamap::convertVectorStrAllowedValuesToDefault_;

    // Note setting the options should go after assigning the correct function pointers
    // Setting defaults
    set<string> set_var1{"false"};
    setPropOption_(Option::ENFORCED, set_var1);

    string str = "NOT_DEFINED";
    set<string> set_var2{str};
    setPropOption_(Option::ALLOWED_VALUES, set_var2);

  }

  bool PropertyStringChoice::propValid(const any& choice) {

    std::cout << "1" << std::endl;
    std::string string_choice = any_cast<std::string>(choice);
    std::cout << "2" << std::endl;
    set<string> opt_val;
    if(options_[Option::ENFORCED].type() == typeid(std::string) ){
      opt_val.insert(std::any_cast<string>(options_[Option::ENFORCED]));
    }else {
      opt_val = getPropOption<set<string>>(Option::ENFORCED);
    }
    string val = *(opt_val.begin());
    if (val.compare("true") == 0) {
      std::cout << "3" << std::endl;
      set<string> str_choices = getPropOption<set<string>>(Option::ALLOWED_VALUES);
      if (str_choices.count(string_choice) > 0) return true;
      throw invalid_argument("The value " + string_choice +
          " is not a valid option");
    }
    return true;
  }
}
