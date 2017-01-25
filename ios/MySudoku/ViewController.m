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
    assert(nil != _theGrid && "viewDidLoad(): The grid property is null. Did you set the referencing outlet?");
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

//
// protocol -->
//

- (SudokuCellContent*)cellContentAtIndex:(uint)index {
    return SudokuCellContentAtIndex(thePuzzle, index);
}

- (void)setSelectedCellAtIndex:(uint)index {
    SudokuOnCellClicked(thePuzzle, index);
    [self onPuzzleUpdated];
}

//
// <-- protocol
//

- (void)dealloc {
    SudokuDeallocPuzzle(thePuzzle);
    thePuzzle = NULL;
}

//
// helpers
//

- (void)generateThePuzzle {
    SudokuGeneratePuzzle(thePuzzle);
    [self onPuzzleUpdated];
    // Lines below are for debug
    NSString *path = [[self applicationDocumentsDirectory].path
                       stringByAppendingPathComponent:@"SudokuSolution.txt"];
    SudokuSaveToFile(thePuzzle, [path UTF8String]);
}

- (IBAction)onNumberClicked:(UIButton *)sender {
    const uint num = [[sender currentTitle] intValue];
    SudokuOnNumberClicked(thePuzzle, num);
    [self onPuzzleUpdated];
}

- (IBAction)onEraserClicked:(UIButton *)sender {
    SudokuOnEraserClicked(thePuzzle);
    [self onPuzzleUpdated];
}

- (void)onPuzzleUpdated
{
    [_theGrid updateContent];
    if (thePuzzle->isFinished)
    {
        UIAlertController* alert = [UIAlertController alertControllerWithTitle:@"Puzzle complete"
            message:@""
            preferredStyle:UIAlertControllerStyleAlert];
        UIAlertAction* actionNew = [UIAlertAction actionWithTitle:@"New puzzle"
            style:UIAlertActionStyleDefault
            handler:^(UIAlertAction * action) {
                [self generateThePuzzle];
            }];
        [alert addAction:actionNew];
        [self presentViewController:alert animated:YES completion:nil];
    }
}

// Return the URL to the application's Documents directory.

- (NSURL*)applicationDocumentsDirectory {
    return [[[NSFileManager defaultManager] URLsForDirectory:NSDocumentDirectory 
         inDomains:NSUserDomainMask] lastObject];
}

@end
