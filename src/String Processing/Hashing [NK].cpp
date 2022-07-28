namespace roll_hash_util {
    constexpr int MaxDim = 4;
    constexpr array<int, MaxDim> primes = {257, 263, 269, 271};
    constexpr array<int, MaxDim> primes_minus1e9 = {7, 9, 21, 33};
    constexpr int modulus(int dim) { return primes_minus1e9[dim] + 1e9; }
    array<vector<int>, MaxDim> p_pow = {};
    void resize(int n) {
        for (int d = 0; d < MaxDim; ++d) {
            auto& pp = p_pow[d];
            if (pp.empty()) {
                pp.push_back(1);
            }
            while (pp.size() < n) {
                pp.push_back(((long long)pp.back() * primes[d]) % modulus(d));
            }
        }
    }
} // namespace roll_hash_util

template <int Dim = 2>
class Rolling_hash {
private:
    size_t len_;
    array<vector<int>, Dim> pref_hash_;
    array<vector<int>, Dim> suff_hash_;

public:
    template <class InputIter>
    Rolling_hash(InputIter first, InputIter last, bool bidir = false) {
        len_ = distance(first, last);
        roll_hash_util::resize(len_);
        
        for (int d = 0; d < Dim; ++d) {
            vector<int>& ph = pref_hash_[d];
            const int m = roll_hash_util::modulus(d);
            const long long p = roll_hash_util::primes[d];
            ph.resize(len_ + 1);
            ph[0] = 0;
            auto it = first;
            for (int i = 0; i < len_; ++i) {
                ph[i + 1] = (((ph[i] * p) % m) + *it) % m;
                ++it;
            }
        }

        if (!bidir) return;
        
        for (int d = 0; d < Dim; ++d) {
            vector<int>& sh = suff_hash_[d];
            const int m = roll_hash_util::modulus(d);
            const long long p = roll_hash_util::primes[d];
            sh.resize(len_ + 1);
            sh[len_] = 0;
            auto it = prev(last);
            for (int i = len_; i > 0; --i) {
                sh[i - 1] = ((sh[i] * p) % m + *it) % m;
                --it;
            }
        }
    }

    array<int, Dim> get(size_t i, size_t n) const {
        array<int, Dim> res;
        for (int d = 0; d < Dim; ++d) {
            const vector<int>& ph = pref_hash_[d];
            const int m = roll_hash_util::modulus(d);
            const long long pp = roll_hash_util::p_pow[d][n];
            res[d] = ((ph[i + n] - (ph[i] * pp) % m) % m + m) % m;
        }
        return res;
    }

    array<int, Dim> getrev(size_t i, size_t n) const {
        assert(!suff_hash_[0].empty());
        array<int, Dim> res;
        for (int d = 0; d < Dim; ++d) {
            const vector<int>& sh = suff_hash_[d];
            const int m = roll_hash_util::modulus(d);
            const long long pp = roll_hash_util::p_pow[d][n];
            res[d] = ((sh[i] - (sh[i + n] * pp) % m) % m + m) % m;
        }
        return res;
    }

    size_t size() const { return len_; }

    array<int, Dim> pref(size_t i) const {
        array<int, Dim> res;
        for (int d = 0; d < Dim; ++d) {
            res[d] = pref_hash_[d][i];
        }
        return res;
    }

    array<int, Dim> suff(size_t i) const {
        array<int, Dim> res;
        for (int d = 0; d < Dim; ++d) {
            res[d] = suff_hash_[d][i];
        }
        return res;
    }
};
