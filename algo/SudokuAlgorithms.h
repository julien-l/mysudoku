//
//  SudokuAlgorithms.h
//  MySudoku
//
//  Created by Julien Lemaitre on 2015-04-04.
//  Copyright (c) 2015 Julien Lemaitre. All rights reserved.
//

#ifndef __MySudoku__SudokuAlgorithms__
#define __MySudoku__SudokuAlgorithms__

// Fwd-declaration
struct SudokuPuzzle;

void sudoku_generate_solution(struct SudokuPuzzle *puzzle);

void sudoku_make_holes(struct SudokuPuzzle *puzzle, uint n);

//! \brief Check if the puzzle is valid and finished and store the result in the \c isFinished field of \c puzzle.
void sudoku_check_if_valid_and_finished(struct SudokuPuzzle *puzzle);

#endif /* defined(__MySudoku__SudokuAlgorithms__) */
