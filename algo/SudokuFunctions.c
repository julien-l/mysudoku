//
//  SudokuFunctions.c
//  MySudoku
//
//  Created by Julien Lemaitre on 2015-04-11.
//  Copyright (c) 2015 Julien Lemaitre. All rights reserved.
//

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "SudokuAlgorithms.h"
#include "SudokuData.h"

#define NCOLS 9
#define NROWS 9

SudokuPuzzle * SudokuAllocPuzzle()
{
    SudokuPuzzle * ptr = (SudokuPuzzle*) malloc(sizeof(SudokuPuzzle));
    memset(ptr, 0, sizeof(SudokuPuzzle));
    ptr->board = (SudokuCellContent*) malloc(sizeof(SudokuCellContent)*NCOLS*NROWS);
    memset(ptr->board, 0, sizeof(SudokuCellContent)*NCOLS*NROWS);
    return ptr;
}

void SudokuDeallocPuzzle(SudokuPuzzle *puzzle)
{
    if (NULL != puzzle)
    {
        free(puzzle->board);
    }
    free(puzzle);
}

void SudokuClearPuzzle(SudokuPuzzle *puzzle)
{
    assert(NULL != puzzle && "SudokuClearPuzzle(): Bad input");
    memset(puzzle->board, 0, sizeof(SudokuCellContent)*NCOLS*NROWS);
}

SudokuCellContent* SudokuCellContentAt(SudokuPuzzle *puzzle, uint row, uint col)
{
    assert(NULL != puzzle && row < NROWS && col < NCOLS && "SudokuCellContentAt(): Bad input");
    return &(puzzle->board[row*NCOLS+col]);
}

void SudokuGeneratePuzzle(SudokuPuzzle *puzzle)
{
    assert(NULL != puzzle && "SudokuGeneratePuzzle(): Bad input");
    SudokuClearPuzzle(puzzle);
    SudokuGenerateSolution(puzzle);
    for (uint i = 0; i < NROWS*NCOLS; ++i)
    {
        if (0 != puzzle->board[i].value)
        {
            puzzle->board[i].type = CELL_TYPE_INITIAL;
        }
        else
        {
            puzzle->board[i].type = CELL_TYPE_EMPTY;
        }
        puzzle->board[i].state = CELL_STATE_NONE;
    }
}

/**
 Save the puzzle to the given text file compatible with http://www.sudoku-solutions.com/
 All numbers are saved in one line, without space.
 */
bool SudokuSaveToFile(SudokuPuzzle *puzzle, const char *filename)
{
    assert(NULL != puzzle && "SudokuSaveToFile(): Bad input");
    printf("Saving solution to file '%s'\n", filename);
    FILE *f = fopen(filename, "w");
    if (NULL == f)
    {
        perror("SudokuSaveToFile(): Can't open file");
        return false;
    }
    for (uint i = 0; i < NROWS*NCOLS; ++i)
    {
        fprintf(f, "%d", puzzle->board[i].value);
    }
    fclose(f);
    return true;
}
