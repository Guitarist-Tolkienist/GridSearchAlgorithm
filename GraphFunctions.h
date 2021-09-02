#ifndef GRIDSEARCHALGORITHM_GRAPHFUNCTIONS_H
#define GRIDSEARCHALGORITHM_GRAPHFUNCTIONS_H

#include <map>
#include <algorithm>
#include <queue>

#include "MATH.h"
using Geometry_2D::SVector_2D;

// Contains association array of nodes corresponding to each other
// May serve as data structure to hold info about:
// - node & node it came from
struct GraphNodesAssoc {
    std::map<SVector_2D, SVector_2D> AssocMap;

    void Insert(const SVector_2D& Key, const SVector_2D& Val) {
        AssocMap.insert({Key, Val});
    }

    SVector_2D Get(const SVector_2D& Key) const {
        return AssocMap.find(Key)->second;
    }

    bool Contains(const SVector_2D& Val) {
        return AssocMap.find(Val) != AssocMap.end();
    }

    void Clear() {
        AssocMap.clear();
    }
};

template<typename T, typename Priority_T>
struct PriorityQueue {
    typedef std::pair<Priority_T, T> PQElement;
    std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> elements;

    inline bool empty() const { return elements.empty();}

    inline void put(T item, Priority_T priority) {elements.emplace(priority, item);}

    inline int Size() {return elements.size();}

    T get() {
        T BestItem = elements.top().second;
        elements.pop();
        return BestItem;
    }
};

template<typename T, typename Cost_T>
struct GraphCost {
    std::map<T, Cost_T> Costs;

    void Insert(const T& Key, Cost_T Val) {
        Costs.insert({Key, Val});
    }

    Cost_T Get(const T& Key) {
        return Costs.find(Key)->second;
    }

    bool Contains(const T& Val) {
        return Costs.find(Val) != Costs.end();
    }
};


#endif //GRIDSEARCHALGORITHM_GRAPHFUNCTIONS_H
