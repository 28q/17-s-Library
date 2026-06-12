#pragma GCC optimize("Ofast,unroll-loops,tree-vectorize,inline")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")

#include <immintrin.h>
#include <cstdio>
#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include <type_traits>
#include <string>
#include <utility>
#include <vector>

namespace fastio {

#define P0 1ULL
#define P1 10ULL
#define P2 100ULL
#define P3 1000ULL
#define P4 10000ULL
#define P5 100000ULL
#define P6 1000000ULL
#define P7 10000000ULL
#define P8 100000000ULL
#define P9 1000000000ULL
#define P10_ 10000000000ULL
#define P11 100000000000ULL
#define P12 1000000000000ULL
#define P13 10000000000000ULL
#define P14 100000000000000ULL
#define P15 1000000000000000ULL
#define P16 10000000000000000ULL
#define P17 100000000000000000ULL
#define P18 1000000000000000000ULL
#define P19 10000000000000000000ULL

#define C(i) ((uint64_t)(p[i]-'0'))

const char *in_ptr, *in_end;

void init_io() {
    struct stat st;
    if (!fstat(0, &st) && S_ISREG(st.st_mode)) {
        in_ptr = (const char*)mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, 0, 0);
        if (in_ptr != MAP_FAILED) { in_end = in_ptr + st.st_size; return; }
    }
    size_t cap = 1 << 24, r, len = 0;
    char *buf = (char*)malloc(cap + 64);
    while ((r = fread(buf + len, 1, cap - len, stdin)) > 0) {
        len += r;
        if (len == cap) buf = (char*)realloc(buf, (cap *= 2) + 64);
    }
    memset(buf + len, 0, 64);
    in_ptr = buf; in_end = buf + len;
}

inline __attribute__((always_inline)) void skip_non_digits() {
    while (in_ptr + 32 <= in_end) {
        __m256i v = _mm256_loadu_si256((const __m256i*)in_ptr);
        uint32_t m = _mm256_movemask_epi8(_mm256_cmpgt_epi8(v, _mm256_set1_epi8('0' - 1)));
        if (m) { in_ptr += __builtin_ctz(m); return; }
        in_ptr += 32;
    }
    while (in_ptr < in_end && *in_ptr < '0') in_ptr++;
}

inline __attribute__((always_inline)) uint64_t read_uint() {
    skip_non_digits();
    if (in_ptr >= in_end) return 0;
    if (in_ptr + 32 <= in_end) {
        __m256i v = _mm256_loadu_si256((const __m256i*)in_ptr);
        __m256i t1 = _mm256_cmpgt_epi8(_mm256_set1_epi8('0'), v);
        __m256i t2 = _mm256_cmpgt_epi8(v, _mm256_set1_epi8('9'));
        uint32_t mask = _mm256_movemask_epi8(_mm256_or_si256(t1, t2));
        if (mask) {
            int len = __builtin_ctz(mask);
            uint64_t val = 0;
            const uint8_t *p = (const uint8_t*)in_ptr;
            if (len <= 20) {
                switch (len) {
                    case 1: val = C(0); break;
                    case 2: val = C(0)*P1 + C(1); break;
                    case 3: val = C(0)*P2 + C(1)*P1 + C(2); break;
                    case 4: val = C(0)*P3 + C(1)*P2 + C(2)*P1 + C(3); break;
                    case 5: val = C(0)*P4 + C(1)*P3 + C(2)*P2 + C(3)*P1 + C(4); break;
                    case 6: val = C(0)*P5 + C(1)*P4 + C(2)*P3 + C(3)*P2 + C(4)*P1 + C(5); break;
                    case 7: val = C(0)*P6 + C(1)*P5 + C(2)*P4 + C(3)*P3 + C(4)*P2 + C(5)*P1 + C(6); break;
                    case 8: val = C(0)*P7 + C(1)*P6 + C(2)*P5 + C(3)*P4 + C(4)*P3 + C(5)*P2 + C(6)*P1 + C(7); break;
                    case 9: val = C(0)*P8 + C(1)*P7 + C(2)*P6 + C(3)*P5 + C(4)*P4 + C(5)*P3 + C(6)*P2 + C(7)*P1 + C(8); break;
                    case 10: val = C(0)*P9 + C(1)*P8 + C(2)*P7 + C(3)*P6 + C(4)*P5 + C(5)*P4 + C(6)*P3 + C(7)*P2 + C(8)*P1 + C(9); break;
                    case 11: val = C(0)*P10_ + C(1)*P9 + C(2)*P8 + C(3)*P7 + C(4)*P6 + C(5)*P5 + C(6)*P4 + C(7)*P3 + C(8)*P2 + C(9)*P1 + C(10); break;
                    case 12: val = C(0)*P11 + C(1)*P10_ + C(2)*P9 + C(3)*P8 + C(4)*P7 + C(5)*P6 + C(6)*P5 + C(7)*P4 + C(8)*P3 + C(9)*P2 + C(10)*P1 + C(11); break;
                    case 13: val = C(0)*P12 + C(1)*P11 + C(2)*P10_ + C(3)*P9 + C(4)*P8 + C(5)*P7 + C(6)*P6 + C(7)*P5 + C(8)*P4 + C(9)*P3 + C(10)*P2 + C(11)*P1 + C(12); break;
                    case 14: val = C(0)*P13 + C(1)*P12 + C(2)*P11 + C(3)*P10_ + C(4)*P9 + C(5)*P8 + C(6)*P7 + C(7)*P6 + C(8)*P5 + C(9)*P4 + C(10)*P3 + C(11)*P2 + C(12)*P1 + C(13); break;
                    case 15: val = C(0)*P14 + C(1)*P13 + C(2)*P12 + C(3)*P11 + C(4)*P10_ + C(5)*P9 + C(6)*P8 + C(7)*P7 + C(8)*P6 + C(9)*P5 + C(10)*P4 + C(11)*P3 + C(12)*P2 + C(13)*P1 + C(14); break;
                    case 16: val = C(0)*P15 + C(1)*P14 + C(2)*P13 + C(3)*P12 + C(4)*P11 + C(5)*P10_ + C(6)*P9 + C(7)*P8 + C(8)*P7 + C(9)*P6 + C(10)*P5 + C(11)*P4 + C(12)*P3 + C(13)*P2 + C(14)*P1 + C(15); break;
                    case 17: val = C(0)*P16 + C(1)*P15 + C(2)*P14 + C(3)*P13 + C(4)*P12 + C(5)*P11 + C(6)*P10_ + C(7)*P9 + C(8)*P8 + C(9)*P7 + C(10)*P6 + C(11)*P5 + C(12)*P4 + C(13)*P3 + C(14)*P2 + C(15)*P1 + C(16); break;
                    case 18: val = C(0)*P17 + C(1)*P16 + C(2)*P15 + C(3)*P14 + C(4)*P13 + C(5)*P12 + C(6)*P11 + C(7)*P10_ + C(8)*P9 + C(9)*P8 + C(10)*P7 + C(11)*P6 + C(12)*P5 + C(13)*P4 + C(14)*P3 + C(15)*P2 + C(16)*P1 + C(17); break;
                    case 19: val = C(0)*P18 + C(1)*P17 + C(2)*P16 + C(3)*P15 + C(4)*P14 + C(5)*P13 + C(6)*P12 + C(7)*P11 + C(8)*P10_ + C(9)*P9 + C(10)*P8 + C(11)*P7 + C(12)*P6 + C(13)*P5 + C(14)*P4 + C(15)*P3 + C(16)*P2 + C(17)*P1 + C(18); break;
                    case 20: val = C(0)*P19 + C(1)*P18 + C(2)*P17 + C(3)*P16 + C(4)*P15 + C(5)*P14 + C(6)*P13 + C(7)*P12 + C(8)*P11 + C(9)*P10_ + C(10)*P9 + C(11)*P8 + C(12)*P7 + C(13)*P6 + C(14)*P5 + C(15)*P4 + C(16)*P3 + C(17)*P2 + C(18)*P1 + C(19); break;
                }
                in_ptr += len; return val;
            }
        }
    }
    uint64_t val = 0;
    while (in_ptr < in_end && *in_ptr >= '0' && *in_ptr <= '9') val = val * 10 + (*in_ptr++ - '0');
    return val;
}

uint16_t lut2[100];
uint32_t lut4[10000];

void init_lut() {
    for (int i = 0; i < 100; i++) lut2[i] = (uint16_t)((i / 10 + '0') | ((i % 10 + '0') << 8));
    for (int i = 0; i < 10000; i++) lut4[i] = ((i / 1000 + '0') | (((i / 100) % 10 + '0') << 8) | (((i / 10) % 10 + '0') << 16) | ((i % 10 + '0') << 24));
}

const size_t OBUF_SIZE = 1 << 24;
char obuf[OBUF_SIZE];
char *out_ptr = obuf;

char errbuf[OBUF_SIZE];
char *err_ptr = errbuf;

inline __attribute__((always_inline)) void flush_out() {
    size_t len = out_ptr - obuf;
    if (len > 0) { if (write(1, obuf, len) == -1) {} out_ptr = obuf; }
}

inline __attribute__((always_inline)) void flush_err() {
    size_t len = err_ptr - errbuf;
    if (len > 0) { if (write(2, errbuf, len) == -1) {} err_ptr = errbuf; }
}

const uint64_t POW10[] = {P0, P1, P2, P3, P4, P5, P6, P7, P8, P9, P10_, P11, P12, P13, P14, P15, P16, P17, P18, P19};

#define W2(o, v) __builtin_memcpy(p + (o), &lut2[v], 2)
#define W4(o, v) __builtin_memcpy(p + (o), &lut4[v], 4)

inline __attribute__((always_inline)) void write_uint(uint64_t x) {
    if (__builtin_expect(out_ptr + 32 > obuf + OBUF_SIZE, 0)) flush_out();
    if (!x) { *out_ptr++ = '0'; *out_ptr++ = '\n'; return; }
    int t = (64 - __builtin_clzll(x)) * 1233 >> 12;
    int digits = t + (x >= POW10[t]);
    char *p = out_ptr;
    out_ptr += digits + 1;
    p[digits] = '\n';
    switch (digits) {
        case 1: p[0] = '0' + x; break;
        case 2: W2(0, x); break;
        case 3: p[0] = '0' + x / 100; W2(1, x % 100); break;
        case 4: W4(0, x); break;
        case 5: p[0] = '0' + x / 10000; W4(1, x % 10000); break;
        case 6: W2(0, x / 10000); W4(2, x % 10000); break;
        case 7: p[0] = '0' + x / 1000000; W2(1, (x / 10000) % 100); W4(3, x % 10000); break;
        case 8: W4(0, x / 10000); W4(4, x % 10000); break;
        case 9: { uint32_t lo = x % P8, hi = x / P8; p[0] = '0' + hi; W4(1, lo / 10000); W4(5, lo % 10000); break; }
        case 10: { uint32_t lo = x % P8, hi = x / P8; W2(0, hi); W4(2, lo / 10000); W4(6, lo % 10000); break; }
        case 11: { uint32_t lo = x % P8, hi = x / P8; p[0] = '0' + hi / 100; W2(1, hi % 100); W4(3, lo / 10000); W4(7, lo % 10000); break; }
        case 12: { uint32_t lo = x % P8, hi = x / P8; W4(0, hi); W4(4, lo / 10000); W4(8, lo % 10000); break; }
        case 13: { uint32_t lo = x % P8; uint64_t hi = x / P8; p[0] = '0' + hi / 10000; W4(1, hi % 10000); W4(5, lo / 10000); W4(9, lo % 10000); break; }
        case 14: { uint32_t lo = x % P8; uint64_t hi = x / P8; W2(0, hi / 10000); W4(2, hi % 10000); W4(6, lo / 10000); W4(10, lo % 10000); break; }
        case 15: { uint32_t lo = x % P8; uint64_t hi = x / P8; p[0] = '0' + hi / 1000000; W2(1, (hi / 10000) % 100); W4(3, hi % 10000); W4(7, lo / 10000); W4(11, lo % 10000); break; }
        case 16: { uint32_t lo = x % P8; uint64_t hi = x / P8; W4(0, hi / 10000); W4(4, hi % 10000); W4(8, lo / 10000); W4(12, lo % 10000); break; }
        case 17: { uint32_t lo = x % P8; uint64_t hi = x / P8; uint32_t top = hi / P8, md = hi % P8; p[0] = '0' + top; W4(1, md / 10000); W4(5, md % 10000); W4(9, lo / 10000); W4(13, lo % 10000); break; }
        case 18: { uint32_t lo = x % P8; uint64_t hi = x / P8; uint32_t top = hi / P8, md = hi % P8; W2(0, top); W4(2, md / 10000); W4(6, md % 10000); W4(10, lo / 10000); W4(14, lo % 10000); break; }
        case 19: { uint32_t lo = x % P8; uint64_t hi = x / P8; uint32_t top = hi / P8, md = hi % P8; p[0] = '0' + top / 100; W2(1, top % 100); W4(3, md / 10000); W4(7, md % 10000); W4(11, lo / 10000); W4(15, lo % 10000); break; }
        case 20: { uint32_t lo = x % P8; uint64_t hi = x / P8; uint32_t top = hi / P8, md = hi % P8; W4(0, top); W4(4, md / 10000); W4(8, md % 10000); W4(12, lo / 10000); W4(16, lo % 10000); break; }
    }
}

inline void write_char(char c) {
    if (__builtin_expect(out_ptr + 1 > obuf + OBUF_SIZE, 0)) flush_out();
    *out_ptr++ = c;
}

inline void write_char_err(char c) {
    if (__builtin_expect(err_ptr + 1 > errbuf + OBUF_SIZE, 0)) flush_err();
    *err_ptr++ = c;
}

inline void write_u64(uint64_t x) {
    if (!x) { write_char('0'); return; }
    int t = (64 - __builtin_clzll(x)) * 1233 >> 12;
    int digits = t + (x >= POW10[t]);
    if (__builtin_expect(out_ptr + digits > obuf + OBUF_SIZE, 0)) flush_out();
    char *p = out_ptr;
    out_ptr += digits;
    switch (digits) {
        case 1: p[0] = '0' + x; break;
        case 2: W2(0, x); break;
        case 3: p[0] = '0' + x / 100; W2(1, x % 100); break;
        case 4: W4(0, x); break;
        case 5: p[0] = '0' + x / 10000; W4(1, x % 10000); break;
        case 6: W2(0, x / 10000); W4(2, x % 10000); break;
        case 7: p[0] = '0' + x / 1000000; W2(1, (x / 10000) % 100); W4(3, x % 10000); break;
        case 8: W4(0, x / 10000); W4(4, x % 10000); break;
        case 9: { uint32_t lo = x % P8, hi = x / P8; p[0] = '0' + hi; W4(1, lo / 10000); W4(5, lo % 10000); break; }
        case 10: { uint32_t lo = x % P8, hi = x / P8; W2(0, hi); W4(2, lo / 10000); W4(6, lo % 10000); break; }
        case 11: { uint32_t lo = x % P8, hi = x / P8; p[0] = '0' + hi / 100; W2(1, hi % 100); W4(3, lo / 10000); W4(7, lo % 10000); break; }
        case 12: { uint32_t lo = x % P8, hi = x / P8; W4(0, hi); W4(4, lo / 10000); W4(8, lo % 10000); break; }
        case 13: { uint32_t lo = x % P8; uint64_t hi = x / P8; p[0] = '0' + hi / 10000; W4(1, hi % 10000); W4(5, lo / 10000); W4(9, lo % 10000); break; }
        case 14: { uint32_t lo = x % P8; uint64_t hi = x / P8; W2(0, hi / 10000); W4(2, hi % 10000); W4(6, lo / 10000); W4(10, lo % 10000); break; }
        case 15: { uint32_t lo = x % P8; uint64_t hi = x / P8; p[0] = '0' + hi / 1000000; W2(1, (hi / 10000) % 100); W4(3, hi % 10000); W4(7, lo / 10000); W4(11, lo % 10000); break; }
        case 16: { uint32_t lo = x % P8; uint64_t hi = x / P8; W4(0, hi / 10000); W4(4, hi % 10000); W4(8, lo / 10000); W4(12, lo % 10000); break; }
        case 17: { uint32_t lo = x % P8; uint64_t hi = x / P8; uint32_t top = hi / P8, md = hi % P8; p[0] = '0' + top; W4(1, md / 10000); W4(5, md % 10000); W4(9, lo / 10000); W4(13, lo % 10000); break; }
        case 18: { uint32_t lo = x % P8; uint64_t hi = x / P8; uint32_t top = hi / P8, md = hi % P8; W2(0, top); W4(2, md / 10000); W4(6, md % 10000); W4(10, lo / 10000); W4(14, lo % 10000); break; }
        case 19: { uint32_t lo = x % P8; uint64_t hi = x / P8; uint32_t top = hi / P8, md = hi % P8; p[0] = '0' + top / 100; W2(1, top % 100); W4(3, md / 10000); W4(7, md % 10000); W4(11, lo / 10000); W4(15, lo % 10000); break; }
        case 20: { uint32_t lo = x % P8; uint64_t hi = x / P8; uint32_t top = hi / P8, md = hi % P8; W4(0, top); W4(4, md / 10000); W4(8, md % 10000); W4(12, lo / 10000); W4(16, lo % 10000); break; }
    }
}

inline void write_i64(int64_t x) {
    if (x < 0) { write_char('-'); x = -x; }
    write_u64(static_cast<uint64_t>(x));
}

inline void write_u64_err(uint64_t x) {
    if (!x) { write_char_err('0'); return; }
    int t = (64 - __builtin_clzll(x)) * 1233 >> 12;
    int digits = t + (x >= POW10[t]);
    if (__builtin_expect(err_ptr + digits > errbuf + OBUF_SIZE, 0)) flush_err();
    char *p = err_ptr;
    err_ptr += digits;
    switch (digits) {
        case 1: p[0] = '0' + x; break;
        case 2: W2(0, x); break;
        case 3: p[0] = '0' + x / 100; W2(1, x % 100); break;
        case 4: W4(0, x); break;
        case 5: p[0] = '0' + x / 10000; W4(1, x % 10000); break;
        case 6: W2(0, x / 10000); W4(2, x % 10000); break;
        case 7: p[0] = '0' + x / 1000000; W2(1, (x / 10000) % 100); W4(3, x % 10000); break;
        case 8: W4(0, x / 10000); W4(4, x % 10000); break;
        case 9: { uint32_t lo = x % P8, hi = x / P8; p[0] = '0' + hi; W4(1, lo / 10000); W4(5, lo % 10000); break; }
        case 10: { uint32_t lo = x % P8, hi = x / P8; W2(0, hi); W4(2, lo / 10000); W4(6, lo % 10000); break; }
        case 11: { uint32_t lo = x % P8, hi = x / P8; p[0] = '0' + hi / 100; W2(1, hi % 100); W4(3, lo / 10000); W4(7, lo % 10000); break; }
        case 12: { uint32_t lo = x % P8, hi = x / P8; W4(0, hi); W4(4, lo / 10000); W4(8, lo % 10000); break; }
        case 13: { uint32_t lo = x % P8; uint64_t hi = x / P8; p[0] = '0' + hi / 10000; W4(1, hi % 10000); W4(5, lo / 10000); W4(9, lo % 10000); break; }
        case 14: { uint32_t lo = x % P8; uint64_t hi = x / P8; W2(0, hi / 10000); W4(2, hi % 10000); W4(6, lo / 10000); W4(10, lo % 10000); break; }
        case 15: { uint32_t lo = x % P8; uint64_t hi = x / P8; p[0] = '0' + hi / 1000000; W2(1, (hi / 10000) % 100); W4(3, hi % 10000); W4(7, lo / 10000); W4(11, lo % 10000); break; }
        case 16: { uint32_t lo = x % P8; uint64_t hi = x / P8; W4(0, hi / 10000); W4(4, hi % 10000); W4(8, lo / 10000); W4(12, lo % 10000); break; }
        case 17: { uint32_t lo = x % P8; uint64_t hi = x / P8; uint32_t top = hi / P8, md = hi % P8; p[0] = '0' + top; W4(1, md / 10000); W4(5, md % 10000); W4(9, lo / 10000); W4(13, lo % 10000); break; }
        case 18: { uint32_t lo = x % P8; uint64_t hi = x / P8; uint32_t top = hi / P8, md = hi % P8; W2(0, top); W4(2, md / 10000); W4(6, md % 10000); W4(10, lo / 10000); W4(14, lo % 10000); break; }
        case 19: { uint32_t lo = x % P8; uint64_t hi = x / P8; uint32_t top = hi / P8, md = hi % P8; p[0] = '0' + top / 100; W2(1, top % 100); W4(3, md / 10000); W4(7, md % 10000); W4(11, lo / 10000); W4(15, lo % 10000); break; }
        case 20: { uint32_t lo = x % P8; uint64_t hi = x / P8; uint32_t top = hi / P8, md = hi % P8; W4(0, top); W4(4, md / 10000); W4(8, md % 10000); W4(12, lo / 10000); W4(16, lo % 10000); break; }
    }
}

inline void write_i64_err(int64_t x) {
    if (x < 0) { write_char_err('-'); x = -x; }
    write_u64_err(static_cast<uint64_t>(x));
}

inline void write_u128(__uint128_t x) {
    if (!x) { write_char('0'); return; }
    const __uint128_t MOD = 10000000000000000000ULL; // 10^19
    uint64_t hi = static_cast<uint64_t>(x / MOD);
    uint64_t lo = static_cast<uint64_t>(x % MOD);
    if (hi) {
        write_u64(hi);
        char buf[19];
        uint64_t t = lo;
        for (int i = 18; i >= 0; --i) {
            buf[i] = '0' + (t % 10);
            t /= 10;
        }
        for (int i = 0; i < 19; ++i) write_char(buf[i]);
    } else {
        write_u64(lo);
    }
}

inline void write_i128(__int128_t x) {
    if (x < 0) { write_char('-'); x = -x; }
    write_u128(static_cast<__uint128_t>(x));
}

inline void write_u128_err(__uint128_t x) {
    if (!x) { write_char_err('0'); return; }
    const __uint128_t MOD = 10000000000000000000ULL;
    uint64_t hi = static_cast<uint64_t>(x / MOD);
    uint64_t lo = static_cast<uint64_t>(x % MOD);
    if (hi) {
        write_u64_err(hi);
        char buf[19];
        uint64_t t = lo;
        for (int i = 18; i >= 0; --i) {
            buf[i] = '0' + (t % 10);
            t /= 10;
        }
        for (int i = 0; i < 19; ++i) write_char_err(buf[i]);
    } else {
        write_u64_err(lo);
    }
}

inline void write_i128_err(__int128_t x) {
    if (x < 0) { write_char_err('-'); x = -x; }
    write_u128_err(static_cast<__uint128_t>(x));
}

inline void skip_whitespace() {
    while (in_ptr < in_end && (*in_ptr == ' ' || *in_ptr == '\n' || *in_ptr == '\t' || *in_ptr == '\r'))
        ++in_ptr;
}

inline __uint128_t read_uint128_raw() {
    skip_whitespace();
    __uint128_t val = 0;
    while (in_ptr < in_end && *in_ptr >= '0' && *in_ptr <= '9') {
        val = val * 10 + (*in_ptr++ - '0');
    }
    return val;
}

inline void read_one(bool &x)           { skip_whitespace(); x = (read_uint() != 0); }
inline void write_one(bool x)           { write_char(x ? '1' : '0'); }

inline void read_one(char &x)           { skip_whitespace(); x = *in_ptr++; }
inline void write_one(char x)           { write_char(x); }

inline void read_one(signed char &x)    { skip_whitespace(); x = *in_ptr++; }
inline void write_one(signed char x)    { write_char(x); }

inline void read_one(unsigned char &x)  { skip_whitespace(); x = *in_ptr++; }
inline void write_one(unsigned char x)  { write_char(x); }

inline void read_one(short &x) {
    skip_whitespace(); bool neg = false;
    if (*in_ptr == '-') { neg = true; ++in_ptr; }
    x = neg ? -static_cast<short>(read_uint()) : static_cast<short>(read_uint());
}
inline void write_one(short x) { write_i64(x); }

inline void read_one(unsigned short &x) { skip_whitespace(); x = static_cast<unsigned short>(read_uint()); }
inline void write_one(unsigned short x) { write_u64(x); }

inline void read_one(int &x) {
    skip_whitespace(); bool neg = false;
    if (*in_ptr == '-') { neg = true; ++in_ptr; }
    x = neg ? -static_cast<int>(read_uint()) : static_cast<int>(read_uint());
}
inline void write_one(int x) { write_i64(x); }

inline void read_one(unsigned int &x) { skip_whitespace(); x = static_cast<unsigned int>(read_uint()); }
inline void write_one(unsigned int x) { write_u64(x); }

inline void read_one(long &x) {
    skip_whitespace(); bool neg = false;
    if (*in_ptr == '-') { neg = true; ++in_ptr; }
    x = neg ? -static_cast<long>(read_uint()) : static_cast<long>(read_uint());
}
inline void write_one(long x) { write_i64(x); }

inline void read_one(unsigned long &x) { skip_whitespace(); x = static_cast<unsigned long>(read_uint()); }
inline void write_one(unsigned long x) { write_u64(x); }

inline void read_one(long long &x) {
    skip_whitespace(); bool neg = false;
    if (*in_ptr == '-') { neg = true; ++in_ptr; }
    x = neg ? -static_cast<long long>(read_uint()) : static_cast<long long>(read_uint());
}
inline void write_one(long long x) { write_i64(x); }

inline void read_one(unsigned long long &x) { skip_whitespace(); x = read_uint(); }
inline void write_one(unsigned long long x) { write_u64(x); }

#ifdef __SIZEOF_INT128__
inline void read_one(__int128_t &x) {
    skip_whitespace(); bool neg = false;
    if (*in_ptr == '-') { neg = true; ++in_ptr; }
    else if (*in_ptr == '+') ++in_ptr;
    __uint128_t val = read_uint128_raw();
    x = neg ? -static_cast<__int128_t>(val) : static_cast<__int128_t>(val);
}
inline void write_one(__int128_t x) { write_i128(x); }

inline void read_one(__uint128_t &x) {
    x = read_uint128_raw();
}
inline void write_one(__uint128_t x) { write_u128(x); }
#endif

inline void read_one(std::string &s) {
    skip_whitespace();
    s.clear();
    while (in_ptr < in_end && *in_ptr > ' ') s += *in_ptr++;
}
inline void write_one(const std::string &s) {
    for (char c : s) write_char(c);
}

template<typename T, typename U>
void read_one(std::pair<T, U> &p) { read_one(p.first); read_one(p.second); }
template<typename T, typename U>
void write_one(const std::pair<T, U> &p) { write_one(p.first); write_char(' '); write_one(p.second); }

template<typename T>
void read_one(std::vector<T> &v) { for (auto &e : v) read_one(e); }
template<typename T>
void write_one(const std::vector<T> &v) {
    for (size_t i = 0; i < v.size(); ++i) {
        if (i) write_char(' ');
        write_one(v[i]);
    }
}

inline void write_one_err(bool x)           { write_char_err(x ? '1' : '0'); }
inline void write_one_err(char x)           { write_char_err(x); }
inline void write_one_err(signed char x)    { write_char_err(x); }
inline void write_one_err(unsigned char x)  { write_char_err(x); }
inline void write_one_err(short x)          { write_i64_err(x); }
inline void write_one_err(unsigned short x) { write_u64_err(x); }
inline void write_one_err(int x)            { write_i64_err(x); }
inline void write_one_err(unsigned int x)   { write_u64_err(x); }
inline void write_one_err(long x)           { write_i64_err(x); }
inline void write_one_err(unsigned long x)  { write_u64_err(x); }
inline void write_one_err(long long x)      { write_i64_err(x); }
inline void write_one_err(unsigned long long x) { write_u64_err(x); }
#ifdef __SIZEOF_INT128__
inline void write_one_err(__int128_t x)     { write_i128_err(x); }
inline void write_one_err(__uint128_t x)    { write_u128_err(x); }
#endif
inline void write_one_err(const std::string &s) { for (char c : s) write_char_err(c); }
template<typename T, typename U>
void write_one_err(const std::pair<T, U> &p) { write_one_err(p.first); write_char_err(' '); write_one_err(p.second); }
template<typename T>
void write_one_err(const std::vector<T> &v) {
    for (size_t i = 0; i < v.size(); ++i) {
        if (i) write_char_err(' ');
        write_one_err(v[i]);
    }
}

inline void scan() {}
template<class Head, class... Tail>
void scan(Head &head, Tail&... tail) {
    read_one(head);
    scan(tail...);
}

template<class T>
void print(const T &t) {
    write_one(t);
    write_char('\n');
}

template<class Head, class... Tail>
void print(const Head &head, const Tail &... tail) {
    write_one(head);
    write_char(' ');
    print(tail...);
}

template<class T>
void printflush(const T &t) {
    write_one(t);
    write_char('\n');
    flush_out();
}

template<class Head, class... Tail>
void printflush(const Head &head, const Tail &... tail) {
    write_one(head);
    write_char(' ');
    printflush(tail...);
}

template<class... T>
void fin(const T &... a) {
    print(a...);
    exit(0);
}

inline void printout() {}
template<class Head, class... Tail>
void printout(const Head &head, const Tail &... tail) {
    write_one(head);
    printout(tail...);
}

inline void debug() {
    write_char_err('\n');
    flush_err();
}
template<class Head, class... Tail>
void debug(const Head &head, const Tail &... tail) {
    write_one_err(head);
    if constexpr (sizeof...(tail) > 0) write_char_err(' ');
    debug(tail...);
}

inline void debugout() {}
template<class Head, class... Tail>
void debugout(const Head &head, const Tail &... tail) {
    write_one_err(head);
    debugout(tail...);
}

} // namespace fastio

namespace {
    struct FastIOInitializer {
        FastIOInitializer() {
            fastio::init_io();
            fastio::init_lut();
            std::atexit([] {
                fastio::flush_out();
                fastio::flush_err();
            });
        }
    };
    FastIOInitializer fastio_init;
}

using namespace fastio;
