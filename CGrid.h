#ifndef PROGRAM_CGRID_H
#define PROGRAM_CGRID_H

#include "MATH.h"
#include <vector>
#include "ISDLDrawable.h"

using Geometry_2D::SVector_2D;

const int OBSTACLE = -1;
const int EMPTY = 0;
const int FOREST = 1;

class CGrid : public ISDLDrawable {
    static const int DEFAULT_CELL_WIDTH = 20;
    static const int DEFAULT_CELL_HEIGHT = 20;
public:
    int RowsNum = 0;
    int ColumnsNum = 0;

    int GapBetweenCells_x = 2;
    int GapBetweenCells_y = 2;

    int shift_x = 30;
    int shift_y = 30;

    int CellWidth = 0;
    int CellHeight = 0;

    std::vector<std::vector<int>> CellVector;
    CGrid();
    CGrid(int Rows, int Columns, int W = DEFAULT_CELL_WIDTH, int H = DEFAULT_CELL_HEIGHT);

    void Draw(SDL_Renderer* Renderer) const override;

    std::vector<SVector_2D> GetCellNeighbours(const SVector_2D& Cell);

    CGrid* operator=(const CGrid& AnotherGrid) {
        RowsNum = AnotherGrid.RowsNum;
        ColumnsNum = AnotherGrid.ColumnsNum;

        GapBetweenCells_x = AnotherGrid.GapBetweenCells_x;
        GapBetweenCells_y = AnotherGrid.GapBetweenCells_y;

        shift_x = AnotherGrid.shift_x;
        shift_y = AnotherGrid.shift_y;

        CellWidth = AnotherGrid.CellWidth;
        CellHeight = AnotherGrid.CellHeight;

        CellVector = AnotherGrid.CellVector;
        return this;
    }
private:
    void Init(int RowNum, int ColumnNum);
};


#endif //PROGRAM_CGRID_H
