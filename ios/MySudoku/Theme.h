//
//  Theme.h
//  MySudoku
//
//  Created by Julien Lemaitre on 2015-04-12.
//  Copyright (c) 2015 Julien Lemaitre. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIColor.h>

@interface Theme : NSObject

+ (UIColor*)textColor;
+ (unsigned int)cellBorderWidth;
+ (UIColor*)cellBorderColor;

// Colors according to cell types

+ (UIColor*)cellDefaultBackgroundColor;
+ (UIColor*)cellBackgroundColorForInitialType;

// Colors according to cell state

+ (UIColor*)cellNoOverlayColor;
+ (UIColor*)cellOverlayColorForSelected;
+ (UIColor*)cellOverlayColorForHighlighted;
+ (UIColor*)cellOverlayColorForPeer;

@end
