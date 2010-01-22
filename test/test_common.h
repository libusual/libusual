
#include <usual/base.h>

#include "tinytest.h"
#include "tinytest_macros.h"

#define str_check(a, b) tt_str_op(a, ==, b)
#define int_check(a, b) tt_int_op(a, ==, b)

extern struct testcase_t aatree_tests[];
extern struct testcase_t cbtree_tests[];
extern struct testcase_t string_tests[];
extern struct testcase_t crypto_tests[];
extern struct testcase_t heap_tests[];
extern struct testcase_t list_tests[];
extern struct testcase_t utf8_tests[];
extern struct testcase_t strpool_tests[];

