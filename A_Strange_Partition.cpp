#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n,x;
        cin>>n>>x;
        long long max_beauty = 0;
        long long min_beauty = 0;
        long long sum = 0;
        for(int i = 0; i < n; i++){
            int j;
            cin>>j;
            max_beauty+= (j + x -1)/x;
            sum += j;
        }
        min_beauty = (sum+x - 1)/x;

        cout<< min_beauty<<" "<<max_beauty<<"\n";
    }
    return 0;
}