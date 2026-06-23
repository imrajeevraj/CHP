#include <bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin>>n;
    int steps = 0;
    while (n != 0){
        if(n <= 5){
            steps++;
            break;
        }else{
            steps = n / 5;
            n = n % 5;
        }
    }
    cout<<steps<<"\n";

    return 0;
}