#ifndef DS_H
#define DS_H

#include <stdint.h>  // TODO: Can we even get rid of this?
#include <stdlib.h>  // GOD MODE TODO: Get rid of this
#include <stdbool.h> // TODO: Get rid of this
#include <string.h>  // TODO: Get rid of this
#include <assert.h>  // TODO: Get rid of this

#define NOT_IMPLEMENTED(...) do {                                          \
                                 assert(false && "TODO: Not implemented"); \
                                 (void) __VA_ARGS__;\
                             } while(false)

typedef struct
{
    uint8_t* data;
    uint64_t len;
    uint64_t capacity;
} DS;

typedef _Float64 float64_t;

/* * * * Declarations * * * */

static inline bool DS_is_alphanumeric(char c);
static inline bool DS_is_number(char c);
static inline bool DS_is_letter(char c);
static inline bool DS_is_upper(char c);
static inline bool DS_is_lower(char c);
static inline uint64_t DS_cstrlen(const char* cstr);
static inline bool DS_cstreq(const char* cstrl, const char* cstrr);
static inline int64_t DS_cstrcmp(const char* cstrl, const char* cstrr);

static inline DS DS_from_cstr(const char* str);
static inline DS DS_from_ds(const DS* ds);
static inline void DS_reserve(DS* ds, const uint64_t new_capacity);
static inline void DS_resize(DS* ds, const uint64_t new_capacity);
static inline void DS_free(DS* ds);
static inline void DS_clear(DS* ds);
static inline void DS_shrink_to_fit(DS* ds);
static inline void DS_push_back_ch(DS* ds, const char c);
static inline void DS_push_back_cstr(DS* ds, const char* cstr);
static inline void DS_push_back_n_cstr(DS* ds, const char* cstr, uint64_t n);
static inline void DS_insert_ch(DS* ds, uint64_t pos, const char c);
static inline void DS_insert_cstr(DS* ds, uint64_t pos, const char* cstr);
static inline void DS_insert_ds(DS* ds, uint64_t pos, const DS* dsubstr);
static inline const char* DS_to_cstr(const DS* cds);
static inline int64_t DS_to_i64(const DS* cds);
static inline uint64_t DS_to_u64(const DS* cds);
static inline float64_t DS_to_f64(const DS* cds);
static inline DS DS_substring(const DS* ds, uint64_t start, uint64_t length);
static inline DS DS_head(const DS* ds, uint64_t end);
static inline DS DS_tail(const DS* ds, uint64_t start);
static inline bool DS_eq_cstr(const DS* ds, const char* cstr);
static inline bool DS_eq_ds(const DS* dsl, const DS* dsr);
static inline int64_t DS_cmp_cstr(const DS* ds, const char* cstr);
static inline int64_t DS_cmp_ds(const DS* dsl, const DS* dsr);
static inline bool DS_contains_cstr(const DS* ds, const char* csubstr);
static inline bool DS_contains_ds(const DS* ds, const DS* dsubstr);
static inline void DS_trim_leading(DS* ds);
static inline void DS_trim_trailing(DS* ds);
static inline void DS_trim(DS* ds);
static inline void DS_to_lower(DS* ds);
static inline void DS_to_upper(DS* ds);
static inline void DS_reverse_case(DS* ds);
static inline void DS_remove_i(DS* ds, uint64_t pos);
static inline void DS_remove_n_i(DS* ds, uint64_t pos, uint64_t n);
static inline void DS_remove_first_ch(DS* ds, char c);
static inline void DS_remove_first_cstr(DS* ds, const char* csubstr);
static inline void DS_remove_first_ds(DS* ds, const DS* dsubstr);
static inline void DS_remove_last_ch(DS* ds, char c);
static inline void DS_remove_last_cstr(DS* ds, const char* csubstr);
static inline void DS_remove_last_ds(DS* ds, const DS* dsubstr);
static inline DS* DS_split_ch(const DS* ds, char delim, uint64_t* count);
static inline uint64_t DS_find_ch(const DS* ds, char c);
static inline uint64_t DS_find_cstr(const DS* ds, const char* cstr);
static inline uint64_t DS_find_ds(const DS* dsl, const DS* dsr);
static inline uint64_t DS_find_last_ch(const DS* ds, char c);
static inline uint64_t DS_find_last_cstr(const DS* ds, const char* cstr);
static inline uint64_t DS_find_last_ds(const DS* dsl, const DS* dsr);
static inline char DS_pop_ch(DS* ds);
static inline char DS_pop_back_ch(DS* ds);
static inline void DS_remove_suffix(DS* ds, const char* suffix_cstr);


/* * * * Implementations * * * */

static inline
bool DS_is_alphanumeric(char c)
{
    return DS_is_number(c) || DS_is_letter(c);
}

static inline
bool DS_is_number(char c)
{
    return c >= '0' && c <= '9';
}

static inline
bool DS_is_letter(char c)
{
    return DS_is_upper(c) || DS_is_lower(c);
}

static inline
bool DS_is_upper(char c)
{
    return c >= 'A' && c <= 'Z';
}

static inline
bool DS_is_lower(char c)
{
    return c >= 'a' && c <= 'z';
}

static inline
uint64_t DS_cstrlen(const char* cstr)
{
    for (uint64_t i = 0;; i++) {
        if (cstr[i] == '\0') return i;
    }
    return 0;
}

static inline
bool DS_cstreq(const char* cstrl, const char* cstrr)
{
    uint64_t len = DS_cstrlen(cstrl);
    if (len != DS_cstrlen(cstrr)) return false;
    for (uint64_t i = 0; i < len; i++) {
        if (cstrl[i] != cstrr[i]) return false;
    }
    return true;
}

static inline int64_t DS_cstrcmp(const char* cstrl, const char* cstrr)
{
    NOT_IMPLEMENTED(cstrl, cstrr);
}

static inline
DS DS_from_cstr(const char* str)
{
    DS ds;
    ds.len = DS_cstrlen(str);
    ds.capacity = ds.len + 1;
    ds.data = malloc(sizeof(uint8_t) * ds.capacity);
    assert(ds.data != NULL);
    memcpy(ds.data, str, ds.capacity);
    return ds;
}

static inline
DS DS_from_ds(const DS* ds)
{
    return DS_from_cstr((const char*) ds->data);
}

static inline
void DS_reserve(DS* ds, const uint64_t new_capacity)
{
    if (new_capacity > ds->capacity) {
        ds->data = realloc(ds->data, new_capacity);
        assert(ds->data);
        ds->capacity = new_capacity;
    }
}

static inline
void DS_resize(DS* ds, const uint64_t new_capacity)
{
    ds->data = realloc(ds->data, new_capacity);
    assert(ds->data);
    ds->capacity = new_capacity;
    if (ds->len >= ds->capacity) {
        ds->len = ds->capacity - 1;
        ds->data[ds->len] = '\0';
    }
}

static inline
void DS_free(DS* ds)
{
    free(ds->data);
    ds->data = NULL;
    ds->len = 0;
    ds->capacity = 0;
}

static inline
void DS_clear(DS* ds)
{
    ds->len = 0;
    if (ds->data) {
        ds->data[0] = '\0';
    }
}

static inline
void DS_shrink_to_fit(DS* ds)
{
    if (ds->len + 1 == ds->capacity) return;

    ds->capacity = ds->len + 1;
    ds->data = realloc(ds->data, ds->capacity);
    assert(ds->data);
}

static inline
void DS_push_back_ch(DS* ds, const char c)
{
    if (ds->capacity <= ds->len + 1) {
        DS_reserve(ds, ds->capacity * 2);
    }
    ds->data[ds->len++] = c;
    ds->data[ds->len] = '\0';
}

static inline
void DS_push_back_cstr(DS* ds, const char* cstr)
{
    uint64_t cstr_len = DS_cstrlen(cstr);

    if (ds->capacity <= ds->len + cstr_len + 1) {
        uint64_t new_capacity = ds->capacity * 2;
        while (new_capacity <= ds->len + cstr_len + 1) {
            new_capacity *= 2;
        }
        DS_reserve(ds, new_capacity);
    }

    memcpy(ds->data + ds->len, cstr, cstr_len + 1);
    ds->len += cstr_len;
}

static inline
void DS_push_back_n_cstr(DS* ds, const char* cstr, uint64_t n)
{
    uint64_t cstr_len = DS_cstrlen(cstr);

    if (n > cstr_len) n = cstr_len;

    if (ds->capacity <= ds->len + n) {
        uint64_t new_capacity = ds->capacity * 2;
        while (new_capacity <= ds->len + n) {
            new_capacity *= 2;
        }
        DS_reserve(ds, new_capacity);
    }

    memcpy(ds->data + ds->len, cstr, n);
    ds->len += n;
}

static inline
void DS_insert_ch(DS* ds, uint64_t pos, const char c)
{
    assert(ds->len >= pos);
    if (ds->capacity <= ds->len + 1) {
        DS_reserve(ds, ds->capacity * 2);
    }
    memmove(ds->data + pos + 1, ds->data + pos, ds->len - pos);
    ds->data[pos] = c;
    ds->len++;
}

static inline
void DS_insert_cstr(DS* ds, uint64_t pos, const char* cstr)
{
    assert(ds->len >= pos);
    uint64_t cstr_len = DS_cstrlen(cstr);
    DS_reserve(ds, ds->len + cstr_len + 1);
    memmove(ds->data + pos + cstr_len, ds->data + pos, ds->len - pos);
    memcpy(ds->data + pos, cstr, cstr_len);
}

static inline
void DS_insert_ds(DS* ds, uint64_t pos, const DS* dsubstr)
{
    assert(ds->len >= pos);
    DS_reserve(ds, ds->len + dsubstr->len + 1);
    memmove(ds->data + pos + dsubstr->len, ds->data + pos, ds->len - pos);
    memcpy(ds->data + pos, dsubstr->data, dsubstr->len);
}

static inline
const char* DS_to_cstr(const DS* cds)
{
    return (const char*) cds->data;
}

static inline
int64_t DS_to_i64(const DS* cds)
{
    DS ds = DS_from_ds(cds);
    DS_trim(&ds);
    int64_t result = 0;
    int64_t sign = 1;
    uint64_t start = 0;
    if (ds.len > 0 && ds.data[0] == '-') {
        sign = -1;
        start = 1;
    }
    if (ds.len > 0 && ds.data[0] == '+') {
        start = 1;
    }
    for (uint64_t i = start; i < ds.len; i++) {
        if (ds.data[i] < '0' || ds.data[i] > '9') {
            return 0;
        }
        result *= 10;
        result += (int64_t) ds.data[i] - '0';
    }
    return result * sign;
}

static inline
uint64_t DS_to_u64(const DS* cds)
{
    DS ds = DS_from_ds(cds);
    DS_trim(&ds);
    uint64_t result = 0;
    for (uint64_t i = 0; i < ds.len; i++) {
        if (ds.data[i] < '0' || ds.data[i] > '9') {
            return 0;
        }
        result *= 10;
        result += (uint64_t) ds.data[i] - '0';
    }
    return result;
}

static inline
float64_t DS_to_f64(const DS* cds)
{
    DS ds = DS_from_ds(cds);
    DS_trim(&ds);
    float64_t result = 0.0;
    float64_t sign = 1.0;
    uint64_t start = 0;
    if (ds.len > 0 && ds.data[0] == '-') {
        sign = -1.0;
        start = 1;
    }
    if (ds.len > 0 && ds.data[0] == '+') {
        start = 1;
    }

    uint64_t dot = 0;
    for (uint64_t i = start; i < ds.len; i++) {
        if (ds.data[i] == '.') {
            dot = i;
            break;
        }

        result *= (float64_t) 10.0;
        result += (float64_t) ds.data[i] - '\0';
    }

    float64_t exp = (float64_t) 10.0;
    for (uint64_t i = dot + 1; i < ds.len; i++) {
        result += (float64_t) (ds.data[i] - '\0') / exp;
        exp *= 10.0;
    }

    return result * sign;
}

static inline
DS DS_substring(const DS* ds, uint64_t start, uint64_t length)
{
    if (start >= ds->len) return DS_from_cstr("");

    DS dsubstr = DS_from_cstr("");
    if (start + length > ds->len) {
        dsubstr.len = ds->len - start;
    }
    DS_reserve(&dsubstr, dsubstr.len + 1);
    memcpy(dsubstr.data, ds->data + start, dsubstr.len);
    dsubstr.data[dsubstr.len] = '\0';
    return dsubstr;
}

static inline
DS DS_head(const DS* ds, uint64_t end)
{
    DS dshead = DS_from_cstr("");
    DS_push_back_n_cstr(&dshead, (const char*) ds->data, end);
    return dshead;
}

static inline
DS DS_tail(const DS* ds, uint64_t start)
{
    DS dstail = DS_from_cstr("");
    DS_push_back_cstr(&dstail, (const char*) ds->data + start);
    return dstail;
}

static inline
bool DS_eq_cstr(const DS* ds, const char* cstr)
{
    return DS_cstreq((const char*) ds->data, cstr);
}

static inline
bool DS_eq_ds(const DS* dsl, const DS* dsr)
{
    return DS_eq_cstr(dsl, (const char*) dsr->data);
}

static inline int64_t DS_cmp_cstr(const DS* ds, const char* cstr)
{
    NOT_IMPLEMENTED(ds, cstr);
}

static inline int64_t DS_cmp_ds(const DS* dsl, const DS* dsr)
{
    NOT_IMPLEMENTED(dsl, dsr);
}

static inline
bool DS_contains_cstr(const DS* ds, const char* csubstr)
{
    return strstr((const char*) ds->data, csubstr);
}

static inline
bool DS_contains_ds(const DS* ds, const DS* dsubstr)
{
    return DS_contains_cstr(ds, (const char*) dsubstr->data);
}

static inline
void DS_trim_leading(DS* ds)
{
    bool found_alphanum = false;
    uint64_t last_whitespace = 0;
    for (uint64_t i = 0; i < ds->len && !found_alphanum; i++) {
        switch (ds->data[i]) {
        case ' ':
        case '\t':
        case '\v':
        case '\n':
        case '\r': {
            last_whitespace = i;
        } break;
        default: {
            found_alphanum = true;
        } break;
        }
    }

    if (found_alphanum) {
        memmove(ds->data, ds->data + last_whitespace + 1, ds->len - last_whitespace + 1);
        ds->len -= last_whitespace;
    }
}

static inline
void DS_trim_trailing(DS* ds)
{
    bool found_alphanum = false;
    uint64_t last_whitespace = 0;
    for (uint64_t i = ds->len - 1; !found_alphanum; i--) {
        switch (ds->data[i]) {
        case ' ':
        case '\t':
        case '\v':
        case '\n':
        case '\r': {
            last_whitespace = i;
        } break;
        default:
            found_alphanum = true;
            break;
        }

        if (i == 0) break;
    }

    if (found_alphanum) {
        ds->len -= last_whitespace;
        ds->data[ds->len] = '\0';
    }
}

static inline
void DS_trim(DS* ds)
{
    DS_trim_leading(ds);
    DS_trim_trailing(ds);
}

static inline
void DS_to_lower(DS* ds)
{
    for (uint64_t i = 0; i < ds->len; i++) {
        if (DS_is_upper(ds->data[i])) {
            ds->data[i] ^= 0x20;
        }
    }
}

static inline
void DS_to_upper(DS* ds)
{
    for (uint64_t i = 0; i < ds->len; i++) {
        if (DS_is_lower(ds->data[i])) {
            ds->data[i] ^= 0x20;
        }
    }
}

static inline void DS_reverse_case(DS* ds)
{
    for (uint64_t i = 0; i < ds->len; i++) {
        if (DS_is_letter(ds->data[i])) {
            ds->data[i] ^= 0x20;
        }
    }
}

static inline
void DS_remove_i(DS* ds, uint64_t pos)
{
    memmove(ds->data + pos, ds->data + pos + 1, ds->len - pos);
    ds->len--;
}

static inline
void DS_remove_n_i(DS* ds, uint64_t pos, uint64_t n)
{
    assert(n > 0 && (pos + n <= ds->len));
    memmove(ds->data + pos, ds->data + pos + n, ds->len - pos - n);
    ds->len -= n;
}

static inline void DS_remove_first_ch(DS* ds, char c)
{
    NOT_IMPLEMENTED(ds, c);
}

static inline
void DS_remove_first_cstr(DS* ds, const char* csubstr)
{
    NOT_IMPLEMENTED(ds, csubstr);
}

static inline
void DS_remove_first_ds(DS* ds, const DS* dsubstr)
{
    DS_remove_first_cstr(ds, (const char*) dsubstr->data);
}

static inline void DS_remove_last_ch(DS* ds, char c)
{
    NOT_IMPLEMENTED(ds, c);
}

static inline void DS_remove_last_cstr(DS* ds, const char* csubstr)
{
    NOT_IMPLEMENTED(ds, csubstr);
}

static inline void DS_remove_last_ds(DS* ds, const DS* dsubstr)
{
    NOT_IMPLEMENTED(ds, dsubstr);
}

static inline
DS* DS_split_ch(const DS* ds, char delim, uint64_t* count)
{
    NOT_IMPLEMENTED(ds, delim, count);
}

static inline
uint64_t DS_find_ch(const DS* ds, char c)
{
    for (uint64_t i = 0; i < ds->len; i++) {
        if (c == ds->data[i]) {
            return i;
        }
    }
    return UINT64_MAX;
}

static inline
uint64_t DS_find_cstr(const DS* ds, const char* cstr)
{
    uint64_t cstr_len = DS_cstrlen(cstr);
    if (cstr_len > ds->len) {
        return UINT64_MAX;
    }

    for (uint64_t i = 0; i < ds->len; i++) {
        if (strcmp((const char*) ds->data + i, cstr) == 0) {
            return i;
        }
    }

    return UINT64_MAX;
}

static inline
uint64_t DS_find_ds(const DS* dsl, const DS* dsr)
{
    return DS_find_cstr(dsl, (const char*) dsr->data);
}

static inline
uint64_t DS_find_last_ch(const DS* ds, char c)
{
    if (ds->len == 0) return UINT64_MAX;
    for (uint64_t i = ds->len - 1;; i--) {
        if (c == ds->data[i]) {
            return i;
        } else if (0 == i) {
            return UINT64_MAX;
        }
    }
    return UINT64_MAX;
}

static inline
uint64_t DS_find_last_cstr(const DS* ds, const char* cstr)
{
    uint64_t cstr_len = DS_cstrlen(cstr);
    if (cstr_len > ds->len) {
        return UINT64_MAX;
    }

    for (uint64_t i = ds->len - 1;; i--) {
        if (strcmp((const char*) ds->data + i, cstr) == 0) {
            return i;
        } else if (0 == i) {
            return UINT64_MAX;
        }
    }

    return UINT64_MAX;
}

static inline
uint64_t DS_find_last_ds(const DS* dsl, const DS* dsr)
{
    return DS_find_last_cstr(dsl, (const char*) dsr->data);
}

static inline
char DS_pop_ch(DS* ds)
{
    if (ds->len == 0) return '\0';
    char c = ds->data[0];
    memmove(ds->data, ds->data + 1, ds->len - 1 == 0 ? 1 : ds->len - 1 );
    ds->len--;
    ds->data[ds->len] = '\0';
    return c;
}

static inline
char DS_pop_back_ch(DS* ds)
{
    ds->len--;
    char c = ds->data[ds->len];
    ds->data[ds->len] = '\0';
    return c;
}

static inline
void DS_remove_suffix(DS* ds, const char* suffix_cstr)
{
    uint64_t suffix_len = DS_cstrlen(suffix_cstr);
    uint64_t index = DS_find_last_cstr(ds, suffix_cstr);
    if (ds->len > index + suffix_len) return; // Substring is not at the end
    ds->len -= suffix_len;
    ds->data[ds->len] = '\0';
}

#endif // DS_H
