#include <stdio.h>

int main() {
char filename[100];
printf("Enter filename to create: ");
scanf("%s", filename);

FILE *f = fopen(filename, "w");
if (f) {
fprintf(f, "File '%s' created by CreateFile task.\n", filename);
fclose(f);
printf("File '%s' created successfully.\n", filename);
} else {
printf("Error creating file '%s'.\n", filename);
}

return 0;
}

