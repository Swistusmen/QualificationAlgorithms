#include <iostream>
#include "DecisionTree.h"
#include "DecisionTree.cpp"
#include "CSVReader.h"
#include <chrono>
#include <string>

int main(){
    auto df=readCSV("store_data.csv");
    DecisionTree<std::string> tree(df);
    auto begin=std::chrono::steady_clock::now();
    tree.calculate();

    auto bestMatch=tree.findBestRecommmendation("chocolate");
    auto bestMatchTime=std::chrono::steady_clock::now();
    auto result=tree.shrinkTableToContainingGoal("chocolate");
    auto resultTime=std::chrono::steady_clock::now();
    std::cout<<"best match time: "<<std::chrono::duration_cast<std::chrono::milliseconds>(bestMatchTime-begin).count()<<std::endl;
    std::cout<<"shrink table time: "<<std::chrono::duration_cast<std::chrono::milliseconds>(bestMatchTime-resultTime).count()<<std::endl;

    std::cout<<"BEST MATCH\n\n";
    for(const auto& it: bestMatch.first){
        std::cout<<it<<", ";
    }
    std::cout<<bestMatch.second<<std::endl;
    std::cout<<"\n\n TABLE \n";
    for(const auto& it: result){
        for(const auto& i:it.first){
            std::cout<<i<<", ";
        }
        std::cout<<": "<<it.second<<std::endl;
    }
    return 0;
}