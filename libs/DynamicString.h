#ifndef DS_IMPLEMENTATION
#define DS_IMPLEMENTATION

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

typedef struct
{
    uint8_t* data;
    uint64_t len;
    uint64_t capacity;
} DS;

DS DS_from_cstr(const char* str)
{
    DS ds;
    ds.len = strlen(str);
    ds.capacity = ds.len + 1;
    ds.data = malloc(sizeof(uint8_t) * ds.capacity);
    assert(ds.data != NULL);
    memcpy(ds.data, str, ds.capacity);
    return ds;
}

void DS_reserve(DS* ds, const uint64_t new_capacity)
{
    if (new_capacity > ds->capacity) {
        ds->data = realloc(ds->data, new_capacity);
        assert(ds->data);
        ds->capacity = new_capacity;
    }
}

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

void DS_free(DS* ds)
{
    free(ds->data);
    ds->data = NULL;
    ds->len = 0;
    ds->capacity = 0;
}

void DS_clear(DS* ds)
{
    ds->len = 0;
    if (ds->data) {
        ds->data[0] = '\0';
    }
}

void DS_shrink_to_fit(DS* ds)
{
    if (ds->len + 1 == ds->capacity) return;

    ds->capacity = ds->len + 1;
    ds->data = realloc(ds->data, ds->capacity);
    assert(ds->data);
}

void DS_push_back_ch(DS* ds, const char c)
{
    if (ds->capacity <= ds->len + 1) {
        DS_reserve(ds, ds->capacity * 2);
    }
    ds->data[ds->len++] = c;
    ds->data[ds->len] = '\0';
}

void DS_push_back_cstr(DS* ds, const char* cstr)
{
    uint64_t cstr_len = strlen(cstr);

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

void DS_push_back_n_cstr(DS* ds, const char* cstr, uint64_t n)
{
    uint64_t cstr_len = strlen(cstr);

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

void DS_insert_ch(DS* ds, uint64_t pos, char c)
{
    if (ds->capacity <= ds->len + 1) {
        DS_reserve(ds, ds->capacity * 2);
    }
    memmove(ds->data + pos + 1, ds->data + pos, sizeof(ds->data[0]) * (ds->len - pos));
    ds->data[pos] = c;
    ds->len++;
}

void DS_insert_cstr(DS* ds, uint64_t pos, char* cstr)
{
}

void DS_insert_ds(DS* ds, uint64_t pos, const DS* dsubstr)
{
}

char* DS_as_cstr(const DS* ds)
{
    return (const char*) ds->data;
}

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

DS DS_head(const DS* ds, uint64_t end)
{
    DS dshead = DS_from_cstr("");
    DS_push_back_n_cstr(&dshead, ds->data, end);
    return dshead;
}

DS DS_tail(const DS* ds, uint64_t start)
{
    DS dstail = DS_from_cstr("");
    DS_push_back_cstr(&dstail, ds->data + start);
    return dstail;
}

bool DS_compare(const DS* dsl, const char* cstr)
{
    return strcmp((const char*) dsl->data, cstr) == 0;
}

bool DS_compare(const DS* dsl, const DS* dsr)
{
    return DS_compare(dsl, (const char*) dsr->data);
}

bool DS_contains(const DS* ds, const char* csubstr)
{
    return strstr((const char*) ds->data, csubstr);
}

bool DS_contains(const DS* ds, const DS* dsubstr)
{
    return DS_contains(ds, (const char*) dsubstr->data);
}

void DS_trim_leading(DS* ds)
{
}

void DS_trim_trailing(DS* ds)
{
}

void DS_trim(DS* ds)
{
}

void DS_to_lower(DS* ds)
{
}

void DS_to_upper(DS* ds)
{
}

void DS_remove_ch(DS* ds, uint64_t pos)
{
}

void DS_remove_substr(DS* ds, const char* csubstr)
{
}

void DS_remove_substr(DS* ds, const DS* dsubstr)
{
    DS_remove_substr(ds, (const char*) dsubstr->data);
}

DS* DS_split(const DS* ds, char delim, uint64_t* count)
{
}

uint64_t DS_find(const DS* ds, char c)
{
    for (uint64_t i = 0; i < ds->len; i++) {
        if (c == ds->data[i]) {
            return i;
        }
    }
    return UINT64_MAX;
}

uint64_t DS_find(const DS* ds, const char* cstr)
{
    uint64_t cstr_len = strlen(cstr);
    if (cstr_len > ds->len) {
        return UINT64_MAX;
    }

    for (uint64_t i = 0; i < ds->len; i++) {
        if (strcmp(ds->data + i, cstr) == 0) {
            return i;
        }
    }

    return UINT64_MAX;
}

uint64_t DS_find_last(const DS* ds, char c)
{
    for (uint64_t i = ds->len - 1;; i--) {
        if (c == ds->data[i]) {
            return i;
        } else if (0 == i) {
            return UINT64_MAX;
        }
    }
    return UINT64_MAX;
}

uint64_t DS_find_last(const DS* ds, const char* cstr)
{
    uint64_t cstr_len = strlen(cstr);
    if (cstr_len > ds->len) {
        return UINT64_MAX;
    }

    for (uint64_t i = ds->len - 1;; i--) {
        if (strcmp(ds->data + i, cstr) == 0) {
            return i;
        } else if (0 == i) {
            return UINT64_MAX;
        }
    }

    return UINT64_MAX;
}

#endif // DS_IMPLEMENTATION
