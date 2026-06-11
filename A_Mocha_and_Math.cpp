# include <bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;

    while(t--){
        int n;
        cin>>n;
        vector<int>array(n);
        
        for(int i = 0; i < n; i++){
            cin>>array[i];


        }
        int max = array[0];
        for(int i = 0; i < n ; i++){
            max &= array[i];
        }
        cout<< max<<"\n";
    }
    return 0;
}