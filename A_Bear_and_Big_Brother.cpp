#include <bits/stdc++.h>
using namespace std;

int main(){
    int l, b;
    cin>>l>>b;
    int year = 0;
    while(l <= b){
        l*=3;
        b*=2;
        year++;
    }
    cout<<year<<"\n";

    return 0;
}