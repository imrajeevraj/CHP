#include <bits/stdc++.h>
using namespace std;

int main() {
    int y;
    cin >> y;

    while (true) {
        y++;
        string s = to_string(y);
        set<char> st(s.begin(), s.end());
        if (st.size() == 4) {
            cout << y << '\n';
            break;
        }
    }

    return 0;
}