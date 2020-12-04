
#ifndef _MAMAP_PROPERTY_OBJECT_HPP
#define _MAMAP_PROPERTY_OBJECT_HPP

#include <any>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <stdexcept>
#include <string>
#include <typeindex>
#include <typeinfo>
#include <variant>
#include <vector>

namespace mamap {

enum class PropertyType {
  UNKNOWN,
  NUMERIC,
  FILE_EXISTS,
  FILE_EXT,
  SISTER_FILE,
  STRING,
  STRING_CHOICE,
  SWITCH
};

enum class Option {
  NO_OPTIONS,
  MIN,
  MAX,
  MIN_LENGTH,
  MAX_LENGTH,
  MUST_EXIST,
  DOES_EXIST,
  ALLOWED_VALUES,
  ENFORCED,
  FILE_NAME,
  FILE_PATH,
  FILE_PATH_NAME,
  VALUE,
  DEFAULT
};

std::ostream& operator<<(std::ostream& out, const Option option);

std::string operator+(std::string str, const Option option);

class PropertyObject {
 protected:
  // Map key is the option name and the type "int, double etc"
  // void * points to the correct value for that type
  std::map<Option, std::any> options_;
  std::map<Option, std::vector<std::type_index>> allowed_option_types_;
  std::map<Option, std::type_index> default_option_type_; 

  //void addAllowedOptionType_(const Option & option, std::type_index ind) {  
   // allowed_option_types_[option].push_back(std::move(ind));
  //}

 // void setDefaultOptionType_(const Option & option, std::type_index ind) {
  //  default_option_type_[option] = std::move(ind);
 // }

  bool propOptionValid_(const Option &option) const {
    return options_.count(option);
  }

  void setPropOption_(const Option &option, const std::any &val) {
      std::any as_default = convert_to_default_(option, val);
      options_[option] = as_default;
  }

  bool conversionAllowed_(Option option, std::type_index type) const {
    for ( const std::type_index & allowed_type : allowed_option_types_.at(option) ){
      if( allowed_type == type ) return true;
    }
    return false;
  } 

  // Convert from the default to the type
  typedef int (*int_func)(Option,std::map<Option, std::any>); 
  std::map<Option,int_func> int_convert_;
  typedef size_t (*size_t_func)(Option,std::map<Option, std::any>); 
  std::map<Option,size_t_func> size_t_convert_;
  typedef double (*double_func)(Option,std::map<Option, std::any>); 
  std::map<Option,double_func> double_convert_;
  typedef std::string (*str_func)(Option,std::map<Option, std::any>); 
  std::map<Option,str_func> str_convert_;
  typedef bool (*bool_func)(Option,std::map<Option, std::any>); 
  std::map<Option,bool_func> bool_convert_;
  typedef std::set<bool> (*set_bool_func)(Option,std::map<Option, std::any>); 
  std::map<Option,set_bool_func> set_bool_convert_;
  typedef std::set<std::string> (*set_str_func)(Option,std::map<Option, std::any>); 
  std::map<Option,set_str_func> set_str_convert_;
  typedef std::set<int> (*set_int_func)(Option,std::map<Option, std::any>); 
  std::map<Option,set_int_func> set_int_convert_;
  typedef std::vector<bool> (*vector_bool_func)(Option,std::map<Option, std::any>); 
  std::map<Option,vector_bool_func> vector_bool_convert_;
  typedef std::vector<std::string> (*vector_str_func)(Option,std::map<Option, std::any>); 
  std::map<Option,vector_str_func> vector_str_convert_;

  // Convert from the supported types to the default to store it
  typedef std::any (*int_func_to_default)(Option,std::map<Option, std::any>, std::any); 
  std::map<Option,int_func_to_default> int_convert_to_default_;
  typedef std::any (*size_t_func_to_default)(Option,std::map<Option, std::any>, std::any); 
  std::map<Option,size_t_func_to_default> size_t_convert_to_default_;
  typedef std::any (*double_func_to_default)(Option,std::map<Option, std::any>, std::any); 
  std::map<Option,double_func_to_default> double_convert_to_default_;
  typedef std::any (*str_func_to_default)(Option,std::map<Option, std::any>, std::any); 
  std::map<Option,str_func_to_default> str_convert_to_default_;
  typedef std::any (*bool_func_to_default)(Option,std::map<Option, std::any>, std::any); 
  std::map<Option,bool_func_to_default> bool_convert_to_default_;
  typedef std::any (*set_bool_func_to_default)(Option,std::map<Option, std::any>, std::any); 
  std::map<Option,set_bool_func_to_default> set_bool_convert_to_default_;
  typedef std::any (*set_str_func_to_default)(Option,std::map<Option, std::any>, std::any); 
  std::map<Option,set_str_func_to_default> set_str_convert_to_default_;
  typedef std::any (*set_int_func_to_default)(Option,std::map<Option, std::any>, std::any); 
  std::map<Option,set_int_func_to_default> set_int_convert_to_default_;
  typedef std::any (*vector_bool_func_to_default)(Option,std::map<Option, std::any>, std::any); 
  std::map<Option,vector_bool_func_to_default> vector_bool_convert_to_default_;
  typedef std::any (*vector_str_func_to_default)(Option,std::map<Option, std::any>, std::any); 
  std::map<Option,vector_str_func_to_default> vector_str_convert_to_default_;

  std::any convert_to_default_(const Option option, const std::any & val) {
      std::string error_msg = "Missing conversion to default function for option ";
      if (val.type() == typeid(int)) {
        if( int_convert_to_default_.count(option) ) { 
          return int_convert_to_default_[option](option,options_, val);
        } else {
          throw std::runtime_error(error_msg + option + 
              ", converting from type int.");
        }
      } else if (val.type() == typeid(size_t)) { 
        if( size_t_convert_to_default_.count(option) ) { 
          return size_t_convert_to_default_[option](option,options_, val);
        } else {
          throw std::runtime_error(error_msg + option + 
              ", converting from type size_t.");
        }
      } else if (val.type() == typeid(double)) { 
        if ( double_convert_to_default_.count(option) ) {
          return double_convert_to_default_[option](option,options_, val);
        }else {
          throw std::runtime_error(error_msg + option + ", converting from type double.");
        }
      } else if (val.type() == typeid(std::string)) { 
        if ( str_convert_to_default_.count(option) ) {
          return str_convert_to_default_[option](option,options_, val);
        }else {
          throw std::runtime_error(error_msg + option + 
              ", converting from  type string.");
        }
      } else if (val.type() == typeid(bool)) { 
        if ( bool_convert_to_default_.count(option) ) {
          return bool_convert_to_default_[option](option,options_, val);
        }else {
          throw std::runtime_error(error_msg + option + 
              ", converting from  type bool.");
        }
      } else if (val.type() == typeid(std::set<std::string>)) { 
        if ( set_str_convert_to_default_.count(option) ) {
          return set_str_convert_to_default_[option](option,options_, val);
        }else {
          throw std::runtime_error(error_msg + option + 
              ", converting from  type set<string>.");
        }
      } else if (val.type() == typeid(std::set<bool>)) { 
        if ( set_bool_convert_to_default_.count(option) ) {
          return set_bool_convert_to_default_[option](option,options_, val);
        }else {
          throw std::runtime_error(error_msg + option + 
              ", converting from  type set<bool>.");
        }
      } else if (val.type() == typeid(std::set<int>)) { 
        if ( set_int_convert_to_default_.count(option) ) {
          return set_int_convert_to_default_[option](option,options_, val);
        }else {
          throw std::runtime_error(error_msg + option + 
              ", converting from  type set<int>.");
        }
      }
      throw std::runtime_error("Conversion to the proposed default type is not supported for option " + option);
  }

  template<class T>
    T convert_(Option option) const {
      std::variant<int,size_t,double,std::string,bool,std::set<std::string>,std::set<bool>, std::set<int>, std::vector<std::string>> val;
      if (typeid(T) == typeid(int)) {
        if( int_convert_.count(option) ) { 
          return std::get<T>(val = int_convert_.at(option)(option,options_));
        } else {
          throw std::runtime_error("Missing conversion function for type int.");
        }
      } else if (typeid(T) == typeid(size_t)) { 
        if( size_t_convert_.count(option) ) { 
          return std::get<T>(val = size_t_convert_.at(option)(option,options_));
        } else {
          throw std::runtime_error("Missing conversion function for type size_t.");
        }
      } else if (typeid(T) == typeid(double)) { 
        if ( double_convert_.count(option) ) {
          return std::get<T>(val = double_convert_.at(option)(option,options_));
        }else {
          throw std::runtime_error("Missing conversion function for type double.");
        }
      } else if (typeid(T) == typeid(std::string)) { 
        if ( str_convert_.count(option) ) {
          return std::get<T>(val = str_convert_.at(option)(option,options_));
        }else {
          throw std::runtime_error("Missing conversion function for type string.");
        }
      } else if (typeid(T) == typeid(bool)) { 
        if ( bool_convert_.count(option) ) {
          return std::get<T>(val = bool_convert_.at(option)(option,options_));
        }else {
          throw std::runtime_error("Missing conversion function for type bool.");
        }
      } else if (typeid(T) == typeid(std::set<std::string>)) { 
        if ( set_str_convert_.count(option) ) {
          return std::get<T>(val = set_str_convert_.at(option)(option,options_));
        }else {
          throw std::runtime_error("Missing conversion function for type set<string>.");
        }
      } else if (typeid(T) == typeid(std::set<bool>)) { 
        if ( set_bool_convert_.count(option) ) {
          return std::get<T>(val = set_bool_convert_.at(option)(option,options_));
        }else {
          throw std::runtime_error("Missing conversion function for type set<bool>.");
        }
      } else if (typeid(T) == typeid(std::set<int>)) { 
        if ( set_int_convert_.count(option) ) {
          return std::get<T>(val = set_int_convert_.at(option)(option,options_));
        }else {
          throw std::runtime_error("Missing conversion function for type set<int>.");
        }
      }
      throw std::runtime_error("Conversion to the proposed type is not supported");
  }

 public:
  virtual ~PropertyObject(void) { }

  virtual bool propValid(const std::any &value) = 0;

  virtual PropertyType getPropertyType(void) const noexcept = 0;

  std::vector<Option> getPropertyOptions(void) const {
    std::vector<Option> options;
    for ( std::pair<Option,std::any> option : options_){
      options.push_back(option.first); 
    }
    return options;
  } 

  // Setup the valid options associated with the parameter
  // WARNING setting a property value will overwrite existing values
  void setPropOption(Option option, const std::any & val) {
    if (!propOptionValid_(option)) {
      throw std::invalid_argument("Property option is unrecognized.");
    }
    setPropOption_(option, val);
  }

  template<class T>
  T getPropOption(const Option &option) const {
    if (!propOptionValid_(option)) {
      std::string err = " An unrecognized property option was detected.";
      throw std::invalid_argument(err);
    }

    if ( !conversionAllowed_(option, typeid(T)) ){
      std::string err = "Conversion of property option's value to type not allowed.";
      throw std::invalid_argument(err);
    }
 
    return convert_<T>(option);
    //return std::any_cast<T>(options_.at(option));
  }

  virtual void postCheck(void) const { return; }
};

}  // namespace mamap
#endif  // _MAMAP_PROPERTY_OBJECT_HPP
