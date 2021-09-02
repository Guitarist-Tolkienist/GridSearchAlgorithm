#include "CWorld.h"
#include <algorithm>

CWorld::CWorld(const SVector_2D& Start,
               const SVector_2D& Target) :
               Renderer(WINDOW_WIDTH, WINDOW_HEIGHT),
               BF_Search(Start, Target),
               Dijkstra_Search(Start, Target),
               AStar_Search(Start, Target){
    InitWorld();
}

void CWorld::SearchPath() {
    if (BF_Search.bFoundPath) {
        BF_Search.RecreatePath();
    }
    if (Dijkstra_Search.bFoundPath) {
        Dijkstra_Search.RecreatePath();
    }
    if (AStar_Search.bFoundPath) {
        AStar_Search.RecreatePath();
    }

    if (bDoNextstep) {
        BF_Search.SearchStep();
        Dijkstra_Search.SearchStep();
        AStar_Search.SearchStep();

        bDoNextstep = false;
    }
}

void CWorld::InitWorld() {
    // INIT CONTROLLER
    Controller.WorldData = this;

    Renderer.Drawables.emplace_back(&BF_Search);
    Renderer.Drawables.emplace_back(&Dijkstra_Search);
    Renderer.Drawables.emplace_back(&AStar_Search);

    CGrid Grid(15, 15);
    PlaceObstructions(Grid);

    BF_Search.SetGrid(Grid);

    Grid.shift_x += 400;
    Dijkstra_Search.SetGrid(Grid);

    Grid.shift_x += 400;
    AStar_Search.SetGrid(Grid);
}

int CWorld::OnExecute() {
    while(bRunning) {
        Renderer.Render();
        bRunning = Controller.UpdateEvent();

        SearchPath();
    }
    return 0;
}

void CWorld::PlaceObstructions(CGrid& Grid) const {
    Grid.CellVector[1][2] = OBSTACLE;
    Grid.CellVector[2][2] = OBSTACLE;
    Grid.CellVector[3][0] = OBSTACLE;
    Grid.CellVector[3][1] = OBSTACLE;
    Grid.CellVector[3][2] = OBSTACLE;

    Grid.CellVector[5][5] = OBSTACLE;
    Grid.CellVector[5][6] = OBSTACLE;
    Grid.CellVector[5][7] = OBSTACLE;
    Grid.CellVector[5][8] = OBSTACLE;
    Grid.CellVector[5][9] = OBSTACLE;
    Grid.CellVector[6][5] = OBSTACLE;
    Grid.CellVector[7][5] = OBSTACLE;
    Grid.CellVector[8][5] = OBSTACLE;
    Grid.CellVector[9][5] = OBSTACLE;

    for (int i = 2; i < Grid.RowsNum - 5; ++i) {
//        Grid.CellVector[i][11] = OBSTACLE;
        Grid.CellVector[i][10] = FOREST;
        Grid.CellVector[i][9] = FOREST;
    }

    Grid.CellVector[0][11] = EMPTY;

}

CWorld::~CWorld() {

}