typedef long long ll;
const int N = 2e5 + 5;
vector<int> g[N];
ll sz[N], dist[N], sum[N];

void dfs(int s, int p) {
    sz[s] = 1;
    dist[s] = 0;
    for (int nxt : g[s]) {
        if (nxt == p)
            continue;
        dfs(nxt, s);
        sz[s] += sz[nxt];
        dist[s] += (dist[nxt] + sz[nxt]);
    }
}

void dfs1(int s, int p) {
    if (p != 0) {
        ll my_size = sz[s];
        ll my_contrib = (dist[s] + sz[s]);

        sum[s] = sum[p] - my_contrib + sz[1] - sz[s] + dist[s];
    }
    for (int nxt : g[s]) {
        if (nxt == p)
            continue;
        dfs1(nxt, s);
    }
}

// problem link: https://cses.fi/problemset/task/1133

int main() {
    int n;
    cin >> n;

    for (int i = 1, u, v; i < n; i++)
        cin >> u >> v, g[u].push_back(v), g[v].push_back(u);

    dfs(1, 0);

    sum[1] = dist[1];

    dfs1(1, 0);

    for (int i = 1; i <= n; i++)
        cout << sum[i] << " ";
    cout << endl;

    return 0;
}