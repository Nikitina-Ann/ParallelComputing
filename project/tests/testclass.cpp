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
#define SIZE 1000 
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
int** new_matrix(int r, int c);

void readMatrix(int** matrix, int r, int c, char* filename);
void writeMatrix(int** matrix, int r, int c);

void mult(int** a, int** b, int** res, int r1, int c1, int r2, int c2);
void testclass::testMult() {
    int** a=new_matrix(SIZE, SIZE);
    int** b=new_matrix(SIZE, SIZE);
    int** multMatrix=new_matrix(SIZE, SIZE);
    int** res=new_matrix(SIZE, SIZE);
    int r1, c1, r2, c2, r, c;
    char filename_a[SIZE], filename_b[SIZE], filename_res[SIZE];
    for (int num =1;num<NUMBER_TEST+1;num++){
        sprintf(filename_a, "files/%d/a.txt", num);
        sprintf(filename_b, "files/%d/b.txt", num);
        sprintf(filename_res, "files/%d/res.txt", num);
        readMatrix(a, r1, c1, filename_a);
        readMatrix(b, r2, c2, filename_b);
        if(c1!=r2)
            CPPUNIT_ASSERT(false);
        mult(a, b, multMatrix, r1, c1, r2, c2);
        readMatrix(res, r, c, filename_res);
        if(c!=c2 || r!=r1)
            CPPUNIT_ASSERT(false);
        for(int i=0;i<r1;i++)
        for(int j=0;j<c2;j++){
            if (multMatrix[i][j]!=res[i][j])
                CPPUNIT_ASSERT(false);
        }
    }
    CPPUNIT_ASSERT(true);
}
