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

- (void) borderShadow: (float)width opacity:(float)opacity
{
    self.layer.masksToBounds = NO;
    //layer.cornerRadius = 8; // if you like rounded corners
    self.layer.shadowOffset = CGSizeMake(-1,0);
    self.layer.shadowRadius = 0.5;
    self.layer.shadowOpacity = opacity;
}

- (void) borderRight: (float)width color:(UIColor*)color
{
    CALayer * layer = [self layer];
    CALayer * b = [CALayer layer];
    b.borderColor = color.CGColor;
    b.borderWidth = width;
    b.frame = CGRectMake(CGRectGetWidth(layer.frame)-width, 0, width, CGRectGetHeight(layer.frame));
    [layer addSublayer:b];
}

- (void) borderLeft: (float)width color:(UIColor*)color
{
    CALayer * layer = [self layer];
    CALayer * b = [CALayer layer];
    b.borderColor = color.CGColor;
    b.borderWidth = width;
    b.frame = CGRectMake(0, 0, width, CGRectGetHeight(layer.frame));
    [layer addSublayer:b];
}

- (void) borderBottom: (float)width color:(UIColor*)color
{
    CALayer * layer = [self layer];
    CALayer * b = [CALayer layer];
    b.borderColor = color.CGColor;
    b.borderWidth = width;
    b.frame = CGRectMake(0, CGRectGetHeight(layer.frame)-width, CGRectGetWidth(layer.frame), width);
    [layer addSublayer:b];
}

- (void) borderTop: (float)width color:(UIColor*)color
{
    CALayer * layer = [self layer];
    CALayer * b = [CALayer layer];
    b.borderColor = color.CGColor;
    b.borderWidth = width;
    b.frame = CGRectMake(0, 0, CGRectGetWidth(layer.frame), width);
    [layer addSublayer:b];
}

@end
