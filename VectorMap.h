#pragma once
#include <vector>
#include <algorithm>

template<typename T>
class VectorMap{
public:
    std::vector<std::pair<std::vector<T>,float>> getTable(){return nodes;}
    void insert(const std::vector<T>& , const float);
private:
    bool canInsert(int currentIndex,std::vector<int> indexes,const std::vector<T>& values);
    std::vector<std::pair<std::vector<T>,float>> nodes;
};