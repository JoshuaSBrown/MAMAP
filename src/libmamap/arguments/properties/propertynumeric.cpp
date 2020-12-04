
#include "propertynumeric.hpp"

#include "propertyobject.hpp"

#include <limits>
#include <sstream>
#include <typeinfo>

using namespace std;

namespace mamap {
/*void PropertyNumeric::setPropOption_(const Option & option, const std::any & val) {
  if ( val.type() != typeid(double)){
    string err = "The Min and Max options of the numeric property must be a double.";
    throw invalid_argument(err);
  }
  PropertyObject::setPropOption_(option, val);
}*/

namespace {

  std::any convertIntBoundToDefault_(Option option, std::map<Option, std::any> options, std::any val) {
    return static_cast<double>(std::any_cast<int>(val));
  }

  std::any convertSizeTBoundToDefault_(Option option, std::map<Option, std::any> options, std::any val) {
    return static_cast<double>(std::any_cast<size_t>(val));
  }

  std::any convertDoubleBoundToDefault_(Option option, std::map<Option, std::any> options, std::any val) {
    return val;
  }

  int getIntBoundValues_(Option option, std::map<Option, std::any> options_){
    return static_cast<int>(std::any_cast<double>(options_.at(option)));
  }

  size_t getSizeTBoundValues_(Option option, std::map<Option, std::any> options_){
    return static_cast<size_t>(std::any_cast<double>(options_.at(option)));
  }

  double getDoubleBoundValues_(Option option, std::map<Option, std::any> options_){
    return std::any_cast<double>(options_.at(option));
  }

}

PropertyNumeric::PropertyNumeric(void) {
    default_option_type_.insert(std::pair<Option, type_index>(Option::MIN, type_index(typeid(double))));
    default_option_type_.insert(std::pair<Option, type_index>(Option::MAX, type_index(typeid(double))));

    allowed_option_types_[Option::MIN].push_back(type_index(typeid(size_t)));
    allowed_option_types_[Option::MIN].push_back(type_index(typeid(int)));
    allowed_option_types_[Option::MIN].push_back(type_index(typeid(double)));
    allowed_option_types_[Option::MAX].push_back(type_index(typeid(size_t)));
    allowed_option_types_[Option::MAX].push_back(type_index(typeid(int)));
    allowed_option_types_[Option::MAX].push_back(type_index(typeid(double)));

    int_convert_[Option::MIN] = &mamap::getIntBoundValues_;
    size_t_convert_[Option::MIN] = &mamap::getSizeTBoundValues_;
    double_convert_[Option::MIN] = &mamap::getDoubleBoundValues_;
    int_convert_[Option::MAX] = &mamap::getIntBoundValues_;
    size_t_convert_[Option::MAX] = &mamap::getSizeTBoundValues_;
    double_convert_[Option::MAX] = &mamap::getDoubleBoundValues_;

    int_convert_to_default_[Option::MIN] = &mamap::convertIntBoundToDefault_;
    size_t_convert_to_default_[Option::MIN] = &mamap::convertSizeTBoundToDefault_;
    double_convert_to_default_[Option::MIN] = &mamap::convertDoubleBoundToDefault_;
    int_convert_to_default_[Option::MAX] = &mamap::convertIntBoundToDefault_;
    size_t_convert_to_default_[Option::MAX] = &mamap::convertSizeTBoundToDefault_;
    double_convert_to_default_[Option::MAX] = &mamap::convertDoubleBoundToDefault_;

    // Set Defaults
    double min_val = std::numeric_limits<double>::lowest();
    std::cout << "Min val set to " << min_val << std::endl;
    double max_val = std::numeric_limits<double>::max();
    std::cout << "Max val set to " << max_val << std::endl;
    setPropOption_(Option::MIN, min_val);
    setPropOption_(Option::MAX, max_val);
}

bool PropertyNumeric::propValid(const std::any & val) {

  // If the properties have not been set then they will be 
  // valid as long as they are of a numeric type
  double converted_val;
  if ( val.type() == typeid(int) ){
    converted_val = static_cast<double>(any_cast<int>(val));
  } else if (val.type() == typeid(double)) {
    converted_val = any_cast<double>(val);
  } else if ( val.type() == typeid(size_t) ){
    converted_val = static_cast<double>(any_cast<size_t>(val));
  } else if (val.type() == typeid(const double)) {
    converted_val = any_cast<const double>(val);
  } else if ( val.type() == typeid(const size_t) ){
    converted_val = static_cast<double>(any_cast<const size_t>(val));
  } else if (val.type() == typeid(const int)) {
    converted_val = static_cast<double>(any_cast<const int>(val));
  } else {
    string err = "The value provided to the property is not a supported type.";
    throw invalid_argument(err);
  }

  // ignore it otherwise, there is no min option 
  double min_val = any_cast<double>(options_[Option::MIN]);
  if ( converted_val < min_val ) {
    std::stringstream err;
    err <<  "The value provided to the property is less than the minimum allowed. The value passed in is "  << converted_val << " the minimum allowed value is "  << min_val;
    throw invalid_argument(err.str());
  }
  // ignore it otherwise, there is no min option 
  double max_val = any_cast<double>(options_[Option::MAX]);
  if ( converted_val > max_val ) {
    std::stringstream err;
    err <<  "The value provided to the property is greater than the maximum allowed. The value passed in is "  << converted_val << " the minimum allowed value is "  << max_val;
    throw invalid_argument(err.str());
  }
  return true;
}

} // namespace mamap
