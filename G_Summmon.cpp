#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;

// Minimal 128-bit unsigned accumulator: value = hi * 2^64 + lo
struct U128 {
    ull hi = 0, lo = 0;
    void add(ull x) {
        ull newlo = lo + x;
        if (newlo < lo) hi++;   // overflow -> carry into hi
        lo = newlo;
    }
};

void printU128(U128 v, ostream &os) {
    if (v.hi == 0) { os << v.lo; return; }
    string digits;
    while (v.hi != 0 || v.lo != 0) {
        ull newhi = v.hi / 10;
        ull rem = v.hi % 10;
        ull newlo = 0;
        // long-divide (rem:lo) by 10, bit by bit
        for (int bit = 63; bit >= 0; bit--) {
            rem = (rem << 1) | ((v.lo >> bit) & 1ULL);
            if (rem >= 10) {
                rem -= 10;
                newlo |= (1ULL << bit);
            }
        }
        digits.push_back(char('0' + (int)rem));
        v.hi = newhi;
        v.lo = newlo;
    }
    reverse(digits.begin(), digits.end());
    os << digits;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int tt; cin >> tt;
    while (tt--) {
        int n; cin >> n;
        vector<ll> a(n);
        for (auto &x : a) cin >> x;

        U128 ans;
        vector<int> st; // monotonic stack of indices

        for (int i = 0; i < n; i++) {
            while (!st.empty() && a[i] % a[st.back()] != 0) {
                ll g = a[i] % a[st.back()];
                ll d = min(g, a[st.back()] - g);
                ans.add((ull)(n - i) * (ull)d);
                st.pop_back();
            }
            st.push_back(i);
        }
        printU128(ans, cout);
        cout << '\n';
    }
}