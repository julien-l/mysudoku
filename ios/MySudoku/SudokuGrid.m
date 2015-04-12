//
//  SudokuGrid.m
//  MySudoku
//
//  Created by Julien Lemaitre on 2015-03-22.
//  Copyright (c) 2015 Julien Lemaitre. All rights reserved.
//

#import "SudokuGrid.h"
#import "SudokuCell.h"

#define NROWS 9
#define NCOLS 9

@implementation SudokuGrid
{
    int m_cellWidthList [NCOLS];
    SudokuCell *m_labelArray [NROWS*NCOLS];
}

- (SudokuCell*)cellAtRow:(uint)row andCol:(uint)col
{
    assert(row < NROWS && col < NCOLS && "cellAtCoords(): Bad inptus");
    return m_labelArray[row*NCOLS+col];
}

- (void)initHelper
{
    memset(m_cellWidthList, 0, sizeof(m_cellWidthList));
    for (uint i = 0; i < NROWS*NCOLS; ++i)
    {
        SudokuCell *cell = [SudokuCell new];
        m_labelArray[i] = cell;
        [self addSubview:cell];
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

//! \note The layout algorithm assumes the display area is a square.

- (void)layoutSubviews
{
    [super layoutSubviews];

    // Compute the layout for the 9x9 grid
    const CGRect rect = [self frame];
    const uint usableWidth = ((uint) rect.size.width);
    const uint cellWidth = (uint) floorf(usableWidth/NCOLS);
    for (uint i = 0; i < NCOLS; ++i)
    {
        m_cellWidthList[i] = cellWidth;
    }
    // Then spread the extra space on the first columns
    const int extraSpace = usableWidth % NCOLS;
    assert(extraSpace < NCOLS && "layoutSubviews(): Bad spacing constraints");
    for (uint i = 0; i < extraSpace; ++i)
    {
        m_cellWidthList[i] += 1;
    }
    // Apply to the labels
    uint dx = 0;
    uint dy = 0;
    for (uint row = 0; row < NROWS; ++row)
    {
        dx = 0;
        const int cellHeigth = m_cellWidthList[row];
        for (uint col = 0; col < NCOLS; ++col)
        {
            CGRect rect = CGRectMake(dx, dy, m_cellWidthList[col], cellHeigth);
            SudokuCell *cell = [self cellAtRow:row andCol:col];
            [cell setFrame:rect];
            if (col != NCOLS-1)
                [cell addBorderRight];
            if (col > 0 && 0 == col%3)
                [cell addBorderLeft];
            if (row != NROWS-1)
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
        NSLog(@"updateContent(): Cannot update grid content, no delegate is set");
        return;
    }
    for (uint i = 0; i < NROWS*NCOLS; ++i)
    {
        [m_labelArray[i] setContent:[_delegate cellContentAtIndex:i]];
    }
    [self setNeedsDisplay];
}

@end
