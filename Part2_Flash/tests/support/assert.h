#ifndef ASSERT_H
#define ASSERT_H

#include "cexception_defines.h"
#include "CException.h"

/* This header is used to mock the standard assert function during unit-testing.
 * The goal is to allow ceedling to verify that proper assertion checking has been
 * added to the code under test.
 *
 * If an assertion fails, this macro will print the failure location for informational
 * purposes and throw a CException up to the unit test level for analysis.
 */
#ifdef NDEBUG
#define assert( expr ) ((void)0)
#else

#define assert( expr ) \
    do { \
        if (!(expr)) \
        { \
            printf( "INFO: assertion failed: %s at line %d (expr %s)\r\n", __FILE__, __LINE__, #expr); \
            Throw(CEXCEPTION_ASSERT_FAIL); \
        } \
    } while(0) \

#endif

#endif // ASSERT_H
