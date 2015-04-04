//
//  SudokuDataSource.h
//  MySudoku
//
//  Created by Julien Lemaitre on 2015-03-23.
//  Copyright (c) 2015 Julien Lemaitre. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "SudokuData.h"

//! \brief The protocol for the Sudoku grid delegate
//!
//! Vocabulary
//!
//! - Region: the big squares of the grid, which are further divided into 9
//! cells each. There are 9 regions in total.
//! - Cell: the 9 cells in one region. There are 81 cells in total.
//!
//! Indexation
//!
//! Regions are not indexed.
//!
//! Cells are indexed from \c 0 to \c 80 in row-major order, without taking into
//! account the regions.
//!
//! |  0  |  1  |  2  | ... |  8  |
//! |  9  | 10  | 11  | ... | 17  |
//! | ...                         |
//! | 72  | 73  | 74  | ... | 80  |
//!
//! Same for the cells.

@protocol SudokuDataSource <NSObject>

//- (const SudokuCellContent *) cellContentAt:(uint)regionIndex andCellIndex:(uint)cellIndex;
//
//- (enum SudokuCellType) cellTypeAt:(uint)regionIndex andCellIndex:(uint)cellIndex;
//
//- (BOOL) cellAt:(uint)regionIndex andCellIndex:(uint)cellIndex hasType:(enum SudokuCellType) type;

- (SudokuCellContent*)cellContentAt:(uint)row andCol:(uint)col;

@end
