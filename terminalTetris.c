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
#include <sys/select.h>
#include <fcntl.h>

int _kbhit()
{
    struct termios oldt, newt;
    int ch;
    int oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF)
    {
        //ungetc(ch, stdin);
        return ch;
    }
    return 0;
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
     int rotState=0;
     int nextBlock=0;
     int currentBlock;
int spawnBlock(int rows, int cols ,int **array,int *CordArray,int num);
void checkLines(int rows, int cols ,int **array);
void incrementRot(){
    (rotState < 3) ? (rotState++) : (rotState=0);
}
void decrementRot(){
    (rotState==0) ? (rotState=3) : (rotState--);
}
void resetGameState(int rows, int cols ,int **array){
    int i , j;
for (i = 0; i < cols; i++) {
    array[i] = calloc(rows,sizeof(int));//malloc(sizeof(int)*rows);
}
return;
}
void freeGameState(int rows, int cols ,int **array){
    int i , j;
for (i = 0; i < cols; i++) {
    free(array[i]);
}
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
    for(int i=0; i < 8 ;i++){
        printf("%d",arr[i]);
        if(i==sizeof(*arr/sizeof(int))-1){
        printf("\n");
        };
    }
}
void printDynamic(int **arr,int rows,int cols){
    for (int i = 0; i < cols; i++)
    {
        for (int j = 0; j < rows; j++){
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

void printGameState(int rows, int cols ,int **array){
    int i , j;
    int CordArray[8] = {9};
    int nextBox;
    if(nextBlock==line){
        nextBox=4;
    }else{
        nextBox=3;
    }
    printf("nextBox:%d\n",nextBox);
    int **matrix=malloc(sizeof(int *)*nextBox);
    resetGameState(nextBox,nextBox,matrix);
    spawnBlock(2,nextBox,matrix,CordArray,nextBlock);
    //printDynamic(matrix,nextBox,nextBox);
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
    if(i<2&&j==rows-1){
        printf("\t |");
        for(int a=0;a<nextBox;a++){
            if (matrix[i][a]==0){
           printf(" ");
            }
            if (matrix[i][a]==1){
            printf("#");
            }      
            //printf("%d",matrix[i][a]);
        }
    }
    if(j==rows-1){
        printf("\n");
    }
  }
}
freeGameState(nextBox,nextBox,matrix);
free(matrix);
matrix = NULL;
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

void appendCordArray(int rows, int cols ,int **array,int *CordArray,int *newCordArray,int blockNum,int rot);

int setGround(int rows, int cols ,int **array,int *CordArray){
    findBlockCords(rows,cols,array,CordArray);
   // printf("setting ground");
   // printArray(CordArray);
    for(int i=0; i<7;i+=2){
        array[CordArray[i]][CordArray[i+1]]=2;
        //printf("Value:%d",array[CordArray[i]][CordArray[i+1]]);
    }
    //printf("\nSETGROUND GAME ARRAY");
   int block = spawnBlock(rows,cols,array,CordArray,0);
        findBlockCords(rows,cols,array,CordArray);
        checkLines(rows,cols,array);
    //printGameState(rows,cols,array);
    return block;
}
void groundGravity(int rows, int cols ,int **array,int *listToClear,int index){

    for (int i = index-1;i>=0;i--){
        printf("i= %d\n",i);
        for(int j = listToClear[i];j>0;j--){
            printf("j=%d",j);
            for(int a = 0;a<rows;a++){
                if(array[j-1][a]==2){
                     array[j-1][a]=0;
                     array[j][a]=2;
                }
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
        if(array[i][j]!=2){
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
void rotateLine(int rows, int cols ,int **array,int *CordArray,int blockNum,int direction){
        int box[4][4]={0};
        int paddingY;
        int paddingX;
        printf("RotState: %d\n",rotState);

        paddingX = (rotState==0) ? CordArray[1] : paddingX;
        paddingY = (rotState==0) ? CordArray[0]-1 : paddingY;

        paddingX = (rotState==1) ? CordArray[1]-2 : paddingX;
        paddingY = (rotState==1) ? CordArray[0] : paddingY;

        paddingX = (rotState==2) ? CordArray[1] : paddingX;
        paddingY = (rotState==2) ? CordArray[0]-2 : paddingY;

        paddingX = (rotState==3) ? CordArray[1]-1 : paddingX;
        paddingY = (rotState==3) ? CordArray[0] : paddingY;

        for(int i=0;i<7;i+=2){
           int Y = CordArray[i]-paddingY;
           int X = CordArray[i+1]-paddingX;
           box[Y][X]=1;
        }
        printFixed(box,4,4);
        //Transpose
        int box2[4][4]={0};
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                box2[i][j] = box[j][i];
                //box[i][j] = 0;
            }
        }
            printf("After Transpose \n");
            printFixed(box2,4,4);
        //Reverse
        if(direction == 0){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                box[i][3-j] = box2[i][j];
            }
        }
        }else if(direction == 1){
            for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                box[3-i][j] = box2[i][j];
            }
        }
        }
            printf("After roto \n");
            printFixed(box,4,4);
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
            appendCordArray(rows,cols,array,CordArray,CordArray2,blockNum,direction);
}
void rotate(int rows, int cols ,int **array,int *CordArray,int blockNum,int padX,int padY,int direction){
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
           int Y = CordArray[i]-Ynum+padY;
           int X = CordArray[i+1]-Xnum+padX;
           matrix[Y][X]=1;
        }
        printf("RotState: %d\n",rotState);
        printFixed2(matrix,3,3);
        //Transpose
        int matrix2[3][3]={0};

        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                matrix2[i][j] = matrix[j][i];
            }
        }
            printf("After Transpose \n");
            printFixed2(matrix2,3,3);
        //Reverse

            for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
               // matrix[i][j] = matrix2[2-i][2-j];
               matrix[i][j] = matrix2[i][j];
            }
        }
        if(direction==1){
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                matrix[i][j] = matrix2[2-i][j];
            }
        }
        }else if(direction==0){
            for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                matrix[i][j] = matrix2[i][2-j];
            }
        }
        }
                printf("After roto \n");
            printFixed2(matrix,3,3);
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
        appendCordArray(rows,cols,array,CordArray,CordArray_temp,blockNum,direction);

}

void appendCordArray(int rows, int cols ,int **array,int *CordArray,int *newCordArray,int blockNum,int rot){
    //int num=0;        
            int padding=0;
            int paddingY=0;
            if(blockNum!=line){
                padding=0;
                paddingY =0;
                padding = (rotState==0) ? 0 : padding;
                padding = (rotState==1) ? -1 : padding;
                paddingY = (rotState ==2) ? -1 : paddingY;
            }else{
                padding = 0;
                paddingY =0;
            }
            
        for(int i=0; i<7;i+=2){
        if(newCordArray[i]+paddingY>=cols||newCordArray[i+1]+padding>=rows){
            printf("too far up/right");
            return;
        }
        if(newCordArray[i+1]+padding<0||newCordArray[i]+paddingY<0){
            printf("too far left");
            return;
        }
        if(array[newCordArray[i]+paddingY][newCordArray[i+1]+padding]==2){
            printf("colision");
            return;
        }
    }
        for(int i=0; i<7;i+=2){
            array[CordArray[i]][CordArray[i+1]]=0;
        }
        for(int i=0; i<7;i+=2){
            array[newCordArray[i]+paddingY][newCordArray[i+1]+padding]=1;
        }
        if(rot == 0){
            incrementRot();
        }else{
            decrementRot();
        }
            findBlockCords(rows,cols,array,CordArray);
}
void rotateRight(int rows, int cols ,int **array,int *CordArray,int blockNum){
    //array[i][j];
    //printf("Rotating\n");
        int padY=0;
        int padX=0;
        padX = (rotState == 1) ? 1 : padX;
        padY = (rotState == 2) ? 1 : padY;
    switch (blockNum)
    {
       case block://block
        return;
        break;
        case line://line
           rotateLine(rows,cols,array,CordArray,blockNum,0);
        break;
        default:
            rotate(rows,cols,array,CordArray,blockNum,padX,padY,0);
        break;
    }
}
void rotateLeft(int rows, int cols ,int **array,int *CordArray,int blockNum){
    //printf("Rotating\n");
        int padY=0;
        int padX=0;
        padX = (rotState == 1) ? 1 : padX;
        padY = (rotState == 2) ? 1 : padY;
    switch (blockNum)
    {
       case block://block
        return;
        break;
        case line://line
           rotateLine(rows,cols,array,CordArray,blockNum,1);
        break;
        default:
            rotate(rows,cols,array,CordArray,blockNum,padX,padY,1);
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
                return 0;
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

     reset:
    time_t t = time(NULL);
    time_t currentT = time(NULL);
     resetGameState(rows,columns,GameState);
     int CordArray[8] = {0};
     int block = spawnBlock(rows,columns,GameState,CordArray,0);
     int currentBlock = block;
                 printGameState(rows,columns,GameState);
     //int rotState;
while (1 == 1)
{
    currentT = time(NULL);
    //printf("Current time %d\n",(int)currentT);
    //printf("time %d\n",(int)t);
    if((int)currentT - (int)t == 1){
        t=currentT;
        int temp = advanceState(rows,columns,GameState,CordArray);
            if(temp == -1){
                break;
            }
            if(temp != 0){
                currentBlock = temp;
            }
        currentT = time(NULL);
                            printf("\n\n\n");
            printGameState(rows,columns,GameState);
    }
    char input;
    //clearScreen();//!Remove to debug
int linput;
linput = _kbhit();
if(linput){
    #ifdef _WIN32
input = getch();
    #else
    input = linput;
    #endif
printf("key code %d \n",input);
        if(input =='d'){
            moveRight(rows,columns,GameState,CordArray);
        } 
        if(input =='a'){
            moveLeft(rows,columns,GameState,CordArray);
        }
        if(input =='s'){
            int temp = advanceState(rows,columns,GameState,CordArray);
            if(temp == -1){
                break;
            }
            if(temp != 0){
                currentBlock = temp;
            }
        }
        if(input == 27){
            printf("Quiting\n");
            break;
        }
        if(input =='e'){
            rotateRight(rows,columns,GameState,CordArray,currentBlock);
        }
        if(input =='q'){
            rotateLeft(rows,columns,GameState,CordArray,currentBlock);
        }
            printf("\n\n\n");
            printGameState(rows,columns,GameState);
}
//printf("non blocking\n");
}
    char answer;
        freeGameState(rows,columns,GameState);
    printf("Game Over\nPlay Again y/n\n");
    scanf(" %c",&answer);
    if(answer =='y'||answer=='Y'){
        goto reset;
    }
        free(GameState);
     GameState = NULL;
    printf("GAME OVER");
    return 0;
}

int spawnBlock(int rows, int cols ,int **array,int *CordArray,int num){
    int checkFlag=0;
    int rNum;
    int flag=0;
    if(num==0){
    rotState = 0;
    if(rows < 5||cols<5){
        printf("to few rows/columns");
        return -1;
    }
     if(nextBlock==0){
     rNum = (rand() % (7 - 1 + 1)) + 1;
     nextBlock = (rand() % (7 - 1 + 1)) + 1;
     flag=1;
     }
     else {
        rNum = nextBlock;
        nextBlock = (rand() % (7 - 1 + 1)) + 1;
     }



        if(CordArray[0] <= 1){
           checkFlag = 1;
        }else{
           checkFlag = 0;
        }
    
    }else{
        rNum = num;
    }

    //rNum=line;//!REMEMBER ME

    switch (rNum)
    {
    case block://block
    if(checkFlag == 1){
    if(array[0][rows/2] == 2)
    return -1;
    if(array[0][rows/2+1] == 2)
    return -1;
    if(array[1][rows/2] == 2)
    return -1;
    if(array[1][rows/2+1] == 2)
    return -1;
    }
    array[0][rows/2] = 1;
    array[0][rows/2+1]=1;
    array[1][rows/2] = 1;
    array[1][rows/2+1]=1;
        break;
        case line://line
    if(checkFlag == 1){
    if(array[0][rows/2-1] == 2)
    return -1;
    if(array[0][rows/2] == 2)
    return -1;
    if(array[0][rows/2+1] == 2)
    return -1;
    if(array[0][rows/2+2] == 2)
    return -1;
    }
    array[0][rows/2-1] = 1;
    array[0][rows/2]=1;
    array[0][rows/2+1] = 1;
    array[0][rows/2+2]=1;

        break;
            case Z://z
    if(checkFlag == 1){
    if(array[0][rows/2-1] == 2)
    return -1;
    if(array[0][rows/2] == 2)
    return -1;
    if(array[1][rows/2] == 2)
    return -1;
    if(array[1][rows/2+1] == 2)
    return -1;
    }
    array[0][rows/2-1] = 1;
    array[0][rows/2]=1;
    array[1][rows/2] = 1;
    array[1][rows/2+1]=1;

        break;
            case S://s
    if(checkFlag == 1){
    if(array[0][rows/2] == 2)
    return -1;
    if(array[0][rows/2+1] == 2)
    return -1;
    if(array[1][rows/2] == 2)
    return -1;
    if(array[1][rows/2-1] == 2)
    return -1;
    }
    array[0][rows/2] = 1;
    array[0][rows/2+1]=1;
    array[1][rows/2] = 1;
    array[1][rows/2-1]=1;

        break;
            case L://L
    if(checkFlag == 1){
    if(array[0][rows/2-1] == 2)
    return -1;
    if(array[1][rows/2-1] == 2)
    return -1;
    if(array[1][rows/2] == 2)
    return -1;
    if(array[1][rows/2+1] == 2)
    return -1;
    }
    array[0][rows/2-1]=1;
    array[1][rows/2-1] = 1;
    array[1][rows/2] = 1;
    array[1][rows/2+1]=1;

        break;
            case J://j
    if(checkFlag == 1){
    if(array[0][rows/2+1] == 2)
    return -1;
    if(array[1][rows/2+1] == 2)
    return -1;
    if(array[1][rows/2] == 2)
    return -1;
    if(array[1][rows/2-1] == 2)
    return -1;
    }
    array[0][rows/2+1]=1;
    array[1][rows/2+1] = 1;
    array[1][rows/2] = 1;
    array[1][rows/2-1]=1;

        break;
            case T://T
    if(checkFlag == 1){
    if(array[0][rows/2] == 2)
    return -1;
    if(array[1][rows/2] == 2)
    return -1;
    if(array[1][rows/2-1] == 2)
    return -1;
    if(array[1][rows/2+1] == 2)
    return -1;
    }
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