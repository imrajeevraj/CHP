#include <bits/stdc++.h>
using namespace std;

int main(){
    int k,n,w;
    cin>>k>>n>>w;
    int price = k * w * (w + 1) / 2;
    cout << max(0, price - n) << "\n";
    return 0;
}