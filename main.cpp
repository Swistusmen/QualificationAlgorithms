#include <iostream>
#include "DecisionTree.h"
#include "DecisionTree.cpp"
#include "CSVReader.h"

int main(){
    auto df=readCSV("sample.csv");
    DecisionTree<std::string> tree(df);
    tree.calculate();

    auto result=tree.shrinkTableToContainingGoal("owca");
    for(const auto& it: result){
        for(const auto& i:it.first){
            std::cout<<i<<", ";
        }
        std::cout<<": "<<it.second<<std::endl;
    }
    tree.findBestRecommmendation("owca");
    return 0;
}