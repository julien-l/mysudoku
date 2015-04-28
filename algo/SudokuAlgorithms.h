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

void SudokuGenerateSolution(struct SudokuPuzzle *puzzle);

void SudokuMakeHoles(struct SudokuPuzzle *puzzle, uint n);

#endif /* defined(__MySudoku__SudokuAlgorithms__) */
