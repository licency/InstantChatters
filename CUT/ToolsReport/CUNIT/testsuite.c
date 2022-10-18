#include "CUnit/Basic.h"

#include "../header/test.h" //(the header file containing function)


int init_suite_func1(void)
{
    
    return 0;
}

int init_suite_func2(void)
{
    
    return 0;
}

int clean_suite_func1(void)
{
    return 0;
}

int clean_suite_func2(void)
{
    return 0;
}

void testSunnyCases1(void)
{
    CU_ASSERT_EQUAL(validName("user1"), 1);
    CU_ASSERT_EQUAL(validName("user12"), 1);
}

void testSunnyCases2(void)
{
    CU_ASSERT_EQUAL(validPass("pass1"), 1);
    CU_ASSERT_EQUAL(validPass("Pass123"), 1);
}

void testRainyCases1(void)
{
    CU_ASSERT_EQUAL(validName("u"), 0);
    CU_ASSERT_EQUAL(validName("userrrrrr112254ooo99125nn8899j1"), 0);
}

void testRainyCases2(void)
{
    CU_ASSERT_EQUAL(validPass("p"), 0);
    CU_ASSERT_EQUAL(validPass("pppppaaaaaasssssss112225544kkk1"), 0);
}
