
#include "propertyfileext.hpp"
#include "string_support.hpp"
#include <stdexcept>
#include <sys/stat.h>

using namespace std;

namespace mamap {

  namespace {

    string getStrValues_(Option option, std::map<Option, std::any> options_) {
      set<string> vals = any_cast<set<string>>(options_.at(option));
      if (vals.size() > 1 ) {
        throw std::runtime_error("Cannot convert set of string to string when there is more than one value.");
      }
      if ( vals.size() == 1 ) {
        return *vals.begin();
      }
      return "";
    }

    set<string> getSetStrValues_(Option option, std::map<Option, std::any> options_) {
      return any_cast<set<string>>(options_.at(option));
    }

    std::any convertStrToDefault_(Option option, std::map<Option, std::any> options, std::any val) {
      return set<string>{any_cast<string>(val)};
    }
    std::any convertSetStrToDefault_(Option option, std::map<Option, std::any> options, std::any val) {
      return val;
    }
  }


  PropertyFileExt::PropertyFileExt(string ext) : PropertyFileExt(set<string>{ext}) {
  }

  PropertyFileExt::PropertyFileExt(set<string> exts) {

    default_option_type_.insert(std::pair<Option, type_index>(Option::ALLOWED_VALUES, type_index(typeid(set<string>))));

    allowed_option_types_[Option::ALLOWED_VALUES].push_back(type_index(typeid(string)));
    allowed_option_types_[Option::ALLOWED_VALUES].push_back(type_index(typeid(set<string>)));

    str_convert_[Option::ALLOWED_VALUES] = &mamap::getStrValues_;
    set_str_convert_[Option::ALLOWED_VALUES] = &mamap::getSetStrValues_;

    str_convert_to_default_[Option::ALLOWED_VALUES] = &mamap::convertStrToDefault_;
    set_str_convert_to_default_[Option::ALLOWED_VALUES] = &mamap::convertSetStrToDefault_;

    for (const std::string & ext : exts) {
      checkExt(ext);
    }

    // Set Defaults
    setPropOption_(Option::ALLOWED_VALUES, exts);
  }

  void PropertyFileExt::extSupported(const string& ext) const {
    checkExt(ext);
    auto exts_ = getPropOption<std::set<std::string>>(Option::ALLOWED_VALUES);
    for (const std::string & ext_ : exts_) {
      if (ext_[0] == '*') {
        return;
      } else if (ext_.compare(ext) == 0) {
        return;
      }
    }
    string err = "The file ext " + ext + " is unsupported";
    throw invalid_argument(err);
  }

  void PropertyFileExt::checkExt(const string& ext) const {
    if (ext.compare("") == 0) {
      return;
    } else if (ext[0] == '*') {
      return;
    } else {
      string excess = grabStrBeforeLastOccurance(ext, ".");
      if (excess.compare("") != 0) {
        throw invalid_argument(
            "An extension must be of type '.ext','*','', "
            "you have used " +
            ext);
      }
    }
    return;
  }

  void PropertyFileExt::setPropOption(Option option,
      std::set<std::string> vars) {
    PropertyObject::setPropOption(option, vars);
  }

  void PropertyFileExt::setPropOption(Option option, std::string var) {
    set<string> vars;
    vars.insert(var);
    PropertyObject::setPropOption(option, vars);
  }

  bool PropertyFileExt::propValid(const any & fileNamePath) {

    std::string filepath;
    if ( fileNamePath.type() == typeid(char *) ) {
      filepath = std::string(std::any_cast<char *>(fileNamePath));
    } else if ( fileNamePath.type() == typeid(const char *) ) {
      filepath = std::string(std::any_cast<const char *>(fileNamePath));
    } else {
      filepath = std::any_cast<std::string>(fileNamePath);
    } 
    string ext = grabStrAfterLastOccuranceInclusive(filepath, ".");
    extSupported(ext);
    return true;
  }

}
