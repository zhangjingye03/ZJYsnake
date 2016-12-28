#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define SIZE 8
#define INITS 2
#define LIMIT SIZE * SIZE / 2
#define random(x) (rand()%x)

char tail = INITS - 1;
char hasFood = 0; char fx, fy;

class snakeBlock {
  public:
    char x;
    char y;
    char d; //0 none 1 up 2 down 3 left 4 right
    snakeBlock () {
      x = -1; y = -1; d = 0;
    }
    snakeBlock (char ix, char iy, char id) {
      x = ix; y = iy; d = id;
    }
    void set(char ix, char iy, char id) {
      x = ix; y = iy; d = id;
    }
};

void printSnake (snakeBlock (*sb)[SIZE * 2]) { // []'s priorty is higher than *. Firstly point to the addr, and then define the type. This is a (SIZE*2)-array with sb-pointer in it.
  char map[SIZE][SIZE];
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      map[i][j] = ' ';
    }
  }
  if (hasFood == 1) map[fy][fx] = 'F';
  for (int i = 0; i <= tail; i++) { // tail is the last element
    map[(*sb)[i].y][(*sb)[i].x] = ( i == 0 ) ? 'O' : 'o'; //*sb[i].x || sb[i]->x
  }
  for (int i = 0; i < SIZE; i++) {
    printf("|");
    for (int j = 0; j < SIZE; j++) {
      printf(" %c", map[i][j]);
    }
    printf(" |\n");
  }
}

void moveBlock (snakeBlock* sCurrent, snakeBlock* sLast) {
  if (sCurrent == sLast) { // i == 0
    if (sCurrent->d == 4) { //right
      sCurrent->x++;
    } else if (sCurrent->d == 3) { //left
      sCurrent->x--;
    } else if (sCurrent->d == 2) { //down
      sCurrent->y++;
    } else { //up
      sCurrent->y--;
    }
  } else { // last block -> current
    sCurrent->x = sLast->x;
    sCurrent->y = sLast->y;
    sCurrent->d = sLast->d;
  }
}

char moveSnake (snakeBlock (*sb)[SIZE * 2], char dir) {
  char jx = (*sb)[0].x, jy = (*sb)[0].y;
  if (dir == 4) { //right
    if ((*sb)[0].d == 3) return 2; // contradict
    jx++;
  } else if (dir == 3) { //left
    if ((*sb)[0].d == 4) return 2; // contradict
    jx--;
  } else if (dir == 2) { //down
    if ((*sb)[0].d == 1) return 2; // contradict
    jy++;
  } else if (dir == 1) { //up
    if ((*sb)[0].d == 2) return 2; // contradict
    jy--;
  }
  if (jx >= SIZE || jx < 0 || jy >= SIZE || jy < 0) return 1;
  if (jx == fx && jy == fy && hasFood == 1) { // gain food~
    (*sb)[tail + 1].x = (*sb)[tail].x; (*sb)[tail + 1].y = (*sb)[tail].y; hasFood = 2; /*tail++; if now append, it is difficult to operate then.*/
  }
  (*sb)[0].d = dir;
  for (int i = tail; i >= 0; i--) {
    moveBlock (&(*sb)[i], (i == 0) ? &(*sb)[i] : &(*sb)[i - 1]);
    if (i != 0 && (*sb)[i].x == jx && (*sb)[i].y == jy) return 3; // crash into self!
  }
  if (hasFood == 2) { hasFood = 0; if (++tail == LIMIT) return 4; } // after move the snake, we append the tail up.
  return 0;
}

void printFrameX() {
  printf("|");
  for (int i = 0; i < SIZE; i++) {
    printf(" -");
  }
  printf(" |\n");
}

int main() {
  snakeBlock s[LIMIT]; // this array contains (SIZE*2) snakeBlock class.
  s[0].set(1,0,4);
  s[1].set(0,0,4); printFrameX();
  while (1) {
    printSnake(&s); // &s is a pointer pointing to the (SIZE*2)-snakeBlock-array.
    printFrameX();
    char a, res;
    a = getc(stdin);
    //printf("\n%d",a);
    if (random(2) == 0 && hasFood == 0) { //true, put food
      fx = random(SIZE); fy = random(SIZE); hasFood = 1;
    }
    printFrameX();
    switch(a) {
      case 119: case 87: //W w
        res = moveSnake(&s, 1);
        break;
      case 97: case 65: //A a
        res = moveSnake(&s, 3);
        break;
      case 115: case 83: //S s
        res = moveSnake(&s, 2);
        break;
      case 100: case 68: //D d
        res = moveSnake(&s, 4);
        break;
      case 113: case 81: //Q q
        return 0;
      default:
        break;
    }
    if (res == 1) {
      printf("\n\nGame Over!\n"); return 0;
    } else if (res == 2) {
      printf("\nInvalid direction!\n");
    } else if (res == 3) {
      printf("\nHow fool you are!\n"); return 0;
    } else if (res == 4) {
      printf("\nYou won~~ You are the snake fucker!\n"); return 0;
    }
  }
}
