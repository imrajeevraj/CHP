# include <bits/stdc++.h>
using namespace std;

int main (){
     int t;
     cin>>t;

     while(t--){
        string s;
        cin>>s;
        int zeros = count(s.begin(), s.end(), '0');
        int ones  = count(s.begin(), s.end(), '1');
        int m = min(zeros,ones);
        if(m % 2 != 0){
            cout<<"DA"<<"\n";
        }else{
            cout<<"NET"<<"\n";
        }
        
     }

    return 0;
}