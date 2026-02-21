#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifdef _WIN32
    #include <conio.h>
    void clearScreen(){
    system("cls");
    }
#else
#include <termios.h>
#include <unistd.h> 
int getch(void){
  struct termios oldattr, newattr;
  unsigned char ch;
  int retcode;
  tcgetattr(STDIN_FILENO, &oldattr);
  newattr=oldattr;
  newattr.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
  retcode=read(STDIN_FILENO, &ch, 1);
  tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
  return retcode<=0? EOF: (int)ch;
}
void clearScreen(){
    system("clear");
}
#endif
enum Block{
    block = 1,
    line,
    Z,
    S,
    L,
    J,
    T,
};
     int rotState;
int spawnBlock(int rows, int cols ,int **array);
void checkLines(int rows, int cols ,int **array);
void incrementRot(){
    (rotState < 3) ? (rotState++) : (rotState=0);
}
void resetGameState(int rows, int cols ,int **array){
    int i , j;
for (i = 0; i < cols; i++) {
    array[i] = calloc(rows,sizeof(int));//malloc(sizeof(int)*rows);
}
int a,b;
return;
}
void printFixed(int arr[4][4], int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%d ", arr[i][j]);
        printf("\n");
    }
}
void printFixed2(int arr[3][3], int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%d ", arr[i][j]);
        printf("\n");
    }
}
void printArray(int arr[8]){
    for(int i; i < 8 ;i++){
        printf("%d",arr[i]);
        if(i==sizeof(*arr/sizeof(int))-1){
        printf("\n");
        };
    }
}
void printGameState(int rows, int cols ,int **array){
    int i , j;
for (i = 0; i < cols; i++) {
  for (j = 0; j < rows; j++) {
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
void appendCordArray(int rows, int cols ,int **array,int *CordArray,int *newCordArray,int blockNum);
int setGround(int rows, int cols ,int **array,int *CordArray){
    findBlockCords(rows,cols,array,CordArray);
    printf("setting ground");
    printArray(CordArray);
    for(int i=0; i<7;i+=2){
        array[CordArray[i]][CordArray[i+1]]=2;
        printf("Value:%d",array[CordArray[i]][CordArray[i+1]]);
    }
    printf("\nSETGROUND GAME ARRAY");
   int block = spawnBlock(rows,cols,array);

        findBlockCords(rows,cols,array,CordArray);
        checkLines(rows,cols,array);
    printGameState(rows,cols,array);
    return block;
}
void groundGravity(int rows, int cols ,int **array,int *listToClear,int index){
    int i,j;
    int diff = listToClear[0] - listToClear[index-1];
    int startRow = listToClear[0]-diff;
    for(i=startRow;i>0;i--){
  for(j=0; j<rows;j++){
    if(array[i][j]==2){
        array[i][j]=0;
        array[i+index][j]=2;
    }
    }
    }
}
void clearLines(int rows, int cols ,int **array,int *listToClear,int index){
    //printf("clear %d,%d",listToClear[index-1],index);
    int i,j;
    for(i=0;i<index;i++){
        //printf("cleared %d",listToClear[i]);
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
            linesToClear[anotherIndex]=i;
            anotherIndex++;
        }
        if(num == 0){
            printf("another index: %d\n",anotherIndex);
        }
    }
    
    if(anotherIndex > 0){
        clearLines(rows,cols,array,linesToClear,anotherIndex);
    }
    return;
}

void moveRight(int rows, int cols ,int **array,int *CordArray){
    for(int i=7; i>1;i-=2){
    if(CordArray[i]+1 >= rows){

        return;
    }
        if(array[CordArray[i-1]][CordArray[i]+1] == 2){
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
    if(CordArray[i+1] == 0){
        return;
    }
        if(array[CordArray[i]][CordArray[i+1]-1] == 2){
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
   for(i=6;i>0;i-=2){
    if(numX==1){
    numX=0;
    }
    for(j=0;j<rows;j++){
       if(array[i][j]==1){
        numX++;
       }
    }
}
}
void Zrotate(int rows, int cols ,int **array,int *CordArray,int blockNum,int padX,int padY){
            int matrix[3][3]={0};

        //Loop through x cords set lowest to var
        int Xnum = CordArray[1];
        for(int i=3;i<8;i+=2){
            if(CordArray[i]<Xnum){
            Xnum = CordArray[i];
            }else{
                continue;
            }
        }
        int Ynum = CordArray[0];
        for(int i=2;i<8;i+=2){
            if(CordArray[i]<Ynum){
            Ynum = CordArray[i];
            }else{
                continue;
            }
        }
        for(int i=0;i<7;i+=2){
           int Y = CordArray[i]-Ynum;
           int X = CordArray[i+1]-Xnum;
           matrix[Y][X]=1;
        }
        //printFixed2(matrix,3,3);
        //Transpose
        int matrix2[3][3]={0};

        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                matrix2[i][j] = matrix[j][i];
            }
        }
            //printf("After Transpose \n");
           // printFixed2(matrix2,3,3);
        //Reverse

            for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
               // matrix[i][j] = matrix2[2-i][2-j];
               matrix[i][j] = matrix2[i][j];
            }
        }
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                matrix[i][j] = matrix2[i][2-j];
            }
        }
                printf("After roto \n");
            printFixed2(matrix,3,3);
            printArray(CordArray);
            int index=0;
            int CordArray_temp[8];
        for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
        if(matrix[i][j]==1){
            CordArray_temp[index]=i+Ynum;
            CordArray_temp[index+1]=j+Xnum;
            index +=2;
            }
            }
        
        }
        //printf("Cord Array after rotation\nXpad %d Ypad %d\n",padX,padY);
        //printArray(CordArray_temp);
        appendCordArray(rows,cols,array,CordArray,CordArray_temp,blockNum);

}

void appendCordArray(int rows, int cols ,int **array,int *CordArray,int *newCordArray,int blockNum){
    //int num=0;
    printf("Appending\n");
        for(int i=0; i<7;i+=2){
        if(newCordArray[i]>=cols||newCordArray[i+1]>=rows){
            printf("too far up/right");
            return;
        }
        if(newCordArray[i+1]<0||newCordArray[i]<0){
            printf("too far left");
            return;
        }
        if(array[newCordArray[i]][newCordArray[i+1]]==2){
            printf("colision");
            return;
        }
    }
        for(int i=0; i<7;i+=2){
            array[CordArray[i]][CordArray[i+1]]=0;
        }
        for(int i=0; i<7;i+=2){
            array[newCordArray[i]][newCordArray[i+1]]=1;
        }
                    incrementRot();
            findBlockCords(rows,cols,array,CordArray);
}
void rotateRight(int rows, int cols ,int **array,int *CordArray,int blockNum){
    //array[i][j];
    //printf("Rotating\n");
    switch (blockNum)
    {
       case block://block
        return;
        break;
        case line://line
        int box[4][4]={0};
        int paddingY;
        int paddingX;
        //printf("RotState: %d\n",rotState);
        if(rotState==0){
        paddingY = CordArray[0]-1;
        paddingX = CordArray[1];
        }else if(rotState == 1){
        paddingY = CordArray[0];
        paddingX = CordArray[1]-1;
        }else if(rotState == 2){
        paddingY = CordArray[0]-2;
        paddingX = CordArray[1];
        }else if(rotState == 3){
        paddingY = CordArray[0];
        paddingX = CordArray[1]-2;
        }
        for(int i=0;i<7;i+=2){
           int Y = CordArray[i]-paddingY;
           int X = CordArray[i+1]-paddingX;
           box[Y][X]=1;
        }
        //printFixed(box,4,4);
        //Transpose
        int box2[4][4]={0};
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                box2[i][j] = box[j][i];
                //box[i][j] = 0;
            }
        }
            //printf("After Transpose \n");
            //printFixed(box2,4,4);
        //Reverse
        //int box3[4][4];
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                box[i][3-j] = box2[i][j];
            }
        }
        //printf("After roto \n");
           // printFixed(box,4,4);
            //printArray(CordArray);
            int num=0;
            int CordArray2[8];
        for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
        if(box[i][j]==1){
            CordArray2[num]=i+paddingY;
            CordArray2[num+1]=j+paddingX;
            num +=2;
            }
            }
        
        }
          //  printf("Cord Array after rotation\nXpad %d Ypad %d\n",paddingX,paddingY);
           // printArray(CordArray2);
            appendCordArray(rows,cols,array,CordArray,CordArray2,blockNum);

           // rotState++;
        break;
            case Z://z
        int padY;
        int padX;
        //printf("RotState: %d\n",rotState);
                if(rotState==0){
        padY = CordArray[0]-1;
        padX = CordArray[1];
        }else if(rotState == 1){
        padY = CordArray[0];
        padX = CordArray[1]-2;
        }else if(rotState == 2){
        padY = CordArray[0];
        padX = CordArray[1];
        }else if(rotState == 3){
        padY = CordArray[0];
        padX = CordArray[1]-1;
        }
            Zrotate(rows,cols,array,CordArray,blockNum,padX,padY);
     
        break;
            case S://s
            int spadX;
            int spadY;
            //printf("RotState: %d\n",rotState);
        if(rotState==0){
        spadY = CordArray[0];
        spadX = CordArray[1]-1;
        }else if(rotState == 1){
        spadY = CordArray[0];
        spadX = CordArray[1]-1;
        }else if(rotState == 2){
        spadY = CordArray[0]-1;
        spadX = CordArray[1]-1;
        }else if(rotState == 3){
        spadY = CordArray[0];
        spadX = CordArray[1];
        }
            Zrotate(rows,cols,array,CordArray,blockNum,spadX,spadY);
        break;
            case L://L
            int lpadX;
            int lpadY;
            //printf("RotState: %d\n",rotState);
        if(rotState==0){
        lpadY = CordArray[0];
        lpadX = CordArray[1];
        }else if(rotState == 1){
        lpadY = CordArray[0];
        lpadX = CordArray[1];
        }else if(rotState == 2){
        lpadY = CordArray[0];
        lpadX = CordArray[1];
        }else if(rotState == 3){
        lpadY = CordArray[0];
        lpadX = CordArray[1]-1;
        }
            Zrotate(rows,cols,array,CordArray,blockNum,lpadX,lpadY);
        break;
            case J://j
            Zrotate(rows,cols,array,CordArray,blockNum,lpadX,lpadY);
        break;
            case T://T
            Zrotate(rows,cols,array,CordArray,blockNum,lpadX,lpadY);
        break;
    }
}
void rotateLeft(int rows, int cols ,int **array,int *CordArray,int blockNum){
    //array[i][j];
    //printf("Rotating\n");
    switch (blockNum)
    {
       case block://block
        return;
        break;
        case line://line
        int box[4][4]={0};
        int paddingY = CordArray[0]-1;
        int paddingX = CordArray[1];
        for(int i=0;i<7;i+=2){
           int Y = CordArray[i]-paddingY;
           int X = CordArray[i+1]-paddingX;
           box[Y][X]=1;
        }
       // printFixed(box,4,4);//transpose
        int box2[4][4]={0};
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                box2[i][j] = box[j][i];
                //box[i][j] = 0;
            }
        }
       // printf("After roto \n");
          //  printFixed(box2,4,4);
        break;
            case Z://z

        break;
            case S://s

        break;
            case L://L

        break;
            case J://j

        break;
            case T://T

        break;
    }
}
int advanceState(int rows, int cols ,int **array,int *CordArray){
    for(int i=7; i>0;i-=2){
           // printf("\n\ncol nums %d\nindex %d",cols,i);
           //printf("\n\n");
    if(CordArray[i-1]+1 > cols-1){
           // printf("GROUND HIT");
        int block = setGround(rows,cols,array,CordArray);
        return block;
    }
        if(array[CordArray[i-1]+1][CordArray[i]] == 2){
            //printf("GROUND 2 HIT");
        int block = setGround(rows,cols,array,CordArray);
        return block;
    }
    }
   findBlockCords(rows,cols,array,CordArray);
           for(int i=6; i+1>0;i-=2){
            array[CordArray[i]+1][CordArray[i+1]]=1;
            array[CordArray[i]][CordArray[i+1]]=0;
        }

                findBlockCords(rows,cols,array,CordArray);
                //printf("debug\n");
                printArray(CordArray);
                return -1;
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
     int block = spawnBlock(rows,columns,GameState);
     int currentBlock = block;
     //int rotState;
while (1 == 1)
{
    char input;
    //clearScreen();//!Remove to debug
        printf("Block %d\n",currentBlock);
            printGameState(rows,columns,GameState);
            //checkLines(rows,columns,GameState);
          //  scanf(" %c",&input);

input = getch();          //  advanceState(rows,columns,GameState,pCordArray);
        if(input =='d'){
            moveRight(rows,columns,GameState,pCordArray);
        } 
        if(input =='a'){
            moveLeft(rows,columns,GameState,pCordArray);
        }
        if(input =='s'){
            int temp = advanceState(rows,columns,GameState,pCordArray);
            if(temp != -1){
                currentBlock = temp;
            }
        }
        if(input == 27){
            printf("Quiting\n");
            break;
        }
        if(input =='e'){
            rotateRight(rows,columns,GameState,pCordArray,currentBlock);
        }
        if(input =='q'){
            rotateLeft(rows,columns,GameState,pCordArray,currentBlock);
        }
      //  findBlockCords(rows,columns,GameState,pCordArray);
}

        free(GameState);
     GameState = NULL;
    printf("GAME OVER");
    return 0;
}


int spawnBlock(int rows, int cols ,int **array){
    if(rows < 5||cols<5){
        printf("to few rows/columns");
        return -1;
    }
     int rNum = (rand() % (7 - 1 + 1)) + 1;
    //int a,b;
   // rNum=Z;//!REMEMBER ME
    rotState = 0;
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
    return rNum;
}