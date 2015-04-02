//
//  ViewController.m
//  MySudoku
//
//  Created by Julien Lemaitre on 2015-03-30.
//  Copyright (c) 2015 Julien Lemaitre. All rights reserved.
//

#import "ViewController.h"
#import "SudokuGrid.h"
#import "SudokuCellContent.h"

@interface ViewController ()
@property (weak, nonatomic) IBOutlet SudokuGrid *theGrid;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    _theGrid.delegate = self;
    [_theGrid updateContent];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (SudokuCellContent*)cellContentAt:(uint)row andCol:(uint)col {
    SudokuCellContent * cellContent = [SudokuCellContent new];
    if (row != col) {
        cellContent.type = TYPE_EMPTY;
    } else {
        cellContent.type = TYPE_INITIAL;
    }
    cellContent.content = [NSString stringWithFormat:@"%i%i",row,col];
    return cellContent;
}

@end
