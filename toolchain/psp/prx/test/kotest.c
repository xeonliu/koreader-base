/* Self-test module for the PRX mechanism: exercises imports (malloc, snprintf, strlen via the main program),
 * exports, floats/doubles across the boundary, static data and constructors. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static int counter = 40;
static int ctor_ran;
__attribute__((constructor)) static void kotest_ctor(void) { ctor_ran = 1; }

int kotest_add(int a, int b) { return a + b + (ctor_ran ? 0 : 1000); }
int kotest_count(void) { return ++counter; }
double kotest_hyp(double a, double b) { return sqrt(a * a + b * b); }
float kotest_half(float x) { return x * 0.5f; }
char *kotest_greet(const char *who) {
    size_t n = strlen(who) + 32;
    char *s = malloc(n);
    snprintf(s, n, "hello %s from a PRX (%d)", who, counter);
    printf("kotest: greeting built in module, %u bytes\n", (unsigned)n);
    return s;
}
