#include <stdio.h>
#include <string.h>
int main() {
char word[] = "oslab", guess[20];
printf("Guess the 5-letter word: ");
scanf("%s", guess);
if (strcmp(word, guess) == 0) printf("Correct!\n");
else printf("Wrong! The word was: %s\n", word);
return 0;
}
