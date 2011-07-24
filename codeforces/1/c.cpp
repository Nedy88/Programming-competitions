#include <iostream>
#include <complex>
#include <cmath>
using namespace std;

#define eps 1e-4

typedef complex<double> point;
#define pi acos(-1.0)

double cross(point a, point b) {
    return imag(conj(a) * b);
}

double dot(point a, point b) {
    return real(a * conj(b));
}

struct line {
    double A, B, C;
};

line get_symmetry_line(point a, point b) {
    line ret;
    point c = b - a;
    ret.A = real(c);
    ret.B = imag(c);
    c = (a + b) / 2.0;
    ret.C = - ret.A * real(c) - ret.B * imag(c);
    return ret;
}

bool is_equal(double a, double b) {
    double dist = fabs(a - b);
    return dist < eps;
}

point get_intersection_point(line a, line b) {
    if (is_equal(a.A, 0.0)) {
        swap(a,b);
    }
    double coef = b.A/a.A;
    double x,y;
    y = (coef * a.C - b.C) / (b.B - coef * a.B);
    x = -(a.B*y + a.C)/a.A;
    return point(x,y);
}

double get_angle_between_vectors(point a, point b) {
    double RR = norm(a);
    double sinphi = fabs(cross(a,b)) / RR;
    double phi = asin(sinphi);
    if (dot(a,b) < 0.0) {
        phi = pi - phi;
    }
    return phi;
}

bool is_integer(double a) {
    int probe = int(a);
    if (is_equal(a, probe) || is_equal(a, probe+1) || is_equal(a, probe-1)) return true;
    return false;
}

bool tryout(int size, double angle) {
    double phi = (2.0 * pi) / size;
    if (is_integer(angle/phi)) return true;
    return false;
}

double solve(point a, point b, point c) {
    line line1, line2;
    line1 = get_symmetry_line(a, b);
    line2 = get_symmetry_line(b, c);
    point o = get_intersection_point(line1, line2);
    double phi1 = get_angle_between_vectors(a - o, b - o);
    double phi2 = get_angle_between_vectors(b - o, c - o);
    int size = 0;
    for (int i = 3;; ++i) {
        if (tryout(i, phi1) && tryout(i, phi2)) {
            size = i;
            break;
        }
    }
    double phi = (2.0 * pi) / size;
    double RR = norm(a - o);
    return 0.5 * RR * sin(phi) * (double)size;
}

int main() {
    point pts[3];
    for (int i = 0; i < 3; ++i) {
        double x,y;
        cin >> x >> y;
        pts[i] = point(x,y);
    }
    double ret = solve(pts[0], pts[1], pts[2]);
    cout.setf(ios::fixed);
    cout.precision(9);
    cout << ret << endl;
    return 0;
}
