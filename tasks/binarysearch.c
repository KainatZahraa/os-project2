#include <stdio.h>
int main() {
int a[10] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20}, val, low = 0, high = 9, mid;
printf("Enter value to search: ");
scanf("%d", &val);
while (low <= high) {
mid = (low + high) / 2;
if (a[mid] == val) { printf("Found at index %d\n", mid); return 0; }
else if (a[mid] < val) low = mid + 1;
else high = mid - 1;
}
printf("Not found\n");
return 0;
}
