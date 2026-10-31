#include "s21_string.h"

#include <stddef.h>
#include <stdio.h>

void s21_strlen_test(void) {
    typedef struct {
        const char *str;
        size_t expected;
    } test_case_strlen;

    test_case_strlen tests[] = {
        {"", 0},
        {"a", 1},
        {"abc", 3},
        {"Hello, World!", 13},
        {"\0hidden", 0},
        {"long string with spaces", 24},
        {NULL, 0},
    };

    size_t num_tests = sizeof(tests) / sizeof(tests[0]);

    for (size_t i = 0; i < num_tests; i++) {
        size_t result = s21_strlen(tests[i].str);
        int success = (result == tests[i].expected);

        printf("input: \"%s\", ", tests[i].str ? tests[i].str : "(null)");
        printf("output: %zu, ", result);
        printf("expected: %zu, ", tests[i].expected);
        printf("result: %s\n", success ? "SUCCESS" : "FAIL");
    }
}

void s21_strcmp_test(void) {
    typedef struct {
        const char *s1;
        const char *s2;
        int expected_sign;
    } test_case_strcmp;

    test_case_strcmp tests[] = {{"abc", "abc", 0},
                                {"abc", "abd", -1},
                                {"abd", "abc", 1},
                                {"", "", 0},
                                {"", "a", -1},
                                {"a", "", 1},
                                {"Hello", "Hello", 0},
                                {"Hello", "World", -1},
                                {"long string", "long string", 0},
                                {"long string", "long strin", 1},
                                {NULL, NULL, 0},
                                {NULL, "test", -1},
                                {"test", NULL, 1},
                                {"\0hidden", "\0hidden", 0},
                                {"\0hidden", "a", -1}};

    size_t num_tests = sizeof(tests) / sizeof(tests[0]);

    for (size_t i = 0; i < num_tests; i++) {
        int result = s21_strcmp(tests[i].s1, tests[i].s2);
        int sign = (result > 0) ? 1 : (result < 0) ? -1 : 0;
        int success = (sign == tests[i].expected_sign);

        printf("s1: \"%s\", s2: \"%s\", ", tests[i].s1 ? tests[i].s1 : "(null)",
               tests[i].s2 ? tests[i].s2 : "(null)");
        printf("Output: %d, ", result);
        printf("Result: %s\n", success ? "SUCCESS" : "FAIL");
    }
}

int main(void) {
    s21_strlen_test();
    s21_strcmp_test();
    return 0;
}