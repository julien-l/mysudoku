//
//  SudokuCell.h
//  MySudoku
//
//  Created by Julien Lemaitre on 2015-03-29.
//  Copyright (c) 2015 Julien Lemaitre. All rights reserved.
//

#import <UIKit/UIControl.h>
#include "Sudoku.h"

@interface SudokuCell : UIControl

@property (nonatomic, setter=setContent:) SudokuCellContent *cellContent;

- (void)setContent:(SudokuCellContent*)cellContent;

- (void)addBorderRight;
- (void)addBorderLeft;
- (void)addBorderBottom;
- (void)addBorderTop;

@end
