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
    NSLog(@"viewDidLoad()");
    if (nil == thePuzzle) {
        thePuzzle = SudokuAllocPuzzle();
        SudokuGeneratePuzzle(thePuzzle);
    }
    [_theGrid setDelegate: self];
    [_theGrid updateContent];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (SudokuCellContent*)cellContentAt:(uint)row andCol:(uint)col {
    return SudokuCellContentAt(thePuzzle, row, col);
}

- (void)dealloc {
    NSLog(@"dealloc()");
    SudokuDeallocPuzzle(thePuzzle);
    thePuzzle = NULL;
}

@end
