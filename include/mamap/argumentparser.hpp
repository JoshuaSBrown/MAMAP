#ifndef _MAMAP_ARGUMENTPARSER_HPP
#define _MAMAP_ARGUMENTPARSER_HPP
#include <any>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <sstream>
#include <unordered_set>
#include <utility>

#include "arguments/argumentnumerical.hpp"
#include "arguments/argumentfile.hpp"
#include "arguments/argumentstring.hpp"
#include "arguments/argumentswitch.hpp"

namespace mamap {

  std::unique_ptr<ArgumentObject> createArgument(ArgumentType type);

class ArgumentParser {
  public:
    struct Citation {
      std::string project_AUTHOR_SURNAME;
      std::string project_AUTHOR_INITIALS;
      std::string project_YEAR_PUBLISHED;
      std::string project_TITLE;
      std::string project_VERSION_MAJOR;
      std::string project_VERSION_MINOR;
      std::string project_VERSION_PATCH;
      std::string project_URL;
    };
 private:
  // 1 - flag name
  // 2 - type
  std::map<std::string, std::vector<std::unique_ptr<ArgumentObject>>> arg_;

  // Known rules
  std::set<std::string> argument_types_;

  // Keeps a list of the flags that were parsed
  std::unordered_set<std::string> flags_parsed_;

  // Known flags and their description
  std::map<std::string, std::pair<std::string, std::string>> flags_;

  std::map<std::string, bool> defaults_set_;

  // Arguments that are stored when argc and argv are parsed
  // by default will be stored as a string
  std::map<std::string,  std::vector<std::string>> values_;

  size_t parseArg_(size_t index, std::vector<std::string> arguments);

  // Determine if the next value in arguments vector is a recognized flag
  bool nextParameterIsAFlag_(size_t index, std::vector<std::string> arguments);

  size_t maxShortFlagSize;
  size_t maxFullFlagSize;
  size_t maxDescriptionSize;
  size_t maxLineLength = 80;

  Citation citation_;
 public:

  // 1 - short flag
  // 2 - long flag
  // 3 - description
  explicit ArgumentParser(std::set<std::vector<std::string>> flags);

  void setCitation(const Citation & citation) {
    citation_ = citation;
  }
  // Set Defaults for the flags in the case that they are not found
  template<class T>
  void setFlagDefaultValue(std::string flag,const T & val) {
    std::stringstream ss;
    ss << val;
    values_[flag].push_back(ss.str());
    defaults_set_[flag] = true;
  }

  // Add a argument without setting any of the values
  void addFlagArg(std::string flag, ArgumentType argname);


  size_t getNumArgs(const std::string & flag) const noexcept {
    if( values_.count(flag) ) {
      return values_.at(flag).size();
    }
    return 0;
  }

  // Set the rules for the flag and the type it is associated with types
  // include:
  // "FILES"
  // "NUMERICAL"
  // "STRING"
  // "SWITCH"
  // The rules are dependent on the type
  template<class T>
    void setFlagArgOpt(
        const std::string & flag, 
        ArgumentType argname,
        PropertyType property,
        Option option,
        T val) {

      
      if (arg_.count(flag) == 0) {
        auto arg = createArgument(argname);
        arg->setArgPropertyOpt(property, option, val);
        arg_[flag].push_back(std::move(arg));
      } else {
        for ( std::unique_ptr<ArgumentObject> & ptr : arg_[flag]){
          try {
            ptr->setArgPropertyOpt(property, option, val);
          } catch (std::exception & e) {
            std::stringstream ss;
            ss << "Error in setFlagArgOpt with flag (" + flag + ")"; 
            ss << "\n" + std::string(e.what());
            throw std::runtime_error(ss.str());
          }
        }
      }

    }

  template<class T>
  T getFlagArgOptValue(
      const std::string & flag,
      int index,
      ArgumentType type,
      PropertyType property,
      Option option) const {

    if(arg_.count(flag) == 0) {
      throw std::runtime_error("Flag is unknown");
    }
    if(index>arg_.at(flag).size()) {
      throw std::runtime_error("Index is larger than the number of flags");
    }
    T val;
    try {
      val = arg_.at(flag).at(index)->getPropertyValues<T>(property,option);
    } catch (std::exception & e) {
      std::stringstream ss;
      ss << "Error in getFlagArgOptValue with flag (" + flag + ")"; 
      ss << "\n" + std::string(e.what());
      throw std::runtime_error(ss.str());
    }
    return val;
  }

  template<class T>
  std::vector<T> getFlagArgOptValues(
      const std::string & flag,
      ArgumentType type,
      PropertyType property,
      Option option) const {

    if(arg_.count(flag) == 0) {
      throw std::runtime_error("Flag is unknown" + flag);
    }
    std::vector<T> values;
    try {
      for ( const auto & val : arg_.at(flag)){
        values.push_back(val->getPropertyValues<T>(property,option));
      }
    } catch (std::exception & e) {
      std::stringstream ss;
      ss << "Error in getFlagArgOptValues with flag (" + flag + ")"; 
      ss << "\n" + std::string(e.what());
      throw std::runtime_error(ss.str());
    }
    return values;
  }


  /**
   * @brief Returns whether the flag was parsed when the arguments were read in. 
   *
   * @param flag
   *
   * @return true or false 
   */
  bool flagParsed(const std::string & flag) const noexcept {
    return flags_parsed_.count(flag);
  }

  template<class T>
  std::vector<T> get(const std::string & flag) const {
    if(arg_.count(flag) == 0) {
      throw std::runtime_error("Flag is unknown cannot get argument " + flag);
    }
    std::vector<T> values;
    ArgumentType type = arg_.at(flag).front()->getArgumentType(); 
    if(type == ArgumentType::SWITCH || typeid(T) == typeid(bool)){
      if(values_.count(flag) == 0) {
        throw std::runtime_error("No values stored for flag " + flag);
      }
      for ( const std::string & val : values_.at(flag) ){
        if (std::is_arithmetic_v<T>) {
          if(val=="true") {
            std::variant<std::string,int,double,long,size_t,float,bool> var = 1;
            values.push_back(std::get<T>(var));
          } else {
            std::variant<std::string,int,double,long,size_t,float,bool> var = 0;
            values.push_back(std::get<T>(var));
          } 
        } else {
          std::variant<std::string,int,double,long,size_t,float,bool> var = val;
          values.push_back(std::get<T>(var));
        }
      }
    }else {
      if(values_.count(flag) == 0) {
        throw std::runtime_error("No values stored for flag " + flag);
      }
      for ( const std::string & val : values_.at(flag) ){
        if( std::is_unsigned<T>::value ) {
          if(val.size() > 0) {
            if(val[0] == '-'){
              throw std::runtime_error("You are attempting to convert a signed value to an unsigned value " + val);
            }
          }  
        }
        std::stringstream ss;
        ss << val;
        T value;
        ss >> value;
        values.push_back(value);
      }
    }
    return values;
  }

  void postParseCheck(void);
  void parse(const char* argv[], int argc);
  void showUsage();
};

}  // namespace mamap
#endif  // _MAMAP_ARGUMENTPARSER_HPP
