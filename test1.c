#include <stdio.h>
#include <stdlib.h>

#define FIELD_WIDTH 8
#define FIELD_HEIGHT 8

int cursorX , cursorY;

int main(void){
  while(1){
    system("clear");
    for(int y=0; y<FIELD_HEIGHT; y++){
      for(int x=0; x<FIELD_WIDTH; x++)
        if((x==cursorX)&&(y==cursorY))
          printf("◎");
        else
          printf("・");
      printf("\n");
    }
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
    }
  }
}