namespace roll_hash_util {
    constexpr int MaxDim = 4;
    constexpr array<int, MaxDim> primes = {257, 263, 269, 271};
    constexpr array<int, MaxDim> primes_minus1e9 = {7, 9, 21, 33};
    constexpr int modulus(int dim) { return primes_minus1e9[dim] + 1e9; }
    array<vector<int>, MaxDim> p_pow = {};
    void resize(int len) {
        for (int d = 0; d < MaxDim; ++d) {
            auto& pp = p_pow[d];
            if (pp.empty()) {
                pp.push_back(1);
            }
            while (pp.size() < len) {
                pp.push_back(((long long)pp.back() * primes[d]) % modulus(d));
            }
        }
    }
} // namespace roll_hash_util

template <int Dim = 2>
struct Rolling_hash {
    array<vector<int>, Dim> pref_hash;
    array<vector<int>, Dim> suff_hash;

    Rolling_hash() {}

    template <class InputIter>
    Rolling_hash(InputIter first, InputIter last, bool bidir = false) {
        hash(first, last);
        if (bidir) {
            hash_rev(first, last);
        }
    }

    template <class InputIter>
    void hash(InputIter first, InputIter last) {
        const auto len = distance(first, last);
        roll_hash_util::resize(len);
        for (int d = 0; d < Dim; ++d) {
            vector<int>& ph = pref_hash[d];
            const int m = roll_hash_util::modulus(d);
            const long long p = roll_hash_util::primes[d];
            ph.resize(len + 1);
            ph[0] = 0;
            auto it = first;
            for (int i = 0; i < len; ++i) {
                ph[i + 1] = (((ph[i] * p) % m) + *it) % m;
                ++it;
            }
        }
    }

    template <class InputIter>
    void hash_rev(InputIter first, InputIter last) {
        const auto len = distance(first, last);
        roll_hash_util::resize(len);
        for (int d = 0; d < Dim; ++d) {
            vector<int>& sh = suff_hash[d];
            const int m = roll_hash_util::modulus(d);
            const long long p = roll_hash_util::primes[d];
            sh.resize(len + 1);
            sh[len] = 0;
            auto it = prev(last);
            for (int i = len; i > 0; --i) {
                sh[i - 1] = ((sh[i] * p) % m + *it) % m;
                --it;
            }
        }
    }

    array<int, Dim> get(int from, int len) const {
        assert(!pref_hash[0].empty());
        array<int, Dim> res;
        for (int d = 0; d < Dim; ++d) {
            const vector<int>& ph = pref_hash[d];
            const int m = roll_hash_util::modulus(d);
            const long long pp = roll_hash_util::p_pow[d][len];
            res[d] = ((ph[from + len] - (ph[from] * pp) % m) % m + m) % m;
        }
        return res;
    }

    array<int, Dim> getrev(int from, int len) const {
        assert(!suff_hash[0].empty());
        array<int, Dim> res;
        for (int d = 0; d < Dim; ++d) {
            const vector<int>& sh = suff_hash[d];
            const int m = roll_hash_util::modulus(d);
            const long long pp = roll_hash_util::p_pow[d][len];
            res[d] = ((sh[from] - (sh[from + len] * pp) % m) % m + m) % m;
        }
        return res;
    }

    int size() const { return pref_hash[0].size() - 1; }
};
