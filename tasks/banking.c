#include <stdio.h>
int main() {
int balance = 1000, withdraw;
printf("Banking System\nCurrent Balance: %d\nEnter amount to withdraw: ", balance);
scanf("%d", &withdraw);
if (withdraw <= balance) {
balance -= withdraw;
printf("Withdrawal successful. New balance: %d\n", balance);
} else {
printf("Insufficient balance.\n");
}
return 0;
}

