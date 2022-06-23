template <class T>
vector<vector<T>> power_set(const vector<T>& vec) {
    vector<vector<T>> res;
    list<T> buf;
    function<void(int)> recurse = [&](int i) -> void {
        if (i == vec.size()) {
            res.emplace_back(buf.begin(), buf.end());
            return;
        }
        recurse(i + 1);
        buf.push_back(vec[i]), recurse(i + 1), buf.pop_back();
    };
    recurse(0);
    return res;
}
