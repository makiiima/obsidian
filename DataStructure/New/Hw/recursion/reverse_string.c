void reverseString(char *s, int sSize) {
  // Base case: if the string is empty or has only one character, do nothing.
  if (sSize <= 1) {
    return;
  }

  // Swap the first and last characters.
  char temp = s[0];
  s[0] = s[sSize - 1];
  s[sSize - 1] = temp;

  // Recursive call for the remaining substring, excluding the first and last
  // characters.
  reverseString(s + 1, sSize - 2);
}
