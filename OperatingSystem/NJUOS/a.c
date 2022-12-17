#include "thread.h"

void Ta() { while (1) { printf("a"); } }
void Tb() { while (1) { printf("b"); } }
void Tc() { while (1) { printf("c"); } }
void Td() { while (1) { printf("d"); } }

int main() {
  create(Ta);
  create(Tb);
  create(Tc);
  create(Td);
}
