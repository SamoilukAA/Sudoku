#pragma once
#include <cstdlib>
#include <ctime>
#include <utility>
#include "list.h"

class sudokuF {
    int size;
    int** sudoku;

    void transposition(); // Транспонирование всей таблицы — столбцы становятся строками и наоборот
    void swap_rows(); // Обмен двух строк в пределах одного района
    void swap_colums(); // Обмен двух столбцов в пределах одного района
    void swap_rows_area(); // Обмен двух районов по горизонтали
    void swap_colums_area(); // Обмен двух районов по вертикали

public:
    sudokuF();
    sudokuF(const sudokuF& s);
    ~sudokuF();
    int getSize();
    int** getField();
    int getCell(int i, int j);
    void setCell(int i, int j, int k);
    sudokuF& operator=(const sudokuF& s);
    void fill();
    bool checkRow(int i, int value);
    bool checkColumn(int j, int value);
    bool checkSquare(int i, int j, int value);
    bool checkWin();
    bool checkValue(int i, int j, int value);
    void openCell(const sudokuF& s);
    void createSudoku(string level);

    void (sudokuF::* funcs[5])() = { &sudokuF::transposition, &sudokuF::swap_rows, &sudokuF::swap_colums,
            &sudokuF::swap_rows_area, &sudokuF::swap_colums_area };

};

// Создание поля судоку
sudokuF createFull();