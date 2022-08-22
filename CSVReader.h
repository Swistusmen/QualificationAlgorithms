#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

std::vector<std::string> splitString(const std::string& str){
    std::vector<std::string> output;
    std::string buffer{""};
    for(const auto& it: str){
        if(it!=','){
                buffer+=it;
        }
        else{
            if(buffer!=""){
            output.push_back(buffer);
            buffer="";
            }
        }
    }
    return output;
}

std::vector<std::vector<std::string>>readCSV(const std::string& filename){
    std::vector<std::vector<std::string>> data;
    std::ifstream file(filename);
    std::string buffer{""};
    while(std::getline(file,buffer)){
        data.push_back(splitString(buffer));
        buffer="";
    }
    return data;
}