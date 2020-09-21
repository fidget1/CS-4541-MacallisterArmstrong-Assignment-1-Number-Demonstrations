#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>

typedef unsigned char *byte_pointer;
void show_bytes(byte_pointer start, size_t len, bool reverse);
void show_int(int i, bool reverse);
void show_float(float f, bool reverse);
void show_pointer(void *x, bool reverse);
void show_short_as_unsigned(short v);
int bool_or(int i, int m);
int bool_xor(int i, int m);
int bis(int i, int m);
int bic(int i, int m);
int uadd_ok(unsigned i, unsigned m);
int tadd_ok(int i, int m, bool verbose);
int tsub_ok(int i, int m, bool verbose);
void test_tsub_ok(bool verbose);
int tmult_ok(int i, int m);
void test_tmult_ok();

void test_tmult_ok() {
    assert(tmult_ok(INT_MAX, 0));
}

int tmult_ok(int i, int m) {
    return !i || ((i * m) / i) == m;
}

// Borrowed entirely from reference
void test_tsub_ok(bool verbose) {
    assert(tsub_ok(INT_MAX, INT_MIN, verbose) == 0);
    assert(tsub_ok(INT_MIN, INT_MAX, verbose) == 0);
    assert(tsub_ok(INT_MAX, -1, verbose) == 0);
    assert(tsub_ok(INT_MIN, 1, verbose) == 0);
    assert(tsub_ok(5, 3, verbose) == 1);
    assert(tsub_ok(-1, 1, verbose) == 1);
}

// Borrowed from reference (and book)
int tsub_ok(int i, int m, bool verbose) {
    int sub = i - m;
    int neg = i < 0 && m >= 0 && sub > 0;
    int pos = i >= 0 && m < 0 && sub < 0;
    if (verbose) {
        printf("sub: %i\n", sub);
        printf("neg: %i\n", neg);
        printf("pos: %i\n\n", pos);
    }
    return !neg && !pos;
}

// Borrowed from reference (and book)
int tadd_ok(int i, int m, bool verbose) {
    int sum = i + m;
    int neg = i < 0 && m < 0 && sum >= 0;
    int pos = i >= 0 && m >= 0 && sum < 0;
    if (verbose) {
        printf("sum: %i\n", sum);
        printf("neg: %i\n", neg);
        printf("pos: %i\n", pos);
        printf("!neg: %i\n", !neg);
        printf("!pos: %i\n", !pos);
    }
    return !neg && !pos;
}

int uadd_ok(unsigned i, unsigned m) {
    unsigned sum = i + m;
    return sum >= i;
}

void show_short_as_unsigned(short v) {
    unsigned short uv = (unsigned short) v;
    printf("v: %d, uv: %u\n", v, uv);
}

void show_bytes(byte_pointer start, size_t len, bool reverse) {
    int i;
    if (reverse == false) {
        for (i = 0; i < len; i++) {
            printf("%.2x ", start[i]);
        }
        printf("\n");
    } else {
        for (i = (int) (len - 1); i >= 0; i--) {
            printf("%.2x ", start[i]);
        }
        printf("\n");
    }
}

void show_int(int i, bool reverse) {
    printf("show_int\n");
    show_bytes((byte_pointer) &i, sizeof(int), reverse);
}

void show_float(float f, bool reverse) {
    printf("show_float\n");
    show_bytes((byte_pointer) &f, sizeof(float), reverse);
}

void show_pointer(void *x, bool reverse) {
    printf("show_pointer\n");
    show_bytes((byte_pointer) &x, sizeof(void *), reverse);
}

int bis(int i, int m) {
    int result = i | m;
    return result;
}

int bic(int i, int m) {
    int result = i & ~m;
    return result;
}

int bool_or(int i, int m) {
    int result = bis(i, m);
    return result;
}

int bool_xor(int i, int m) {
    int result = bis(bic(i, m), bic(m, i));
    return result;
}