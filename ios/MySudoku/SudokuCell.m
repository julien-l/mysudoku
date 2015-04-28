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
#import "Theme.h"

@interface SudokuCell ()

    @property UILabel *label;

@end

@implementation SudokuCell

- (id)init
{
    if (self = [super init])
    {
        _label = [UILabel new];
        [_label setTextAlignment:NSTextAlignmentCenter];
        [_label setTextColor:Theme.textColor];
        [_label setAutoresizingMask:(UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight)];
        [self addSubview:_label];
    }
    return self;
}

- (void)setContent:(SudokuCellContent*)cellContent
{
    _cellContent = cellContent;
    if (cellContent->value > 0) {
        [_label setText:[NSString stringWithFormat:@"%d", cellContent->value]];
    }
    else {
        [_label setText:@""];
    }
    // For the type we set the background color of the container (not the label)
    switch (cellContent->type)
    {
        case CELL_TYPE_INITIAL:
            [self setBackgroundColor:Theme.cellBackgroundColorForInitialType];
            break;
        default:
            [self setBackgroundColor:Theme.cellDefaultBackgroundColor];
            break;
    }
    // For the state, we set the label's color (as an overlay)
    switch (cellContent->state)
    {
        case CELL_STATE_SELECTED:
            [_label setBackgroundColor:Theme.cellOverlayColorForSelected];
            break;
        case CELL_STATE_PEER:
            [_label setBackgroundColor:Theme.cellOverlayColorForPeer];
            break;
        default:
            [_label setBackgroundColor:Theme.cellNoOverlayColor];
            break;
    }
}

- (void)addBorderRight
{
    [self borderRight:Theme.cellBorderWidth color:Theme.cellBorderColor];
}

- (void)addBorderLeft
{
    [self borderLeft:Theme.cellBorderWidth color:Theme.cellBorderColor];
}

- (void)addBorderBottom
{
    [self borderBottom:Theme.cellBorderWidth color:Theme.cellBorderColor];
}

- (void)addBorderTop
{
    [self borderTop:Theme.cellBorderWidth color:Theme.cellBorderColor];
}

@end
