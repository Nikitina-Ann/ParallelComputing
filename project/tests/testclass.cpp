/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   testclass.cpp
 * Author: ann
 *
 * Created on 02.03.2016, 9:45:32
 */
#include <iostream>
#include "testclass.h"
#define SIZE 100 
#define NUMBER_TEST 5
CPPUNIT_TEST_SUITE_REGISTRATION(testclass);

testclass::testclass() {
}

testclass::~testclass() {
}

void testclass::setUp() {
}

void testclass::tearDown() {
}

void readMatrix(int a[SIZE][SIZE], int *r, int *c, char* filename);
void testclass::testReadMatrix(){
    const int r=5, c=6;
    int test[r][c] = {{1, 2, 3, 4, 5, 6}, 
                      {3, 2, 1, 9, 8, 7}, 
                      {4, 5, 6, 7, 8, 9},
                      {2, 1, 2, 1, 2, 1}, 
                      {2, 2, 2, 2, 2, 2}};
    int r1, c1;
    int a[SIZE][SIZE];
    readMatrix(a, &r1, &c1,  "files/a.txt");
    if(c!=c1 || r!=r1)
            CPPUNIT_ASSERT(false);
    for(int i=0;i<r;i++)
        for(int j=0;j<c;j++){
            if (test[i][j]!=a[i][j])
                CPPUNIT_ASSERT(false);
        }
    CPPUNIT_ASSERT(true);
}

void writeMatrix(int res[SIZE][SIZE], int r, int c);
void testclass::testWriteMatrix(){
    const int r=5, c=6;
    int test[SIZE][SIZE] = {{1, 2, 3, 4, 5, 6}, 
                            {3, 2, 1, 9, 8, 7}, 
                            {4, 5, 6, 7, 8, 9},
                            {2, 1, 2, 1, 2, 1}, 
                            {2, 2, 2, 2, 2, 2}};
    writeMatrix(test, r, c);
    int r1, c1;
    int a[SIZE][SIZE];
    readMatrix(a, &r1, &c1,  "files/output.txt");
    if(c!=c1 || r!=r1)
            CPPUNIT_ASSERT(false);
    for(int i=0;i<r;i++)
        for(int j=0;j<c;j++){
            if (test[i][j]!=a[i][j])
                CPPUNIT_ASSERT(false);
        }
    CPPUNIT_ASSERT(true);
    
}

void mult(int a[SIZE][SIZE], int b[SIZE][SIZE], int res[SIZE][SIZE], int r1, int c1, int c2);
void testclass::testMult() {
    int r1, c1, r2, c2, r, c;
    int a[SIZE][SIZE], b[SIZE][SIZE], out[SIZE][SIZE], res[SIZE][SIZE];
    char filename_a[SIZE], filename_b[SIZE], filename_res[SIZE];
    for (int num =1;num<NUMBER_TEST+1;num++){
        sprintf(filename_a, "files/%d/a.txt", num);
        sprintf(filename_b, "files/%d/b.txt", num);
        sprintf(filename_res, "files/%d/res.txt", num);
        readMatrix(a, &r1, &c1, filename_a);
        readMatrix(b, &r2, &c2, filename_b);
        if(c1!=r2)
            CPPUNIT_ASSERT(false);
        mult(a, b, out, r1, c1, c2);
        readMatrix(res, &r, &c, filename_res);
        if(c!=c2 || r!=r1)
            CPPUNIT_ASSERT(false);
        for(int i=0;i<r1;i++)
        for(int j=0;j<c2;j++){
            if (out[i][j]!=res[i][j])
                CPPUNIT_ASSERT(false);
        }
    }
    CPPUNIT_ASSERT(true);
}
