//
//  SudokuCellContent.h
//  MySudoku
//
//  Created by Julien Lemaitre on 2015-03-30.
//  Copyright (c) 2015 Julien Lemaitre. All rights reserved.
//

#import <Foundation/Foundation.h>

//! \brief The different possible states of a cell

enum SudokuCellType
{
    TYPE_EMPTY,     //!< Cell is empty
    TYPE_NUMBER,    //!< Cell has one number
    TYPE_PENCIL,    //!< Cell has one or more pencil notes
    TYPE_INITIAL,   //!< Cell has a number part of the initial values
};

typedef enum SudokuCellType SudokuCellType;

//! \brief The content of one cell
//!
//! Array \c content is populated according to the value of \c type:
//! - empty if \c type is \c TYPE_EMPTY
//! - size 1 if \c type is \c TYPE_NUMBER
//! - size in range [0 9] if \c type is \c TYPE_PENCIL
//! - size 1 if \c type is \c TYPE_INITIAL

@interface SudokuCellContent : NSObject

@property SudokuCellType type;
@property (copy) NSString * content;

@end
