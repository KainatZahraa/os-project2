#include <stdio.h>
#include <unistd.h>
int main() {
printf("Stopwatch (5 seconds):\n");
for (int i = 1; i <= 5; i++) {
printf("%d second(s)\n", i);
sleep(1);
}
return 0;
}
