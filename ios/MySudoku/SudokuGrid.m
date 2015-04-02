//
//  SudokuGrid.m
//  MySudoku
//
//  Created by Julien Lemaitre on 2015-03-22.
//  Copyright (c) 2015 Julien Lemaitre. All rights reserved.
//

#import "SudokuGrid.h"
#import "SudokuCell.h"

#define NROW 9
#define NCOL 9

@implementation SudokuGrid

int m_cellWidthList[NCOL] = {0,0,0, 0,0,0, 0,0,0};
SudokuCell * m_labelArray[NROW*NCOL];

- (SudokuCell*)labelAt:(uint)row and:(uint)col
{
    assert(row < NROW && col < NCOL);
    return m_labelArray[row*NCOL + col];
}

- (void)storeCellPointerAt:(uint)row and:(uint)col pointer:(SudokuCell*)cell
{
    assert(row < NROW && col < NCOL);
    m_labelArray[row*NCOL + col] = cell;
}

- (void)initHelper
{
    // Add the labels
    for (uint row = 0; row < NROW; ++row)
    {
        for (uint col = 0; col < NCOL; ++col)
        {
            SudokuCell * cell = [SudokuCell new];
            [self addSubview:cell];
            [self storeCellPointerAt:row and:col pointer:cell];
        }
    }
}

-  (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        [self initHelper];
    }
    return self;
}

- (id)initWithCoder:(NSCoder*)decoder
{
    self = [super initWithCoder:decoder];
    if (self)
    {
        [self initHelper];
    }
    return self;
}

- (void)layoutSubviews
{
    [super layoutSubviews];

    // Compute the layout for the 9x9 grid
    const CGRect rect = [self frame];
    const uint usableWidth = ((uint)rect.size.width);
    const uint cellWidth = (uint) floorf(usableWidth / NCOL);
    NSLog(@"Width for cells = %i, column width = %i", usableWidth, cellWidth);
    for (uint i = 0; i < NCOL; ++i)
    {
        m_cellWidthList[i] = cellWidth;
    }
    // Then spread the extra space on the first columns
    const int extraSpace = usableWidth % NCOL;
    assert(extraSpace < NCOL);
    NSLog(@"Extra space = %i", extraSpace);
    for (uint i = 0; i < extraSpace; ++i)
    {
        m_cellWidthList[i] += 1;
    }
    for (uint i = 0; i < NCOL; ++i)
    {
        NSLog(@"%i, ", m_cellWidthList[i]);
    }
    // Apply to the labels
    uint dx = 0;
    uint dy = 0;
    for (uint row = 0; row < NROW; ++row)
    {
        dx = 0;
        const int cellHeigth = m_cellWidthList[row];
        for (uint col = 0; col < NCOL; ++col)
        {
            CGRect rect = CGRectMake(dx, dy, m_cellWidthList[col], cellHeigth);
            SudokuCell * cell = [self labelAt:row and:col];
            [cell setFrame:rect];
            if (col != NCOL-1)
                [cell addBorderRight];
            if (col > 0 && 0 == col%3)
                [cell addBorderLeft];
            if (row != NROW-1)
                [cell addBorderBottom];
            if (row > 0 && 0 == row%3)
                [cell addBorderTop];
            dx += m_cellWidthList[col];
        }
        dy += cellHeigth;
    }
}

- (void)updateContent
{
    if (nil == _delegate)
    {
        NSLog(@"Cannot update grid content, no delegate is set");
        return;
    }

    for (uint row = 0; row < NROW; ++row)
    {
        for (uint col = 0; col < NCOL; ++col)
        {
            SudokuCell * cell = [self labelAt:row and:col];
            [cell setContent:[_delegate cellContentAt:row andCol:col]];
        }
    }
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code
}
*/

@end
