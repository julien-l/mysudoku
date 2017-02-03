//
//  Sudoku.h
//  MySudoku
//
//  Created by Julien Lemaitre on 2015-04-11.
//  Copyright (c) 2015 Julien Lemaitre. All rights reserved.
//

#ifndef __MySudoku__Sudoku__
#define __MySudoku__Sudoku__

#define SUDOKU_DATA_VERSION 01

//
// Structures
//

//! \brief The different possible types of a cell

enum SudokuCellType
{
    CELL_TYPE_EMPTY = 0,    //!< \brief Cell is initially empty (needs to be filled)
    CELL_TYPE_INITIAL,      //!< \brief Cell has a number part of the initial values
};

//! \brief The different possible states of a cell

enum SudokuCellState
{
    CELL_STATE_NONE = 0,    //!< \brief Cell is in none of the following states
    CELL_STATE_SELECTED,    //!< \brief Cell is selected = was clicked
    CELL_STATE_HIGHLIGHTED, //!< \brief Cell is highlighted to attract attention (for hints)
    CELL_STATE_PEER,        //!< \brief Cell is a peer of the currently highlighted (same row, column, unit)
};

//! \brief Current mode of selection (one by one or sequence)

enum SudokuSelectionMode
{
    SELECTION_MODE_ONE_BY_ONE,  //!< \brief Select a cell then a number to fill it
    SELECTION_MODE_SEQUENCE,    //!< \brief Select a number then click on cells to fill (they will fill with the currently selected number)
};

//! \brief The content of one cell

struct SudokuCellContent
{
    enum SudokuCellType     m_type;     //!< \brief Type of cell (e.g. empty, given)
    enum SudokuCellState    m_state;    //!< \brief Graphical state
    unsigned int            m_value;    //!< \brief Current value [1..9], 0 for empty
    unsigned int            m_index;    //!< \brief Cell index in the grid [0..80]
};

//! \brief The puzzle data

struct SudokuPuzzle
{
    struct SudokuCellContent *  m_board;                //!< \brief Array of cells
    unsigned int                m_selectedCellIndex;    //!< \brief Index of the currently selected cell
    enum SudokuSelectionMode    m_selectionMode;        //!< \brief Current selection mode (one by one, sequence)
    unsigned int                m_currentNumber;        //!< \brief Value of the currently selected number
    bool                        m_isFinished;           //!< \brief Flag set to true when the puzzle is solved
};

//
// Interface
//

struct SudokuPuzzle * sudoku_alloc_puzzle();
void sudoku_dealloc_puzzle(struct SudokuPuzzle *puzzle);
void sudoku_clear_puzzle(struct SudokuPuzzle *puzzle);
struct SudokuCellContent * sudoku_cell_content_at_index(struct SudokuPuzzle *puzzle, unsigned int index);
void sudoku_generate_puzzle(struct SudokuPuzzle *puzzle);
bool sudoku_save_to_file(struct SudokuPuzzle *puzzle, const char *filename);

//
// Callbacks for user interface
//

void sudoku_on_cell_clicked(struct SudokuPuzzle *puzzle, unsigned int index);
void sudoku_on_number_clicked(struct SudokuPuzzle *puzzle, unsigned int number);
void sudoku_on_eraser_clicked(struct SudokuPuzzle *puzzle);
void sudoku_on_mode_changed(struct SudokuPuzzle *puzzle, enum SudokuSelectionMode mode);

#endif /* defined(__MySudoku__Sudoku__) */
