#ifndef MATCH_H
#define MATCH_H MATCH_H

#include <math.h>
#include <stddef.h>

typedef double score_t;
#define SCORE_MAX INFINITY
#define SCORE_MIN -INFINITY

#define MATCH_MAX_LEN 1024

#define inf(fmt, ...)                                                                              \
  fprintf(stderr, "(%s:%-5d %s) " fmt "\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__)

int has_match(const char* needle, const char* haystack);
score_t match_positions(const char* needle, const char* haystack, size_t* positions);
score_t match(const char* needle, const char* haystack);

#endif
