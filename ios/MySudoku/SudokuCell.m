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
        // Configure the label
        _label = [UILabel new];
        [_label setTextAlignment:NSTextAlignmentCenter];
        [_label setTextColor:_textColor];
        [_label setAutoresizingMask:(UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight)];
        [self addSubview:_label];
    }
    return self;
}

- (void)setSingleNumber:(NSString*)number {
    [_label setText:number];
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
