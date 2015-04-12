//
//  SudokuCell.m
//  MySudoku
//
//  Created by Julien Lemaitre on 2015-03-29.
//  Copyright (c) 2015 Julien Lemaitre. All rights reserved.
//

#import "SudokuCell.h"
#import <UIKit/UILabel.h>
#import "UIView+Borders.h"

@interface SudokuCell ()

    @property UILabel * label;

@end

@implementation SudokuCell

- (id)init
{
    if (self = [super init])
    {
        // Set default properties values
        _cellBorderWidth = 1;
        _cellBorderColor = [[UIColor lightGrayColor] colorWithAlphaComponent:0.25f];
        _textColor = [UIColor darkGrayColor];
        _cellInitialBackgroundColor = [[UIColor darkGrayColor] colorWithAlphaComponent:0.25f];
        // Configure the label
        _label = [UILabel new];
        [_label setTextAlignment:NSTextAlignmentCenter];
        [_label setTextColor:_textColor];
        [_label setAutoresizingMask:(UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight)];
        [self addSubview:_label];
    }
    return self;
}

- (void)setContent:(SudokuCellContent*)cellContent
{
    [_label setText:[NSString stringWithFormat:@"%d", cellContent->value]];
    switch (cellContent->type)
    {
        case CELL_TYPE_INITIAL:
            [_label setBackgroundColor:_cellInitialBackgroundColor];
            break;
        default:
            [_label setBackgroundColor:[UIColor whiteColor]];
            break;
    }
    switch (cellContent->state)
    {
        case CELL_STATE_SELECTED:
            [_label setBackgroundColor:[UIColor blueColor]];
            break;
        case CELL_STATE_PEER:
            [_label setBackgroundColor:[[UIColor blueColor] colorWithAlphaComponent:0.25f]];
            break;
        default:
            // Do nothing, leave the cells as-is
            break;
    }
}

- (void)addBorderRight
{
    [self borderRight:_cellBorderWidth color:_cellBorderColor];
}

- (void)addBorderLeft
{
    [self borderLeft:_cellBorderWidth color:_cellBorderColor];
}

- (void)addBorderBottom
{
    [self borderBottom:_cellBorderWidth color:_cellBorderColor];
}

- (void)addBorderTop
{
    [self borderTop:_cellBorderWidth color:_cellBorderColor];
}

@end
