#include <stdio.h>

int main() {
char filename[100];
printf("Enter filename to delete: ");
scanf("%s", filename);

if (remove(filename) == 0) {
printf("File '%s' deleted successfully.\n", filename);
} else {
perror("Error deleting file");
}

return 0;
}

