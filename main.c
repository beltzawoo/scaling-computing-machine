#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define BLUE 1
#define RED 2
#define EMPTY 0

void print(int c) {
    if (c == BLUE)
        printf("X") ;
    if (c == RED)
        printf("@") ;
    if (c == EMPTY)
        printf("O") ;
}

struct col {int* cells; int alloc_height; int used_height; long int number;};
typedef struct col col;


void _free_col(col column) {
    // frees the column
    free(column.cells);
}

void _fill_col(col column) {
    // fill all unused but allocated sizes with empty
    for (int i=column.used_height; i<column.alloc_height; i++) {
        column.cells[i] = EMPTY;
    }
}

col _new_col(int size, int number, bool fill_unused) {
    // Returns a new empty column of size size
    col ccol = {malloc(sizeof(int) * size), size, 0, number};
    if (fill_unused)
        _fill_col(ccol);
    return ccol;
}

void _resize_column(col *column) {
    // doubles the height of the column
    col new_col = _new_col(column->alloc_height*2, column->number, false);
    new_col.used_height = column->used_height;
    for (int i=0; i<column->alloc_height; i++) {
        new_col.cells[i] = column->cells[i];
    }
    _fill_col(new_col);
    _free_col(*column);
    *column = new_col;
}

void _put_cell(col column, int cell) {
    // Puts cell in column, and updates the height of the column
    if (column.used_height+1 < column.alloc_height) {
        _resize_column(&column);
    }
    column.cells[column.used_height] = cell;
}

int _get_gravity_index(col column) {
    // Returns the next index a cell can be inserted into the column
    return column.used_height;
}


struct tab {col* columns; int alloc_width; int used_width; int zero_index; };
typedef struct tab tab;


void _free_tab(tab table) {
    // frees the tab
    for (int i=0; i<table.alloc_width; i++) {
        free(table.columns[i].cells);
    }
    free(table.columns);
}

tab _new_tab(int alloc_width, int zero_index, bool malloc_unused, int col_size) {
    // Returns a new tab (game board) of size size
    // with the zero_index col of size col_size initialized
    // or if malloc_unused is true, with all the other columns initialized
    tab ttab = {malloc(sizeof(col) * alloc_width), alloc_width, 1, zero_index};
    if (malloc_unused) {
        for (int i=0; i<alloc_width; i++) {
            ttab.columns[i] = _new_col(col_size, i-zero_index, true);
        }
    } else
        ttab.columns[zero_index] = _new_col(col_size, 0, true);
    return ttab;
}


int _get_col_index_by_number(int col_number, tab table) {
    // Gets the index of a col in the table by its number.
    return table.zero_index+col_number;
}

int _resize_tab(tab *table, int col_index) {
    // Takes the tab
    // Resizes it so that the new column exists:
    //  if new column too far away, extend tab
    //  if new column too low, offset everything by extending, and change zero_index accordingly
    // in all cases, len should be updated
    int target_width = table->alloc_width*2;
    while (col_index > target_width-1) {
         target_width *= 2;
    }
    tab new_tab = _new_tab(target_width, table->zero_index, false, 1);
    for (i=0, i<i)
    
}

int add_cell(int cell, int col_number, tab table) {
    // does everything to add a cell at the correct column.
    int col_index = _get_col_index_by_number(col_number, table);
    if (col_index < 0 || col_index > table.alloc_width-1) {
        _resize_tab(&table, col_index);
    }

    col column = table.columns[col_index];

    _put_cell(table.columns[col_index], cell);
}


bool check_win(col last_column, int color) {
    // TODO
    // check column, and see if 5 are in a row
    // if not, see if some might be aligned (5 before and after)
    // also check if it's in diagonal
}


struct player {int color; char* nickname;};
typedef struct player player;

struct game {int* players; };
typedef struct game game;




