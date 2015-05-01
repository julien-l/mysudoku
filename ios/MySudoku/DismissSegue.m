//
//  DismissSegue.m
//  MySudoku
//
//  Created by Julien Lemaitre on 2015-05-03.
//  Copyright (c) 2015 Julien Lemaitre. All rights reserved.
//

#import "DismissSegue.h"

@implementation DismissSegue

- (void)perform {
    UIViewController *sourceViewController = self.sourceViewController;
    [sourceViewController.presentingViewController dismissViewControllerAnimated:YES completion:nil];
}

@end
