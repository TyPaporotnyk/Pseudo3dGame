//
// Created by Даниил on 05.05.2022.
//

#ifndef PSEUDO3DGAME_CONFIGPARSER_H
#define PSEUDO3DGAME_CONFIGPARSER_H

#include <sstream>
#include <fstream>
#include <iostream>
#include <map>

class ConfigParser
{
private:
    std::fstream stream;
    std::map<std::string, std::string> elements;

public:
    void parse(const std::string& path);

    std::string lookupString(const std::string& name);

    int lookupInt(const std::string& name);

    float lookupFloat(const std::string& name);

    bool lookupBool(const std::string& name);
};


#endif //PSEUDO3DGAME_CONFIGPARSER_H
