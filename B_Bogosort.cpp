#include <bits/stdc++.h>
using namespace std;

int main() {
    // Fast input/output
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t; // Number of test cases

    while (t--) {
        int n;
        cin >> n; // Size of the array

        vector<int> a(n);

        // Read the array elements
        for (int &x : a)
            cin >> x;

        // Sort the array in descending order.
        // This arrangement always satisfies the problem's condition.
        sort(a.begin(), a.end(), greater<int>());

        // Print the rearranged array
        for (int x : a)
            cout << x << " ";

        cout << '\n';
    }

    return 0;
}