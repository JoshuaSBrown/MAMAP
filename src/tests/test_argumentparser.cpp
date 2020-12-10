
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "argumentparser.hpp"
#include "arguments/argumenttypes.hpp"
#include "arguments/properties/propertytypes.hpp"
#include "arguments/properties/propertyoptions.hpp"
#include "string_support.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace mamap;
using namespace std;

TEST_CASE("Argument Parser","[unit]") {

  cerr << "Testing: ArgumentParser" << endl;
  cerr << "Testing: constructor" << endl;
  {
    vector<string> flag = {
      "-p_P", "--punfile-pair",
      "File containing dimer of two "
        "monomers. This file should have the .pun extension."};
    set<vector<string>> flags;
    flags.insert(flag);
    ArgumentParser ArgPars(flags);
  }
}

TEST_CASE("Argument Parser Show Usage","[unit]"){ 
  vector<string> flag1 = {
    "-p_P", "--punfile-pair",
    "File containing dimer of two "
      "monomers. This file should have the .pun extension."};
  vector<string> flag2 = {"-p_1", "--punfile-mon1",
    "File containing monomer 1"};
  vector<string> flag3 = {"-homo", "--homo-level", "HOMO molecular orbital"};

  set<vector<string>> flags;
  flags.insert(flag1);
  flags.insert(flag2);
  flags.insert(flag3);

  ArgumentParser ArgPars(flags);
  ArgPars.showUsage();
}

TEST_CASE("Argument Parser setFlagArgOpt","[unit]"){ 
    vector<string> flag1 = {
      "-p_P", "--punfile-pair",
      "File containing dimer of two "
        "monomers. This file should have the .pun extension."};
    vector<string> flag2 = {"-p_1", "--punfile-mon1",
      "File containing monomer 1"};
    vector<string> flag3 = {"-homo", "--homo-level", "HOMO molecular orbital"};

    set<vector<string>> flags;
    flags.insert(flag1);
    flags.insert(flag2);
    flags.insert(flag3);

    ArgumentParser ArgPars(flags);

    string val = ".pun";
    ArgPars.setFlagArgOpt(
        "--punfile-pair", 
        ArgumentType::FILES,
        PropertyType::FILE_EXT,
        Option::ALLOWED_VALUES, val);

    string val2 = ".7";
    ArgPars.setFlagArgOpt(
        "--punfile-pair",
        ArgumentType::FILES,
        PropertyType::FILE_EXT,
        Option::ALLOWED_VALUES, val2);
    string val3 = ".orb";
    ArgPars.setFlagArgOpt(
        "--punfile-pair",
        ArgumentType::FILES,
        PropertyType::FILE_EXT,
        Option::ALLOWED_VALUES, val3);
}

TEST_CASE("Argument Parser parse command","[unit]"){ 
  vector<string> flag1 = {
    "-p_P", "--punfile-pair",
    "File containing dimer of two "
      "monomers. This file should have the .pun extension."};
  vector<string> flag2 = {"-p_1", "--punfile-mon1",
    "File containing monomer 1"};
  vector<string> flag3 = {"-homo", "--homo-level", "HOMO molecular orbital"};

  set<vector<string>> flags;
  flags.insert(flag1);
  flags.insert(flag2);
  flags.insert(flag3);

  ArgumentParser ArgPars(flags);

  string val = ".pun";
  string val2 = ".7";
  string val3 = ".orb";
  set<string> exts = {val, val2, val3};
  ArgPars.setFlagArgOpt(
      "--punfile-pair",
      ArgumentType::FILES,
      PropertyType::FILE_EXT,
      Option::ALLOWED_VALUES, exts);
  ArgPars.setFlagArgOpt(
      "--punfile-mon1",
      ArgumentType::FILES,
      PropertyType::FILE_EXT,
      Option::ALLOWED_VALUES, exts);
  ArgPars.setFlagArgOpt(
      "--punfile-mon2",
      ArgumentType::FILES,
      PropertyType::FILE_EXT,
      Option::ALLOWED_VALUES, exts);

  ArgPars.setFlagArgOpt(
      "--punfile-pair",
      ArgumentType::FILES,
      PropertyType::FILE_EXISTS,
      Option::MUST_EXIST, true);
  ArgPars.setFlagArgOpt(
      "--punfile-mon1",
      ArgumentType::FILES,
      PropertyType::FILE_EXISTS,
      Option::MUST_EXIST, false);
  ArgPars.setFlagArgOpt(
      "--punfile-mon2",
      ArgumentType::FILES,
      PropertyType::FILE_EXISTS,
      Option::MUST_EXIST, true);

  int argc = 7;
  const char* argv[7];  // = {"calc_J","--punfile-pair", "testfile.pun",
  // "--punfile-mon1","file.orb"};
  argv[0] = "calc_J";
  argv[1] = "--punfile-pair";
  argv[2] = "testfile.pun";
  argv[3] = "--punfile-mon1";
  argv[4] = "file.orb";
  argv[5] = "--punfile-mon2";
  argv[6] = "testfile.pun";
  ArgPars.parse(argv, argc);

  argc = 7;
  const char* argv2[7];
  argv2[0] = "calc_J";
  argv2[1] = "--punfile-pair";
  argv2[2] = "testfile.pun";
  argv2[3] = "--punfile-mon1";
  argv2[4] = "file.orb";
  argv2[5] = "--punfile-mon2";
  argv2[6] = "fort.7";

  CHECK_THROWS(ArgPars.parse(argv2, argc));
}

TEST_CASE("Argument Parser get command","[unit]"){ 
  vector<string> flag1 = {
    "-p_P", "--punfile-pair",
    "File containing dimer of two "
      "monomers. This file should have the .pun extension."};
  vector<string> flag2 = {"-p_1", "--punfile-mon1",
    "File containing monomer 1"};
  vector<string> flag3 = {"-homo", "--homo-level", "HOMO molecular orbital"};

  set<vector<string>> flags;
  flags.insert(flag1);
  flags.insert(flag2);
  flags.insert(flag3);

  ArgumentParser ArgPars(flags);

  string val = ".pun";
  string val2 = ".7";
  string val3 = ".orb";
  set<string> exts = {val, val2, val3};
  ArgPars.setFlagArgOpt(
      "--punfile-pair", 
      ArgumentType::FILES,
      PropertyType::FILE_EXT,
      Option::ALLOWED_VALUES, exts);
  ArgPars.setFlagArgOpt(
      "--punfile-mon1",
      ArgumentType::FILES,
      PropertyType::FILE_EXT,
      Option::ALLOWED_VALUES, exts);
  vector<string> sis_exts{".log"};
  ArgPars.setFlagArgOpt(
      "--punfile-mon1",
      ArgumentType::FILES,
      PropertyType::SISTER_FILE,
      Option::ALLOWED_VALUES,".log");

  const int argc = 5;
  const char* argv[argc];
  argv[0] = "calc_J";
  argv[1] = "--punfile-pair";
  argv[2] = "file.orb";
  argv[3] = "--punfile-mon1";
  argv[4] = "testfile.pun";
  ArgPars.parse(argv, argc);

  std::vector<string> fileName = ArgPars.get<string>("--punfile-pair");
  CHECK(fileName.at(0).compare("file.orb") == 0);
  std::vector<string> fileName2 = ArgPars.get<string>("--punfile-mon1");
  CHECK(fileName2.at(0).compare("testfile.pun") == 0);
}

TEST_CASE("Argument Parser get multiple args to same flag","[unit]"){ 

  WHEN("Testing file arugments") {
    vector<string> flag1 = {
      "-p_P", "--punfile-pair",
      "File containing dimer of two "
        "monomers. This file should have the .pun extension."};
    set<vector<string>> flags;
    flags.insert(flag1);

    ArgumentParser ArgPars(flags);

    string val = ".pun";
    string val2 = ".7";
    string val3 = ".orb";
    set<string> exts = {val, val2, val3};
    ArgPars.setFlagArgOpt(
        "--punfile-pair", 
        ArgumentType::FILES,
        PropertyType::FILE_EXT,
        Option::ALLOWED_VALUES, exts);

    const int argc = 5;
    const char* argv[argc];
    argv[0] = "calc_J";
    argv[1] = "--punfile-pair";
    argv[2] = "file.orb";
    argv[3] = "testfile.pun";
    ArgPars.parse(argv, argc);

    std::vector<string> fileName = ArgPars.get<string>("--punfile-pair");
    CHECK(fileName.at(0) == "file.orb");
    CHECK(fileName.at(1) == "testfile.pun");
  }

  WHEN("Testing numeric arguments"){
    vector<string> flag1 = {
      "-num", "--numbers",
      "Numbers to read in"};
    set<vector<string>> flags;
    flags.insert(flag1);

    ArgumentParser ArgPars(flags);

    ArgPars.setFlagArgOpt(
        "--numbers", 
        ArgumentType::NUMERIC,
        PropertyType::NUMERIC,
        Option::MAX, 11);
    ArgPars.setFlagArgOpt(
        "--numbers", 
        ArgumentType::NUMERIC,
        PropertyType::NUMERIC,
        Option::MIN, 0);


    const int argc = 3;
    const char* argv[argc];
    argv[0] = "calc_J";
    argv[1] = "--numbers";
    // 12 is outside the maximum
    argv[2] = "12";
    CHECK_THROWS(ArgPars.parse(argv, argc));
 
  }
}

TEST_CASE("Argument Parser getting numerical types","[unit]"){ 
  WHEN("All parameters are allowed to be positive") {
    vector<string> flag1 = {
      "-num", "--numbers",
      "Numbers to read in"};
    set<vector<string>> flags;
    flags.insert(flag1);

    ArgumentParser ArgPars(flags);

    ArgPars.setFlagArgOpt(
        "--numbers", 
        ArgumentType::NUMERIC,
        PropertyType::NUMERIC,
        Option::MAX, 11);
    ArgPars.setFlagArgOpt(
        "--numbers", 
        ArgumentType::NUMERIC,
        PropertyType::NUMERIC,
        Option::MIN, 0);


    const int argc = 5;
    const char* argv[argc];
    argv[0] = "calc_J";
    argv[1] = "--numbers";
    argv[2] = "0";
    argv[3] = "3";
    argv[4] = "11";
    ArgPars.parse(argv, argc);

    std::vector<int> numbers = ArgPars.get<int>("--numbers");
    CHECK(numbers.at(0) == 0);
    CHECK(numbers.at(1) == 3);
    CHECK(numbers.at(2) == 11);


    std::vector<double> numbers_double = ArgPars.get<double>("--numbers");
    CHECK(numbers_double.at(0) == Approx(0));
    CHECK(numbers_double.at(1) == Approx(3));
    CHECK(numbers_double.at(2) == Approx(11));

    std::vector<size_t> numbers_size_t = ArgPars.get<size_t>("--numbers");
    CHECK(numbers_size_t.at(0) == 0);
    CHECK(numbers_size_t.at(1) == 3);
    CHECK(numbers_size_t.at(2) == 11);
  }

  WHEN("Some arguments are negative how is casting affected"){
    vector<string> flag1 = {
      "-num", "--numbers",
      "Numbers to read in"};
    set<vector<string>> flags;
    flags.insert(flag1);

    ArgumentParser ArgPars(flags);

    ArgPars.setFlagArgOpt(
        "--numbers", 
        ArgumentType::NUMERIC,
        PropertyType::NUMERIC,
        Option::MAX, 11);
    ArgPars.setFlagArgOpt(
        "--numbers", 
        ArgumentType::NUMERIC,
        PropertyType::NUMERIC,
        Option::MIN, -5);

    const int argc = 5;
    const char* argv[argc];
    argv[0] = "calc_J";
    argv[1] = "--numbers";
    argv[2] = "-4";
    argv[3] = "3.21";
    argv[4] = "11";
    ArgPars.parse(argv, argc);

    
    std::vector<int> numbers = ArgPars.get<int>("--numbers");
    CHECK(numbers.at(0) == -4);
    CHECK(numbers.at(1) == 3);
    CHECK(numbers.at(2) == 11);

    std::vector<double> numbers_double = ArgPars.get<double>("--numbers");
    CHECK(numbers_double.at(0) == Approx(-4));
    CHECK(numbers_double.at(1) == Approx(3.21));
    CHECK(numbers_double.at(2) == Approx(11));

    // Should throw because we have negative values
    CHECK_THROWS(ArgPars.get<size_t>("--numbers"));
  }

}
