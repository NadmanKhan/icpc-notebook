int orientation(Point2D a, Point2D b, Point2D c) {
    auto cross_mag =
        ((b.y - a.y) * (c.x - b.x)) - ((b.x - a.x) * (c.y - b.y));
    if (cross_mag == 0) return 0;    // colinear
    return (cross_mag > 0) ? -1 : 1; // clock- or counterclock-wise
}

bool cw(Point2D a, Point2D b, Point2D c, bool include_collinear) {
    int o = orientation(a, b, c);
    return o < 0 || (include_collinear && o == 0);
}
bool collinear(Point2D a, Point2D b, Point2D c) { return orientation(a, b, c) == 0; }

void convex_hull(vector<Point2D>& a, bool include_collinear = false) {
    Point2D p0 = *min_element(a.begin(), a.end(), [](Point2D a, Point2D b) {
        return make_pair(a.y, a.x) < make_pair(b.y, b.x);
    });
    sort(a.begin(), a.end(), [&p0](const Point2D& a, const Point2D& b) {
        int o = orientation(p0, a, b);
        if (o == 0)
            return (p0.x - a.x) * (p0.x - a.x) + (p0.y - a.y) * (p0.y - a.y) < (p0.x - b.x) * (p0.x - b.x) + (p0.y - b.y) * (p0.y - b.y);
        return o < 0;
    });
    if (include_collinear) {
        int i = (int)a.size() - 1;
        while (i >= 0 && collinear(p0, a[i], a.back())) i--;
        reverse(a.begin() + i + 1, a.end());
    }

    vector<Point2D> st;
    for (int i = 0; i < (int)a.size(); i++) {
        while (st.size() > 1 && !cw(st[st.size() - 2], st.back(), a[i], include_collinear))
            st.pop_back();
        st.push_back(a[i]);
    }

    a = st;
}