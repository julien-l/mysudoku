//
//  UIView+Borders.m
//  MySudoku
//
//  Created by Julien Lemaitre on 2015-03-22.
//  Copyright (c) 2015 Julien Lemaitre. All rights reserved.
//

#import "UIView+Borders.h"
@import QuartzCore;

@implementation UIView (Borders)

- (id) borderRight: (float) width
{
    CALayer * layer = [self layer];
    CALayer * b = [CALayer layer];
    b.borderColor = [UIColor darkGrayColor].CGColor;
    b.borderWidth = width;
    b.frame = CGRectMake(CGRectGetWidth(layer.frame)-width, 0, width, CGRectGetHeight(layer.frame));
    [b setBorderColor:[UIColor blackColor].CGColor];
    [layer addSublayer:b];
    return self;
}

- (id) borderLeft: (float) width
{
    CALayer * layer = [self layer];
    CALayer * b = [CALayer layer];
    b.borderColor = [UIColor darkGrayColor].CGColor;
    b.borderWidth = width;
    b.frame = CGRectMake(0, 0, width, CGRectGetHeight(layer.frame));
    [b setBorderColor:[UIColor blackColor].CGColor];
    [layer addSublayer:b];
    return self;
}

- (id) borderBottom: (float) width
{
    CALayer * layer = [self layer];
    CALayer * b = [CALayer layer];
    b.borderColor = [UIColor darkGrayColor].CGColor;
    b.borderWidth = width;
    b.frame = CGRectMake(0, CGRectGetHeight(layer.frame)-width, CGRectGetWidth(layer.frame), width);
    [b setBorderColor:[UIColor blackColor].CGColor];
    [layer addSublayer:b];
    return self;
}

- (id) borderTop: (float) width
{
    CALayer * layer = [self layer];
    CALayer * b = [CALayer layer];
    b.borderColor = [UIColor darkGrayColor].CGColor;
    b.borderWidth = width;
    b.frame = CGRectMake(0, 0, CGRectGetWidth(layer.frame), width);
    [b setBorderColor:[UIColor blackColor].CGColor];
    [layer addSublayer:b];
    return self;
}

@end
