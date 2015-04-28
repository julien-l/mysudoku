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

#include "Sudoku.h"

typedef int CandidateListType;

#define BIT_ALL_CANDIDATES          511 // 2^9-1
#define BIT_REFILL_CANDIDATES(x)    x = BIT_ALL_CANDIDATES;
#define BIT_CLEAR(x,bit)            x &= ~(1<<bit)
#define BIT_CHECK(x,bit)            (x & (1<<bit))
#define BIT_CHECK_ANY(x)            (0 != (x & BIT_ALL_CANDIDATES))

#define NCOLS       9
#define NROWS       9
#define NREGIONS    3

// -----------------------------------------------------------------------------
// Local functions processing intermediate data
// -----------------------------------------------------------------------------

uint GetRandomNumberFromCandidateListAndRemoveIt(CandidateListType *list, uint index)
{
    assert(NULL != list && index < (NROWS*NCOLS) && "GetRandomNumberFromCandidateListAndRemoveIt(): Bad input");
    // 1. count how many remaining numbers we have (how many set bits)
    uint count = 0;
    for (uint i = 0; i < NCOLS; ++i)
    {
        if (BIT_CHECK(list[index],i)) {
            ++count;
        }
    }
    assert(count > 0 && "GetRandomNumberFromCandidateListAndRemoveIt(): Could not find a remaining number in the list");
    // 2. generate random index (will be 0 when count is 1)
    uint randomIndex = (uint) arc4random() % count;
    // 3. get the corresponding candidate
    CandidateListType candidate = 0;
    for (; candidate < NCOLS; ++candidate)
    {
        if (BIT_CHECK(list[index],candidate)) {
            if (0 == randomIndex) {
                break;
            }
            else {
                --randomIndex;
            }
        }
    }
    assert(0 <= candidate && candidate < NCOLS && 0 == randomIndex && "GetRandomNumberFromCandidateListAndRemoveIt(): Bad search for random number");
    // 4. remove it from the candidate list
    BIT_CLEAR(list[index],candidate);
    return (uint)(candidate+1); // Indices start at 0 but values start at 1, need to increase
}

bool CheckNoConflict(SudokuPuzzle *puzzle, uint index, uint value)
{
    assert(NULL != puzzle && index < (NROWS*NCOLS) && "CheckNoConflict(): Bad input");
    // 0. get corresponding row and column
    const uint rowIndex = (uint) floorf(index/NCOLS);
    const uint colIndex = (uint) index%NCOLS;
    // 1. check row
    for (uint col = 0; col < NCOLS; ++col)
    {
        if (colIndex == col) {
            continue;
        }
        if (puzzle->board[rowIndex*NCOLS+col].value == value) {
            return false;
        }
    }
    // 2. check column
    for (uint row = 0; row < NROWS; ++row)
    {
        if (rowIndex == row) {
            continue;
        }
        if (puzzle->board[row*NCOLS+colIndex].value == value) {
            return false;
        }
    }
    // 3. check region
    {
        const uint regionRowIndex = (uint) floorf(rowIndex/NREGIONS);
        const uint regionColIndex = (uint) floorf(colIndex/NREGIONS);
        assert(regionRowIndex < NREGIONS && regionColIndex < NREGIONS && "CheckNoConflict(): Region indices out of range");
        const uint start = regionRowIndex*NREGIONS*NCOLS + regionColIndex*NREGIONS;
        for (uint row = 0; row < NREGIONS; ++row)
        {
            for (uint col = 0; col < NREGIONS; ++col)
            {
                const uint currentIndex = start + row*NCOLS + col;
                if (currentIndex == index) {
                    continue;
                }
                if (puzzle->board[currentIndex].value == value) {
                    return false;
                }
            }
        }
    }
    // all good
    return true;
}

// -----------------------------------------------------------------------------
// Functions from the interface
// -----------------------------------------------------------------------------

void SudokuGenerateSolution(SudokuPuzzle *puzzle)
{
    assert(NULL != puzzle && "SudokuGenerateSolution(): Bad input");
    CandidateListType candidateList [NCOLS*NROWS];
    for (uint i = 0; i < NROWS*NCOLS; ++i)
    {
        BIT_REFILL_CANDIDATES(candidateList[i]);
    }
    // TODO add a fixed counter corresponding to the worst case scenario (we try
    // all possibilities for each cell) so that we have a hard iteration limit
    for (uint i = 0; i < NROWS*NCOLS;)
    {
        // Are we out of remaining number?
        // If no, try to fill the cell, if yes, backtrack
        if (BIT_CHECK_ANY(candidateList[i]))
        {
            const uint num = GetRandomNumberFromCandidateListAndRemoveIt(candidateList, i);
            if (CheckNoConflict(puzzle, i, num))
            {
                puzzle->board[i].value = num;
                ++i;
            }
        }
        // Else, backtrack
        else
        {
            assert(i > 0 && "SudokuGenerateSolution(): Trying to backtrack past 0");
            BIT_REFILL_CANDIDATES(candidateList[i]);
            puzzle->board[i].value = 0;
            --i;
        }
    }
}

void SudokuMakeHoles(struct SudokuPuzzle *puzzle, uint n)
{
    assert(NULL != puzzle && n < NROWS*NCOLS && "SudokuMakeHoles(): Bad input");
    // Placeholder for now. A real algorithm needs to make sure that there is a
    // solution when removing cells.
    for (uint i = 0; i < n; ++i)
    {
        uint randomIndex = (uint) arc4random() % (NROWS*NCOLS);
        puzzle->board[randomIndex].value = 0;
    }
}
