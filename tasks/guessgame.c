#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
srand(time(0));
int target = rand() % 10 + 1, guess;
printf("Guess a number between 1 and 10: ");
scanf("%d", &guess);
if (guess == target) printf("Correct! The number was %d\n", target);
else printf("Wrong! The number was %d\n", target);
return 0;
}
