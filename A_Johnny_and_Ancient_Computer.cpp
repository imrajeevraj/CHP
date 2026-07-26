#include <bits/stdc++.h>
using namespace std;

int main(){

    int t;
    cin >> t;
    while(t--){
        long long a, b;
        cin >> a >> b;

        int cntA = 0, cntB = 0;
        while(a % 2 == 0){ 
            a /= 2; cntA++; 
        }
        while(b % 2 == 0){ 
            b /= 2; cntB++; 
        }

        if(a != b){
            cout << -1 << "\n";
        } else {
            int d = abs(cntA - cntB);
            cout << (d + 2) / 3 << "\n";
        }
    }

    return 0;
}