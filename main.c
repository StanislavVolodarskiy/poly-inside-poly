#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "lib.h"

poly_t read_poly() {
    poly_t poly;

    if (scanf("%d", &poly.n) != 1) {
        exit(1);
    }
    poly.segs = malloc(sizeof(seg_t) * poly.n);
    if (poly.segs == NULL) {
        exit(1);
    }
    for (int i = 0; i < poly.n; ++i) {
        if (scanf("%lf %lf", &poly.segs[i].p2.x, &poly.segs[i].p2.y) != 2) {
            exit(1);
        }
    }
    int i = poly.n - 1;
    for (int j = 0; j < poly.n; ++j) {
        poly.segs[j].p1 = poly.segs[i].p2;
        i = j;
    }
    return poly;
}

int compare_doubles(const void *o1, const void *o2) {
    const double v1 = *(const double *)o1;
    const double v2 = *(const double *)o2;
    if (v1 < v2) { return -1; }
    if (v1 > v2) { return  1; }
                 { return  0; }
}

double *make_ys(const poly_t *p, const poly_t *q) {
    const int n = p->n + q->n;
    double *ys = malloc(sizeof(double) * n);
    if (ys == NULL) {
        exit(1);
    }
    for (int i = 0; i < p->n; ++i) {
        ys[i] = p->segs[i].p2.y;
    }
    for (int i = 0; i < q->n; ++i) {
        ys[i + p->n] = q->segs[i].p2.y;
    }
    qsort(ys, n, sizeof(double), compare_doubles);
    return ys;
}

typedef struct {
    int    b; // 0b01 for q, 0b10 for p
    double n; // intersection point numerator
    double d; // intersection point denominator
} isect_t;

isect_t *alloc_isects(const poly_t *p, const poly_t *q) {
    isect_t *isects = malloc(sizeof(isect_t) * (p->n + q->n));
    if (isects == NULL) {
        exit(1);
    }
    return isects;
}

int append_isects(isect_t *isects, double y, const poly_t *p, int b) {
    int n = 0;
    for (int i = 0; i < p->n; ++i) {
        const point_t *p1 = &p->segs[i].p1;
        const point_t *p2 = &p->segs[i].p2;
        if (p1->y > p2->y) {
            p1 = &p->segs[i].p2;
            p2 = &p->segs[i].p1;
        }
        const double y1 = p1->y;
        const double y2 = p2->y;
        assert(y1 <= y2);
        if (y1 < y && y < y2) {
            const double x1 = p1->x;
            const double x2 = p2->x;
            isects[n].b = b;
            isects[n].n = x2 * (y - y1) + x1 * (y2 - y);
            isects[n].d = y2 - y1;
            ++n;
        }
    }
    return n;
}

int compare_isects(const void *o1, const void *o2) {
    const isect_t *i1 = o1;
    const isect_t *i2 = o2;
    const double v1 = i1->n * i2->d;
    const double v2 = i2->n * i1->d;
    if (v1 < v2) { return -1; }
    if (v1 > v2) { return  1; }
                 { return  0; }
}

bool contains_in_stripe(const poly_t *p, const poly_t *q, double y,
                        isect_t *isects) {
    int n  = append_isects(isects    , y, p, /* 0b10 */ 2);
        n += append_isects(isects + n, y, q, /* 0b01 */ 1);
    qsort(isects, n, sizeof(isect_t), compare_isects);
    int state = /* 0b00 */ 0;
    for (int i = 0; i < n; ++i) {
        state ^= isects[i].b;
        if (state == /* 0b01 */ 1) {
            return false;
        }
    }
    return true;
}

bool contains(const poly_t *p, const poly_t *q) {
    if (isect_sides(p, q)) {
        return false;
    }
    const int n = p->n + q->n;
    double *ys = make_ys(p, q);
    isect_t *isects = alloc_isects(p, q);
    for (int i = 1; i < n; ++i) {
        assert(ys[i - 1] <= ys[i]);
        const double y = (ys[i - 1] + ys[i]) / 2;
        if (!contains_in_stripe(p, q, y, isects)) {
            // TODO: free ys
            // TODO: free isects
            return false;
        }
    }
    // TODO: free ys
    // TODO: free isects
    return true;
}

int main() {
    poly_t p = read_poly();
    poly_t q = read_poly();
    puts((contains(&p, &q)) ? "yes" : "no");
}
