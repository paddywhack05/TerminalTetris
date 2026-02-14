#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
void spawnBlock(int rows, int cols ,int **array);
void checkLines(int rows, int cols ,int **array);
void resetGameState(int rows, int cols ,int **array){
    int i , j;
for (i = 0; i < cols; i++) {
    array[i] = malloc(sizeof(int)*rows);//calloc(rows,sizeof(int));malloc(sizeof(int)*rows);
}
int a,b;
for( a=0; a < cols; a++){
    for(b=0; b<rows;b++){
        array[a][b] = 0;
        //printf("%d",array[a][b]);
       // if(array[a][b]=0){
         //   printf(" ");
      //  }
       // if(b==rows-1){
       //     printf("\n");
       // }
    }
}
return;
}
void printArray(int *arr){
    for(int i; i < sizeof(*arr/sizeof(int)) ;i++){
        printf("%d\n",arr[i]);
    }
}
void printGameState(int rows, int cols ,int **array){
    int i , j;
for (i = 0; i < cols; i++) {
  for (j = 0; j < rows; j++) {
  //  printf("%d", array[i][j]);
    if (array[i][j]==0){
        printf(".");
    } 
   if (array[i][j]==1){
        printf("#");
    }
if (array[i][j]==2){
        printf("2");
    }
    if(j==rows-1){
        printf("\n");
    }
  }
}
}
void changeGameState(int rows, int cols ,int **array){
int a,b;
for( a=0; a < cols; a++){
  for(b=0; b<rows;b++){
    if(a == 0){
                array[a][b] = 1;
    }
    }
}
}
void findBlockCords(int rows, int cols ,int **array,int*CordArray){    
    //  printArray(CordArray);
int a,b;
int num=0;
for(a=0; a < cols; a++){
  for(b=0; b<rows;b++){
    if(array[a][b]==1){
        CordArray[num]=a;
        CordArray[num+1]=b;
        num +=2;
    }
  }
}

}

void setGround(int rows, int cols ,int **array,int *CordArray){
    findBlockCords(rows,cols,array,CordArray);
    printf("setting ground");
    printArray(CordArray);
    for(int i=0; i<7;i+=2){
        array[CordArray[i]][CordArray[i+1]]=2;
        printf("Value:%d",array[CordArray[i]][CordArray[i+1]]);
    }
    printf("\nSETGROUND GAME ARRAY");
    spawnBlock(rows,cols,array);

        findBlockCords(rows,cols,array,CordArray);
        checkLines(rows,cols,array);
    //memset(CordArray, 0x00, 8);
    printGameState(rows,cols,array);
    //printf("\n\n\n");
//array[1][1] = 2;
}
void groundGravity(int rows, int cols ,int **array,int *listToClear,int index){
    printf("Ground Grav\n");
    int i,j;
    int diff = listToClear[0] - listToClear[index-1];
    int startRow = listToClear[0]-diff;
    for(i=startRow;i>0;i--){
  for(j=0; j<rows;j++){
    if(array[i][j]==2){
        array[i][j]=0;
        array[i+index][j]=2;
    }
      //  array[listToClear[i]][j]=0;
    }
    }
}
void clearLines(int rows, int cols ,int **array,int *listToClear,int index){
    printf("clear %d,%d",listToClear[index-1],index);
    int i,j;
    for(i=0;i<index;i++){
        printf("cleared %d",listToClear[i]);
  for(j=0; j<rows;j++){
    //int cordarray[listToClear[i]][j];
        //memset(,0,rows);
        array[listToClear[i]][j]=0;
    }
    }
    groundGravity(rows, cols, array, listToClear, index);
    return;
}
void checkLines(int rows, int cols ,int **array){
    int linesToClear[4];
   // printf("%d",sizeof(linesToClear));
    int anotherIndex=0;
    int i , j;
for (i = cols-1; i > 0; i--) {
        int num = rows;
  for (j = 0; j < rows; j++) {
        if(array[i][j]!=array[i][0]||array[i][j]!=2){
            break;
        }else{
            num--;
        }
        }
         if(num==0){
            printf("Oh shit a line: %d",i);
            linesToClear[anotherIndex]=i;
 printf("\nList el i %d\n",linesToClear[anotherIndex]);
 printf("\nList el 0 %d\n",linesToClear[0]);
            anotherIndex++;
        }
        if(num == 0){
            printf("another index: %d\n",anotherIndex);
        }
    }
    
    if(anotherIndex > 0){
          //  printf("\nList el 0\n",linesToClear[0]);
          printf("Array before func %d\n",linesToClear[anotherIndex -1]);
        clearLines(rows,cols,array,linesToClear,anotherIndex);
    }
    return;
   // printArray(linesToClear);
}

void moveRight(int rows, int cols ,int **array,int *CordArray){
    for(int i=7; i>1;i-=2){
           // printf("\n\ncol nums %d\nindex %d",cols,i);
           //printf("\n\n");
           printf("Arr row:%d\nrows:%d\n",CordArray[i]+1,rows-1);
            printf("Arr row 7:%d\nrows:%d\n",CordArray[7]+1,rows-1);
    if(CordArray[i]+1 >= rows){

            printf("HIT WALL");
        //setGround(rows,cols,array,CordArray);
        return;
    }
        if(array[CordArray[i-1]][CordArray[i]+1] == 2){
            printf("Wall 2 HIT");
        //setGround(rows,cols,array,CordArray);
        return;
    }
    }
        findBlockCords(rows,cols,array,CordArray);
        for(int i=7; i>0;i-=2){
            array[CordArray[i-1]][CordArray[i]+1]=1;
            array[CordArray[i-1]][CordArray[i]]=0;
        }
                findBlockCords(rows,cols,array,CordArray);
}

void moveLeft(int rows, int cols ,int **array,int *CordArray){
    for(int i=0; i<7;i+=2){
        printf("left");
           // printf("\n\ncol nums %d\nindex %d",cols,i);
           //printf("\n\n");
        //   printf("Arr row:%d\nrows:%d\n",CordArray[i]+1,rows-1);
        //    printf("Arr row 7:%d\nrows:%d\n",CordArray[7]+1,rows-1);
    if(CordArray[i+1] == 0){

            printf("HIT WALL");
        //setGround(rows,cols,array,CordArray);
        return;
    }
        if(array[CordArray[i]][CordArray[i+1]-1] == 2){
            printf("Wall 2 HIT");
        //setGround(rows,cols,array,CordArray);
        return;
    }
    }
        findBlockCords(rows,cols,array,CordArray);
        for(int i=0; i<7;i+=2){
            array[CordArray[i]][CordArray[i+1]-1]=1;
            array[CordArray[i]][CordArray[i+1]]=0;
        }
                findBlockCords(rows,cols,array,CordArray);
}
int findCenter(int rows, int cols ,int **array,int *CordArray){
    int lineDiff = CordArray[6]-CordArray[0];
    int numX=0;
    int i,j;
   for(i=0;i<4;i++){
    for(j=0;j<rows;j++){

    }
}
}
void rotateRight(int rows, int cols ,int **array,int *CordArray){
 //CordArray[]
}
void rotateLeft(int rows, int cols ,int **array,int *CordArray){
 //CordArray[]
}
void advanceState(int rows, int cols ,int **array,int *CordArray){
    for(int i=7; i>0;i-=2){
           // printf("\n\ncol nums %d\nindex %d",cols,i);
           //printf("\n\n");
    if(CordArray[i-1]+1 > cols-1){
            printf("GROUND HIT");
        setGround(rows,cols,array,CordArray);
        return;
    }
        if(array[CordArray[i-1]+1][CordArray[i]] == 2){
            printf("GROUND 2 HIT");
        setGround(rows,cols,array,CordArray);
        return;
    }
    }
   findBlockCords(rows,cols,array,CordArray);
           for(int i=6; i+1>0;i-=2){
            array[CordArray[i]+1][CordArray[i+1]]=1;
            array[CordArray[i]][CordArray[i+1]]=0;
        }
    /*
    array[CordArray[6]+1][CordArray[7]]=1;
    array[CordArray[6]][CordArray[7]]=0;
    array[CordArray[4]+1][CordArray[5]]=1;
    array[CordArray[4]][CordArray[5]]=0;
    array[CordArray[2]+1][CordArray[3]]=1;
    array[CordArray[2]][CordArray[3]]=0;
    array[CordArray[0]+1][CordArray[1]]=1;
    array[CordArray[0]][CordArray[1]]=0;
    */
                findBlockCords(rows,cols,array,CordArray);
                printf("debug\n");
                printArray(CordArray);
/*for (unsigned i = 8 ; i-- > 0 ; )
{
    printf("%d",i);
    array[(CordArray[i])][CordArray[i+1]]=0;
    array[(CordArray[i]+1)][CordArray[i+1]]=1;
  // do stuff with i
}*/

}

int main(void) {
    srand(time(NULL));
    int rows=0;
    int columns=0;

    printf("How many rows\n");
    scanf("%d",&rows);  
    printf("rows:%d\n",rows);
    printf("how many columns\n");
    scanf("%d",&columns);
    printf("columns:%d\n",columns);
     int **GameState = malloc(sizeof(int *)*columns);
    if(GameState == NULL){
        printf("malloc is fucked");
        return 1;
    }

     resetGameState(rows,columns,GameState);
     int CordArray[8] ={0};
     int *pCordArray =CordArray;
   // printGameState(rows,columns,GameState);
   spawnBlock(rows,columns,GameState);
 //  findBlockCords(rows,columns,GameState,pCordArray);
   //printf("%p",CordArray);
   // printGameState(rows,columns,GameState);
/*for(int i=0;i<30;i++){
        advanceState(rows,columns,GameState,pCordArray);
        findBlockCords(rows,columns,GameState,pCordArray);
        printGameState(rows,columns,GameState);
}*/
   // int s = 1;  
while (1 == 1)
{
    char input;
            printGameState(rows,columns,GameState);
            //checkLines(rows,columns,GameState);
            scanf(" %c",&input);
      //  advanceState(rows,columns,GameState,pCordArray);
        if(input =='d'){
            moveRight(rows,columns,GameState,pCordArray);
        } 
        if(input =='a'){
            moveLeft(rows,columns,GameState,pCordArray);
        }
        if(input =='s'){
            advanceState(rows,columns,GameState,pCordArray);
        }
        if(input =='e'){
            rotateRight(rows,columns,GameState,pCordArray);
        }
        if(input =='q'){
            rotateLeft(rows,columns,GameState,pCordArray);
        }
      //  findBlockCords(rows,columns,GameState,pCordArray);
}

  //  advanceState(rows,columns,GameState,pCordArray);
  //  findBlockCords(rows,columns,GameState,pCordArray);
    //    printGameState(rows,columns,GameState);
  //  printf("array address inside Main: %p\n pcor = %p", CordArray,pCordArray);
    //printf("\n\n\n\n\n\n");
    //Gravity(rows,columns,GameState);
        free(GameState);
     GameState = NULL;
     printf("GAME OVER");
    return 0;
}

enum Block{
    block = 1,
    line,
    Z,
    S,
    L,
    J,
    T,
};
void spawnBlock(int rows, int cols ,int **array){
    if(rows < 5||cols<5){
        printf("to few rows/columns");
        return;
    }
     int rNum = (rand() % (7 - 1 + 1)) + 1;
    //int a,b;
    switch (rNum)
    {
    case block://block
    array[0][rows/2] = 1;
    array[0][rows/2+1]=1;
    array[1][rows/2] = 1;
    array[1][rows/2+1]=1;

        break;
        case line://line
    array[0][rows/2-1] = 1;
    array[0][rows/2]=1;
    array[0][rows/2+1] = 1;
    array[0][rows/2+2]=1;

        break;
            case Z://z
    array[0][rows/2-1] = 1;
    array[0][rows/2]=1;
    array[1][rows/2] = 1;
    array[1][rows/2+1]=1;

        break;
            case S://s
    array[0][rows/2] = 1;
    array[0][rows/2+1]=1;
    array[1][rows/2] = 1;
    array[1][rows/2-1]=1;

        break;
            case L://L
    array[0][rows/2-1]=1;
    array[1][rows/2-1] = 1;
    array[1][rows/2] = 1;
    array[1][rows/2+1]=1;

        break;
            case J://j
    array[0][rows/2+1]=1;
    array[1][rows/2+1] = 1;
    array[1][rows/2] = 1;
    array[1][rows/2-1]=1;

        break;
            case T://T
    array[0][rows/2] = 1;
    array[1][rows/2]=1;
    array[1][rows/2-1] = 1;
    array[1][rows/2+1]=1;

        break;
    default:
    printf("rNum is broken %d",rNum);
        break;
    }

}