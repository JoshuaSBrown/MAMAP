#include "mamap/arguments/argumentobject.hpp"

namespace mamap {

  std::string operator+(std::string str, const ArgumentType arg) {
    if( arg == ArgumentType::NUMERIC ) {
      str += "NUMERIC";
    }else if(arg == ArgumentType::FILES ) {
      str += "FILES";
    } else if( arg == ArgumentType::STRING ) {
      str += "STRING";
    } else if ( arg == ArgumentType::SWITCH ) {
      str += "SWITCH";
    } 
    return str;
  }
}
