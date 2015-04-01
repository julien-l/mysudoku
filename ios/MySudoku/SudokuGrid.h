//
//  SudokuGrid.h
//  MySudoku
//
//  Created by Julien Lemaitre on 2015-03-22.
//  Copyright (c) 2015 Julien Lemaitre. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "SudokuDataSource.h"

@interface SudokuGrid : UIView

@property (readonly) uint cellBorderWidth;     //!< Size of the borders between cells in the same region
@property (readonly) UIColor * cellBorderColor;

// Delegate properties should always be weak references
// See http://stackoverflow.com/a/4796131/263871 for the rationale
// (Tip: If you're not using ARC, use `assign` instead of `weak`)
@property (nonatomic, weak) id<SudokuDataSource> delegate;

- (void)updateContent;

@end
