//
//  UIView+Borders.h
//  MySudoku
//
//  Created by Julien Lemaitre on 2015-03-22.
//  Copyright (c) 2015 Julien Lemaitre. All rights reserved.
//

#import <UIKit/UIView.h>

@interface UIView (Borders)
- (void) borderShadow: (float)width opacity:(float)opacity;
- (void) borderRight: (float)width color:(UIColor*)color;
- (void) borderLeft: (float)width color:(UIColor*)color;
- (void) borderBottom: (float)width color:(UIColor*)color;
- (void) borderTop: (float)width color:(UIColor*)color;
@end