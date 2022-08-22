#pragma once
#include <vector>
#include <algorithm>
#include <map>
#include <numeric>
#include <string>
#include "Qualifier.h"
#include "Qualifier.cpp"
#include "VectorMap.h"
#include "VectorMap.cpp"

template<typename T>
class DecisionTree{
    public:
        DecisionTree(std::vector<std::vector<T>> _data): Data(std::move(_data)){}

        void calculate();
        std::vector<std::pair<std::vector<std::pair<T,bool>>,float>> getDecisionTreeRepresentation(){return output;};
        std::vector<std::pair<std::vector<T>,float>> shrinkTableToContainingGoal(const T&) const;
        std::pair<std::vector<T>,float> findBestRecommmendation(const T&) const;

    private:
        std::vector<std::pair<T,int>> getOrderedSet();
        std::vector<std::pair<T,float>> calculateGiniIndexes(const std::vector<std::pair<T,int>>&);
        std::vector<Qualifier<T>> createQualifiers(std::vector<std::pair<T,float>>&);
        std::vector<std::pair<std::vector<std::pair<T,bool>>,float>> createDesisionTree(std::vector<Qualifier<T>>, std::vector<std::pair<T,bool>>, std::vector<std::vector<T>>);

    private:
        std::vector<std::pair<std::vector<std::pair<T,bool>>,float>> output; 
        std::vector<std::vector<T>> Data;
        T goal;
};