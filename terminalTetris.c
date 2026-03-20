#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
    #include <sysinfoapi.h>
    void clearScreen(){
    system("cls");
    }
    long uniTime(){
        DWORD t = GetTickCount();
    return (long)t;
}
enum arrowKeys{
    UP_ARROW=72,
    DOWN_ARROW=80,
    LEFT_ARROW=75,
    RIGHT_ARROW=77,
};
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
long uniTime(){
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC,&t);
    long millisec = t.tv_sec*1000;
    long milli = t.tv_nsec/1e+6;
    return millisec + milli;
}
enum arrowKeys{
    UP_ARROW=65,
    DOWN_ARROW=66,
    LEFT_ARROW=68,
    RIGHT_ARROW=67,
};
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
     int score=0;
     int totalLinesCleared=0;
     char *UTF;
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
void givePoints(int linesCleared){
    totalLinesCleared += linesCleared;
    switch (linesCleared)
    {
    case 1:
        score += 100;
        break;
    case 2:
        score += 300;
        break;
    case 3:
        score += 500;
        break;
    case 4:
        score += 1000;
        break;
    }
}
void freeGameState(int rows, int cols ,int **array){
    int i , j;
for (i = 0; i < cols; i++) {
    free(array[i]);
}
return;
}


void printGameState(int rows, int cols ,int **array){
    char boxY[] = "│";
    char boxX[] = "─";
    char boxBL[] = "└";
    char boxBR[] = "┘";
    char boxTL[] = "┌";
    char boxTR[] = "┐";
    if(UTF==NULL){
        strcpy(boxY,"|");
        strcpy(boxX,"=");
        strcpy(boxBL," ");
        strcpy(boxBR," ");
        strcpy(boxTL," ");
        strcpy(boxTR," ");
    }
    int i , j;
    int CordArray[8] = {9};
    int nextBox;
    if(nextBlock==line){
        nextBox=4;
    }else{
        nextBox=3;
    }
    int **matrix=malloc(sizeof(int *)*nextBox);
    resetGameState(nextBox,nextBox,matrix);
    spawnBlock(2,nextBox,matrix,CordArray,nextBlock);
for(int a=0;a<rows;a++){
    if(a==0){
        printf("%s",boxTL);
    }
printf("%s",boxX);
if(a==rows-1){
    printf("%s\n",boxTR);
}
}
for (i = 0; i < cols; i++) {
  for (j = 0; j < rows; j++) {
    if(j==0){
        printf("%s",boxY);
    }
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
    printf("%s",boxY);
}
    if(i==0&&j==rows-1){
        printf("  score:%d",score);
    }
    if(i==1&&j==rows-1||i==2&&j==rows-1){
        printf(" ");
        for(int a=0;a<nextBox;a++){
            if (matrix[i-1][a]==0){
           printf(" ");
            }
            if (matrix[i-1][a]==1){
            printf("#");
            }      
        }
    }
    if(j==rows-1){
        printf("\n");
    }
  }
}
for(int b=0;b<rows;b++){
if(b==0){
    printf("%s",boxBL);
}
printf("%s",boxX);

if(b==rows-1){
    printf("%s\n",boxBR);
}
}
    //fflush(stdout);
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
    for(int i=0; i<7;i+=2){
        array[CordArray[i]][CordArray[i+1]]=2;
    }
   int block = spawnBlock(rows,cols,array,CordArray,0);
        findBlockCords(rows,cols,array,CordArray);
        checkLines(rows,cols,array);
    return block;
}
void groundGravity(int rows, int cols ,int **array,int *listToClear,int index){

    for (int i = index-1;i>=0;i--){
        for(int j = listToClear[i];j>1;j--){
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
    int i,j;
    for(i=0;i<index;i++){
  for(j=0; j<rows;j++){
        array[listToClear[i]][j]=0;
    }
    }
    groundGravity(rows, cols, array, listToClear, index);
    return;
}
void checkLines(int rows, int cols ,int **array){
    int linesToClear[4];
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
        }
    }
    
    if(anotherIndex > 0){
        clearLines(rows,cols,array,linesToClear,anotherIndex);
        givePoints(anotherIndex);
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
        //Transpose
        int box2[4][4]={0};
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                box2[i][j] = box[j][i];
                //box[i][j] = 0;
            }
        }
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
        //Transpose
        int matrix2[3][3]={0};

        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                matrix2[i][j] = matrix[j][i];
            }
        }
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
            //printf("too far up/right");
            return;
        }
        if(newCordArray[i+1]+padding<0||newCordArray[i]+paddingY<0){
            //printf("too far left");
            return;
        }
        if(array[newCordArray[i]+paddingY][newCordArray[i+1]+padding]==2){
            //printf("colision");
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
    if(CordArray[i-1]+1 > cols-1){
        int block = setGround(rows,cols,array,CordArray);
        return block;
    }
        if(array[CordArray[i-1]+1][CordArray[i]] == 2){
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
                return 0;
}

int main(void) {
    srand(time(NULL));
    int rows=0;
    int columns=0;
    setlocale(LC_CTYPE,"");
    char *textMode = setlocale(LC_CTYPE,NULL);
    if(strstr(textMode,".UTF-8")||strstr(textMode,".utf8")){
        UTF = textMode;
    }else{
    UTF = setlocale(LC_ALL,".UTF-8");
    }
    printf("How many rows\n");
    //fflush(stdout);
    scanf("%d",&rows);  
    printf("rows:%d\n",rows);
    printf("how many columns\n");
    //fflush(stdout);
    scanf("%d",&columns);
    printf("columns:%d\n",columns);
    if(rows < 5||columns<5){
        printf("to few rows/columns\n");
        //fflush(stdout);
        rows=10;
        columns=16;
    }
     int **GameState = malloc(sizeof(int *)*columns);
    if(GameState == NULL){
        printf("malloc is fucked");
        return 1;
    }

     reset:
     score=0;
     totalLinesCleared=0;
    long t = uniTime();
    long currentT = uniTime();
     resetGameState(rows,columns,GameState);
     int CordArray[8] = {0};
     int block = spawnBlock(rows,columns,GameState,CordArray,0);
     int currentBlock = block;
                 printGameState(rows,columns,GameState);
     //int rotState;
while (1 == 1)
{
    currentT = uniTime();
    if(currentT - t >= 500){
        t=currentT;
        int temp = advanceState(rows,columns,GameState,CordArray);
            if(temp == -1){
                break;
            }
            if(temp != 0){
                currentBlock = temp;
            }
        currentT = uniTime();
            clearScreen();//!Remove to debug
                            printf("\n\n\n");
            printGameState(rows,columns,GameState);
    }
    char input;
int linput;
linput = _kbhit();
if(linput){
    #ifdef _WIN32
input = _getch();
if(input==224||input==0||input == -32){
    input = _getch();
    switch(input){
        case UP_ARROW:
        input='e';
        break;
        case DOWN_ARROW:
        input='s';
        break;
        case LEFT_ARROW:
        input='a';
        break;
        case RIGHT_ARROW:
        input='d';
        break;
    }
}
    #else
    input = linput;
    int newinput;
    if(input==27){
        input=_kbhit();
        input=_kbhit();
        switch(input){
        case UP_ARROW:
        input='e';
        break;
        case DOWN_ARROW:
        input='s';
        break;
        case LEFT_ARROW:
        input='a';
        break;
        case RIGHT_ARROW:
        input='d';
        break;
        default:
        input = '\e';
        break;
        }
    
    }
    #endif
printf("key code %d \n",input);
//fflush(stdout);
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
        if(input == '\e'){
            printf("Quiting\n");
            break;
        }
        if(input =='e'){
            rotateRight(rows,columns,GameState,CordArray,currentBlock);
        }
        if(input =='q'){
            rotateLeft(rows,columns,GameState,CordArray,currentBlock);
        }
            clearScreen();//!Remove to debug
            printf("\n\n\n");
            printGameState(rows,columns,GameState);
}
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
    printf("GAME OVER\n");
    return 0;
}

int spawnBlock(int rows, int cols ,int **array,int *CordArray,int num){
    int checkFlag=0;
    int rNum;
    int flag=0;
    if(num==0){
    rotState = 0;
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