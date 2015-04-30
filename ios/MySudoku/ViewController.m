//
//  ViewController.m
//  MySudoku
//
//  Created by Julien Lemaitre on 2015-03-30.
//  Copyright (c) 2015 Julien Lemaitre. All rights reserved.
//

#import "ViewController.h"
#import "SudokuGrid.h"
#include "Sudoku.h"

@interface ViewController ()
@property (weak, nonatomic) IBOutlet SudokuGrid *theGrid;

@end

@implementation ViewController
{
    SudokuPuzzle *thePuzzle;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    [_theGrid setDelegate:self];
    if (nil == thePuzzle) {
        thePuzzle = SudokuAllocPuzzle();
    }
    [self generateThePuzzle];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (SudokuCellContent*)cellContentAtIndex:(uint)index {
    return SudokuCellContentAtIndex(thePuzzle, index);
}

- (void)setSelectedCellAtIndex:(uint)index {
    SudokuOnCellClicked(thePuzzle, index);
}

- (void)dealloc {
    SudokuDeallocPuzzle(thePuzzle);
    thePuzzle = NULL;
}

- (void)generateThePuzzle {
    SudokuGeneratePuzzle(thePuzzle);
    [_theGrid updateContent];
    // Lines below are for debug
    NSString *path = [[self applicationDocumentsDirectory].path
                       stringByAppendingPathComponent:@"SudokuSolution.txt"];
    SudokuSaveToFile(thePuzzle, [path UTF8String]);
}

- (IBAction)onNumberClicked:(UIButton *)sender {
    const uint num = [[sender currentTitle] integerValue];
    SudokuOnNumberClicked(thePuzzle, num);
    [_theGrid updateContent];
}

- (IBAction)onEraserClicked:(UIButton *)sender {
    SudokuOnEraserClicked(thePuzzle);
    [_theGrid updateContent];
}

/**
 Returns the URL to the application's Documents directory.
 */
- (NSURL*)applicationDocumentsDirectory {
    return [[[NSFileManager defaultManager] URLsForDirectory:NSDocumentDirectory 
         inDomains:NSUserDomainMask] lastObject];
}

@end
