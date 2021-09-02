#include "CGrid.h"
#include <SDL2/SDL.h>

CGrid::CGrid() {
    Init(0, 0);
}

CGrid::CGrid(int Rows, int Columns, int W, int H) : RowsNum(Rows), ColumnsNum(Columns), CellWidth(W), CellHeight(H) {
    Init(H, W);
}

void CGrid::Draw(SDL_Renderer* Renderer) const {
    for (int i = 0; i < RowsNum; ++i) {
        for (int j = 0; j < ColumnsNum; ++j) {
            // CHOOSE COLOR
            switch (CellVector[i][j]) {
                case OBSTACLE:
                    SDL_SetRenderDrawColor(Renderer, 10, 10, 10, 0);
                    break;
                case EMPTY:
                    SDL_SetRenderDrawColor(Renderer, 50, 200, 100, 0);
                    break;
                case FOREST:
                    SDL_SetRenderDrawColor(Renderer, 00, 250, 100, 0);
                    break;
                default:
                    SDL_SetRenderDrawColor(Renderer, 10, 10, 150, 255);
                    break;
            }

            SDL_Rect Rect = {shift_x + CellWidth * j + (j + 1) * GapBetweenCells_x, shift_y + CellHeight * i + (i + 1) * GapBetweenCells_y, CellWidth, CellHeight};
            SDL_RenderFillRect(Renderer, &Rect);
        }
    }
}

void CGrid::Init(int RowNum, int ColumnNum) {
    for (int i = 0; i < RowNum; ++i) {
        std::vector<int> Row;
        for (int j = 0; j < ColumnNum; ++j) {
            Row.emplace_back(0);
        }
        CellVector.push_back(Row);
    }
}

std::vector<SVector_2D> CGrid::GetCellNeighbours(const SVector_2D& Cell) {
    std::vector<SVector_2D> Neighbours;

    for (int i = Cell.Y - 1; i <= Cell.Y + 1; ++i) {
        for (int j = Cell.X - 1; j <= Cell.X + 1; ++j) {

            // DO NOT CONSIDER CORNERS
            /*if (i == Cell.Y - 1 && j == Cell.X - 1 ||
                i == Cell.Y - 1 && j == Cell.X + 1 ||
                i == Cell.Y + 1 && j == Cell.X - 1 ||
                i == Cell.Y + 1 && j == Cell.X + 1) continue;
*/
            if (i == Cell.Y && j == Cell.X) continue;
            if (i < 0 || i >= RowsNum || j < 0 || j >= ColumnsNum) continue;
            if (CellVector[i][j] == OBSTACLE) continue;
            Neighbours.emplace_back(SVector_2D(j, i));
        }
    }

    return Neighbours;
}
