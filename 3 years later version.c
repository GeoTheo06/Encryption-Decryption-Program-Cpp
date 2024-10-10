/* This program shows how I would implement the vigenere encryption now, 3 years
 later. (Original program was made in 2022). Back then it took me more than 3
 days and now it took me less than half an hour. This shows how much I've
 developed since then. It's in C because of Uni but it's ok.
*/
#include <stdio.h>
#include <stdlib.h>

int main() {
  int n, m;
  scanf("%d %d", &n, &m);
  char ch;
  scanf("%c", &ch);
  char *word = (char *)malloc(sizeof(char) * n);
  char *key = (char *)malloc(sizeof(char) * m);
  char *arr = (char *)malloc(sizeof(char) * n);
  for (int i = 0; i < n; i++) {
    scanf("%c", &word[i]);
  }
  scanf("%c", &ch);
  for (int i = 0; i < m; i++) {
    scanf("%c", &key[i]);
  }
  int keyIncr;
  int shift;
  for (int i = 0; i < n; i++) {
    keyIncr = i % m;
    shift = key[keyIncr] - 'A';
    if (word[i] + shift <= 90) {
      arr[i] = word[i] + shift;
    } else {
      arr[i] = (word[i] + shift) % 'Z' + 'A' - 1;
    }
  }
  for (int i = 0; i < n; i++) {
    printf("%c", arr[i]);
  }
}
