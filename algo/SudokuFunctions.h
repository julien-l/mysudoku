//
//  SudokuFunctions.h
//  MySudoku
//
//  Created by Julien Lemaitre on 2015-04-11.
//  Copyright (c) 2015 Julien Lemaitre. All rights reserved.
//

#ifndef __MySudoku__SudokuFunctions__
#define __MySudoku__SudokuFunctions__

#include <stdint.h>

// Fwd-declaration
struct SudokuCellContent;
struct SudokuPuzzle;

struct SudokuPuzzle * SudokuAllocPuzzle();

void SudokuDeallocPuzzle(struct SudokuPuzzle *puzzle);

void SudokuClearPuzzle(struct SudokuPuzzle *puzzle);

struct SudokuCellContent * SudokuCellContentAt(struct SudokuPuzzle *puzzle, uint row, uint col);

bool SudokuSaveToFile(struct SudokuPuzzle *puzzle, const char *filename);

void SudokuGeneratePuzzle(struct SudokuPuzzle *puzzle);

#endif /* defined(__MySudoku__SudokuFunctions__) */
