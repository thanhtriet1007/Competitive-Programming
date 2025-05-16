#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char a[1002];

int main() {
   
    scanf("%s", a);
    char tmp[] = "!@#$%^&*()-+";
    int cntLower = 0, cntUpper = 0, cntNumber = 0, cntSpec = 0;
    int len = strlen(a);
    if (len < 8) {
        printf("NO");
        return 0;
    }
    int ok = 1;
    int tmpLen = strlen(tmp);
    for (int i = 0; i < len; ++i) {
        if (a[i] == a[i + 1]) {
            ok = 0;
        }
        if (a[i] >= 'a' && a[i] <= 'z') ++cntLower;
        if (a[i] >= 'A' && a[i] <= 'Z') ++cntUpper;
        if (a[i] >= '0' && a[i] <= '9') ++cntNumber;
        for (int j = 0; j < tmpLen; ++j) {
            if (a[i] == tmp[j]) ++cntSpec;
        }
    }
    /*printf("%d %d %d %d ", cntLower, cntUpper, cntNumber, cntSpec);*/
    if (ok && cntLower > 0 && cntUpper > 0 && cntNumber > 0 && cntSpec > 0) printf("YES");
    return 0;
}