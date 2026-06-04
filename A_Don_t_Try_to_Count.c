#include <stdio.h>
#include <string.h>

int main() {

    int t;
    scanf("%d", &t);

    while (t--) {

        int n, m;
        scanf("%d %d", &n, &m);

        char x[300], s[300];

        scanf("%s", x);
        scanf("%s", s);

        int ans = 0;

        while (strlen(x) < strlen(s)) {

            char temp[300];

            strcpy(temp, x);
            strcat(x, temp);

            ans++;
        }

        if (strstr(x, s) != NULL) {
            printf("%d\n", ans);
        }
        else {

            char temp[300];

            strcpy(temp, x);
            strcat(x, temp);

            ans++;

            if (strstr(x, s) != NULL)
                printf("%d\n", ans);
            else
                printf("-1\n");
        }
    }

    return 0;
}