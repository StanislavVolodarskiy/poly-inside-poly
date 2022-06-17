#include <assert.h>
#include <stdbool.h>

#include "lib.h"

void test_area2(
    double x1, double y1, double x2, double y2, double x3, double y3,
    double expected
) {
    const point_t p1 = {x1, y1};
    const point_t p2 = {x2, y2};
    const point_t p3 = {x3, y3};
    assert(area2(&p1, &p2, &p3) == expected);
}

void test_isect_seg_seg(
    double x1, double y1, double x2, double y2,
    double x3, double y3, double x4, double y4,
    bool expected
) {
    const seg_t seg1 = {{x1, y1}, {x2, y2}};
    const seg_t seg2 = {{x3, y3}, {x4, y4}};
    assert(isect_seg_seg(&seg1, &seg2) == expected);
    assert(isect_seg_seg(&seg2, &seg1) == expected);
}

void test_isect_sides(
    double px1, double py1, double px2, double py2, double px3, double py3,
    double qx1, double qy1, double qx2, double qy2, double qx3, double qy3,
    bool expected) {
    seg_t psegs[] = {
        {{px1, py1}, {px2, py2}},
        {{px2, py2}, {px3, py3}},
        {{px3, py3}, {px1, py1}}
    };
    seg_t qsegs[] = {
        {{qx1, qy1}, {qx2, qy2}},
        {{qx2, qy2}, {qx3, qy3}},
        {{qx3, qy3}, {qx1, qy1}}
    };
    poly_t p = {3, psegs};
    poly_t q = {3, qsegs};
    assert(isect_sides(&p, &q) == expected);
}

int main() {
    test_area2(2, 1, 3, 2, 4, 3, 0); 
    test_area2(3, 1, 4, 2, 5, 4, 1); 
    test_area2(3, 1, 4, 2, 6, 3, -1); 

    test_isect_seg_seg(3, 1, 4, 2, 3, 2, 4, 1, true); 
    test_isect_seg_seg(3, 1, 4, 2, 5, 2, 6, 1, false); 
    test_isect_seg_seg(3, 1, 5, 3, 4, 2, 5, 1, false); 

    test_isect_sides(0, 0, 2, 0, 0, 2, 1, 0, 1, 1, 0, 1, false);
    test_isect_sides(0, 0, 3, 0, 0, 3, 1, 1, 2, 1, 2, 1, false);
    test_isect_sides(0, 0, 2, 0, 0, 2, 1, 0, 2, 1, 0, 1, true);
}
