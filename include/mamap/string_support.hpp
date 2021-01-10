
#ifndef _MAMAP_STRING_SUPPORT_HPP_
#define _MAMAP_STRING_SUPPORT_HPP_

#include <string>
#include <vector>

namespace mamap {

// Split a std::string up by spaces
std::vector<std::string> splitSt(const std::string & input);

// Given a path name this function finds the last part
// in the path which should be associated with the path
// /director/structure/File.cc
// passing this path into the function will return File.cc
std::string lastStringInPath(const std::string& input);

// Grab Path only leave off the file name
std::string getPath(std::string input);

// Grabs the last n characters of a string
std::string lastN(std::string input, int n);

// Removes the last n characters from a string
std::string cut_end(std::string input, int n);

std::string firstN(std::string input, int n);

std::string cut_beg(std::string input, int n);

// Converts a string to an upper case version
std::string to_upper(std::string input);

// trim from both ends (in place)
void trim(std::string &s);

// trim from start (copying)
std::string ltrimmed(std::string s);

// trim from end (copying)
std::string rtrimmed(std::string s);

// trim from both ends (copying)
std::string trimmed(std::string s);

bool constains(const std::string & str, const std::string & substr);

// Remove everything in str that is part and between str1 and str2
// E.g.
// std::string str = "bladh (fdls) fda";
//
// new_str = removeEverythingBetweenAndIncluding(str,"(",")");
//
// where new_str becomes
//
// "bladh  fda";
//
std::string removeEverythingBetweenAndIncluding(
    std::string str,
    const std::string & str1,
    const std::string & str2);

std::string getEverythingBetweenAndExcluding(
    std::string str,
    const std::string & str1,
    const std::string & str2);

std::string removeSubStr(std::string line, const std::string & substr);

void removeSpace(std::string s);

// Grab everything after the first occurance of a string.
std::string grabStrAfterFirstOccurance(std::string s, std::string occ);

std::string grabStrAfterLastOccurance(std::string s, std::string occ);

std::string grabStrAfterLastOccuranceInclusive(std::string s, std::string occ);

// Grab everything before first occurance of a string
std::string grabStrBeforeFirstOccurance(std::string s, std::string occ);

std::string grabStrBeforeLastOccurance(std::string s, std::string occ);

std::string grabStrBeforeLastOccuranceInclusive(std::string s, std::string occ);

// Determine if the sub string exists within the string
bool foundSubStrInStr(std::string s, std::string sub_s);

// Determine if whole string is alphabetical characters
bool isAlphabetical(std::string s);

}  // namespace mamap
#endif  // _MAMAP_STRING_SUPPORT_HPP_
