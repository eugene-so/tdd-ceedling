/*******************************************************************************
 *    INCLUDED FILES
 ******************************************************************************/
#include "CException.h"
#include "unity.h"

#include <stdlib.h>
#include <string.h>

#include "cexception_defines.h"

#include "RandomMinute.h"

/*******************************************************************************
 *    DEFINITIONS
 ******************************************************************************/

/*******************************************************************************
 *    PRIVATE TYPES
 ******************************************************************************/
enum { BOUND=30 };

/*******************************************************************************
 *    PRIVATE DATA
 ******************************************************************************/
static int minute;

/*******************************************************************************
 *    PRIVATE FUNCTIONS
 ******************************************************************************/
static void AssertMinuteIsInRange()
{
    if (minute < -BOUND || minute > BOUND)
    {
        printf("bad minute value: %d\n", minute);
        TEST_FAIL();
    }
}


/*******************************************************************************
 *    SETUP, TEARDOWN
 ******************************************************************************/

void setUp(void)
{
    /* This runs before every test function on this file */
    RandomMinute_Create(BOUND);
    srand(1);
}

void tearDown(void)
{
    /* This runs after every test function on this file */
}

/*******************************************************************************
 *    TESTS
 ******************************************************************************/
void test_RandomMinute_GetIsInRange(void)
{
    for (uint8_t i = 0; i < 100; ++i)
    {
        minute = RandomMinute_Get();
        AssertMinuteIsInRange();
    }
}

void test_RandomMinute_AllValuesPossible(void)
{
    int hit[2*BOUND + 1];
    memset(hit, 0, sizeof(hit));
    int i;
    for (i = 0; i < 400; i++)
    {
        minute = RandomMinute_Get();
        AssertMinuteIsInRange();
        hit[minute + BOUND]++;
    }
    for (i = 0; i < 2* BOUND + 1; i++)
    {
        TEST_ASSERT_TRUE(hit[i] > 0);
    }
}


