/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   testclass.h
 * Author: ann
 *
 * Created on 02.03.2016, 9:45:31
 */

#ifndef TESTCLASS_H
#define TESTCLASS_H

#include <cppunit/extensions/HelperMacros.h>

class testclass : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(testclass);

    CPPUNIT_TEST(testMult);
    CPPUNIT_TEST(testReadMatrix);
    CPPUNIT_TEST(testWriteMatrix);

    CPPUNIT_TEST_SUITE_END();

public:
    testclass();
    virtual ~testclass();
    void setUp();
    void tearDown();

private:
    void testMult();
    void testReadMatrix();
    void testWriteMatrix();

};

#endif /* TESTCLASS_H */

