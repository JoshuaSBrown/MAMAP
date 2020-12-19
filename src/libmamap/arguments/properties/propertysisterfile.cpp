
#include "mamap/arguments/properties/propertysisterfile.hpp"
#include "mamap/string_support.hpp"
#include <stdexcept>
#include <set>
#include <vector>
#include <sys/stat.h>

using namespace std;

namespace mamap {

  namespace {

    std::vector<std::string> getVecStr_(Option option, std::map<Option, std::any> options_) {
      return std::any_cast<std::vector<std::string>>(options_[option]);
    }

    std::set<std::string> getSetStr_(Option option, std::map<Option, std::any> options_) {
      std::set<string> values_new;
      std::vector<string> values = std::any_cast<std::vector<std::string>>(options_[option]);
      for ( auto value : values ) {
        values_new.insert(value);
      }
      return values_new;
    }

    std::string getStr_(Option option, std::map<Option, std::any> options_) {
      vector<string> values = std::any_cast<std::vector<std::string>>(options_[option]);
      if ( values.size()!=0 ){
        throw std::runtime_error("Cannot convert to string, there is more than one value.");
      }
      return values.at(0);
    }

    std::any convertVecStrToDefault_(std::any val){
      return val;
    }

    std::any convertSetStrToDefault_(std::any val){
      set<string> values = std::any_cast<std::set<std::string>>(val);
      std::vector<string> new_values;
      for ( auto value : values ) {
        new_values.push_back(value);
      }
      return new_values;
    }

    std::any convertStrToDefault_(std::any val){
      if( val.type() == typeid(string) ) {
        return std::vector<string>{std::any_cast<std::string>(val)};
      } else if (val.type() == typeid(const char *)) {
        return std::vector<string>{string(std::any_cast<const char *>(val))};
      } else if (val.type() == typeid(char *)) {
        return std::vector<string>{string(std::any_cast<char *>(val))};
      }
      throw std::runtime_error("Unable to convert supposed string to default, unrecognized type.");
    }

    std::vector<bool> getVecBoolEXIST_(Option option, std::map<Option, std::any> options_) {
      return std::any_cast<std::vector<bool>>(options_[option]);
    }

    std::vector<string> getVecStrEXIST_(Option option, std::map<Option, std::any> options_) {
      std::vector<bool> values = std::any_cast<std::vector<bool>>(options_[option]);
      std::vector<std::string> values_new;
      for ( const bool & value : values ) {
        if( value ) {
          values_new.push_back("true");
        } else {
          values_new.push_back("false");
        }
      }
      return values_new;
    }
    std::vector<int> getVecIntEXIST_(Option option, std::map<Option, std::any> options_) {
      std::vector<bool> values = std::any_cast<std::vector<bool>>(options_[option]);
      std::vector<int> values_new;
      for ( const bool & value : values ) {
        if( value ) {
          values_new.push_back(1);
        } else {
          values_new.push_back(0);
        }
      }
      return values_new;
    }

    std::any convertVecBoolEXISTToDefault_(std::any val) {
      return val;
    }

    std::any convertVecStrEXISTToDefault_(std::any val) {
      std::vector<string> values = std::any_cast<std::vector<string>>(val);
      std::vector<bool> values_new;
      for( string value : values ){
        if( to_upper(value).compare("TRUE")==0 ) {
          values_new.push_back(true);
        } else if( to_upper(value).compare("FALSE")==0) {
          values_new.push_back(false);
        }else if ( value == "0" ) {
          values_new.push_back(false);
        }else if ( value == "1" ) {
          values_new.push_back(true);
        } else if ( to_upper(value) == "ON") {
          values_new.push_back(true);
        } else if ( to_upper(value) == "OFF") {
          values_new.push_back(false);
        } else {
          throw std::runtime_error("Cannot convert vector of strings to vector of bools, unable to identify whether string should be true or false.");
        }
      } 
      return values_new;
    }

    std::any convertVecIntEXISTToDefault_(std::any val) {
      std::vector<int> values = std::any_cast<std::vector<int>>(val);
      std::vector<bool> values_new;
      for( int value : values ){
        if(value == 0 ) {
          values_new.push_back(true);
        }else {
          values_new.push_back(false);
        }
      }
      return values;
    }
  }

  PropertySisterFile::PropertySisterFile(void) {

    // Set Default type
    default_option_type_.insert(std::pair<Option, type_index>(Option::ALLOWED_VALUES, type_index(typeid(vector<string>))));
    default_option_type_.insert(std::pair<Option, type_index>(Option::FILE_NAME, type_index(typeid(vector<string>))));
    default_option_type_.insert(std::pair<Option, type_index>(Option::FILE_PATH, type_index(typeid(vector<string>))));
    default_option_type_.insert(std::pair<Option, type_index>(Option::FILE_PATH_NAME, type_index(typeid(vector<string>))));
    default_option_type_.insert(std::pair<Option, type_index>(Option::DOES_EXIST, type_index(typeid(vector<bool>))));

    // Stores the extensions 
    allowed_option_types_[Option::ALLOWED_VALUES].push_back(type_index(typeid(vector<string>)));
    allowed_option_types_[Option::ALLOWED_VALUES].push_back(type_index(typeid(set<string>)));
    allowed_option_types_[Option::ALLOWED_VALUES].push_back(type_index(typeid(string)));
    allowed_option_types_[Option::FILE_NAME].push_back(type_index(typeid(vector<string>)));
    allowed_option_types_[Option::FILE_PATH].push_back(type_index(typeid(vector<string>)));
    allowed_option_types_[Option::FILE_PATH_NAME].push_back(type_index(typeid(vector<string>)));
    allowed_option_types_[Option::DOES_EXIST].push_back(type_index(typeid(vector<bool>)));
    allowed_option_types_[Option::DOES_EXIST].push_back(type_index(typeid(vector<string>)));
    allowed_option_types_[Option::DOES_EXIST].push_back(type_index(typeid(vector<int>)));

    vector_str_convert_[Option::ALLOWED_VALUES] = &mamap::getVecStr_;
    set_str_convert_[Option::ALLOWED_VALUES] = &mamap::getSetStr_;
    str_convert_[Option::ALLOWED_VALUES] = &mamap::getStr_;
    vector_str_convert_[Option::FILE_NAME] = &mamap::getVecStr_;
    vector_str_convert_[Option::FILE_PATH] = &mamap::getVecStr_;
    vector_str_convert_[Option::FILE_PATH_NAME] = &mamap::getVecStr_;

    vector_bool_convert_[Option::DOES_EXIST] = &mamap::getVecBoolEXIST_;
    vector_str_convert_[Option::DOES_EXIST] = &mamap::getVecStrEXIST_;
    vector_int_convert_[Option::DOES_EXIST] = &mamap::getVecIntEXIST_;

    vector_str_convert_to_default_[Option::ALLOWED_VALUES] = &mamap::convertVecStrToDefault_;
    set_str_convert_to_default_[Option::ALLOWED_VALUES] = &mamap::convertSetStrToDefault_;
    str_convert_to_default_[Option::ALLOWED_VALUES] = &mamap::convertStrToDefault_;
    vector_str_convert_to_default_[Option::FILE_NAME] = &mamap::convertVecStrToDefault_;
    vector_str_convert_to_default_[Option::FILE_PATH] = &mamap::convertVecStrToDefault_;
    vector_str_convert_to_default_[Option::FILE_PATH_NAME] = &mamap::convertVecStrToDefault_;

    vector_bool_convert_to_default_[Option::DOES_EXIST] = &mamap::convertVecBoolEXISTToDefault_;
    vector_str_convert_to_default_[Option::DOES_EXIST] = &mamap::convertVecStrEXISTToDefault_;
    vector_int_convert_to_default_[Option::DOES_EXIST] = &mamap::convertVecIntEXISTToDefault_;


    // Set Defaults
    setPropOption_(Option::ALLOWED_VALUES, vector<string>{"NOT_DEFINED"});
    setPropOption_(Option::FILE_NAME, vector<string>{"NOT_DEFINED"});
    setPropOption_(Option::FILE_PATH, vector<string>{"NOT_DEFINED"});
    setPropOption_(Option::FILE_PATH_NAME, vector<string>{"NOT_DEFINED"});
    setPropOption_(Option::DOES_EXIST, vector<bool>{false});
  }

  bool PropertySisterFile::fileExist(const string& fileNamePath) const {
    struct stat buf;
    return (stat(fileNamePath.c_str(), &buf) == 0);
  }

  void PropertySisterFile::extSupported(const string& ext) const {
    checkExt(ext);
    auto exts_ = getPropOption<std::set<std::string>>(Option::ALLOWED_VALUES);
    for (auto ext_ : exts_) {
      if (ext_.compare(ext) == 0) {
        return;
      }
    }
    string err = "The file ext " + ext + " is unsupported";
    throw invalid_argument(err);
  }

  void PropertySisterFile::checkExt(const string& ext) const {
    string excess = grabStrBeforeLastOccurance(ext, ".");
    if (excess.compare("") != 0) {
      throw invalid_argument(
          "An extension must be of type '.ext'"
          "you have used " +
          ext);
    }
    return;
  }

  bool PropertySisterFile::propValid(const std::any & name_and_path) {

    std::string fileNamePath; 
    if ( name_and_path.type() == typeid(char *) ) {
      fileNamePath = std::string(std::any_cast<char *>(name_and_path));
    } else if ( name_and_path.type() == typeid(const char *) ) {
      fileNamePath = std::string(std::any_cast<const char *>(name_and_path));
    } else if ( name_and_path.type() == typeid(const std::string) ) {
      fileNamePath = std::any_cast<const std::string>(name_and_path);
    } else if ( name_and_path.type() == typeid(std::string) ) {
      fileNamePath = std::any_cast<std::string>(name_and_path);
    } else {
      std::runtime_error("Unrecognized property value!.");
    }

    string fileName = lastStringInPath(fileNamePath);

    string path = getPath(fileNamePath);

    string sisterFileCore = grabStrBeforeLastOccurance(fileName, ".");
    auto sister_exts = getPropOption<std::set<std::string>>(Option::ALLOWED_VALUES);
    vector<string> fileNames;
    vector<string> filePaths;
    vector<string> filePathNames;
    vector<bool> fileExists;

    for (auto sister_ext : sister_exts) {
      
      if (sister_ext.compare("NOT_DEFINED") != 0) {
        string sisterFileName = sisterFileCore + sister_ext;
        string sisterPath = path + sisterFileName;

        fileNames.push_back(sisterFileName);
        filePaths.push_back(path);
        filePathNames.push_back(sisterPath);
        if (fileExist(sisterPath)) {
          fileExists.push_back(true);
        } else {
          fileExists.push_back(false);
        }
      } else {
        throw std::runtime_error("Sister file extensions have not been specified for " + fileName);
      }
    }

    setPropOption_(Option::FILE_NAME, fileNames);
    setPropOption_(Option::FILE_PATH, filePaths);
    setPropOption_(Option::FILE_PATH_NAME, filePathNames);
    setPropOption_(Option::DOES_EXIST, fileExists);
    return true;
  }
}
