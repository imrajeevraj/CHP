#include <stdio.h>
#include <string.h>

int main() {
    int tc;
    scanf("%d", &tc);

    while (tc--) {
        char s[35], t[35];
        scanf("%s %s", s, t);

        int cnt[26] = {0};
        int j = strlen(t) - 1;
        int ok = 1;

        for (int i = strlen(s) - 1; i >= 0; i--) {
            if (j >= 0 && s[i] == t[j]) {
                j--;
            } else {
                cnt[s[i] - 'A']++;
            }

            if (j >= 0 && cnt[t[j] - 'A'] > 0) {
                ok = 0;
                break;
            }
        }

        if (j >= 0) ok = 0;

        printf(ok ? "YES\n" : "NO\n");
    }

    return 0;
}