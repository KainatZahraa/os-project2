#include <stdio.h>
int main() {
int a, b; char op;
printf("Calculator\nEnter expression (e.g., 5 + 3): ");
scanf("%d %c %d", &a, &op, &b);
switch (op) {
case '+': printf("Result: %d\n", a + b); break;
case '-': printf("Result: %d\n", a - b); break;
case '*': printf("Result: %d\n", a * b); break;
case '/': b != 0 ? printf("Result: %.2f\n", (float)a / b) : printf("Cannot divide by 0\n"); break;
default: printf("Invalid operator\n");
}
return 0;
}
