#pragma once
#include <cstdlib>
#include <ctime>
#include <utility>
#include "list.h"

class sudokuF {
    int size;
    int** sudoku;

    // Транспонирование всей таблицы — столбцы становятся строками и наоборот(transposing)
    void transposition() {
        int tmp;
        for (int i = 0; i < size; i++)
            for (int j = i; j < size; j++) {
                swap(sudoku[i][j], sudoku[j][i]);
            }
    }

    // Обмен двух строк в пределах одного района(swap_rows)
    void swap_rows() {
        srand(time(0));
        int x = rand() % 9 / 3;
        x *= 3;
        int i1 = rand() % ((x + 3) - x) + x;
        int i2 = rand() % ((x + 3) - x) + x;
        swap(sudoku[i1], sudoku[i2]);
    }

    // Обмен двух столбцов в пределах одного района(swap_colums)
    void swap_colums() {
        srand(time(0));
        int y = rand() % 9 / 3;
        y *= 3;
        int j1 = rand() % ((y + 3) - y) + y;
        int j2 = rand() % ((y + 3) - y) + y;
        for (int i = 0; i < size; i++)
        {
            int tmp = sudoku[i][j1];
            sudoku[i][j1] = sudoku[i][j2];
            sudoku[i][j2] = tmp;
        }
    }

    // Обмен двух районов по горизонтали(swap_rows_area)
    void swap_rows_area() {
        srand(time(0));
        int x1 = rand() % 9 / 3;
        x1 *= 3;
        int x2 = rand() % 9 / 3;
        x2 *= 3;
        for (int i = 0; i < 3; i++)
            swap(sudoku[x1 + i], sudoku[x2 + i]);
    }

    // Обмен двух районов по вертикали(swap_colums_area)
    void swap_colums_area() {
        srand(time(0));
        int y1 = rand() % 9 / 3;
        y1 *= 3;
        int y2 = rand() % 9 / 3;
        y2 *= 3;
        for (int j = 0; j < 3; j++)
        {
            for (int i = 0; i < size; i++)
            {
                int tmp = sudoku[i][y1 + j];
                sudoku[i][y1 + j] = sudoku[i][y2 + j];
                sudoku[i][y2 + j] = tmp;
            }
        }
    }

public:
    sudokuF() {
        size = 9;
        sudoku = new int* [size];
        for (int i = 0; i < size; i++)
            sudoku[i] = new int[size];
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                sudoku[i][j] = 0;
            }
        }
    }

    sudokuF(const sudokuF& s) {
        size = s.size;
        sudoku = new int* [size];
        for (int i = 0; i < size; i++)
            sudoku[i] = new int[size];
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                sudoku[i][j] = s.sudoku[i][j];
    }

    ~sudokuF() {
        for (int i = 0; i < size; i++)
            delete[] sudoku[i];
        delete[] sudoku;
    }

    int getSize() { return size; }
    int** getField() { return sudoku; }
    int getCell(int i, int j) { return sudoku[i][j]; }
    void setCell(int i, int j, int k) { sudoku[i][j] = k; }

    sudokuF& operator=(const sudokuF& s) {
        if (&s == this) return *this;
        for (int i = 0; i < size; i++)
            delete[] sudoku[i];
        delete[] sudoku;
        size = s.size;
        sudoku = new int* [size];
        for (int i = 0; i < size; i++)
            sudoku[i] = new int[size];
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                sudoku[i][j] = s.sudoku[i][j];
        return *this;
    }

    void fill() {
        int n = 3;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                sudoku[i][j] = ((i * n + i / n + j) % (n * n) + 1);
            }
        }
    }

    bool checkRow(int i, int value)
    {
        for (int j = 0; j < size; j++)
        {
            if (sudoku[i][j] == value)
            {
                return true;
            }
        }
        return false;
    }

    bool checkColumn(int j, int value)
    {
        for (int i = 0; i < size; i++)
        {
            if (sudoku[i][j] == value)
            {
                return true;
            }
        }
        return false;
    }

    bool checkSquare(int i, int j, int value)
    {
        int quad = 3;

        int sizey = i / quad;
        int sizex = j / quad;


        sizey = (sizey * quad);
        sizex = (sizex * quad);

        for (int i = sizey; i < sizey + quad; i++)
        {
            for (int j = sizex; j < sizex + quad; j++)
            {
                if (sudoku[i][j] == value)
                {
                    return true;
                }
            }
        }
        return false;

    }

    bool checkWin() {
        for (int i = 0; i<size; i++)
            for (int j = 0; j < size; j++) {
                if (sudoku[i][j] == 0)
                    return false;
            }
        return true;
    }

    bool checkValue(int i, int j, int value) {
        if (sudoku[i][j] != value)
            return true;
        else return false;
    }

    void openCell(const sudokuF& s) {
        int i, j;
        bool chosen = false;
        srand(time(0));
        while (!chosen) {
            i = rand() % size;
            j = rand() % size;
            if (sudoku[i][j] == 0) {
                sudoku[i][j] = s.sudoku[i][j];
                chosen = true;
            }
        }
    }

    void createSudoku(string level) {
        List l;
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                l.addLast(pair<int, int>(make_pair(i, j)));
        srand(time(0));
        int lev;
        if (level == "Easy")
            lev = 40;
        if (level == "Medium")
            lev = 50;
        if (level == "Hard")
            lev = 60;
        /* int check[9][9];
         for (int i = 0; i < size; i++)
             for (int j = 0; j < size; j++)
                 check[i][j] = 0;*/
        /*bool flag;
        for (int k = 0; k < 50; k++) {
            flag = true;
            while (flag) {

                int i = rand() % size;
                int j = rand() % size;
                if (!check[i][j]) {
                    sudoku[i][j] = 0;
                    check[i][j] = 1;
                    flag = false;
                }
            }
        }*/
        for (int k = 0; k < lev; k++) {
            int i = rand() % l.getN() + 1;
            sudoku[l.getPair(i).first][l.getPair(i).second] = 0;
            l.del(i);
        }
    }

    void (sudokuF::* funcs[5])() = { &sudokuF::transposition, &sudokuF::swap_rows, &sudokuF::swap_colums,
            &sudokuF::swap_rows_area, &sudokuF::swap_colums_area };
};

// Создание поля судоку
sudokuF createFull() {
    sudokuF sf;
    sf.fill();
    srand(time(0));
    for (int i = 0; i < 5; ++i) {
        // вызываем рандомную функцию из массива
        (sf.*sf.funcs[rand() % 5])();
    }
    return sf;
}