#include "DecisionTree.h"

template<typename T>
std::pair<std::vector<T>,float> DecisionTree<T>::findBestRecommmendation(const T& value) const
{
    auto table=shrinkTableToContainingGoal(value);
    auto highestValue=std::max_element(table.begin(),table.end(),[](const auto& p1, const auto&p2){
        return p1.second<p2.second;
    })->second;

    int bestMatch{-1};
    for(int i=0;i<table.size();i++){
        if(table[i].second==highestValue){
            if(bestMatch==-1){
                bestMatch=i;
            }else{
                if(table[i].first.size()<table[bestMatch].first.size()){
                    bestMatch=i;
                }
            }
        }
    } 
    return table[bestMatch];
}

template<typename T>
std::vector<std::pair<std::vector<T>,float>> DecisionTree<T>::shrinkTableToContainingGoal(const T& goal) const
{
    VectorMap<T> map;
    for(const auto&it: output){
        for(const auto&i: it.first){
            if(i.first==goal&&i.second==true && it.second!=0.0f){
                std::vector<T> buffer;
                for(const auto& d:it.first){
                    if(d.second!=false){
                        buffer.emplace_back(d.first);
                    }
                }
                if(buffer.size()>1){
                map.insert(buffer,it.second);
                }
            }
        }
    }
    return map.getTable();
}

template<typename T>
void DecisionTree<T>::calculate()
{
    auto set=getOrderedSet();
    std::cout<<"Mam sety\n";
    auto ginis=calculateGiniIndexes(set);
    std::cout<<"Mam wspolczynniki giniego\n";
    auto qualifiers=createQualifiers(ginis);
    std::cout<<"Mam kwalifikatory\n";
    output=createDesisionTree(qualifiers, {},Data);
}

template<typename T>
std::vector<std::pair<T,int>> DecisionTree<T>::getOrderedSet()
{
    std::vector<std::pair<T,int>> set;

    for(const auto& row: Data){
        for(const auto& element: row){
            auto found=std::find_if(set.begin(),set.end(),[&element](const auto& p){
            return p.first==element;});

            if(found!=set.end()){
                set.at(found-set.begin()).second+=1;
            }else{
                set.emplace_back(element,1);
            }
        }
    }
    
    std::sort(set.begin(),set.end(),[](const auto& p1, const auto& p2){
        return p1.second<p2.second;
    });

    return set;
}

template<typename T>
std::vector<std::pair<T,float>> DecisionTree<T>::calculateGiniIndexes(const std::vector<std::pair<T,int>>& set)
{
    int totalNumberOfOccurancess{0};
    totalNumberOfOccurancess=std::accumulate(set.begin(),set.end(),totalNumberOfOccurancess,[](auto& p1, const auto& p2){
        return p1+p2.second;
    });
    const float avgNumberOfOcurrancess=static_cast<float>(totalNumberOfOccurancess/set.size());
    float dividend{0.0f};
    std::vector<std::pair<T,float>> ginis;
    const int noElements=set.size();

    for(int i=0;i<noElements;++i){
        dividend+=2*(1+i)-noElements-1;
        const auto G=dividend*set.at(i).second/(noElements*noElements*set.at(i).second);
        ginis.emplace_back(set.at(i).first,G);
    }

    return ginis;
}

template<typename T>
std::vector<Qualifier<T>> DecisionTree<T>::createQualifiers(std::vector<std::pair<T,float>>&  ginis)
{
    std::vector<Qualifier<T>> qualifiers;
    for(const auto& it: ginis){
        qualifiers.emplace_back(Qualifier(it.first));
    }
    return qualifiers;
}

template<typename T>
std::vector<std::pair<std::vector<std::pair<T,bool>>,float>> DecisionTree<T>::createDesisionTree(std::vector<Qualifier<T>> q, std::vector<std::pair<T,bool>> usedQ,std::vector<std::vector<T>> v)
{
    //TODO: optimize- write version with tail recursion
    //TODO: optimize write version which is iterative
    //TODO: make it parallel
    //Bottleneck
   if(q.empty()){
    return {};
   }
   std::vector<std::pair<std::vector<std::pair<T,bool>>,float>> table;
   std::vector<std::vector<T>> L;
   std::vector<std::vector<T>> R;
   auto myQ=q.back();
   
   for(auto& it: v){
        if(myQ(it)){
            L.push_back(it);
        }else{
            R.push_back(it);
        }
   }

   usedQ.emplace_back(q.back().getVal(),false);
   table.emplace_back(usedQ,static_cast<float>(static_cast<float>(R.size())/static_cast<float>(Data.size())));
   usedQ.back().second=true;
   table.emplace_back(usedQ,static_cast<float>(static_cast<float>(L.size())/static_cast<float>(Data.size())));

    q.pop_back();

   if(!L.empty()){
   auto Lprim=createDesisionTree(q,usedQ,L);
   if(!Lprim.empty())
   table.insert(table.end(),Lprim.begin(),Lprim.end());
   }
   if(!R.empty()){
    usedQ.back().second=false;
    auto Rprim=createDesisionTree(q,usedQ,R);
    if(!Rprim.empty())
    table.insert(table.end(),Rprim.begin(),Rprim.end());
   }
   return table;
}

