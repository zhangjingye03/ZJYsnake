#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define SIZE 8
#define INITS 2
#define random(x) (rand()%x)

char tail = INITS - 1;


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
  for (int i = 0; i <= tail; i++) { // tail is the last element
    map[(*sb)[i].y][(*sb)[i].x] = ( i == 0 ) ? 'O' : 'o'; //*sb[i].x || sb[i]->x
    //printf("index%d, x = %x, y = %x, d = %x\n", i, (*sb)[i].x, (*sb)[i].y, (*sb)[i].getD());
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
  if (dir == 4) { //right
    if ((*sb)[0].d == 3) return 2; // contradict
    if ((*sb)[0].x == SIZE - 1) return 1; // game over
  } else if (dir == 3) { //left
    if ((*sb)[0].d == 4) return 2; // contradict
    if ((*sb)[0].x == 0) return 1; // game over
  } else if (dir == 2) { //down
    if ((*sb)[0].d == 1) return 2; // contradict
    if ((*sb)[0].y == SIZE - 1) return 1; // game over
  } else if (dir == 1) { //up
    if ((*sb)[0].d == 2) return 2; // contradict
    if ((*sb)[0].y == 0) return 1; // game over
  }
  (*sb)[0].d = dir;
  for (int i = tail; i >= 0; i--) {
    moveBlock (&(*sb)[i], (i == 0) ? &(*sb)[i] : &(*sb)[i - 1]);
  }
  return 0;
}

void printFrameX() {
  printf("|");
  for (int i = 0; i < SIZE; i++) {
    printf(" -");
  }
  printf(" |\n");
}

char hasFood = 0; char fx, fy;
int main() {
  snakeBlock s[SIZE * 2]; // this array contains (SIZE*2) snakeBlock class.
  s[0].set(1,0,4);
  s[1].set(0,0,4); printFrameX();
  while (1) {
    printSnake(&s); // &s is a pointer pointing to the (SIZE*2)-snakeBlock-array.
    printFrameX();
    char a, res;
    a = getc(stdin);
    //printf("\n%d",a);
    if (random(3) == 0 && hasFood == 0) { //true, put food
      fx = random(SIZE); fy = random(SIZE); hasFood = 1;
    }

    printFrameX();
    switch(a) {
      case 119: case 87: //W w
        // judge food
        // move snake
        res = moveSnake(&s, 1);
        break;
      case 97: case 65: //A a
        // judge food
        // move snake
        res = moveSnake(&s, 3);
        break;
      case 115: case 83: //S s
        // judge food
        // move snake
        res = moveSnake(&s, 2);
        break;
      case 100: case 68: //D d
        // judge food
        // move snake
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
    }
  }
}
