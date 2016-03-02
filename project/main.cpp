#include <iostream>
#include <stdio.h>
using namespace std;
#define SIZE 100 //максимальный размер матриц
//int r1, c1, r2, c2; //размерности матриц a, b
//Умножение матриц
void mult(int a[SIZE][SIZE], int b[SIZE][SIZE], int res[SIZE][SIZE], int r1, int c1, int c2) {
    for(int i=0; i<r1; ++i)
    for(int j=0; j<c2; ++j)
    for(int k=0; k<c1; ++k)
    {
        res[i][j]+=a[i][k]*b[k][j];
    }
}
//Чтение элементов матрицы
void readMatrix(int a[SIZE][SIZE], int *r, int *c, char* filename) {
    FILE *in=fopen(filename, "rt");//файл чтения
    fscanf(in,"%d %d", r, c); //Считали размерности
    for(int i=0;i<*c;i++)
    {
     for(int j=0;j<*r;j++)
       fscanf(in,"%d",&a[i][j]);
    }
    fclose(in);
}
void writeMatrix(int res[SIZE][SIZE], int r, int c){
    FILE *out=fopen("files/output.txt", "wt");//файл записи
    for(int i=0; i<r; ++i)
        for(int j=0; j<c; ++j)
        {
            fprintf(out,"%d ",res[i][j]);
            if(j==c-1)
                fprintf(out, "\n") ;
        }
    fclose(out);
}
int main()
{
    int r1, c1, r2, c2; //размерности матриц a, b
    int a[SIZE][SIZE], b[SIZE][SIZE], res[SIZE][SIZE];
    //Чтение элементов матрицы
    readMatrix(a, &r1, &c1, "files/a.txt");
    readMatrix(b, &r2, &c2, "files/b.txt");
    if(c1!=r2){
        cout << endl << "Количество столбцов первой матрицы не равно количеству строк второй матрицы" << endl;
        return -1;
    }
    //Умножение матриц
    mult(a, b, res, r1, c1, c2);
    writeMatrix(res, r1, c2);
    cout << endl << "Результат:" << endl;
    for(int i=0; i<r1; ++i){
        for(int j=0; j<c2; ++j)
        {
            cout << " " << res[i][j];
            if(j==c2-1)
                cout << endl;
        }
    }
    return 0;
}
