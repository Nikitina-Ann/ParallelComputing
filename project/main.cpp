#include <iostream>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>
#include <cstdlib>
#include <cmath>
using namespace std;
#define SIZE 1000 //максимальный размер матриц
#define THR_NUM  2 //число потоков
#define TEST_NUM  50 //количество тестов
struct timeval tv1,tv2,dtv;

struct matrix_args{
    int** a;
    int** b;
    int** res;
    int c1;
    int c2;
    int start;
    int end;
} ARG[THR_NUM];

//Получение времени выполнения
long int dtime(){
  dtv.tv_sec= tv2.tv_sec -tv1.tv_sec;
  dtv.tv_usec=tv2.tv_usec-tv1.tv_usec;
  if(dtv.tv_usec<0) { dtv.tv_sec--; dtv.tv_usec+=1000000; }
    return dtv.tv_sec+dtv.tv_usec*1e-6;
}
//Чтение матрицы из файла
void readMatrix(int** matrix, int r, int c, char* filename) {
    FILE *in=fopen(filename, "rt");//файл чтения
    fscanf(in,"%d %d", &r, &c); //Считали размерности
    for(int i=0;i<r;i++)
    {
     for(int j=0;j<c;j++)
       fscanf(in,"%d",&matrix[i][j]);
    }
    fclose(in);
}
//Запись матрицы в файл
void writeMatrix(int** matrix, int r, int c, char* filename){
    FILE *out=fopen(filename, "wt");//файл записи
    fprintf(out,"%d %d\n", r, c);
    for(int i=0; i<r; ++i)
        for(int j=0; j<c; ++j)
        {
            fprintf(out,"%d ",matrix[i][j]);
            if(j==c-1)
                fprintf(out, "\n") ;
        }
    fclose(out);
}
/*Умножение матриц
 * Флаг openMp == false - распараллеливание с помощью OpenMP не используется
 * Флаг openMp == true - OpenMP используется
 */
bool mult(int** a, int** b, int** res, int r1, int c1, int r2, int c2, bool openMP, int numThread){
    if(c1 != r2)
        return false;
    #pragma omp parallel for num_threads(numThread) if(openMP)
        for(int i=0; i<r1; i++)
            for(int j=0; j<c2; j++)
                for(int k=0; k<c1; k++)
                    res[i][j]+=a[i][k]*b[k][j];  
    return true;
}
//Умножение матриц PTHREAD
void *mult_pthread(void *pargs){
    struct matrix_args *args = (struct matrix_args *) pargs;
    int** a = args->a;
    int** b = args->b;
    int** res = args->res;
    int c1 = args->c1;
    int c2 = args->c2;
    int start = args->start;
    int end = args->end;
    for(int i = start; i < end; i++)
        for(int j = 0; j < c2; j++)
            for(int k = 0; k < c1; k++)
                res[i][j]+= a[i][k] * b[k][j];
    pthread_exit(NULL);
}
//Генерация матрицы с рандомными значениями от 0 до 100
void generateMatrix(int** matrix, int r, int c){
    for(int i=0; i<r; i++)
        for(int j=0; j<c; j++){
            matrix[i][j] = rand()% 100;
        }
}
//Сравнение матриц
bool compareMatrix(int** a, int** b, int r1, int c1, int r2, int c2){
    if(c1!=c2 || r1!=r2)
        return false;
    for(int i=0;i<r1;i++)
        for(int j=0;j<c1;j++){
            if (b[i][j]!=a[i][j])
                return false;
        }
    return true;
}
//Создание матрицы и заполнение ее нулями
int** new_matrix(int r, int c){
    int **matrix = new int* [r]; 
    for (int i = 0; i < r; i++)
        matrix[i] = new int [c]; 
    for(int i=0; i<r; ++i)
        for(int j=0; j<c; ++j)
            matrix[i][j]=0;
    return matrix;
}
//Удаление матрицы
void delete_matrix(int** matrix, int r, int c){
for (int i = 0; i < c; i++)
        delete [] matrix[r];
}
//Вычисление математического ожидания, дисперсии, доверительного интервала
float matStatistic(float* timeMatr, int size){
    float sum=0;
    float aver, disp, min, max;
    for (int i=0; i< size; i++){
        sum=sum+timeMatr[i];
    }
    aver= (float)sum/size;
    sum=0;
    for (int i=0; i< size; i++){
       sum=sum+pow(timeMatr[i]-aver, 2);
    }
    disp = sqrt(sum/(size-1));
    min=aver-2.0086*disp/sqrt(TEST_NUM);
    max=aver+2.0086*disp/sqrt(TEST_NUM);
    printf("среднее= %f дисперсия=%f. %f < x < %f\n\n", aver, disp, min, max);
}
int main()
{
    float timeMatr[TEST_NUM];float timeMatr1[TEST_NUM];float timeMatr2[TEST_NUM];
    int r1, c1, r2, c2, r, c; //размерности матриц
    r1 = c1 =  r2 =  c2 = r = c = SIZE;
    
    for (int i=0; i<TEST_NUM; i++){
    //int i=1;
    int** a=new_matrix(r1, c1);
    int** b=new_matrix(r2, c2);
    int** res=new_matrix(r, c);
    int** res1=new_matrix(r, c);
    int** res2=new_matrix(r, c);
    //генерация входных матриц
    generateMatrix(a, r1, c1);
    generateMatrix(b, r2, c2);
    struct timezone tz;
    gettimeofday(&tv1, &tz); 
    //Умножение матриц
    if(!mult(a, b, res, r1, c1, r2, c2, false, THR_NUM)){
        printf("Ошибка!!! Количество строк первой матрицы должно быть равно количеству столбцов второй матрицы!");
        exit(1);
    }
    gettimeofday(&tv2, &tz);
    timeMatr[i]=dtime();
    
    //Распараллеленный алгоритм умножения
    pthread_t threads[THR_NUM];
    gettimeofday(&tv1, &tz); 
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    int step = (int)((double)SIZE/(double)THR_NUM);
    int pos = 0;
    for(int k = 0; k < THR_NUM; k++){
        ARG[k].a = a;
        ARG[k].b = b;
        ARG[k].res = res1;
        ARG[k].c1 = c1;
        ARG[k].c2 = c2;
        ARG[k].start = pos;
        pos += step;
        ARG[k].end = (k == THR_NUM - 1) ? SIZE : pos;
        int q=pthread_create(&threads[k], &attr, mult_pthread, (void *)&ARG[k]);
        if(q){
            printf("Ошибка при создании потоков\n");
            exit(1);
        }
    }
    pthread_attr_destroy(&attr);
    for(int k = 0; k < THR_NUM; k++)
        pthread_join(threads[k], NULL);
    gettimeofday(&tv2, &tz); 
    timeMatr1[i]=dtime();
    
    //OpenMP
    gettimeofday(&tv1, &tz); 
    mult(a, b, res2, r1, c1, r2, c2, true, THR_NUM);
    gettimeofday(&tv2, &tz); 
    timeMatr2[i]=dtime();

    if(!compareMatrix (res, res1, r1, c1, r2, c2))
        return -1;
    if(!compareMatrix (res, res2, r1, c1, r2, c2))
        return -2;
    delete_matrix(a, r1, c1);
    delete_matrix(b, r2, c2);
    delete_matrix(res, r, c);
    delete_matrix(res1, r, c);
    delete_matrix(res2, r, c);
    }
    //printf("%f    %f   %f \n", timeMatr[i], timeMatr1[i], timeMatr2[i]);
    printf("Последовательное умножение\n");
    matStatistic(timeMatr, TEST_NUM);  
    printf("Умножение PThread\n");
    matStatistic(timeMatr1, TEST_NUM);  
    printf("Умножение OpenMPI\n");
    matStatistic(timeMatr2, TEST_NUM);  
    return 0;
}