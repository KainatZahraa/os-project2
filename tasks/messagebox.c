#include <stdio.h>
int main() {
char msg[100];
printf("Enter your message: ");
scanf(" %[^\n]", msg);
printf("Message recieved: \"%s\"\n", msg);
return 0;
}
