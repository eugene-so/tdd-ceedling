/*******************************************************************************
 *    INCLUDED FILES
 ******************************************************************************/
#include "CException.h"
#include "unity.h"

#include <string.h>

#include "cexception_defines.h"

#include "LightControllerSpy.h"

/*******************************************************************************
 *    DEFINITIONS
 ******************************************************************************/

/*******************************************************************************
 *    PRIVATE TYPES
 ******************************************************************************/

/*******************************************************************************
 *    PRIVATE DATA
 ******************************************************************************/

/*******************************************************************************
 *    PRIVATE FUNCTIONS
 ******************************************************************************/

/*******************************************************************************
 *    SETUP, TEARDOWN
 ******************************************************************************/

void setUp(void)
{
    /* This runs before every test function on this file */
    LightController_Create();
}

void tearDown(void)
{
    /* This runs after every test function on this file */
    LightController_Destroy();
}

/*******************************************************************************
 *    TESTS
 ******************************************************************************/
void test_lightControllerSpy_Create(void)
{
    TEST_ASSERT_EQUAL_INT32(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    TEST_ASSERT_EQUAL_INT32(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}

void test_lightControllerSpy_RememberLastLightIdControlled(void)
{
    LightController_On(10);
    TEST_ASSERT_EQUAL_INT32(10, LightControllerSpy_GetLastId());
    TEST_ASSERT_EQUAL_INT32(LIGHT_ON, LightControllerSpy_GetLastState());

}
