/*******************************************************************************
 *    INCLUDED FILES
 ******************************************************************************/
#include "CException.h"
#include "unity.h"

#include <stdlib.h>
#include <string.h>

#include "cexception_defines.h"

#include "flash.h"
#include "m28w160ect.h"
#include "mock_io.h"
#include "mock_MicroTime.h"

/*******************************************************************************
 *    DEFINITIONS
 ******************************************************************************/

/*******************************************************************************
 *    PRIVATE TYPES
 ******************************************************************************/

/*******************************************************************************
 *    PRIVATE DATA
 ******************************************************************************/
static ioAddress m_address;
static ioData m_data;
static int m_result;

/*******************************************************************************
 *    PRIVATE FUNCTIONS
 ******************************************************************************/

/*******************************************************************************
 *    SETUP, TEARDOWN
 ******************************************************************************/

void setUp(void)
{
    /* This runs before every test function on this file */
    m_address = 0x1000;
    m_data = 0xBEEF;
    m_result = -1;

    Flash_Create();
    MicroTime_Get_ExpectAndReturn(0);
}

void tearDown(void)
{
    /* This runs after every test function on this file */
    Flash_Destroy();
}

/*******************************************************************************
 *    TESTS
 ******************************************************************************/
void test_Flash_WriteSucceeds_Immediately(void)
{
    IO_Write_Expect(CommandRegister, ProgramCommand);
    IO_Write_Expect(m_address, m_data);
    IO_Read_ExpectAndReturn(StatusRegister, ReadyBit);
    IO_Read_ExpectAndReturn(m_address, m_data);
    m_result = Flash_Write(m_address, m_data);
    TEST_ASSERT_EQUAL_INT32(0, m_result);
}

void test_Flash_WriteSucceeds_NotImmediately(void)
{
    IO_Write_Expect(CommandRegister, ProgramCommand);
    IO_Write_Expect(m_address, m_data);
    IO_Read_ExpectAndReturn(StatusRegister, 0);
    MicroTime_Get_ExpectAndReturn(0);
    IO_Read_ExpectAndReturn(StatusRegister, 0);
    MicroTime_Get_ExpectAndReturn(0);
    IO_Read_ExpectAndReturn(StatusRegister, 0);
    MicroTime_Get_ExpectAndReturn(0);
    IO_Read_ExpectAndReturn(StatusRegister, ReadyBit);
    IO_Read_ExpectAndReturn(m_address, m_data);

    m_result = Flash_Write(m_address, m_data);
    TEST_ASSERT_EQUAL_INT32(0, m_result);
}

void test_Flash_WriteFails_VppError(void)
{
    IO_Write_Expect(CommandRegister, ProgramCommand);
    IO_Write_Expect(m_address, m_data);
    IO_Read_ExpectAndReturn(StatusRegister, ReadyBit | VppErrorBit);
    IO_Write_Expect(CommandRegister, Reset);

    m_result = Flash_Write(m_address, m_data);
    TEST_ASSERT_EQUAL_INT32(FLASH_VPP_ERROR, m_result);
}

void test_Flash_WriteFails_FlashReadBackError(void)
{
    IO_Write_Expect(CommandRegister, ProgramCommand);
    IO_Write_Expect(m_address, m_data);
    IO_Read_ExpectAndReturn(StatusRegister, ReadyBit);
    IO_Read_ExpectAndReturn(m_address, m_data-1);

    m_result = Flash_Write(m_address, m_data);
    TEST_ASSERT_EQUAL_INT32(FLASH_READ_BACK_ERROR, m_result);
}

void test_Flash_WriteFails_Timeout(void)
{
    IO_Write_Expect(CommandRegister, ProgramCommand);
    IO_Write_Expect(m_address, m_data);
    for (int i = 0; i < 10; ++i)
    {
        IO_Read_ExpectAndReturn(StatusRegister, ~ReadyBit);
        MicroTime_Get_ExpectAndReturn(500+i*500);
    }

    m_result = Flash_Write(m_address, m_data);
    TEST_ASSERT_EQUAL_INT32(FLASH_TIMEOUT_ERROR, m_result);
}
