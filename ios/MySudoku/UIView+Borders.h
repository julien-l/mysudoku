//
//  UIView+Borders.h
//  MySudoku
//
//  Created by Julien Lemaitre on 2015-03-22.
//  Copyright (c) 2015 Julien Lemaitre. All rights reserved.
//

#import <UIKit/UIView.h>

@interface UIView (Borders)
- (id) borderRight: (float) width;
- (id) borderLeft: (float) width;
- (id) borderBottom: (float) width;
- (id) borderTop: (float) width;
@end