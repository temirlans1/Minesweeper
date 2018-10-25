#include <stdio.h>
#include <time.h>
char map[100][100];
int view[100][100];
int n,m;
int mine_count = 0;

int addProximities(int i, int j){
    int c = 0;
    if(map[i+1][j-1] == '*')c++;
    if(map[i+1][j] == '*')c++;
    if(map[i+1][j+1] == '*')c++;
    if(map[i][j-1] == '*')c++;
    if(map[i][j+1] == '*')c++;
    if(map[i-1][j-1] == '*')c++;
    if(map[i-1][j] == '*')c++;
    if(map[i-1][j+1] == '*')c++;
    return c;
}

void show_map(){
    printf("#  ");
    for(int i=1;i<=m;i++){
        printf("%i ", i);
        if(i<10)printf(" ");
    }
    printf("\n");
    for(int i=1;i<=n;i++){
        printf("%i ", i);
        if(i<10)printf(" ");
        for(int j=1;j<=m;j++){
            if(view[i][j]==1)printf("%c  ", map[i][j]);
            else
                if(view[i][j]==2)printf("F  ");
            else printf("~  ");
            //printf("%c  ", map[i][j]);
        }
        printf("\n");
    }
}

void end_game(int x,int y, int w){
    printf("# ");
    for(int i=1;i<=m;i++){
        printf("%i ", i);
        if(i<10)printf(" ");
    }
    printf("\n");
    for(int i=1;i<=n;i++){
        printf("%i ", i);
        if(i<10)printf(" ");
        for(int j=1;j<=m;j++){
            if(i==x && j==y && w==0)printf("X  ");
            else printf("%c  ", map[i][j]);
        }
        printf("\n");
    }
}

void open_free(int x,int y, int prex, int prey){
    //printf("open_free entered: %i, %i, %i, %i\n", x,y,prex,prey);
    if(view[x][y] != 2){
        view[x][y]=1;
        if(x!=0 && y!=0){
            if(map[x+1][y-1] == '.' && view[x+1][y-1]==0)open_free(x+1,y-1,x,y);
            if(map[x+1][y] == '.' && view[x+1][y]==0)open_free(x+1,y,x,y);
            if(map[x+1][y+1] == '.' && view[x+1][y+1]==0)open_free(x+1,y+1,x,y);
            if(map[x][y-1] == '.' && view[x][y-1]==0)open_free(x,y-1,x,y);
            if(map[x][y+1] == '.' && view[x][y+1]==0)open_free(x,y+1,x,y);
            if(map[x-1][y-1] == '.' && view[x-1][y-1]==0)open_free(x-1,y-1,x,y);
            if(map[x-1][y] == '.' && view[x-1][y]==0)open_free(x-1,y,x,y);
            if(map[x-1][y+1] == '.' && view[x-1][y+1]==0)open_free(x-1,y+1,x,y);
        }
        if(x!=0 && y!=0){
            if(map[x+1][y-1] >= '0' && map[x+1][y-1] <= '9')view[x+1][y-1]=1;
            if(map[x+1][y] >= '0' && map[x+1][y] <= '9')view[x+1][y]=1;
            if(map[x+1][y+1] >= '0' && map[x+1][y+1] <= '9')view[x+1][y+1]=1;
            if(map[x][y-1] >= '0' && map[x][y-1] <= '9')view[x][y-1]=1;
            if(map[x][y+1] >= '0' && map[x][y+1] <= '9')view[x][y+1]=1;
            if(map[x-1][y-1] >= '0' && map[x-1][y-1] <= '9')view[x-1][y-1]=1;
            if(map[x-1][y] >= '0' && map[x-1][y] <= '9')view[x-1][y]=1;
            if(map[x-1][y+1] >= '0' && map[x-1][y+1] <= '9')view[x-1][y+1]=1;
        }
    }
}

int check_win(){
    int c = 0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(view[i][j]==0)c++;
            if(view[i][j]==2 && map[i][j]=='*')c++;
        }
    }
    if(c == mine_count)return 1;
    else return 0;
}

int main()
{
    setvbuf(stdout, NULL, _IONBF, 0);
    srand(time(NULL));
    printf("Welcome to the Minesweeper!!!\n");
    printf("Please, enter a directions of the map: ");
    scanf("%i %i", &n, &m);
    printf("Please, enter a number of MINES in the map: ");
    while(1){
        scanf("%i", &mine_count);
        if(mine_count > n*m){
            printf("\nInvalid number! Please, re-enter: ");
        }
        else break;
    }



    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++){
            map[i][j] = '.';
            view[i][j] = 0;
        }
    }

    for(int i=0;i<mine_count;i++){
        int row = rand() %n + 1, column = rand()%m + 1;
        while(map[row][column] == '*'){
            row = rand()%n + 1;
            column = rand()%m + 1;
        }
        map[row][column] = '*';
        //view[row][column] = 1;
    }

    /*printf("map with mines\n");
    for(int i=0;i<=13;i++){
        for(int j=0;j<=31;j++){
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
*/
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(map[i][j] != '*'){
                int c = addProximities(i,j);
                if(c >0)map[i][j] = c + '0';
                //view[i][j] = 1;
            }
        }
    }

/*    printf("map with mines and numbers\n");
    for(int i=1;i<=12;i++){
        for(int j=1;j<=30;j++){
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
*/
    while(1){
        int r, c, cmd;
        /*for(int i=1;i<=12;i++){
            for(int j=1;j<=30;j++){
                if(view[i][j] == 0)printf("%c", map[i][j]);
                else printf("x");
            }
            printf("\n");
        }*/
        show_map();
        printf("'0' - to put a FLAG || '1' - to remove a FLAG || '2' - to uncover a cell: \n");
        scanf("%i", &cmd);
        if(cmd == 0){
            printf("Enter row, column of the map you want to flag: \n");
            scanf("%i %i", &r, &c);
            if(r<1 || r>n || c<1 || c>m){
                printf("Invalid numbers!\n");
            }
            else view[r][c] = 2;
        }
        if(cmd == 1){
            printf("Enter row, column of the map you want to remove flag: \n");
            scanf("%i %i", &r, &c);
            if(r<1 || r>n || c<1 || c>m){
                printf("Invalid numbers!\n");
            }
            else view[r][c] = 0;
        }
        if(cmd == 2){
            printf("Enter row, column of the map you want to uncover: \n");
            scanf("%i %i", &r, &c);
            if(r<1 || r>n || c<1 || c>m){
                printf("Invalid numbers!\n");
            }
            if(map[r][c]=='*'){
                printf("You LOSE!\n");
                end_game(r,c,0);
                return 0;
            }
            else if(map[r][c] == '.'){
                open_free(r,c,r,c);
            }
            else {
                view[r][c]=1;
            }
            if(check_win() == 1){
                printf("You WON!\n");
                end_game(r,c,1);
                return 0;
            }
        }

    }


    return 0;
}
