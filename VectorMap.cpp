#include "VectorMap.h"

template<typename T>
void VectorMap<T>::insert(const std::vector<T>& values, const float percentage)
{
    if(values.empty()){
        return;
    }
    if(nodes.empty()){
        nodes.emplace_back(values,percentage);
        return;
    }

    std::vector<int> indexes;
    const int noVectors=nodes.size();
    int currentIndex{0};
    for(int i=0;i<noVectors;i++){
        if(nodes[i].first[0]==values[0]){
            indexes.push_back(i);
        }
    }
    currentIndex++;
    if(canInsert(currentIndex,indexes,values)){
        nodes.emplace_back(values,percentage);
    }
}

template<typename T>
bool VectorMap<T>::canInsert(int currentIndex,std::vector<int> indexes,const std::vector<T>& values)
{
    if(values.size()==currentIndex&&!indexes.empty()){
        return false;
    }
    if(values.size()==currentIndex&&indexes.empty()){
        return true;
    }
    if(indexes.empty()){
        return true;
    }
    std::vector<int> buffer;
    for(const auto& it: indexes){
        if((nodes[it].first.size()>=currentIndex+1)&&nodes[it].first[currentIndex]==values[currentIndex]){
            buffer.push_back(it);
        }
    }
    indexes=buffer;
    currentIndex++;
    return canInsert(currentIndex,indexes,values);
}