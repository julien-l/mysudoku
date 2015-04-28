//
//  Sudoku.h
//  MySudoku
//
//  Created by Julien Lemaitre on 2015-04-11.
//  Copyright (c) 2015 Julien Lemaitre. All rights reserved.
//

#ifndef __MySudoku__Sudoku__
#define __MySudoku__Sudoku__

#include <stdint.h>

#define SUDOKU_DATA_VERSION 01

// -----------------------------------------------------------------------------
// Structures
// -----------------------------------------------------------------------------

//! \brief The different possible types of a cell

enum SudokuCellType
{
    CELL_TYPE_EMPTY = 0,    //!< Cell is empty
    CELL_TYPE_NUMBER,       //!< Cell has one number
    CELL_TYPE_PENCIL,       //!< Cell has one or more pencil notes
    CELL_TYPE_INITIAL,      //!< Cell has a number part of the initial values
};

typedef enum SudokuCellType SudokuCellType;

//! \brief The different possible states of a cell

enum SudokuCellState
{
    CELL_STATE_NONE = 0,    //!< Cell is in none of the following states
    CELL_STATE_SELECTED,    //!< Cell is selected = was clicked
    CELL_STATE_HIGHLIGHTED, //!< Cell is highlighted to attract attention (for hints)
    CELL_STATE_PEER,        //!< Cell is a peer of the currently highlighted (same row, column, unit)
};

typedef enum SudokuCellState SudokuCellState;

//! \brief The content of one cell
//!
//! Array \c content is populated according to the value of \c type:
//! - empty if \c type is \c CELL_TYPE_EMPTY
//! - size 1 if \c type is \c CELL_TYPE_NUMBER
//! - size in range [0 9] if \c type is \c CELL_TYPE_PENCIL
//! - size 1 if \c type is \c CELL_TYPE_INITIAL

struct SudokuCellContent
{
    SudokuCellType type;
    SudokuCellState state;
    uint value;
    uint index;
};

typedef struct SudokuCellContent SudokuCellContent;

//! \brief The puzzle data

struct SudokuPuzzle
{
    SudokuCellContent *board;
    uint selectedCellIndex;
};

typedef struct SudokuPuzzle SudokuPuzzle;

// -----------------------------------------------------------------------------
// Interface
// -----------------------------------------------------------------------------

SudokuPuzzle * SudokuAllocPuzzle();

void SudokuDeallocPuzzle(SudokuPuzzle *puzzle);

void SudokuClearPuzzle(SudokuPuzzle *puzzle);

SudokuCellContent * SudokuCellContentAtIndex(SudokuPuzzle *puzzle, uint index);

void SudokuGeneratePuzzle(SudokuPuzzle *puzzle);

bool SudokuSaveToFile(SudokuPuzzle *puzzle, const char *filename);

// -----------------------------------------------------------------------------
// Callbacks for user interface
// -----------------------------------------------------------------------------

void SudokuOnCellClicked(SudokuPuzzle *puzzle, uint index);

#endif /* defined(__MySudoku__Sudoku__) */
