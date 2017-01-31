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
    struct SudokuPuzzle *thePuzzle;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    assert(nil != _theGrid && "viewDidLoad(): The grid property is null. Did you set the referencing outlet?");
    [_theGrid setDelegate:self];
    if (nil == thePuzzle) {
        thePuzzle = sudoku_alloc_puzzle();
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

- (struct SudokuCellContent*)cellContentAtIndex:(uint)index {
    return sudoku_cell_content_at_index(thePuzzle, index);
}

- (void)setSelectedCellAtIndex:(uint)index {
    sudoku_on_cell_clicked(thePuzzle, index);
    [self onPuzzleUpdated];
}

//
// <-- protocol
//

- (void)dealloc {
    sudoku_dealloc_puzzle(thePuzzle);
    thePuzzle = NULL;
}

//
// helpers
//

- (void)generateThePuzzle {
    sudoku_generate_puzzle(thePuzzle);
    [self onPuzzleUpdated];
    // Lines below are for debug
    NSString *path = [[self applicationDocumentsDirectory].path
                       stringByAppendingPathComponent:@"SudokuSolution.txt"];
    sudoku_save_to_file(thePuzzle, [path UTF8String]);
}

- (IBAction)onNumberClicked:(UIButton *)sender {
    const uint num = [[sender currentTitle] intValue];
    sudoku_on_number_clicked(thePuzzle, num);
    [self onPuzzleUpdated];
}

- (IBAction)onEraserClicked:(UIButton *)sender {
    sudoku_on_eraser_clicked(thePuzzle);
    [self onPuzzleUpdated];
}

- (void)onPuzzleUpdated
{
    [_theGrid updateContent];
    if (thePuzzle->m_isFinished)
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
