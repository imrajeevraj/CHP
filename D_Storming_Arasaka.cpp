#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000001;
int spf[MAXN];      
int bigOmega[MAXN]; 
int smallOmega[MAXN]; 

int main(){

    for (int i = 2; i < MAXN; i++){
        if (spf[i] == 0){
            for (long long j = i; j < MAXN; j += i)
                if (spf[j] == 0) spf[j] = i;
        }
    }

    bigOmega[1] = 0;
    smallOmega[1] = 0;
    for (int i = 2; i < MAXN; i++){
        int p = spf[i];
        int rest = i / p;
        bigOmega[i] = bigOmega[rest] + 1;
        if (spf[rest] == p) smallOmega[i] = smallOmega[rest];
        else smallOmega[i] = smallOmega[rest] + 1;
    }

    int t;
    cin >> t;
    while (t--){
        int n;
        cin >> n;
        cout << (smallOmega[n] + bigOmega[n] - 1) << "\n";
    }
    return 0;
}