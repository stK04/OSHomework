#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct point {
    double x;
    double y;
    double mass;
};

struct point *find_closest(struct point *points, int n, struct point *point) {
    double min_distance = INFINITY;
    struct point *closest = NULL;
    for (int i = 0; i < n; i++) {
        double distance = sqrt(pow(points[i].x - point->x, 2) +
                               pow(points[i].y - point->y, 2));
        if (distance < min_distance) {
            min_distance = distance;
            closest = &points[i];
        }
    }
    return closest;
}

struct point *evaporate_points(struct point *points, int n) {
    while (n > 1) {
        struct point *min_point = points;
        for (int i = 1; i < n; i++) {
            if (points[i].mass < min_point->mass) {
                min_point = &points[i];
            }
        }

        struct point *closest_point = find_closest(points, n - 1, min_point);

        closest_point->mass += min_point->mass;

        for (int i = 0; i < n - 1; i++) {
            if (&points[i] == min_point) {
                points[i] = points[n - 1];
                break;
            }
        }
        n--;
    }
    points[0].mass += points[n].mass;
    return points;
}


