#include<bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;

    while(t--){
        int n;
        cin >> n;

        vector<int> arr(n);

        for(int i = 0; i < n; i++){
            cin >> arr[i];
        }

        bool found = false;

        for(int i = n - 1; i >= 1; i--){
            if(arr[i - 1] > arr[i]){

                for(int j = i - 2; j >= 0; j--){

                    if(arr[j] < arr[i - 1]){

                        cout << "YES\n";
                        cout << j + 1 << " " << i << " " << i + 1 << "\n";

                        found = true;
                        goto endLoops;
                    }
                }
            }
        }

        endLoops:

        if(!found){
            cout << "NO\n";
        }
    }

    return 0;
}