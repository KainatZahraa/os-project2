#include <time.h>
#include <stdio.h>
int main() {
time_t now = time(NULL);
struct tm *t = localtime(&now);
printf("Date: %02d-%02d-%04d\n", t->tm_mday, t->tm_mon + 1, t->tm_year + 1900);
return 0;
}
