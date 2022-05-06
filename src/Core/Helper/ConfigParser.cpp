//
// Created by Даниил on 05.05.2022.
//

#include "ConfigParser.h"

void ConfigParser::parse(const std::string& path)
{
    stream.open(path);

    if(!stream.is_open())
        std::cout << "File is not open!" << std::endl;

    std::string delimiter = "=";
    std::string str;

    while(std::getline(stream, str))
    {
        std::string name;
        std::string value;

        name = str.substr(0,str.find(delimiter));
        value = str.substr(str.find(delimiter)+1, str.length()-1);

        elements.insert({name, value});
    }

    stream.close();
}

std::string ConfigParser::lookupString(const std::string& name)
{
    return elements.find(name)->second;
}

int ConfigParser::lookupInt(const std::string& name)
{
    return std::stoi(elements.find(name)->second);
}

float ConfigParser::lookupFloat(const std::string& name)
{
    return std::stof(elements.find(name)->second);
}

bool ConfigParser::lookupBool(const std::string& name)
{
    return elements.find(name)->second == "true"  ||
            elements.find(name)->second == "True" ||
            elements.find(name)->second == "1";
}