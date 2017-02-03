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

#define NO_CELL_SELECTED    81
#define ERASER_SELECTED     0   // zero corresponds to an empty cell: assign the eraser to the cell to clear it
#define NO_NUMBER_SELECTED  81

// Helper macros
#define CURRENT_CELL(p)         p->m_board[p->m_selectedCellIndex]
#define IN_RANGE(n,low,up)      (n>=low && n<=up)

//
// Local functions
//

//! \brief Update the graphical state of the peers of the given cell

void set_state_for_peers_of_index(struct SudokuPuzzle *puzzle, unsigned int index, int state)
{
    assert(NULL != puzzle && index < NROWS*NCOLS && "set_state_for_peers_of_index(): Bad input");
    // get corresponding row and column
    const unsigned int rowIndex = (unsigned int) floorf(index/NCOLS);
    const unsigned int colIndex = (unsigned int) index%NCOLS;
    // update row and column
    for (unsigned int col = 0; col < NCOLS; ++col)
    {
        if (colIndex == col) {
            continue;
        }
        puzzle->m_board[rowIndex*NCOLS+col].m_state = state;
    }
    for (unsigned int row = 0; row < NROWS; ++row)
    {
        if (rowIndex == row) {
            continue;
        }
        puzzle->m_board[row*NCOLS+colIndex].m_state = state;
    }
    // update region
    const unsigned int regionRowIndex = (unsigned int) floorf(rowIndex/NREGIONS);
    const unsigned int regionColIndex = (unsigned int) floorf(colIndex/NREGIONS);
    assert(regionRowIndex < NREGIONS && regionColIndex < NREGIONS && "set_state_for_peers_of_index(): Region indices out of range");
    const unsigned int start = regionRowIndex*NREGIONS*NCOLS + regionColIndex*NREGIONS;
    for (unsigned int row = 0; row < NREGIONS; ++row)
    {
        for (unsigned int col = 0; col < NREGIONS; ++col)
        {
            const unsigned int currentIndex = start + row*NCOLS + col;
            if (currentIndex == index) {
                continue;
            }
            puzzle->m_board[currentIndex].m_state = state;
        }
    }
}

//
// Interface
//

//! \brief Allocate memory for a puzzle
//!
//! The memory is not initialized. Don't forget to de-allocate the memory with
//! sudoku_dealloc_puzzle().

struct SudokuPuzzle * sudoku_alloc_puzzle()
{
    struct SudokuPuzzle * ptr = (struct SudokuPuzzle*) malloc(sizeof(struct SudokuPuzzle));
    ptr->m_board = (struct SudokuCellContent*) malloc(sizeof(struct SudokuCellContent)*NCOLS*NROWS);
    return ptr;
}

//! \brief De-allocate the memory for the given puzzle

void sudoku_dealloc_puzzle(struct SudokuPuzzle *puzzle)
{
    if (NULL != puzzle)
    {
        free(puzzle->m_board);
    }
    free(puzzle);
}

//! \brief Clear the given puzzle

void sudoku_clear_puzzle(struct SudokuPuzzle *puzzle)
{
    assert(NULL != puzzle && "sudoku_clear_puzzle(): Bad input");
    memset(puzzle->m_board, 0, sizeof(struct SudokuCellContent)*NCOLS*NROWS);
    for (unsigned int i = 0; i < NROWS*NCOLS; ++i)
    {
        puzzle->m_board[i].m_index = i;
    }
    puzzle->m_selectedCellIndex = NO_CELL_SELECTED;
    puzzle->m_selectionMode = SELECTION_MODE_ONE_BY_ONE;
    puzzle->m_currentNumber = NO_NUMBER_SELECTED;
    puzzle->m_isFinished = false;
}

//! \brief Get the cell structure at the given index

struct SudokuCellContent * sudoku_cell_content_at_index(struct SudokuPuzzle *puzzle, unsigned int index)
{
    assert(NULL != puzzle && index < NROWS*NCOLS && "SudokuCellContentAtIndex(): Bad input");
    return &(puzzle->m_board[index]);
}

//! \brief Generate a puzzle

void sudoku_generate_puzzle(struct SudokuPuzzle *puzzle)
{
    assert(NULL != puzzle && "sudoku_generate_puzzle(): Bad input");
    sudoku_clear_puzzle(puzzle);
    sudoku_generate_solution(puzzle);
    sudoku_make_holes(puzzle, 10);
    for (unsigned int i = 0; i < NROWS*NCOLS; ++i)
    {
        if (0 != puzzle->m_board[i].m_value)
        {
            puzzle->m_board[i].m_type = CELL_TYPE_INITIAL;
        }
        else
        {
            puzzle->m_board[i].m_type = CELL_TYPE_EMPTY;
        }
        puzzle->m_board[i].m_state = CELL_STATE_NONE;
    }
}

//! \brief Save the puzzle to the given text file
//!
//! The file is compatible with http://www.sudoku-solutions.com/ (useful to test
//! solutions).

bool sudoku_save_to_file(struct SudokuPuzzle *puzzle, const char *filename)
{
    assert(NULL != puzzle && "SudokuSaveToFile(): Bad input");
    printf("Saving solution to file '%s'\n", filename);
    FILE *f = fopen(filename, "w");
    if (NULL == f)
    {
        perror("sudoku_save_to_file(): Can't open file");
        return false;
    }
    for (unsigned int i = 0; i < NROWS*NCOLS; ++i)
    {
        fprintf(f, "%d", puzzle->m_board[i].m_value);
    }
    fclose(f);
    return true;
}

//
// Callbacks for user interface
//

//! \brief Callback when selecting a number in the menu

void sudoku_on_number_clicked(struct SudokuPuzzle *puzzle, unsigned int number)
{
    assert(NULL != puzzle && "sudoku_on_number_clicked(): Bad input");
    puzzle->m_currentNumber = number;
    if (SELECTION_MODE_ONE_BY_ONE == puzzle->m_selectionMode &&
        CELL_TYPE_EMPTY == CURRENT_CELL(puzzle).m_type &&
        NO_CELL_SELECTED != puzzle->m_selectedCellIndex)
    {
        CURRENT_CELL(puzzle).m_value = number;
        sudoku_check_if_valid_and_finished(puzzle);
    }
}

//! \brief Callback when selecting a cell in the grid

void sudoku_on_cell_clicked(struct SudokuPuzzle *puzzle, unsigned int index)
{
    assert(NULL != puzzle && index < NROWS*NCOLS && "sudoku_on_cell_clicked(): Bad input");
    // Unselect previous cell
    if (NO_CELL_SELECTED != puzzle->m_selectedCellIndex)
    {
        CURRENT_CELL(puzzle).m_state = CELL_STATE_NONE;
        set_state_for_peers_of_index(puzzle, puzzle->m_selectedCellIndex, CELL_STATE_NONE);
    }
    // Select new one
    puzzle->m_selectedCellIndex = index;
    CURRENT_CELL(puzzle).m_state = CELL_STATE_SELECTED;
    set_state_for_peers_of_index(puzzle, puzzle->m_selectedCellIndex, CELL_STATE_PEER);
    if (SELECTION_MODE_SEQUENCE == puzzle->m_selectionMode &&
        CELL_TYPE_EMPTY == CURRENT_CELL(puzzle).m_type &&
        NO_NUMBER_SELECTED != puzzle->m_currentNumber)
    {
        CURRENT_CELL(puzzle).m_value = puzzle->m_currentNumber;
        sudoku_check_if_valid_and_finished(puzzle);
    }
}

//! \brief Callback when selecting the eraser in the menu

void sudoku_on_eraser_clicked(struct SudokuPuzzle *puzzle)
{
    sudoku_on_number_clicked(puzzle, ERASER_SELECTED);
}

//! \brief Callback when selecting the mode in the menu

void sudoku_on_mode_changed(struct SudokuPuzzle *puzzle, enum SudokuSelectionMode mode)
{
    assert(NULL != puzzle && "sudoku_on_mode_changed(): Bad input");
    puzzle->m_selectionMode = mode;
}
