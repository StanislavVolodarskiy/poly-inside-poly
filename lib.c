#include "lib.h"

double area2(const point_t *p1, const point_t *p2, const point_t *p3) {
    const double x1 = p2->x - p1->x;
    const double y1 = p2->y - p1->y;
    const double x2 = p3->x - p1->x;
    const double y2 = p3->y - p1->y;
    return x1 * y2 - y1 * x2;
}

bool isect_line_seg(const seg_t *line, const seg_t *seg) {
    const double a1 = area2(&line->p1, &line->p2, &seg->p1);
    const double a2 = area2(&line->p1, &line->p2, &seg->p2);
    if (a1 < 0 && 0 < a2) {
        return true;
    }
    if (a2 < 0 && 0 < a1) {
        return true;
    }
    return false;
}

bool isect_seg_seg(const seg_t *s1, const seg_t *s2) {
    return isect_line_seg(s1, s2) && isect_line_seg(s2, s1);
}

bool isect_sides(const poly_t *p, const poly_t *q) {
    for (int i = 0; i < p->n; ++i) {
        for (int j = 0; j < q->n; ++j) {
            if (isect_seg_seg(&p->segs[i], &q->segs[j])) {
                return true;
            }
        }
    }
    return false;
}
