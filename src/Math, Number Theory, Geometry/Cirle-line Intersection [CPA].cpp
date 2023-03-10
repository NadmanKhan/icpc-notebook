// assume the cirlce is centered at the origin
vector<pair<double, double>> circle_line_intersect(double r, double a, double b, double c) {
    double x0 = -a * c / (a * a + b * b), y0 = -b * c / (a * a + b * b);
    if (c * c > r * r * (a * a + b * b) + EPS) {
        return {};
    } else if (abs(c * c - r * r * (a * a + b * b)) < EPS) {
        return {make_pair(x0, y0)};
    } else {
        double d = r * r - c * c / (a * a + b * b);
        double mult = sqrt(d / (a * a + b * b));
        double ax, ay, bx, by;
        ax = x0 + b * mult;
        bx = x0 - b * mult;
        ay = y0 - a * mult;
        by = y0 + a * mult;
        return {make_pair(ax, ay), make_pair(bx, by)};
    }
}