//
//  SudokuAlgorithms.h
//  MySudoku
//
//  Created by Julien Lemaitre on 2015-04-04.
//  Copyright (c) 2015 Julien Lemaitre. All rights reserved.
//

#ifndef __MySudoku__SudokuAlgorithms__
#define __MySudoku__SudokuAlgorithms__

#include <stdbool.h>

// Fwd-declaration
struct SudokuPuzzle;

bool SudokuCheckNoConflict(struct SudokuPuzzle *puzzle, uint index, uint value);

void SudokuGenerateSolution(struct SudokuPuzzle *puzzle);

#endif /* defined(__MySudoku__SudokuAlgorithms__) */
