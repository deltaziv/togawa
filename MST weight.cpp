#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 998244353;

ll modpow(ll a, unsigned long long e){
    ll r = 1;
    a %= MOD;
    while(e){
        if(e & 1) r = (r * a) % MOD;
        a = (a * a) % MOD;
        e >>= 1;
    }
    return r;
}

struct DSU {
    vector<int> p;
    vector<unsigned long long> sz;
    DSU(int n): p(n+1), sz(n+1,1ULL){
        for(int i=1;i<=n;i++) p[i]=i;
    }
    int find(int x){ return p[x]==x?x:p[x]=find(p[x]); }
    bool unite(int a,int b, unsigned long long &sa, unsigned long long &sb){
        a = find(a); b = find(b);
        if(a==b) return false;
        sa = sz[a]; sb = sz[b];
        if(sz[a] < sz[b]) swap(a,b);
        p[b] = a;
        sz[a] += sz[b];
        return true;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    long long S;
    if(!(cin >> n >> S)) return 0;
    vector<tuple<int,int,int>> edges;
    edges.reserve(n-1);
    for(int i=0;i<n-1;i++){
        int u,v,w; cin >> u >> v >> w;
        edges.emplace_back(w,u,v);
    }
    sort(edges.begin(), edges.end()); // by w asc

    DSU dsu(n);
    ll result = 1;

    for(auto &t : edges){
        int w,u,v;
        tie(w,u,v) = t;
        unsigned long long sa=0, sb=0;
        if(!dsu.unite(u,v, sa, sb)) continue;
        unsigned long long cnt = sa * sb; 
        if(w <= S){
           
            if(cnt > 0) cnt -= 1ULL;
            if(cnt == 0ULL) continue;
            ll base = (S - w + 1) % MOD;
            result = result * modpow(base, cnt) % MOD;
        }
    }

    cout << result % MOD << "\n";
    return 0;
}