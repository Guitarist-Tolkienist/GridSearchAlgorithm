#ifndef GRIDSEARCHALGORITHM_SEARCHDATASTRUCTURE_H
#define GRIDSEARCHALGORITHM_SEARCHDATASTRUCTURE_H

#include "GraphFunctions.h"
#include "MATH.h"
#include "CGrid.h"
#include "CSDL_Text.h"

struct SearchFrontier : ISDLDrawable {
    std::queue<SVector_2D>* Frontier = nullptr;

    const CGrid* DrawingGrid = nullptr;

    void Draw(SDL_Renderer* Renderer) const override;
};

struct SearchPrFrontier : ISDLDrawable {
    PriorityQueue<SVector_2D, float>* Pr_Frontier = nullptr;

    const CGrid* DrawingGrid = nullptr;

    void Draw(SDL_Renderer* Renderer) const override;
};

struct SearchCameFrom : ISDLDrawable {
    GraphNodesAssoc* CameFrom = nullptr;

    const CGrid* DrawingGrid = nullptr;

    void Draw(SDL_Renderer* Renderer) const override;
};

class GridPoint: public ISDLDrawable {
    static const int DEFAULT_RADIUS = 7;
public:
    SVector_2D ActualPosition;
    SVector_2D Center;
    int radius_;

    GridPoint(const SVector_2D& PointCenter,
              int Radius = DEFAULT_RADIUS) : Center(PointCenter),
                                             ActualPosition(PointCenter),
                                             radius_(Radius) {}

    void Draw(SDL_Renderer* Renderer) const override;
};

class GridSearch : public ISDLDrawable {
protected:
    CSDLText SearchName;
    CGrid Grid;

    GridPoint m_Start;
    GridPoint m_Target;

public:
    bool bFoundPath = false;

    GridSearch(const SVector_2D& Origin,
               const SVector_2D& Target) : m_Start(Origin),
                                           m_Target(Target),
                                           SearchName("Grid Search") {}

    GridSearch(const GridSearch& GridS) : Grid(GridS.Grid),
                                          m_Start(GridS.m_Start),
                                          m_Target(GridS.m_Target),
                                          SearchName("Grid Search") {}

    void SetGrid(const CGrid& GridData) {
        Grid = GridData;
        CalculateGridPointsPositions();
    }

    virtual void RecreatePath() = 0;
    virtual void SearchStep() = 0;
    virtual void Draw(SDL_Renderer* Renderer) const override;

protected:
    virtual void CalculateGridPointsPositions() {
        // CONVERTING GRID POSITION TO ACTUAL POSITION IN WINDOW
        m_Start.ActualPosition.X = Grid.shift_x + m_Start.Center.X * float(Grid.CellWidth + Grid.GapBetweenCells_x) + Grid.CellWidth / 2.0f + Grid.GapBetweenCells_x;
        m_Start.ActualPosition.Y = Grid.shift_y + m_Start.Center.Y * float(Grid.CellHeight + Grid.GapBetweenCells_y) + Grid.CellHeight / 2.0f + Grid.GapBetweenCells_y;

        // CONVERTING GRID POSITION TO ACTUAL POSITION IN WINDOW
        m_Target.ActualPosition.X = Grid.shift_x + m_Target.Center.X * float(Grid.CellWidth + Grid.GapBetweenCells_x) + Grid.CellWidth / 2.0f + Grid.GapBetweenCells_x;
        m_Target.ActualPosition.Y = Grid.shift_y + m_Target.Center.Y * float(Grid.CellWidth + Grid.GapBetweenCells_x) + Grid.CellWidth / 2.0f + Grid.GapBetweenCells_x;

        // TEXT POSITION
        int x = Grid.shift_x + 20;
        int y = Grid.shift_y + Grid.RowsNum * (Grid.CellHeight + Grid.GapBetweenCells_y) + 10;
        SearchName.SetTextPosition(x, y);
    }
};

class BreadthFirst_GridSearch : public GridSearch {
    SearchFrontier Frontier;
    SearchCameFrom CameFrom;
public:
    BreadthFirst_GridSearch(const SVector_2D& Start,
                            const SVector_2D& Target);

    virtual void SearchStep() override;
    virtual void RecreatePath() override;

    virtual void Draw(SDL_Renderer* Renderer) const override;
};

class Dijkstra_GridSearch : public GridSearch {
public:
    Dijkstra_GridSearch(const SVector_2D& Start,
                        const SVector_2D& Target);


    virtual void RecreatePath() override;
    virtual void SearchStep() override;
    virtual void Draw(SDL_Renderer* Renderer) const override;

protected:
    SearchPrFrontier PrFrontier;
    SearchCameFrom CameFrom;
    GraphCost<SVector_2D, float> CostSoFar;

    CGrid CostsGrid;

    float GetMovementCost(const SVector_2D& From, const SVector_2D& To) const;

    virtual void CalculateGridPointsPositions() override;
private:
    void DefineCosts();
};

class AStar_GridSearch : public Dijkstra_GridSearch {
public:
    AStar_GridSearch(const SVector_2D& Origin,
                     const SVector_2D& Target);

    virtual void SearchStep() override;

private:
    float heuristic(const SVector_2D& A, const SVector_2D& B);
};


#endif //GRIDSEARCHALGORITHM_SEARCHDATASTRUCTURE_H
