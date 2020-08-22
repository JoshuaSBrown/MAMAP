
#include "propertystringchoice.hpp"
#include "string_support.hpp"
#include <iostream>
#include <set>
#include <stdexcept>
#include <sys/stat.h>
#include <typeinfo>
#include <typeindex>

using namespace std;

namespace mamap {
  namespace {
    std::set<bool> getSetBoolEnforced_(Option option, std::map<Option, std::any> options_){
      set<bool> values;
      // Because the default is a set of strings
      set<string> stored_values = std::any_cast<set<string>>(options_.at(option));
      for ( std::string val : stored_values){
        if( to_upper(val) == "TRUE" ) {
          values.insert(true);
        } else if( to_upper(val) == "FALSE") {
          values.insert(false);
        }
      } 
      return values;
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

    std::set<string> getSetStrEnforced_(Option option, std::map<Option, std::any> options_){
      // Because the default is a set of strings
      std::cout << "Any cast to set<string> for Enforced" << std::endl;
      set<string> stored_values = std::any_cast<set<string>>(options_.at(option));
      return stored_values;
    }

    std::set<int> getSetIntEnforced_(Option option, std::map<Option, std::any> options_){
      set<int> values;
      // Because the default is a set of strings
      set<string> stored_values = std::any_cast<set<string>>(options_.at(option));
      for ( std::string val : stored_values){
        if( to_upper(val) == "TRUE" ) {
          values.insert(1);
        } else if( to_upper(val) == "FALSE") {
          values.insert(0);
        }
      } 
      return values;
    }

    std::string getStrAllowedValues_(Option option, std::map<Option, std::any> options_){
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

    std::set<string> getSetStrAllowedValues_(Option option, std::map<Option, std::any> options_){
      // Because the default is a set of strings
      set<string> stored_values = std::any_cast<set<string>>(options_.at(option));
      int ind = 0;
      for ( string item : stored_values ) {
        std::cout << ind << " Content allowed_values " << item << std::endl;
        ++ind;
      }
      return stored_values;
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
  }

  PropertyStringChoice::PropertyStringChoice(void) {
    set<string> set_var1{"false"};
    setPropOption_(Option::ENFORCED, set_var1);

    default_option_type_.insert(std::pair<Option, type_index>(Option::ENFORCED, type_index(typeid(set<string>))));

    allowed_option_types_[Option::ENFORCED].push_back(type_index(typeid(set<string>)));
    allowed_option_types_[Option::ENFORCED].push_back(type_index(typeid(set<bool>)));
    allowed_option_types_[Option::ENFORCED].push_back(type_index(typeid(set<int>)));

    str_convert_[Option::ENFORCED] = &mamap::getStrEnforced_;
    set_bool_convert_[Option::ENFORCED] = &mamap::getSetBoolEnforced_;
    set_str_convert_[Option::ENFORCED] = &mamap::getSetStrEnforced_;
    set_int_convert_[Option::ENFORCED] = &mamap::getSetIntEnforced_;

    string str = "NOT_DEFINED";
    set<string> set_var2{str};
    setPropOption_(Option::ALLOWED_VALUES, set_var2);

    default_option_type_.insert(std::pair<Option, type_index>(Option::ALLOWED_VALUES, type_index(typeid(set<string>))));

    allowed_option_types_[Option::ALLOWED_VALUES].push_back(type_index(typeid(set<string>)));
    allowed_option_types_[Option::ALLOWED_VALUES].push_back(type_index(typeid(vector<string>)));

    str_convert_[Option::ALLOWED_VALUES] = &mamap::getStrAllowedValues_;
    set_str_convert_[Option::ALLOWED_VALUES] = &mamap::getSetStrAllowedValues_;
    vector_str_convert_[Option::ALLOWED_VALUES] = &mamap::getVectorStrAllowedValues_;

  }

  /*void PropertyStringChoice::setPropOption( option,
    set<string> set_vars) {

    if (option.compare("STRING_CHOICES") == 0) {
    setPropOption_(option, set_vars);
    return;
    } else if (option.compare("STRING_CHOICE_ENFORCED") == 0) {
    if (set_vars.size() > 1) {
    string err = "";
    for (auto var : set_vars) {
    err.append(var);
    err.append(" ");
    }
    trim(err);
    throw invalid_argument(
    "Option STRING_CHOICE_ENFORCED only accepts one "
    "value either true or false you have passed the following values " +
    err);
    }

    string var = *(set_vars.begin());
    if (var.compare("false") == 0 || var.compare("true") == 0) {
    setPropOption_(option, set_vars);
    return;
    } else {
    throw invalid_argument("The option " + option +
    " can only be set to values"
    " of true or false you have set it to " +
    var);
    }
    }
    string vars = "";
    for (auto var : set_vars) {
    vars.append(var);
    vars.append(" ");
    }
    trim(vars);
    throw invalid_argument("Unrecognized option value combo " + option + " " +
    vars);
    }*/

  bool PropertyStringChoice::propValid(const any& choice) {

    std::cout << "1" << std::endl;
    std::string string_choice = any_cast<std::string>(choice);
    std::cout << "2" << std::endl;
    set<string> opt_val;
    if(options_[Option::ENFORCED].type() == typeid(std::string) ){
      std::cout << "Converting to string and inserting" << std::endl;
      opt_val.insert(std::any_cast<string>(options_[Option::ENFORCED]));
    }else {
      std::cout << "Converting to set string and writing" << std::endl;
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
