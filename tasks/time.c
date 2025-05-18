#include <time.h>
#include <stdio.h>
#include <unistd.h>
int main() {
for (int i = 0; i < 5; i++) {
time_t now = time(NULL);
printf("Current time: %s", ctime(&now));
sleep(1);
}
return 0;
}
