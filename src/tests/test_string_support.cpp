
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "string_support.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace mamap;
using namespace std;

TEST_CASE("String Support","[unit]") {

  cerr << "Testing: splitSt" << endl;
  {
    string str = "Hello World    Lot of space";
    vector<string> v_str = splitSt(str);
    CHECK(v_str.at(0).compare("Hello") == 0);
    CHECK(v_str.at(1).compare("World") == 0);
    CHECK(v_str.at(2).compare("Lot") == 0);
    CHECK(v_str.at(3).compare("of") == 0);
    CHECK(v_str.at(4).compare("space") == 0);
  }

  cerr << "Testing: lastN" << endl;
  {
    string str = "Hi there!";
    string var = lastN(str, 3);
    CHECK(var.compare("re!") == 0);
  }

  cerr << "Testing: lastStringInPath" << endl;
  {
    string str = "Path/To/Important/File.cc";
    string fileName = lastStringInPath(str);
    CHECK(fileName.compare("File.cc") == 0);
  }

  cerr << "Testing: getPath" << endl;
  {
    string str = "Path/To/Important/File.cc";
    string filePath = getPath(str);
    cerr << filePath << endl;
    CHECK(filePath.compare("Path/To/Important/") == 0);
    string str2 = "File.cc";
    string str3 = getPath(str2);
    CHECK(str3.compare("") == 0);
  }

  cerr << "Testing: cut_end" << endl;
  {
    string str = "Important words";
    string var = cut_end(str, 3);
    CHECK(var.compare("Important wo") == 0);
  }

  cerr << "Testing: foundStrInSubStr" << endl;
  {
    string str = "This is my world.";
    CHECK(foundSubStrInStr(str, "my"));
    CHECK(!foundSubStrInStr(str, "nothing"));

    string str2 =
        " Alpha  occ. eigenvalues --  -10.20023 -10.19942 -10.19578 -10.19497  "
        "-0.76368";
    CHECK(foundSubStrInStr(str2, " Alpha  occ. eigenvalues --"));
  }

  cerr << "Testing: isAlphabetical" << endl;
  {
    string str = "This has spaces";
    CHECK(isAlphabetical(str) == false);
    string str2 = "JustLetters";
    CHECK(isAlphabetical(str2) == true);
    string str3 = "";
    CHECK(isAlphabetical(str3) == false);
  }

  cerr << "Testing: grabStrAfterFisrtOccurance" << endl;
  {
    string str = "Words and Numbers 023D-23 blah";
    string str2 = grabStrAfterFirstOccurance(str, "D");
    CHECK(str2.compare("-23 blah") == 0);
    string str3 = grabStrAfterFirstOccurance(str, "MOM");
    CHECK(str3.compare("") == 0);
  }

  cerr << "Testing: grabStrAfterLastOccurance" << endl;
  {
    string str = "This.is.a.file.name";
    string str2 = grabStrAfterLastOccurance(str, ".");
    CHECK(str2.compare("name") == 0);
    string str3 = "NoExtfilename";
    string str4 = grabStrAfterLastOccurance(str3, ".");
    CHECK(str4.compare("") == 0);
  }

  cerr << "Testing: grabStrBeforeFisrtOccurance" << endl;
  {
    string str = "Words and Numbers 023D-23 blah";
    string str2 = grabStrBeforeFirstOccurance(str, "D");
    CHECK(str2.compare("Words and Numbers 023") == 0);
    string str3 = grabStrBeforeFirstOccurance(str, "DADA");
    CHECK(str3.compare(str) == 0);
  }

}

TEST_CASE("String foundSubStrInStr","[unit]") {
  string str = "This is the day of tomorrow";
  string substr = "day";
  CHECK(foundSubStrInStr(str,substr));
}

TEST_CASE("String remove SubStr","[unit]") {
  string str = "This is the day of tomorrow";
  string substr = "day ";
  string line = removeSubStr(str, substr);
  CHECK(line.compare("This is the of tomorrow") == 0);
}

TEST_CASE("remove everything between two substrings","[unit]") {
  string str = "This is the day of tomorrow";
  string substr1 = " is";
  string substr2 = "of";
  string line = removeEverythingBetweenAndIncluding(str,substr1,substr2);
  std::cout << str << std::endl;
  std::cout << substr1 << std::endl;
  std::cout << substr2 << std::endl;
  std::cout << line << std::endl;
  CHECK(line.compare("This tomorrow") == 0);
}

TEST_CASE("get everything between two substrings","[unit]") {
  string str = "This is the day of tomorrow";
  string substr1 = " is ";
  string substr2 = " of";
  string line = getEverythingBetweenAndExcluding(str,substr1,substr2);
  std::cout << str << std::endl;
  std::cout << substr1 << std::endl;
  std::cout << substr2 << std::endl;
  std::cout << line << std::endl;
  CHECK(line.compare("the day") == 0);
}

