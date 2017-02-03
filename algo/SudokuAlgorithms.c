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

// Encode a candidate list for a cell, see generate_puzzle()

typedef int CandidateListType;

#define BIT_ALL_CANDIDATES          511 // 2^9-1
#define BIT_REFILL_CANDIDATES(x)    x = BIT_ALL_CANDIDATES;
#define BIT_CLEAR(x,bit)            x &= ~(1<<bit)
#define BIT_CHECK(x,bit)            (x & (1<<bit))
#define BIT_EMPTY(x)                (0 == x)

#define NCOLS       9
#define NROWS       9
#define NREGIONS    3

//
// Local functions processing intermediate data
//

//! \brief Count the number of bits set in the mask

unsigned int count_bits(CandidateListType byte)
{
    unsigned int c;
    for (c = 0; byte; byte >>= 1)
    {
        c += byte & 0x1;
    }
    return c;
}

//! \brief Get a random number from the candidate list and remove it
//!
//! The candidate list for a cell is the list of remaining numbers that can
//! potentially be assigned to the cell without causing a conflict.
//! The list is encoded in a bitset. Bits are cleared when a number is removed.

unsigned int get_random_number_from_candidate_list_and_remove_it(CandidateListType *list, unsigned int index)
{
    unsigned int randomIndex;   // index of the selected candidate in the list
    unsigned int count;         // number of remaining candidates in the list
    unsigned int candidate;     // selected candidate

    assert(NULL != list && index < (NROWS*NCOLS) && "get_random_number_from_candidate_list_and_remove_it(): Bad input");

    // 1. count how many remaining numbers we have (how many set bits)
    count = count_bits(list[index]);
    assert(count > 0 && "get_random_number_from_candidate_list_and_remove_it(): No candidate remaining");

    // 2. generate random index (will be 0 when count is 1)
    randomIndex = (unsigned int) arc4random() % count;

    // 3. get the corresponding candidate
    for (candidate = 0; candidate < NCOLS; ++candidate)
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
    assert(0 <= candidate && candidate < NCOLS && 0 == randomIndex && "get_random_number_from_candidate_list_and_remove_it(): Bad index");

    // 4. remove it from the candidate list
    BIT_CLEAR(list[index],candidate);

    return (unsigned int)(candidate+1); // Indices start at 0 but values start at 1, need to increase
}

//! \brief Check if cells are conflicting

bool has_conflict(struct SudokuPuzzle *puzzle, unsigned int index, unsigned int value)
{
    assert(NULL != puzzle && index < (NROWS*NCOLS) && "has_conflict(): Bad input");
    // 0. get corresponding row and column
    const unsigned int rowIndex = (unsigned int) floorf(index/NCOLS);
    const unsigned int colIndex = (unsigned int) index%NCOLS;
    // 1. check row
    for (unsigned int col = 0; col < NCOLS; ++col)
    {
        if (colIndex == col) {
            continue;
        }
        if (puzzle->m_board[rowIndex*NCOLS+col].m_value == value) {
            return true;
        }
    }
    // 2. check column
    for (unsigned int row = 0; row < NROWS; ++row)
    {
        if (rowIndex == row) {
            continue;
        }
        if (puzzle->m_board[row*NCOLS+colIndex].m_value == value) {
            return true;
        }
    }
    // 3. check region
    {
        const unsigned int regionRowIndex = (unsigned int) floorf(rowIndex/NREGIONS);
        const unsigned int regionColIndex = (unsigned int) floorf(colIndex/NREGIONS);
        assert(regionRowIndex < NREGIONS && regionColIndex < NREGIONS && "has_conflict(): Region indices out of range");
        const unsigned int start = regionRowIndex*NREGIONS*NCOLS + regionColIndex*NREGIONS;
        for (unsigned int row = 0; row < NREGIONS; ++row)
        {
            for (unsigned int col = 0; col < NREGIONS; ++col)
            {
                const unsigned int currentIndex = start + row*NCOLS + col;
                if (currentIndex == index) {
                    continue;
                }
                if (puzzle->m_board[currentIndex].m_value == value) {
                    return true;
                }
            }
        }
    }
    // no conflict found
    return false;
}

//
// Functions from the interface
//

//! \brief Generate a solved puzzle
//!
//! Algorithm:
//!
//! ~~~~
//! for each cell
//!     while the candidate list is not empty
//!         num := pick a random candidate
//!         if num causes no conflict
//!         then
//!             go to next cell
//!         endif
//!     end while
//!     if no candidate was found
//!     then
//!         backtrack
//!     endif
//! end for
//! ~~~~

void sudoku_generate_solution(struct SudokuPuzzle *puzzle)
{
    assert(NULL != puzzle && "sudoku_generate_solution(): Bad input");
    CandidateListType candidateList [NCOLS*NROWS];
    for (unsigned int i = 0; i < NROWS*NCOLS; ++i)
    {
        BIT_REFILL_CANDIDATES(candidateList[i]);
    }

    // TODO add a fixed counter corresponding to the worst case scenario (we try
    // all possibilities for each cell) so that we have a hard iteration limit
    for (unsigned int i = 0; i < NROWS*NCOLS;)
    {
        bool found = false;
        // Try each candidate: if a candidate can be assigned to the cell
        // without causing a conflit, go to the next cell.
        // If no suitable candidate was found, then backtrack.
        while (!BIT_EMPTY(candidateList[i]))
        {
            const unsigned int num = get_random_number_from_candidate_list_and_remove_it(candidateList, i);
            if (!has_conflict(puzzle, i, num))
            {
                puzzle->m_board[i].m_value = num;
                found = true;
                ++i;
                break;
            }
        }
        if (!found)
        {
            assert(i > 0 && "sudoku_generate_solution(): Trying to backtrack past 0");
            BIT_REFILL_CANDIDATES(candidateList[i]);
            puzzle->m_board[i].m_value = 0;
            --i;
        }
    }
}

//! \brief Make n holes in the given puzzle
//!
//! @todo Implement the difficulty level here (instead of just the number of holes.

void sudoku_make_holes(struct SudokuPuzzle *puzzle, unsigned int n)
{
    assert(NULL != puzzle && n < NROWS*NCOLS && "sudoku_make_holes(): Bad input");
    // Placeholder for now. A real algorithm needs to make sure that there is a
    // solution when removing cells.
    for (unsigned int i = 0; i < n; ++i)
    {
        unsigned int randomIndex = (unsigned int) arc4random() % (NROWS*NCOLS);
        puzzle->m_board[randomIndex].m_value = 0;
    }
}

//! \brief Check if the puzzle is valid and finished
//!
//! The result is stored in SudokuPuzzle::isFinished.

void sudoku_check_if_valid_and_finished(struct SudokuPuzzle *puzzle)
{
    assert(NULL != puzzle && "sudoku_check_if_valid_and_finished(): Bad input");
    puzzle->m_isFinished = false;
    // Divide the test into two loops.
    // Motivation: the second test (for conflicts) takes more time and needs to
    // be performed only when all cells have been filled
    for (unsigned int i = 0; i < NROWS*NCOLS; ++i)
    {
        if (0 == puzzle->m_board[i].m_value)
            return;
    }
    for (unsigned int i = 0; i < NROWS*NCOLS; ++i)
    {
        if (has_conflict(puzzle, i, puzzle->m_board[i].m_value))
            return;
    }
    puzzle->m_isFinished = true;
}
