//
//  UIView+Borders.h
//  MySudoku
//
//  Created by Julien Lemaitre on 2015-03-22.
//  Copyright (c) 2015 Julien Lemaitre. All rights reserved.
//

#import <UIKit/UIView.h>

@interface UIView (Borders)
- (id) borderShadow: (float)width opacity:(float)opacity;
- (id) borderRight: (float)width color:(UIColor*)color;
- (id) borderLeft: (float)width color:(UIColor*)color;
- (id) borderBottom: (float)width color:(UIColor*)color;
- (id) borderTop: (float)width color:(UIColor*)color;
@end