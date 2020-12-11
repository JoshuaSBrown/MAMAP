#include "mamap/arguments/properties/propertyobject.hpp"
#include "mamap/arguments/properties/propertystring.hpp"

#include <any>
#include <map>
#include <memory>

using namespace std;

namespace mamap { 
  namespace {

    std::any convertIntBoundToDefault_(std::any val) {
      int value = std::any_cast<int>(val);
      if ( value < 0 ) {
        throw std::runtime_error("Cannot convert option value to size_t because int value is less than 0.");
      }
      size_t default_val = static_cast<size_t>(value);
      std::any converted_val = default_val;
      return converted_val;
    }

    std::any convertSizeTBoundToDefault_(std::any val) {
      return val;
    }

    int getIntBoundValues_(Option option, std::map<Option, std::any> options_){
      size_t stored_value = std::any_cast<size_t>(options_.at(option));
      return static_cast<int>(stored_value);
    }

    size_t getSizeTBoundValues_(Option option, std::map<Option, std::any> options_){
      size_t stored_value = std::any_cast<size_t>(options_.at(option));
      return stored_value;
    }

  } // namespace

  PropertyString::PropertyString(void) {

    default_option_type_.insert(std::pair<Option, type_index>(Option::MIN_LENGTH, type_index(typeid(size_t))));
    default_option_type_.insert(std::pair<Option, type_index>(Option::MAX_LENGTH, type_index(typeid(size_t))));

    allowed_option_types_[Option::MIN_LENGTH].push_back(type_index(typeid(size_t)));
    allowed_option_types_[Option::MIN_LENGTH].push_back(type_index(typeid(int)));
    allowed_option_types_[Option::MAX_LENGTH].push_back(type_index(typeid(size_t)));
    allowed_option_types_[Option::MAX_LENGTH].push_back(type_index(typeid(int)));

    int_convert_[Option::MIN_LENGTH] = &mamap::getIntBoundValues_;
    size_t_convert_[Option::MIN_LENGTH] = &mamap::getSizeTBoundValues_;
    int_convert_[Option::MAX_LENGTH] = &mamap::getIntBoundValues_;
    size_t_convert_[Option::MAX_LENGTH] = &mamap::getSizeTBoundValues_;

    int_convert_to_default_[Option::MIN_LENGTH] = &mamap::convertIntBoundToDefault_;
    size_t_convert_to_default_[Option::MIN_LENGTH] = &mamap::convertSizeTBoundToDefault_;
    int_convert_to_default_[Option::MAX_LENGTH] = &mamap::convertIntBoundToDefault_;
    size_t_convert_to_default_[Option::MAX_LENGTH] = &mamap::convertSizeTBoundToDefault_;

    // Set Defaults
    size_t min_len = 0;
    size_t max_len = -1;
    setPropOption_(Option::MIN_LENGTH, min_len);
    setPropOption_(Option::MAX_LENGTH, max_len);
  }

  bool PropertyString::propValid(const std::any& value) {

    std::string val;
    if ( value.type() == typeid(char *) ) {
      val = std::string(std::any_cast<char *>(value));
    } else if ( value.type() == typeid(const char *) ) {
      val = std::string(std::any_cast<const char *>(value));
    } else {
      val = std::any_cast<std::string>(value);
    } 

    if (val.size() > getPropOption<size_t>(Option::MAX_LENGTH)) {
      string err = "The string is larger than allowed " + val +
        " the "
        "maximum allowed value is " +
        to_string(getPropOption<size_t>(Option::MAX_LENGTH));
      throw invalid_argument(err);
    } else if (val.size() < getPropOption<size_t>(Option::MIN_LENGTH)) {
      string err = "The string is smaller than allowed " + val +
        " the "
        "maximum allowed value is " +
        to_string(getPropOption<size_t>(Option::MIN_LENGTH));
      throw invalid_argument(err);
    }
    return true;
  }

} // namespace mamap
