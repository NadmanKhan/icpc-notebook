template <typename T>
struct Trie_Bits {
    static constexpr int num_bits = std::numeric_limits<T>::digits;

    struct Node {
        int count = 0;
        int trail[2] = {-1, -1};
    };

    vector<Node> container;

    Trie_Bits() {
        container.emplace_back();
    }

    bool contains(T x) {
        int v = 0;
        for (int i = num_bits - 1; i >= 0; i--) {
            int bit = (x >> i) & 1;
            if (container[v].trail[bit] == -1) {
                return false;
            }
            v = container[v].trail[bit];
        }
        return true;
    }

    bool insert(T x) {
        if (contains(x)) {
            return false;
        }
        int v = 0;
        for (int i = num_bits - 1; i >= 0; i--) {
            int bit = (x >> i) & 1;
            if (container[v].trail[bit] == -1) {
                container[v].trail[bit] = container.size();
                container.emplace_back();
            }
            v = container[v].trail[bit];
            container[v].count++;
        }
        return true;
    }

    void erase(T x) {
        int v = 0;
        for (int i = num_bits - 1; i >= 0; i--) {
            int bit = (x >> i) & 1;
            v = container[v].trail[bit];
            container[v].count--;
        }
    }
};