# include<bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;

    while (t--){
        long long n;
        cin>>n;
        bool odd_divisor = false;
        while (n > 1){
            if(n % 2 == 0){
                n/=2;
            }else{
               odd_divisor = true;
               break; 
            }
        }

        if(odd_divisor){
            cout<<"YES\n";
        }else{
            cout<<"NO\n";
        }
        
    }
    

    return 0;
}