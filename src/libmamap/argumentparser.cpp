#include <exception>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <sys/stat.h>
#include <typeindex>
#include <vector>

#include "mamap/argumentparser.hpp"

#include "mamap/mamap_config.hpp"
#include "mamap/string_support.hpp"

using namespace std;

namespace mamap {

  std::unique_ptr<ArgumentObject> createArgument(ArgumentType type) {
    if (type == ArgumentType::NUMERIC) {
      return std::unique_ptr<ArgumentObject>(new ArgumentNumerical);
    } else if (type == ArgumentType::STRING) {
      return std::unique_ptr<ArgumentObject>(new ArgumentString);
    } else if (type == ArgumentType::SWITCH) {
      return std::unique_ptr<ArgumentObject>(new ArgumentSwitch);
    } else if (type == ArgumentType::FILES) {
      return std::unique_ptr<ArgumentObject>(new ArgumentFile);
    }
    return std::unique_ptr<ArgumentObject>();
  }

  ArgumentParser::ArgumentParser(set<vector<string>> flags) {

    vector<string> flag_help;
    flag_help.push_back("--help");
    flag_help.push_back("-h");
    flag_help.push_back("Display help message");
    flags.insert(flag_help);

    maxShortFlagSize = 0;
    maxFullFlagSize = 0;
    maxDescriptionSize = 0;

    for (auto flag : flags) {

      if (flag.size() > 3) {
        throw invalid_argument(
            "Flags may only be passed with a max of three "
            "values: full flag name, abbreviated name, and flag description");
      }

      string full_flag = "NO_FLAG_SPECIFIED";
      string short_flag = "NO_SHORT_FLAG_SPECIFIED";
      string desc = "NO_DESCRIPTION_GIVEN";

      bool description = false;
      bool abbreviation = false;
      bool flag_name = false;
      for (auto item : flag) {
        trim(item);
        string doubledash = firstN(item, 2);
        string singledash = firstN(item, 1);
        if (doubledash.compare("--") == 0) {
          if (flag_name) {
            string err = "A flag name has already been suppied:\n";
            err.append(full_flag);
            err.append("\nNow you are supplying a second one:\n");
            err.append(item);
            throw invalid_argument(err);
          }
          full_flag = item;
          defaults_set_[item] = false;
          flag_name = true;
          if (full_flag.size() > maxFullFlagSize) {
            maxFullFlagSize = full_flag.size();
          }
        } else if (singledash.compare("-") == 0) {
          if (abbreviation) {
            string err = "A flag name has already been suppied:\n";
            err.append(short_flag);
            err.append("\nNow you are supplying a second one:\n");
            err.append(item);
            throw invalid_argument(err);
          }
          short_flag = item;
          abbreviation = true;
          if (short_flag.size() > maxShortFlagSize) {
            maxShortFlagSize = short_flag.size();
          }
        } else {
          if (description) {
            string err = "A description has already been suppied:\n";
            err.append(desc);
            err.append("\nNow you are supplying a second one:\n");
            err.append(item);
            throw invalid_argument(err);
          }
          desc = item;
          description = true;
          if (desc.size() > maxDescriptionSize) {
            maxDescriptionSize = desc.size();
          }
        }
      }
      if (!flag_name) {
        throw invalid_argument("You have failed to provide the full flag name");
      }
      flags_[full_flag] = make_pair(short_flag, desc);
    }
  }

  void ArgumentParser::showUsage(void) {
    cout << endl;
    cout << endl;
    cout << "Options:" << endl;
    cout << endl;

    for (auto item : flags_) {
      string full_flag = item.first;
      size_t diff = maxFullFlagSize - full_flag.size();
      cout << full_flag;
      for (size_t i = 0; i <= diff; ++i) {
        cout << " ";
      }
      string short_flag = item.second.first;
      diff = maxShortFlagSize - short_flag.size();
      cout << short_flag;
      for (size_t i = 0; i <= diff; ++i) {
        cout << " ";
      }

      size_t space = maxFullFlagSize + maxShortFlagSize + 2;
      size_t allowed = maxLineLength - space;
      string space_block = "";
      for (size_t sp = 0; sp < space; sp++) {
        space_block.append(" ");
      }

      string desc = item.second.second;
      vector<string> vec_string = splitSt(desc);
      size_t words_size = 0;
      for (auto word : vec_string) {
        words_size += word.size() + 1;
        if (words_size < allowed) {
          cout << word << " ";
        } else {
          cout << endl;
          cout << space_block;
          cout << word << " ";
          words_size = 0;
        }
      }
      cout << endl;
      cout << endl;
    }
    cout << endl;
  }

  void ArgumentParser::addFlagArg(string flag, ArgumentType argname) {
    arg_[flag].push_back(createArgument(argname));
  }
  
  bool ArgumentParser::nextParameterIsAFlag_(size_t index,
                                             vector<string> arguments) {

    if ((index + 1) < arguments.size()) {
      for (auto flag : flags_) {
        if (flag.first.compare(arguments.at(index + 1)) == 0) {
          return true;
        } else if (flag.second.first.compare(arguments.at(index + 1)) == 0) {
          return true;
        }
      }
    }
    return false;
  }

  size_t ArgumentParser::parseArg_(size_t index, vector<string> arguments) {
    string flag = arguments.at(index);
    // If the abbreviated flag is passed we need to resolve the full flag name
    if (flags_.count(flag) == 0) {
      for (auto item : flags_) {
        if (item.second.first.compare(flag) == 0) {
          flag = item.first;
          break;
        }
      }
    }

    bool unrecognized = true;

    // Parse String Arguments
    if (arg_.count(flag) != 0) {

      ArgumentType type = arg_[flag].front()->getArgumentType(); 
      // Switch does not require an argument
      if ( type == ArgumentType::SWITCH && 
          (nextParameterIsAFlag_(index, arguments) ||
           (index + 1) >= arguments.size())){
      
        std::cout << "Type is a switch" << std::endl;
        unrecognized = false;
        if(defaults_set_[flag] == true ){
          values_[flag].at(0) = "true";
        }else {
          values_[flag].emplace_back("true");
        }
      } else { 
        if ((index + 1) >= arguments.size()) {
          string err = "" + flag + " Missing arguments";
          throw runtime_error(err);
        }
        int arg_index = 0;
        do { // Allow reading of multiple arguments
          string argument = arguments.at(index + 1);
          std::cout << "Parsing argument " << argument << std::endl;
          if ( arg_index != 0){
            // Need to duplicate the argument
            addFlagArg(flag, type);
            ArgumentType type = arg_[flag].front()->getArgumentType();
            std::vector<PropertyType> arg_props = arg_[flag].front()->getProperties();
              
            auto values = arg_[flag].front()->getPropertyValues();
            arg_[flag].push_back(createArgument(type));
            arg_[flag].back()->setValues(values);
            // TODO Need to specify index setFlagArgOpt(flag, arg_name, property, option, val);
          }
          arg_[flag].at(arg_index)->argValid(argument);
          unrecognized = false;
          if (defaults_set_.count(flag) ) {
            if(defaults_set_[flag] == true ){
              values_[flag].clear();
              //addValue_(flag,argument);
              values_[flag].emplace_back(argument);
              defaults_set_[flag] = false;
            } else {
              //addValue_(flag,argument);
              values_[flag].emplace_back(argument);
            }
          }
          ++index;
          ++arg_index;
          
          if( (index+1) >= arguments.size() ) break;
        } while ( arguments.at(index+1).at(0) != '-' );
      }
    }

    if (unrecognized) {
      throw invalid_argument("The flag " + flag + " was unrecognized");
    }
    return index;
  }

  void ArgumentParser::postParseCheck(void) {
    //for (std::pair<std::string, std::vector<std::unique_ptr<ArgumentObject>>> & flag_arg : arg_) {
    for (auto & flag_arg : arg_) {
      for ( std::unique_ptr<ArgumentObject> & arg : flag_arg.second ){
        arg->postArgCheck();
      }
    }
  }

  void ArgumentParser::parse(const char* argv[], int argc) {

    // Convert to vector of strings
    vector<string> arguments(argv , argv + argc);

    std::cout << "All arguments" << std::endl;
    for (std::string & str : arguments ) {
      std::cout << str << std::endl;
    }

    if (argc <= 1) {
      cout << "Usage: " << arguments.at(0) << " <options(s)> SOURCES";
      showUsage();
      throw runtime_error("Must provide arguments");
    }

    string help_flag = "--help";
    string help_flag_short = "-h";
    string citation_flag = "--citation";
    string citation_flag_short = "-cite";
    string version_flag = "--version";
    string version_flag_short = "-v";

    size_t allowed_args_before_exit = 2;
    size_t index = 1;
    for (; index < arguments.size(); ++index) {
      std::cout << "Arg loop index " << index << " size " << arguments.size() << " argument is " << arguments.at(index) << std::endl;
      std::cout << "Arg 0 val " << arguments.at(0) << std::endl;
      std::cout << "Arg size -1 val " << arguments.back() << std::endl;
      if (help_flag.compare(arguments.at(index)) == 0 ||
          help_flag_short.compare(arguments.at(index)) == 0) {
        cout << "Usage: " << arguments.at(0) << " <options(s)> SOURCES";
        showUsage();
        if (allowed_args_before_exit == arguments.size()) {
          exit(0);
        }
        ++allowed_args_before_exit;
      } else if (version_flag.compare(arguments.at(index)) == 0 ||
                 version_flag_short.compare(arguments.at(index)) == 0) {
        exit(0);
      } else if (citation_flag.compare(arguments.at(index)) == 0 ||
                 citation_flag_short.compare(arguments.at(index)) == 0) {
        cout << "\nCitation: " << mamap_AUTHOR_SURNAME << ", ";
        cout << mamap_AUTHOR_INITIALS << " (";
        cout << mamap_YEAR_PUBLISHED << "). ";
        cout << mamap_TITLE << " (Version ";
        cout << mamap_VERSION_MAJOR << ".";
        cout << mamap_VERSION_MINOR << "). [Software]. Available from ";
        cout << mamap_URL << ".\n\n";
        if (allowed_args_before_exit == arguments.size()) {
          exit(0);
        }
        ++allowed_args_before_exit;
      } else {
        std::cout << "Index before " << index << " size " << arguments.size() << " argument " << arguments.at(index) << std::endl;
        index = parseArg_(index, arguments);
        std::cout << "Index after " << index << " size " << arguments.size() << " argument " << arguments.at(index) << std::endl;
      }
    }
    postParseCheck();
  }
}
