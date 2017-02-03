//
//  Theme.m
//  MySudoku
//
//  Created by Julien Lemaitre on 2015-04-12.
//  Copyright (c) 2015 Julien Lemaitre. All rights reserved.
//

#import "Theme.h"

@implementation Theme

+ (UIColor*)textColor {
    return [UIColor darkGrayColor];
}

+ (unsigned int)cellBorderWidth {
    return 1;
}

+ (UIColor*)cellBorderColor {
    return [UIColor darkGrayColor];
}

// Colors according to cell types

+ (UIColor*)cellDefaultBackgroundColor {
    return [UIColor whiteColor];
}

+ (UIColor*)cellBackgroundColorForInitialType {
    return [UIColor lightGrayColor];
}

// Colors according to cell state

+ (UIColor*)cellNoOverlayColor {
    return [UIColor clearColor];
}

+ (UIColor*)cellOverlayColorForSelected {
    return [[UIColor blueColor] colorWithAlphaComponent:0.25f];
}

+ (UIColor*)cellOverlayColorForHighlighted {
    return [[UIColor redColor] colorWithAlphaComponent:0.5f];
}

+ (UIColor*)cellOverlayColorForPeer {
    return [[UIColor blueColor] colorWithAlphaComponent:0.10f];
}

@end
