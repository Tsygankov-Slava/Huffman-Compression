#pragma once

#include <iostream>
#include <map>
#include <string>

/**
 * The Flag class describes the flag that the user passes to us
 */
class Flag {
public:
    std::string name;      /** flag name*/
    bool isRequiredFlag;   /** does this flag have to be present when the program starts */
    bool isContainsValue;  /** should the flag contain a value */
    std::string value;     /** the flag value that is added after the flag */
    bool isPassed = false; /** has this flag been entered */

    Flag(std::string name, bool isRequiredFlag, bool isContainsValue) : name(std::move(name)), isRequiredFlag(isRequiredFlag), isContainsValue(isContainsValue){};
};

/**
 * The CLI class describes the command line interface
 * He is engaged in reading flags and checking for the validity of the transmitted information
 * All errors related to the transmitted information are handled in this class
 */
class CLI {
    int argc;
    char **argv;

public:
    std::map<std::string, Flag> flags;
    enum ParseState { WRONG,
                      EXIT,
                      OK };

public:
    explicit CLI(int argc, char *argv[]) : argc(argc), argv(argv){};
    CLI &flag(const std::string &name, bool requiredField = false, bool containsValue = false);
    ParseState parse();

private:
    ParseState parseFlags();
    CLI::ParseState checkRequiredFlags();
    CLI::ParseState checkFiles();
};
