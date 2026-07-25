#include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;
    while (t--) {
        int n;
        string s;
        cin >> n >> s;

        int balance = 0, ans = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '(') {
                balance++;
            } else {
                if (balance > 0) balance--;
                else ans++; 
            }
        }
        cout << ans << "\n";
    }

    return 0;
}