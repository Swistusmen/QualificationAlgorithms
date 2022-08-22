#include "Qualifier.h"

template<typename T>
bool Qualifier<T>::operator()(const std::vector<T>& vec)
{
    auto result=std::find_if(vec.begin(),vec.end(),[this](const auto& elem){
        return elem==val;
    });
    return result!=vec.end();
}