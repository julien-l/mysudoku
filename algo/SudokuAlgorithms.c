//
//  SudokuAlgorithms.c
//  MySudoku
//
//  Created by Julien Lemaitre on 2015-04-04.
//  Copyright (c) 2015 Julien Lemaitre. All rights reserved.
//

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>

#include "SudokuData.h"
#include "SudokuFunctions.h"

#define NCOLS       9
#define NROWS       9
#define NREGIONS    3

void SudokuGenerateSolution(SudokuPuzzle *puzzle)
{
    assert(NULL != puzzle && "SudokuGenerateSolution(): Bad input");
    // Placeholder for now:
    for (uint row = 0; row < NROWS; ++row)
    {
        for (uint col = 0; col < NCOLS; ++col)
        {
            SudokuCellContent *cell = SudokuCellContentAt(puzzle, row, col);
            cell->value = row*NCOLS+col + 1;
        }
    }
}
