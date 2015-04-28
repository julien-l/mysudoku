//
//  Sudoku.c
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
#include <math.h>

#include "SudokuAlgorithms.h"
#include "Sudoku.h"

#define NCOLS       9
#define NROWS       9
#define NREGIONS    3

#define NO_CELL_SELECTED 81

// Helper macros
#define CURRENT_CELL(p)         p->board[p->selectedCellIndex]

// -----------------------------------------------------------------------------
// Helper functions
// -----------------------------------------------------------------------------

void SetStateForPeersOfIndex(struct SudokuPuzzle *puzzle, uint index, int state)
{
    assert(NULL != puzzle && index < NROWS*NCOLS && "SetStateForPeersOfIndex(): Bad input");
    // get corresponding row and column
    const uint rowIndex = (uint) floorf(index/NCOLS);
    const uint colIndex = (uint) index%NCOLS;
    // update row and column
    for (uint col = 0; col < NCOLS; ++col)
    {
        if (colIndex == col) {
            continue;
        }
        puzzle->board[rowIndex*NCOLS+col].state = state;
    }
    for (uint row = 0; row < NROWS; ++row)
    {
        if (rowIndex == row) {
            continue;
        }
        puzzle->board[row*NCOLS+colIndex].state = state;
    }
    // update region
    const uint regionRowIndex = (uint) floorf(rowIndex/NREGIONS);
    const uint regionColIndex = (uint) floorf(colIndex/NREGIONS);
    assert(regionRowIndex < NREGIONS && regionColIndex < NREGIONS && "SetStateForPeersOfIndex(): Region indices out of range");
    const uint start = regionRowIndex*NREGIONS*NCOLS + regionColIndex*NREGIONS;
    for (uint row = 0; row < NREGIONS; ++row)
    {
        for (uint col = 0; col < NREGIONS; ++col)
        {
            const uint currentIndex = start + row*NCOLS + col;
            if (currentIndex == index) {
                continue;
            }
            puzzle->board[currentIndex].state = state;
        }
    }
}

// -----------------------------------------------------------------------------
// Interface
// -----------------------------------------------------------------------------

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
    for (uint i = 0; i < NROWS*NCOLS; ++i)
    {
        puzzle->board[i].index = i;
    }
    puzzle->selectedCellIndex = NO_CELL_SELECTED;
    puzzle->selectionMode = SELECTION_MODE_ONE_BY_ONE;
    puzzle->currentNumber = 1;
}

SudokuCellContent * SudokuCellContentAtIndex(SudokuPuzzle *puzzle, uint index)
{
    assert(NULL != puzzle && index < NROWS*NCOLS && "SudokuCellContentAtIndex(): Bad input");
    return &(puzzle->board[index]);
}

void SudokuGeneratePuzzle(SudokuPuzzle *puzzle)
{
    assert(NULL != puzzle && "SudokuGeneratePuzzle(): Bad input");
    SudokuClearPuzzle(puzzle);
    SudokuGenerateSolution(puzzle);
    SudokuMakeHoles(puzzle, 10);
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

void SudokuOnNumberClicked(struct SudokuPuzzle *puzzle, uint number)
{
    assert(NULL != puzzle && number >= 1 && number <= 9 && "SudokuOnNumberClicked(): Bad input");
    puzzle->currentNumber = number;
    if (SELECTION_MODE_ONE_BY_ONE == puzzle->selectionMode &&
        CELL_TYPE_INITIAL != CURRENT_CELL(puzzle).type)
    {
        CURRENT_CELL(puzzle).value = number;
    }
}

// -----------------------------------------------------------------------------
// Callbacks for user interface
// -----------------------------------------------------------------------------

void SudokuOnCellClicked(struct SudokuPuzzle *puzzle, uint index)
{
    assert(NULL != puzzle && index < NROWS*NCOLS && "SudokuOnCellClicked(): Bad input");
    // Unselect previous cell
    if (NO_CELL_SELECTED != puzzle->selectedCellIndex)
    {
        CURRENT_CELL(puzzle).state = CELL_STATE_NONE;
        SetStateForPeersOfIndex(puzzle, puzzle->selectedCellIndex, CELL_STATE_NONE);
    }
    // Select new one
    puzzle->selectedCellIndex = index;
    CURRENT_CELL(puzzle).state = CELL_STATE_SELECTED;
    SetStateForPeersOfIndex(puzzle, puzzle->selectedCellIndex, CELL_STATE_PEER);
}
