#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Sudoku.h"

Sudoku::Sudoku(){
    int i, j = 0;
    for(i=0;i<sudokusize;i++){
        map[i] = 0;
        ans[i] = 0;
        filled[i] = 0;
    }
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            arr[i][j] = 0;
        }
    }
    fill = 0;
}

void Sudoku::giveQuestion(){
    int i = 0;
    int Q[sudokusize] = {
        0, 4, 0, 2, 1, 0, 0, 0, 0,
        8, 0, 7, 0, 0, 0, 0, 9, 0,
        2, 0, 0, 8, 0, 0, 4, 0, 1,
        3, 0, 0, 0, 0, 2, 9, 0, 5,
        0, 0, 5, 7, 0, 8, 6, 0, 0,
        7, 0, 6, 5, 0, 0, 0, 0, 4,
        5, 0, 1, 0, 0, 4, 0, 0, 9,
        0, 6, 0, 0, 0, 0, 7, 0, 8,
        0, 0, 0, 0, 2, 7, 0, 5, 0
    };
    for(i=0;i<sudokusize;i++){
        map[i] = Q[i];
    }
    transform();
}

void Sudoku::readIn(){
    int i = 0;
    for(i=0;i<sudokusize;i++){
        cin>>map[i];
    }
}

void Sudoku::solve(){
    int i, result = 0;
    int blank = nextblank(-1);

    if(ini_check() == false){
        blank = sudokusize;
    }
    else{
        if(blank == sudokusize){
            result = 1;
            for(i=0;i<sudokusize;i++){
                ans[i] = map[i];
            }
        }
    }

    while(blank>=0 && blank<sudokusize && result<2){
        map[blank]++;
        if(map[blank] > 9){
            map[blank] = 0;
            arr[blank/9][blank%9] = 0;
            blank = pre();
        }
        else{
            if(check(blank) == true){
                filled[fill++] = blank;
                blank = nextblank(blank);
                if(blank == sudokusize){
                    result++;
                    for(i=0;i<sudokusize;i++){
                        ans[i] = map[i];
                    }
                    blank = pre();
                }
            }
        }
    }

    if(result==1){
        cout << "1" << "\n";
        output(true);
    }
    else if(result>1){
        cout << "2";
    }
    else{
        cout << "0";
    }
}

int Sudoku::nextblank(int blank){
    do{
        blank++;
    }
    while(blank<sudokusize && map[blank]>0);
    return blank;
}

bool Sudoku::ini_check(){
    int i, j, m, n= 0;
    for(i=0;i<sudokusize;i++){
        arr[i/9][i%9] = map[i];
    }
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            if(arr[i][j] != 0){
                for(m=j+1;m<9;m++){
                    if(arr[i][m] != 0){
                        if(arr[i][j] == arr[i][m]){
                            return false;
                        }
                    }
                }
            }
        }
    }
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            if(arr[j][i] != 0){
                for(m=j+1;m<9;m++){
                    if(arr[m][i] != 0){
                        if(arr[j][i] == arr[m][i]){
                            return false;
                        }
                    }
                }
            }
        }
    }
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            if(arr[i][j] != 0){
                for(m=3*(i/3);m<(3*(i/3)+3);m++){
                    for(n=3*(j/3);n<(3*(j/3)+3);n++){
                        if(i!=m && j!=n){
                            if(arr[m][n] != 0){
                                if(arr[i][j] == arr[m][n]){
                                    return false;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return true;
}

int Sudoku::pre(){
    if(fill <= 0){
        return -1;
    }
    else{
        return filled[--fill];
    }
}

bool Sudoku::check(int blank){
    int x, y, i, j = 0;
    x = blank/9;
    y = blank%9;
    arr[x][y] = map[blank];
    for(i=0;i<9;i++){
        if(i==y){
            continue;
        }
        if(arr[x][y] == arr[x][i]){
            return false;
        }
    }
    for(i=0;i<9;i++){
        if(i==x){
            continue;
        }
        if(arr[x][y] == arr[i][y]){
            return false;
        }
    }
    for(i=3*(x/3);i<(3*(x/3)+3);i++){
        for(j=3*(y/3);j<(3*(y/3)+3);j++){
            if(i==x && j==y){
                continue;
            }
            if(arr[x][y] == arr[i][j]){
                return false;
            }
        }
    }
    return true;
}

 void Sudoku::transform(){
    change();
    output(false);
}

void Sudoku::change(){
    srand(time(0));
    changeNum(rand()%9+1, rand()%9+1);
    changeRow(rand()%3, rand()%3);
    changeCol(rand()%3, rand()%3);
    rotate(rand()%101);
    flip(rand()%2);
}

void Sudoku::changeNum(int a, int b){
    int i, j = 0;
     for(i=0;i<sudokusize;i++){
        arr[i/9][i%9] = map[i];
    }
    if(a != b){
        for(i=0; i<9; ++i){
            for(j=0;j<9;j++){
                if(arr[i][j] == a){
                    arr[i][j] = b;
                }
                else if(arr[i][j] == b){
                    arr[i][j] = a;
                }
            }
        }
    }
    for(i=0;i<sudokusize;i++){
        map[i] = arr[i/9][i%9];
    }
}

 void Sudoku::changeRow(int a, int b){
    int i, j = 0;
    int store = 0;
    for(i=0;i<sudokusize;i++){
        arr[i/9][i%9] = map[i];
    }
    if(a != b)
        for(i=0; i<3; ++i){
            for(j=0;j<9;j++){
                store = arr[i+3*a][j];
                arr[i+3*a][j] = arr[i+3*b][j];
                arr[i+3*b][j] = store;
            }
        }
    for(i=0;i<sudokusize;i++){
        map[i] = arr[i/9][i%9];
    }
}

void Sudoku::changeCol(int a, int b){
    int i, j, store = 0;
    for(i=0;i<sudokusize;i++){
        arr[i/9][i%9] = map[i];
    }
    if(a != b)
        for(i=0; i<9; ++i){
            for(j=0;j<3;j++){
                store = arr[i][j+3*a];
                arr[i][j+3*a] = arr[i][j+3*b];
                arr[i][j+3*b] = store;
            }
        }
    for(i=0;i<sudokusize;i++){
        map[i] = arr[i/9][i%9];
    }
}

void Sudoku::rotate(int n){
    int newrotate[9][9] = {0};
    int i, j = 0;
    for(i=0;i<sudokusize;i++){
        arr[i/9][i%9] = map[i];
    }
    if(n%4==0){
        for(i=0;i<9;i++){
            for(j=0;j<9;j++){
            arr[i][j] = arr[i][j];
            }
        }
    }
    else if(n%4==1){
        for(i=0;i<9;i++){
            for(j=0;j<9;j++){
                newrotate[i][j] = arr[8-j][i];
            }
        }
        for(i=0;i<9;i++){
            for(j=0;j<9;j++){
                arr[i][j] = newrotate[i][j];
            }
        }
    }
    else if(n%4==2){
        for(i=0;i<9;i++){
            for(j=0;j<9;j++){
                newrotate[i][j] = arr[8-i][8-j];
            }
        }
        for(i=0;i<9;i++){
            for(j=0;j<9;j++){
                arr[i][j] = newrotate[i][j];
            }
        }
    }
    else if(n%4==3){
        for(i=0;i<9;i++){
            for(j=0;j<9;j++){
                newrotate[i][j] = arr[j][8-i];
            }
        }
        for(i=0;i<9;i++){
            for(j=0;j<9;j++){
                arr[i][j] = newrotate[i][j];
            }
        }
    }
    for(i=0;i<sudokusize;i++){
        map[i] = arr[i/9][i%9];
    }
}

void Sudoku::flip(int n){
    int newflip[9][9] = {0};
    int i, j = 0;
    for(i=0;i<sudokusize;i++){
        arr[i/9][i%9] = map[i];
    }
    if(n==0){
        for(i=0;i<9;i++){
            for(j=0;j<9;j++){
                newflip[i][j] = arr[8-i][j];
        }
    }
}
    else if(n==1){
        for(i=0;i<9;i++){
            for(j=0;j<9;j++){
               newflip[i][j] = arr[i][8-j];
            }
        }
    }
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            arr[i][j] = newflip[i][j];
        }
    }
    for(i=0;i<sudokusize;i++){
        map[i] = arr[i/9][i%9];
    }
}

void Sudoku::output(bool trueans){
    int i = 0;
    if(!trueans){
        for(i=0;i<sudokusize;i++){
            cout<<map[i]<<((i+1)%9==0?'\n':' ');
        }
    }
    else{
        for(i=0;i<sudokusize;i++){
            cout<<ans[i]<<((i+1)%9==0?'\n':' ');
        }
    }
}

