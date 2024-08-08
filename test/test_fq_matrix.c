/**
This file contains basic test cases for the functions in fq_matrix.c.
For details on how to execute/add test cases, please refer to the README.md
And test functions are named in the format of test_XXX_base or test_XXX_edge.
For example, test_mat_create_base is a test case for the function mat_create.

If you find a new test case, you need to create a new function in the form of
test_XXX_YYY. For example, test_mat_create_withzero is a test case for the
function mat_create in fq_matrix.c with fill = 0.0.

Finally, you need to add new test cases to the suite.
For example, you need to add the following code to the FqMatrixGetSuite
function:
        SUITE_ADD_TEST(suite, test_mat_create_withzero);

You can refer to the test cases in test/test_fq_matrix.c for details.
**/

#include "../include/fq_matrix.h"
#include "CuTest.h"
#include "stdio.h"

void test_mat_create_base(CuTest *tc) {
  for (Vi i = 0; i < 5; i++) {
    for (Vi j = 0; j < 5; j++) {
      Matrix *mat = mat_create(i, j, 0.0);
      if (i * j <= 0) {
        CuAssertPtrEquals(tc, NULL, mat);
      } else {
        CuAssertIntEquals(tc, i, mat->row);
        CuAssertIntEquals(tc, j, mat->col);
        for (Vi k = 0; k < i * j; k++) {
          CuAssertDblEquals(tc, 0.0, mat->data[k], EPSILON);
        }
        mat_destroy(mat);
      }
    }
  }
}

void test_mat_destroy_base(CuTest *tc) {
  Matrix *mat = mat_create(2, 2, 0.0);
  CuAssertIntEquals(tc, 0, mat_destroy(mat));
}

void test_identity_base(CuTest *tc) {
  for (Vi i = 0; i < 5; i++) {
    for (Vi j = 0; j < 5; j++) {
      Matrix *mat = mat_create(i, j, 0.0);
      identity(mat);
      if (i * j <= 0) {
        CuAssertPtrEquals(tc, NULL, mat);
      } else if (i != j || i < 2 || i > 4) {
        for (Vi k = 0; k < i * j; k++) {
          CuAssertDblEquals(tc, 0.0, mat->data[k], EPSILON);
        }
      } else {
        for (Vi k = 0; k < i * j; k++) {
          if (k % (i + 1) == 0) {
            CuAssertDblEquals(tc, 1.0, mat->data[k], EPSILON);
          } else {
            CuAssertDblEquals(tc, 0.0, mat->data[k], EPSILON);
          }
        }
      }
      mat_destroy(mat);
    }
  }
}

CuSuite *FqMatrixGetSuite() {
  CuSuite *suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, test_mat_create_base);
  SUITE_ADD_TEST(suite, test_mat_destroy_base);
  SUITE_ADD_TEST(suite, test_identity_base);
  return suite;
}