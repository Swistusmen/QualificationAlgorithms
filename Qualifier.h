#pragma once
#include <algorithm>
#include <functional>

template<typename T>
class Qualifier{
    public:
        Qualifier(T element):val(element){};
        //Qualifier(T element, std::function<bool(const T&)>);

        bool operator()(const std::vector<T>& );
        T getVal() const {return val;}
    private:
        T val;
    //std::function<bool(const std::vector<T>&)> question;
};