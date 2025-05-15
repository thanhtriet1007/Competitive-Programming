#include <stdio.h>
#include <math.h>
#include <string.h>

char ch[100];

int main() {    
    scanf("%s", ch);
    int sum = 0, len = strlen(ch);
    for (int i = 0; ch[i] != '\0'; ++i) {
        sum += (int)(ch[i] - 0);
    }
    printf("%d", sum / len);
    return 0;
}