//
//  SudokuCell.h
//  MySudoku
//
//  Created by Julien Lemaitre on 2015-03-29.
//  Copyright (c) 2015 Julien Lemaitre. All rights reserved.
//

#import <UIKit/UIControl.h>

@interface SudokuCell : UIControl

@property uint cellBorderWidth;         //!< Size of the borders between cells in the same region
@property UIColor * cellBorderColor;    //!< Color of the borders
@property UIColor * textColor;          //!< Color for the text

- (void)setSingleNumber:(NSString*)number;

- (void)addBorderRight;
- (void)addBorderLeft;
- (void)addBorderBottom;
- (void)addBorderTop;

@end
