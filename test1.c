#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



#define FIELD_WIDTH 8
#define FIELD_HEIGHT 8


#define BLOCK_TYPE_MAX 7

enum{
  CELL_TYPE_NONE,     //=0
  CELL_TYPE_BLOCK_0,  //=1
  CELL_TYPE_BLOCK_1,  //=2
  CELL_TYPE_BLOCK_2,  //=3
  CELL_TYPE_BLOCK_3,  //=4
  CELL_TYPE_BLOCK_4,  //=5
  CELL_TYPE_BLOCK_5,  //=6
  CELL_TYPE_BLOCK_6,  //=7
  CELL_TYPE_MAX       //=8
};

char cellAA[][3+1]={
  "・",// CELL_TYPE_NONE
  "○",// CELL_TYPE_BLOCK_0
  "△",// CELL_TYPE_BLOCK_1
  "□",// CELL_TYPE_BLOCK_2   
  "●",// CELL_TYPE_BLOCK_3
  "▲",// CELL_TYPE_BLOCK_4
  "■",// CELL_TYPE_BLOCK_5
  "☆",// CELL_TYPE_BLOCK_6
};

int cells[FIELD_HEIGHT][FIELD_WIDTH];
int checked[FIELD_HEIGHT][FIELD_WIDTH];

int cursorX , cursorY;
int selectedX = -1, selectedY = -1;

int getConnectedBlockCount(int _x, int _y, int _cellType, int _count){
  if(
    (_x<0)||(_x>=FIELD_WIDTH)||(_y<0)||(_y>=FIELD_HEIGHT)
    || checked[_y][_x]
    ||(cells[_y][_x]==CELL_TYPE_NONE)
    ||(cells[_y][_x]!=_cellType)
  )
    return _count;

  _count++;
  checked[_y][_x] = true;

  _count = getConnectedBlockCount(_x, _y-1, _cellType, _count);
  _count = getConnectedBlockCount(_x-1, _y, _cellType, _count);
  _count = getConnectedBlockCount(_x, _y+1, _cellType, _count);
  _count = getConnectedBlockCount(_x+1,  _y, _cellType, _count);
}

int main(void){
  srand((unsigned int)time(NULL));
  for(int y=0; y<FIELD_HEIGHT; y++)
      for(int x=0; x<FIELD_WIDTH; x++)
        cells[y][x]= CELL_TYPE_BLOCK_0 + rand() %BLOCK_TYPE_MAX;

  while(1){
    system("clear");
    for(int y=0; y<FIELD_HEIGHT; y++){
      for(int x=0; x<FIELD_WIDTH; x++)
        if((x==cursorX)&&(y==cursorY))
          printf("◎");
        else
          printf("%s", cellAA[cells[y][x]]);
      if(y==selectedY)
        printf("←");
      printf("\n");
    }

    for(int x=0; x<FIELD_WIDTH; x++)
      printf("%s",(x==selectedX)? "↑":" ");
      printf("\n");

    switch(getchar()){
      case 'w':
        cursorY--; 
        break;
      case 's':
        cursorY++; 
        break;
      case 'a':
        cursorX--; 
        break;
      case 'd':
        cursorX++; 
        break;
      default:
        if(selectedX < 0){
          selectedX = cursorX;
          selectedY = cursorY;
        }
        else{
          int temp = cells[cursorX][cursorY];
          cells[cursorY][cursorX] = cells[selectedY][selectedX];
          cells[selectedY][selectedX] = temp;

          memset(checked, 0, sizeof checked);
          for(int y=0; y<FIELD_HEIGHT; y++)
            for(int x=0; x<FIELD_WIDTH; x++){
              int n = getConnectedBlockCount(x, y, cells[y][x], 0);
              if(n >= 3)
                cells[y][x] = CELL_TYPE_NONE;
            }
          selectedX =
          selectedY = -1;
        }
        break;
    }
  }
}