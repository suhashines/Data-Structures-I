#include <bits/stdc++.h>
using namespace std;
using clk = chrono::high_resolution_clock;
using ns = chrono::duration<double, std::milli>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> sizes = {1000000, 2000000, 4000000, 8000000, 16000000}; // adjust to machine
    cout << "n,vector_random_access_ms,vector_insert_front_ms,list_insert_front_ms\n";

    std::mt19937 rng(12345);
    for (int n : sizes) {
        // prepare data
        vector<int> v;
        v.reserve(n);
        for (int i = 0; i < n; ++i) v.push_back(i);

        // 1) random access on vector: 1,000,000 reads
        volatile int sink = 0;
        int reads = 1000000;
        uniform_int_distribution<int> dist(0, n-1);
        auto t0 = clk::now();
        for (int i = 0; i < reads; ++i) {
            int idx = dist(rng);
            sink += v[idx]; // O(1)
        }
        auto t1 = clk::now();
        double rand_access_ms = ns(t1 - t0).count();

        // 2) insert at front on vector: do m inserts into copy
        int m = min(5000, n/10 + 1); // keep it reasonable
        vector<int> vcopy = v;
        auto t2 = clk::now();
        for (int i = 0; i < m; ++i) {
            vcopy.insert(vcopy.begin(), -i); // O(n) each
        }
        auto t3 = clk::now();
        double vec_insert_front_ms = ns(t3 - t2).count();

        // 3) insert at front on std::list: do m inserts
        list<int> L(v.begin(), v.end());
        auto t4 = clk::now();
        for (int i = 0; i < m; ++i) {
            L.push_front(-i); // O(1) each
        }
        auto t5 = clk::now();
        double list_insert_front_ms = ns(t5 - t4).count();

        cout << n << ',' 
             << rand_access_ms << ',' 
             << vec_insert_front_ms << ','
             << list_insert_front_ms << '\n';
    }
    return 0;
}