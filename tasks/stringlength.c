#include <stdio.h>
#include <string.h>
int main() {
char s[100];
printf("Enter a string: ");
scanf("%s", s);
printf("Length: %lu\n", strlen(s));
return 0;
}
