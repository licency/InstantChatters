#include "CUnit/CUnit.h"
#include "../header/test.h"
#include "../header/testsuite.h"

 int main()
 {
     CU_pSuite pSuite1 = NULL;
     CU_pSuite pSuite2 = NULL;
    
     /* initialize the CUnit test registry */
     if(CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();
    
    pSuite1 = CU_add_suite("Name valid or invalid", init_suite_func1, clean_suite_func1);
    pSuite2 = CU_add_suite("Password valid or invalid", init_suite_func2, clean_suite_func2);
    
    if (NULL == pSuite1)
    {
        /* CU_cleanup_registry() is used to clean up and release
        memory used by the framework */
        //CU_cleanup_registry();
        return CU_get_error();
    }

    if (NULL == pSuite1)
    {
        /* CU_cleanup_registry() is used to clean up and release
        memory used by the framework */
        //CU_cleanup_registry();
        return CU_get_error();
    }

    /* Adding tests to the suite */
    /* CU_add_test() macro automatically generates a unique test name based
    on the test function name, and adds it to the specified suite.  */
     if ((NULL == CU_add_test(pSuite1,
                             "test of validName() in normal cases", testSunnyCases1)) ||
        (NULL == CU_add_test(pSuite1,
                             "test of invalidName() in error cases", testRainyCases1)))
    {
        //CU_cleanup_registry();
        return CU_get_error();
    }
    
    if ((NULL == CU_add_test(pSuite2,
                             "test of validPass() in normal cases", testSunnyCases2)) ||
        (NULL == CU_add_test(pSuite2,
                             "test of invalidPass() in error cases", testRainyCases2)))
    {
        //CU_cleanup_registry();
        return CU_get_error();
    }

     /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
 }
