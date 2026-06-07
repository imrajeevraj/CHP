#include<bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin>>t;
    
    while (t--){
        int n;
        cin >> n;
        vector<int>arr(n);
        for(int i = 0; i < n; i++){
            cin >> arr[i];
        }
        unordered_map<int,int>freq;

        int max_freq = 0;
        
        for(int i: arr){
            freq[i]++;
            if(freq[i] > max_freq){
                max_freq = freq[i];
            }
        }
        int ans = 0;
        while(max_freq < n) {
            ans++;                   

            int add = min(max_freq, n - max_freq);

            ans += add;              
            max_freq += add;
        }
        cout << ans << "\n";
    }
    return 0;
    
}