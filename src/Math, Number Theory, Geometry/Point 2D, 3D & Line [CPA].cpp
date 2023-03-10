using ftype = double; // or long long, int, etc.
struct Point2 {
    ftype x, y;
};
struct Point3 {
    ftype x, y, z;
};
// Define natural operator overloads for Point2 and Point3
// +, - with another point
// *, / with an ftype scalar
ftype dot(Point2 a, Point2 b) {
    return a.x * b.x + a.y * b.y;
}
ftype dot(Point3 a, Point3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
ftype norm(Point2 a) {
    return dot(a, a);
}
double abs(Point2 a) {
    return sqrt(norm(a));
}
double proj(Point2 a, Point2 b) {
    return dot(a, b) / abs(b);
}
double angle(Point2 a, Point2 b) {
    return acos(dot(a, b) / abs(a) / abs(b));
}
Point3 cross(Point3 a, Point3 b) {
    return Point3(a.y * b.z - a.z * b.y,
                  a.z * b.x - a.x * b.z,
                  a.x * b.y - a.y * b.x);
}
ftype triple(Point3 a, Point3 b, Point3 c) {
    return dot(a, cross(b, c));
}
ftype cross(Point2 a, Point2 b) {
    return a.x * b.y - a.y * b.x;
}
Point2 lines_intersect(Point2 a1, Point2 d1, Point2 a2, Point2 d2) {
    return a1 + cross(a2 - a1, d2) / cross(d1, d2) * d1;
}
Point3 planes_intersect(Point3 a1, Point3 n1, Point3 a2, Point3 n2, Point3 a3, Point3 n3) {
    Point3 x(n1.x, n2.x, n3.x);
    Point3 y(n1.y, n2.y, n3.y);
    Point3 z(n1.z, n2.z, n3.z);
    Point3 d(dot(a1, n1), dot(a2, n2), dot(a3, n3));
    return Point3(triple(d, y, z),
                  triple(x, d, z),
                  triple(x, y, d)) /
           triple(n1, n2, n3);
}
