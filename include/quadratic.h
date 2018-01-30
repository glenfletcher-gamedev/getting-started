#ifndef QUADRATIC_H
#define QUADRATIC_H

inline bool evaluateQuadraticRangeMin(float a, float b, float c, float x_min, float x_max, float &x) {
    float det = b*b - 4*a*c;
    if (det >= 0) {
        float f = 1.f/(2*a);
        float rdet = sqrt(det);
        float x1 = -(rdet+b)*f;
        float x2 = (rdet-b)*f;
        if (x1 >= x_min and x1 <= x_max and x2 >= x_min and x2 <= x_max)
        {
            if (x1 < x2) x = x1;
            else x = x2;
            return true;
        }
        else if (x1 >= x_min and x1 <= x_max)
        {
            if (x1 < x2) x = x1;
            else x = x_min;
            return true;
        }
        else if (x2 >= x_min and x2 <= x_max)
        {
            if (x1 < x2) x = x_min;
            else x = x2;
            return true;
        }
    }
    return false;
}

#endif // QUADRATIC_H
