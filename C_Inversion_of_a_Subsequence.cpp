#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {

        int n;
        cin >> n;

        vector<int> a(n);
        vector<int> b(n);

        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

    
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }

        bool same = true;        
        bool allZero = true;     
        bool allOne = true;      
        int parity = 0;          

        for (int i = 0; i < n; i++) {

            
            if (a[i] != b[i]) {
                same = false;
                parity = parity ^ a[i];
            }

            
            if (a[i] != 0) {
                allZero = false;
            }

            
            if (b[i] != 1) {
                allOne = false;
            }
        }

        if (same) {
            cout << 0 << endl;
        }
        else if (allZero) {
            cout << -1 << endl;
        }
        else if (allOne) {
            cout << -1 << endl;
        }
        else if (parity == 1) {
            cout << 1 << endl;
        }
        else {
            cout << 2 << endl;
        }
    }

    return 0;
}