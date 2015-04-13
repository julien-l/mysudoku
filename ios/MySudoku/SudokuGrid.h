//
//  SudokuGrid.h
//  MySudoku
//
//  Created by Julien Lemaitre on 2015-03-22.
//  Copyright (c) 2015 Julien Lemaitre. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SudokuDataSource.h"

// Fwd-declaration
@class SudokuCell;

@interface SudokuGrid : UIView

// Delegate properties should always be weak references
// See http://stackoverflow.com/a/4796131/263871 for the rationale
// (Tip: If you're not using ARC, use `assign` instead of `weak`)
@property (nonatomic, weak) id<SudokuDataSource> delegate;

- (void)updateContent;

- (IBAction)buttonTapped:(SudokuCell*)sender;

@end
