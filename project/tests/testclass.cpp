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


//int r1, c1, r2, c2;

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

void testclass::testReadMatrix() {
    int** a;
    int** b;
    //readMatrix(a, b);
    /*if (true ) {
        CPPUNIT_ASSERT(false);
    }*/
}

void writeMatrix(int res[SIZE][SIZE], int r, int c);

void testclass::testWriteMatrix() {
    int** res;
    //writeMatrix(res);
    /*if (true ) {
        CPPUNIT_ASSERT(false);
    }*/
}

void mult(int a[SIZE][SIZE], int b[SIZE][SIZE], int res[SIZE][SIZE], int r1, int c1, int c2);

void testclass::testMult() {
    int r1, c1, r2, c2;
    int a[SIZE][SIZE], b[SIZE][SIZE], out[SIZE][SIZE], res[SIZE][SIZE];
    readMatrix(a, &r1, &c1, "files/a.txt");
    readMatrix(b, &r2, &c2, "files/b.txt");
    /*if(c1!=r2)
        CPPUNIT_ASSERT(false);*/
    mult(a, b, out, r1, c1, c2);
    int c,r;
    readMatrix(res, &r, &c, "files/res.txt");
    writeMatrix(out, r1, c2);
    if(c!=c2 || r!=r1)
        CPPUNIT_ASSERT(false);
    for(int i=0;i<r1;i++)
    for(int j=0;j<c2;j++){
        if (out[i][j]!=res[i][j])
          CPPUNIT_ASSERT(false);
    }
    CPPUNIT_ASSERT(true);
}
