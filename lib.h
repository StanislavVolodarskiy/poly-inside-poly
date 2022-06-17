#ifndef LIB_H_
#define LIB_H_

#include <stdbool.h>

typedef struct {
    double x;
    double y;
} point_t;

typedef struct {
    point_t p1;
    point_t p2;
} seg_t;

double area2(const point_t *p1, const point_t *p2, const point_t *p3);

bool isect_seg_seg(const seg_t *s1, const seg_t *s2);

typedef struct {
    int n;
    seg_t *segs;
} poly_t;

bool isect_sides(const poly_t *p, const poly_t *q);

#endif // #ifndef LIB_H_
