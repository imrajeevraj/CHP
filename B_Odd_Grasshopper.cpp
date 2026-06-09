# include <bits/stdc++.h>
using namespace std;

int main(){
    int t ;
    cin >> t ;

    while (t--){
        long long x, n, result = 0;
        cin >> x >> n;
        if (n % 4 == 0){ result = x; }
        else if (n % 4 == 1){
            if(x % 2 != 0){
                result = (x + n);
            }else{
                result = (x - n);
            }
        } 
        else if (n % 4 == 2){
            if(x % 2 != 0){
                result = (x - 1);
            }else{
                result = (x + 1);
            }
        }
        else {
            if(x % 2 != 0){
                result = (x - n - 1);
            }else{
                result = (x + n + 1);
            }
        }
        cout << result << "\n";
    }
    return 0; 
}
