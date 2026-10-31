#include "s21_string.h"

size_t s21_strlen(const char *str) {
    size_t len = 0;
    if (str != NULL) {
        while (str[len] != '\0') {
            len++;
        }
    }
    return len;
}

int s21_strcmp(const char *s1, const char *s2) {
    if (s1 == NULL && s2 == NULL) return 0;
    if (s1 == NULL) return -1;
    if (s2 == NULL) return 1;

    while (*s1 && *s2 && *s1 == *s2) {
        s1++;
        s2++;
    }
    return (unsigned char)*s1 - (unsigned char)*s2;
}