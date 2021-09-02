#include "SearchDataStructures.h"
#include <SDL2/SDL.h>

void GridPoint::Draw(SDL_Renderer* Renderer) const {
    SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 255);

    for(int x= ActualPosition.X - radius_; x <= ActualPosition.X + radius_; x++){
        for(int y= ActualPosition.Y - radius_; y <= ActualPosition.Y + radius_; y++){
            if((std::pow(ActualPosition.Y - y, 2) + std::pow(ActualPosition.X - x, 2)) <= std::pow(radius_, 2)){
                SDL_RenderDrawPoint(Renderer, x, y);
            }
        }
    }
}

void GridSearch::Draw(SDL_Renderer *Renderer) const {
    Grid.Draw(Renderer);

    m_Start.Draw(Renderer);
    m_Target.Draw(Renderer);

    SearchName.Draw(Renderer);
}


void SearchPrFrontier::Draw(SDL_Renderer* Renderer) const {
    PriorityQueue<SVector_2D, float> Frontier = *Pr_Frontier;

    SVector_2D Origin = {float(DrawingGrid->shift_x), float(DrawingGrid->shift_y)};
    SVector_2D CellSize = {float(DrawingGrid->CellWidth), float(DrawingGrid->CellHeight)};
    SVector_2D GapBetweenCells = {float(DrawingGrid->GapBetweenCells_x), float(DrawingGrid->GapBetweenCells_y)};

    int RedComponent = 255;
    while(!Frontier.elements.empty()) {
        SDL_SetRenderDrawColor(Renderer, RedComponent, 0, 100, 255);
        RedComponent = RedComponent - 10 < 0 ? 0 : RedComponent - 10;

        auto FrontierElement = Frontier.elements.top().second;
        Frontier.elements.pop();

        SDL_Rect Rect = {int(Origin.X + CellSize.X * FrontierElement.X + (FrontierElement.X + 1) * GapBetweenCells.X),
                         int(Origin.Y + CellSize.Y * FrontierElement.Y + (FrontierElement.Y + 1) * GapBetweenCells.Y),
                         int(CellSize.X),
                         int(CellSize.Y)};
        SDL_RenderFillRect(Renderer, &Rect);
    }
}

void SearchCameFrom::Draw(SDL_Renderer* Renderer) const {
    if (!CameFrom || !DrawingGrid) return;

    SVector_2D Origin = {float(DrawingGrid->shift_x), float(DrawingGrid->shift_y)};
    SVector_2D CellSize = {float(DrawingGrid->CellWidth), float(DrawingGrid->CellHeight)};
    SVector_2D GapBetweenCells = {float(DrawingGrid->GapBetweenCells_x), float(DrawingGrid->GapBetweenCells_y)};

    SDL_SetRenderDrawColor(Renderer, 5, 150, 10, 255);

    for (const auto& CameFromElement: CameFrom->AssocMap) {
        SVector_2D SourceElement = CameFromElement.second;

        SDL_Rect Rect = {int(Origin.X + CellSize.X * SourceElement.X + (SourceElement.X + 1) * GapBetweenCells.X),
                         int(Origin.Y + CellSize.Y * SourceElement.Y + (SourceElement.Y + 1) * GapBetweenCells.Y),
                         int(CellSize.X),
                         int(CellSize.Y)};
        SDL_RenderFillRect(Renderer, &Rect);
    }
}

void SearchFrontier::Draw(SDL_Renderer* Renderer) const {
    if (!Frontier || !DrawingGrid) return;

    std::queue<SVector_2D> FrontierCopy = *Frontier;

    SVector_2D Origin = {float(DrawingGrid->shift_x), float(DrawingGrid->shift_y)};
    SVector_2D CellSize = {float(DrawingGrid->CellWidth), float(DrawingGrid->CellHeight)};
    SVector_2D GapBetweenCells = {float(DrawingGrid->GapBetweenCells_x), float(DrawingGrid->GapBetweenCells_y)};

    int RedComponent = 255;
    while(!FrontierCopy.empty()) {
        SDL_SetRenderDrawColor(Renderer, RedComponent, 0, 100, 255);

        auto FrontierElement = FrontierCopy.front();
        FrontierCopy.pop();

        SDL_Rect Rect = {int(Origin.X + CellSize.X * FrontierElement.X + (FrontierElement.X + 1) * GapBetweenCells.X),
                         int(Origin.Y + CellSize.Y * FrontierElement.Y + (FrontierElement.Y + 1) * GapBetweenCells.Y),
                         int(CellSize.X),
                         int(CellSize.Y)};
        SDL_RenderFillRect(Renderer, &Rect);
    }
}

// BreadthFirst
BreadthFirst_GridSearch::
BreadthFirst_GridSearch(const SVector_2D &Start,
                        const SVector_2D &Target) :
                        GridSearch(Start, Target) {
    Frontier.DrawingGrid = &Grid;
    Frontier.Frontier = new std::queue<SVector_2D>;
    Frontier.Frontier->emplace(m_Start.Center);

    CameFrom.DrawingGrid = &Grid;
    CameFrom.CameFrom = new GraphNodesAssoc;
    CameFrom.CameFrom->Insert(m_Start.Center, m_Start.Center);

    // Text
    SearchName.SetText("Breadth First Search");
}

void BreadthFirst_GridSearch::SearchStep() {
    if (Frontier.Frontier->empty() || bFoundPath) return;

    SVector_2D CurrentPos = Frontier.Frontier->front();
    Frontier.Frontier->pop();
    if (CurrentPos == m_Target.Center) {
        bFoundPath = true;
        return;
    }

    std::vector<SVector_2D> Neighbours = Grid.GetCellNeighbours(CurrentPos);

    for (const SVector_2D &Neighbour: Neighbours) {
        if (!CameFrom.CameFrom->Contains(Neighbour)) {
            Frontier.Frontier->emplace(Neighbour);
            CameFrom.CameFrom->Insert(Neighbour, CurrentPos);
        }
    }
}

void BreadthFirst_GridSearch::RecreatePath() {
    if (!bFoundPath) return;

    std::vector<SVector_2D> Path;

    SVector_2D Current = m_Target.Center;
    while (Current != m_Start.Center) {
        Path.emplace_back(Current);
        Current = CameFrom.CameFrom->Get(Current);
    }
    Path.emplace_back(m_Start.Center);

    for (auto Step: Path) {
        Grid.CellVector[Step.Y][Step.X] = 2;
    }
}

void BreadthFirst_GridSearch::Draw(SDL_Renderer* Renderer) const {
    GridSearch::Draw(Renderer);

    if (!bFoundPath) {
        Frontier.Draw(Renderer);
        CameFrom.Draw(Renderer);
    }
}


// Dijkstra
void Dijkstra_GridSearch::DefineCosts() {
    if (Grid.CellVector.empty()) return;

    CostsGrid = Grid;

    int StartX = m_Start.Center.X;
    int StartY = m_Start.Center.Y;

    CostsGrid.CellVector[StartY][StartX] = 0;

    // Set costs above Start in its column
    int Cost = 1;
    int i_up = StartY - 1;
    while (i_up >= 0) {
        CostsGrid.CellVector[i_up][StartX] = Grid.CellVector[i_up][StartX] == FOREST ? Cost + 2 : Cost;
        i_up--;
        Cost++;
    }

    // Set costs below Start in its column
    Cost = 1;
    int i_down = StartY + 1;
    while (i_down <= Grid.RowsNum) {
        CostsGrid.CellVector[i_down][StartX] = Grid.CellVector[i_down][StartX] == FOREST ? Cost + 2 : Cost;;
        i_down++;
        Cost++;
    }

    // Set costs to the left of Start
    for (int i = 0; i < CostsGrid.RowsNum; ++i) {
        Cost = CostsGrid.CellVector[i][StartX] + 1;

        int j = StartX - 1;
        while (j >= 0) {
            CostsGrid.CellVector[i][j] = Grid.CellVector[i][j] == FOREST ? Cost + 2 : Cost;;
            j--;
            Cost++;
        }
    }

    // Set costs to the right of Start
    for (int i = 0; i < CostsGrid.RowsNum; ++i) {
        Cost = CostsGrid.CellVector[i][StartX] + 1;

        int j = StartX + 1;
        while (j < Grid.ColumnsNum) {
            CostsGrid.CellVector[i][j] = Grid.CellVector[i][j] == FOREST ? Cost + 2 : Cost;
            j++;
            Cost++;
        }
    }


    // print costs grid
    /*for (int i = 0; i < CostsGrid.RowsNum; ++i) {
        for (int j = 0; j < CostsGrid.RowsNum; ++j) {
            if (CostsGrid.CellVector[i][j] < 10) {
                std::cout << " ";
            }
            std::cout << CostsGrid.CellVector[i][j] << " ";
        }
        std::cout << "\n";
    }*/
}

float Dijkstra_GridSearch::GetMovementCost(const SVector_2D& From, const SVector_2D& To) const {
    float CostFrom = CostsGrid.CellVector[From.Y][From.X];
    float CostTo = CostsGrid.CellVector[To.Y][To.X];
    return CostTo - CostFrom;
}

void Dijkstra_GridSearch::RecreatePath() {
    if (!bFoundPath) return;

    std::vector<SVector_2D> Path;

    SVector_2D Current = m_Target.Center;
    while (Current != m_Start.Center) {
        Path.emplace_back(Current);
        Current = CameFrom.CameFrom->Get(Current);
    }
    Path.emplace_back(m_Start.Center);

    for (auto Step: Path) {
        Grid.CellVector[Step.Y][Step.X] = 2;
    }
}

void Dijkstra_GridSearch::SearchStep() {
    if (PrFrontier.Pr_Frontier->empty() || bFoundPath) return;

    SVector_2D CurrentPos = PrFrontier.Pr_Frontier->get();
    if (CurrentPos == m_Target.Center) {
        bFoundPath = true;
        return;
    }

    std::vector<SVector_2D> Neighbours = Grid.GetCellNeighbours(CurrentPos);

    for (const SVector_2D &Neighbour: Neighbours) {
        float NewCost = CostSoFar.Get(CurrentPos) + GetMovementCost(CurrentPos, Neighbour);
        if (!CameFrom.CameFrom->Contains(Neighbour) || NewCost < CostSoFar.Get(Neighbour)) {
            CostSoFar.Insert(Neighbour, NewCost);
            float Priority = NewCost;
            PrFrontier.Pr_Frontier->put(Neighbour, Priority);
            CameFrom.CameFrom->Insert(Neighbour, CurrentPos);
        }
    }
}

void Dijkstra_GridSearch::Draw(SDL_Renderer* Renderer) const {
    GridSearch::Draw(Renderer);

    if (!bFoundPath) {
        PrFrontier.Draw(Renderer);
        CameFrom.Draw(Renderer);
    }
}

void Dijkstra_GridSearch::CalculateGridPointsPositions() {
    GridSearch::CalculateGridPointsPositions();
    DefineCosts();
}

Dijkstra_GridSearch::
Dijkstra_GridSearch(const SVector_2D &Start,
                    const SVector_2D &Target) :
                    GridSearch(Start, Target) {
    PrFrontier.DrawingGrid = &Grid;
    PrFrontier.Pr_Frontier = new PriorityQueue<SVector_2D, float>;
    PrFrontier.Pr_Frontier->put(m_Start.Center, 0.0f);

    CameFrom.DrawingGrid = &Grid;
    CameFrom.CameFrom = new GraphNodesAssoc;
    CameFrom.CameFrom->Insert(m_Start.Center, m_Start.Center);

    DefineCosts();
    // Text
    SearchName.SetText("Dijkstra Search");
}


// A*
AStar_GridSearch::
AStar_GridSearch(const SVector_2D &Origin,
                 const SVector_2D &Target)  :
                 Dijkstra_GridSearch(Origin, Target) {
    // Text
    SearchName.SetText("A* Search");
}

float AStar_GridSearch::heuristic(const SVector_2D &A, const SVector_2D &B) {
    return std::abs(A.X - B.X) + std::abs(A.Y - B.Y);
}

void AStar_GridSearch::SearchStep() {
    if (PrFrontier.Pr_Frontier->empty() || bFoundPath) return;

    SVector_2D CurrentPos = PrFrontier.Pr_Frontier->get();
    if (CurrentPos == m_Target.Center) {
        bFoundPath = true;
        return;
    }

    std::vector<SVector_2D> Neighbours = Grid.GetCellNeighbours(CurrentPos);

    for (const SVector_2D& Neighbour: Neighbours) {
        float NewCost = CostSoFar.Get(CurrentPos) + GetMovementCost(CurrentPos, Neighbour);
        if (!CameFrom.CameFrom->Contains(Neighbour) || NewCost < CostSoFar.Get(Neighbour)) {
            CostSoFar.Insert(Neighbour, NewCost);
            float Priority = NewCost + heuristic(m_Target.Center, Neighbour);
            PrFrontier.Pr_Frontier->put(Neighbour, Priority);
            CameFrom.CameFrom->Insert(Neighbour, CurrentPos);
        }
    }
}
