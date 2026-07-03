#include <bits/stdc++.h>
using namespace std;

int main(){
    int t; 
    scanf("%d", &t);
    while (t--) {
        int n; 
        char buf[200005];
        scanf("%d %s", &n, buf);
        string s(buf);

        int left = 0, right = n - 1;
        while (left < n && s[left] == '0') left++;
        while (right >= 0 && s[right] == '1') right--;

        if (left > right) {
            printf("Bob\n");
            continue;
        }

        bool allEven = true;
        int run = 1;
        for (int i = left; i < right; i++) {
            if (s[i+1] == s[i]) run++;
            else {
                if (run % 2 == 1) allEven = false;
                run = 1;
            }
        }
        if (run % 2 == 1) allEven = false;

        printf(allEven ? "Bob\n" : "Alice\n");
    }
}