struct Fraction {
    int p, q;

    Fraction (int _p, int _q) : p(_p), q(_q) {
    }

    std::strong_ordering operator<=> (const Fraction &oth) const {
        return p * oth.q <=> q * oth.p;
    }
};