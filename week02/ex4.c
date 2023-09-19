#include <stdio.h>
#include <string.h>
#include <ctype.h>

int countOccurrences(char input[], char target) {
  int length = strlen(input);
  int cnt = 0;

  for (int i = 0; i < length; i++) {
    if (tolower(input[i]) == tolower(target)) {
      cnt++;
    }
  }

  return cnt;
}

void countAll(char input[]) {
  int length = strlen(input);

  for (int i = 0; i < length; i++) {
    int cnt = 0;

    for (int j = 0; j < length; j++) {
      if (tolower(input[i]) == tolower(input[j])) {
        cnt++;
      }
    }

    printf("%c:%d, ", tolower(input[i]), cnt);
  }

  printf("\n");
}

int main() {
  char input[256];
  scanf("%s ", input);

  countAll(input);

  char tar = getchar();
  int cnt = countOccurrences(input, tar);
  printf("%c:%d\n", tar, cnt);

  return 0;
}