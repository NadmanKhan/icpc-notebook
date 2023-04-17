int orientation(const Point& p, const Point& q, const Point& r) {
    /// ||cross(PQ, QR)|| > 0 => left turn (counter-clockwise) =>  1
    /// ||cross(PQ, QR)|| < 0 => right turn (clockwise)        => -1
    /// ||cross(PQ, QR)|| = 0 => straight line (collinear)     =>  0

    /// PQ = (Qx - Px, Qy - Py)
    /// QR = (Rx - Qx, Ry - Qy)
    /// cross(PQ, QR) = (Qx - Px) * (Ry - Qy) - (Qy - Py) * (Rx - Qx)

    auto v = (q.x - p.x) * (r.y - q.y) - (q.y - p.y) * (r.x - q.x);
    return (v > 0) - (v < 0);
}
