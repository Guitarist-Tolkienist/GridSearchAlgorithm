#ifndef GRIDSEARCHALGORITHM_CWORLD_H
#define GRIDSEARCHALGORITHM_CWORLD_H

#include "MATH.h"
#include "CSDL_Controller.h"
#include "CSDL_Renderer.h"
#include "CGrid.h"
#include <cmath>
#include "CSDL_Text.h"

#include "SearchDataStructures.h"



class CWorld {
    CSDL_Renderer Renderer;
    CSDL_Controller Controller;

    BreadthFirst_GridSearch BF_Search;

    Dijkstra_GridSearch Dijkstra_Search;

    AStar_GridSearch AStar_Search;
public:
    bool bDoNextstep = false;
    bool bRunning = true;

    CWorld(const SVector_2D& Start = SVector_2D(4, 4),
           const SVector_2D& Target = SVector_2D(14, 7));
    ~CWorld();

    int OnExecute();
private:
    void SearchPath();

    void InitWorld();

    void PlaceObstructions(CGrid& Grid) const;
};


#endif //GRIDSEARCHALGORITHM_CWORLD_H
