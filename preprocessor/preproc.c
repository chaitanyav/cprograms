#include <stdio.h>
#define TWO 2
#define OW "Consistency is the last refuge of the unimagina\
tive. - Oscar Wilde"

#define FOUR TWO*TWO
#define PX printf("%d\n", x)
#define HAL 'z'
#define HAP "Z"
#define SQUARE(x) ((x)*(x))
#define PRINTSQUARE(x) printf("%d is the square of " #x"\n", ((x)*(x)))
#define XNAME(n) x ## n
#define PR(...) printf(__VA_ARGS__)
#define FOO
#ifndef FOO
#error This is some error
#endif

int main(int argc, char *argv[]) {
  char *s = HAP;
  char c = HAL;
  int x = TWO;
  int XNAME(1) = 14;
  int XNAME(2) = 20;
  x = FOUR;
  PX;
  printf("%s\n", OW);
  printf("TWO: OW\n");
  PR("%d\n", SQUARE(2));
  PRINTSQUARE(3);
  printf("%s %s\n", __DATE__, __TIME__);
  printf("%s\n", __func__);
  return 0;
}
