//
//  SudokuGrid.h
//  MySudoku
//
//  Created by Julien Lemaitre on 2015-03-22.
//  Copyright (c) 2015 Julien Lemaitre. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface SudokuGrid : UIView

@property (readonly) uint cellBorderWidth;     //!< Size of the borders between cells in the same region
@property (readonly) UIColor * cellBorderColor;

@end
