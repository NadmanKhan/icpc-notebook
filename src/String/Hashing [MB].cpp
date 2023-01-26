const int PRIMES[] = {2147462393, 2147462419, 2147462587, 2147462633};

// ll base_pow,base_pow_1;
ll base1 = 43, base2 = 47, mod1 = 1e9 + 7, mod2 = 1e9 + 9;

struct Hash {
public:
    vector<int> base_pow, f_hash, r_hash;
    ll base, mod;

    Hash() {}
    // Update it make it more dynamic like segTree class and DSU
    Hash(int mxSize, ll base, ll mod) // Max size
    {
        this->base = base;
        this->mod = mod;
        base_pow.resize(mxSize + 2, 1), f_hash.resize(mxSize + 2, 0), r_hash.resize(mxSize + 2, 0);

        for (int i = 1; i <= mxSize; i++) {
            base_pow[i] = base_pow[i - 1] * base % mod;
        }
    }

    void init(string s) {
        int n = s.size();

        for (int i = 1; i <= n; i++) {
            f_hash[i] = (f_hash[i - 1] * base + int(s[i - 1])) % mod;
        }

        for (int i = n; i >= 1; i--) {
            r_hash[i] = (r_hash[i + 1] * base + int(s[i - 1])) % mod;
        }
    }

    int forward_hash(int l, int r) {
        int h = f_hash[r + 1] - (1LL * base_pow[r - l + 1] * f_hash[l]) % mod;
        return h < 0 ? mod + h : h;
    }

    int reverse_hash(int l, int r) {
        int h = r_hash[l + 1] - (1LL * base_pow[r - l + 1] * r_hash[r + 2]) % mod;
        return h < 0 ? mod + h : h;
    }
};

class DHash {
public:
    Hash sh1, sh2;
    DHash() {}

    DHash(int mx_size) {
        sh1 = Hash(mx_size, base1, mod1);
        sh2 = Hash(mx_size, base2, mod2);
    }

    void init(string s) {
        sh1.init(s);
        sh2.init(s);
    }

    ll forward_hash(int l, int r) {
        return (ll(sh1.forward_hash(l, r)) << 32) | (sh2.forward_hash(l, r));
    }

    ll reverse_hash(int l, int r) {
        return ((ll(sh1.reverse_hash(l, r)) << 32) | (sh2.reverse_hash(l, r)));
    }
};