#include<iostream>
#include<cmath>
#include<set>
using namespace std;
#define N 9

bool checkRow(int grid[][N],int row){
    set<int> st;
    for(int i=0;i<N;i++){
        if(st.find(grid[row][i])!=st.end()) return false;
        if(grid[row][i] != 0) st.insert(grid[row][i]);
    }
    return true;
}
bool checkCol(int grid[][N],int col){
    set<int> st;
    for(int i=0;i<N;i++){
        if(st.find(grid[i][col])!=st.end()) return false;
        if(grid[i][col] != 0) st.insert(grid[i][col]);
    }
    return true;
}
bool checkBox(int grid[][N],int startRow,int startCol){
    set<char> st;
    for(int i=0;i<(int)sqrt(N);i++){
        for(int j=0;j<(int)sqrt(N);j++){
            int x = grid[i+startRow][j+startCol];
            if(st.find(x)!=st.end()) return false;
            if(x!=0) st.insert(x);
        }
    }
}
bool isValid(int grid[][N], int row, int col){ 
    return checkRow(grid, row) && checkCol(grid, col) && 
           checkBox(grid, row - row % (int)sqrt(N), col - col % (int)sqrt(N)); 
} 
bool noDuplicacy(int grid[][N]){ 
    for (int i=0;i<N;i++){ 
        for (int j=0;j<N;j++){
            if (!isValid(grid, i, j)) 
                return false; 
        } 
    } 
    return true; 
} 

bool isSudokuUnsolved(int grid[][N]){
    int i,j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            if(grid[i][j] == 0){
                return true;
            }
        }
    }
    return false;
}

bool isInRange(int grid[][N]){
    int i,j;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            if(grid[i][j]<0 || grid[i][j] > N){
                return false;
            }
        }
    }
    return true;
}

bool sudokuChecker(int grid[][N]){
    if(!isInRange(grid)) return false;
    if(noDuplicacy(grid)==false) return false;
    return true;
}

bool isSudokuInvalid(int grid[][N]){
    if(!isInRange(grid)){
        cout<<endl<<"Invalid Sudoku. Numbers must be between 1 and "<<N<<endl;
        return true;
    }
    if(!noDuplicacy(grid)){
        cout<<endl<<"Invalid Sudoku. Duplicate Numbers in Sudoku"<<endl;
        return true;
    }
    return false;
}

bool isPossible(int grid[][N],int x,int y,int num){
    int i,j;
    for(i=0;i<N;i++)
        if(grid[i][y] == num)
            return false;
    for(j=0;j<N;j++)
        if(grid[x][j] == num)
            return false;
    int subBox_N = (int)sqrt(N);
    int subX = x - x % subBox_N;
    int subY = y - y % subBox_N;
    for(i=0;i<subBox_N;i++)
        for(j=0;j<subBox_N;j++)
            if(grid[i+subX][j+subY] == num)
                return false;
    return true;
}

bool sudokuSolver(int grid[][N],int x,int y){
    if(x==N-1 && y==N) return true;
    if(y==N){
        x++;
        y=0;
    }
    if(grid[x][y]>0)
        return sudokuSolver(grid,x,y+1);
    for(int num=1;num<=N;num++){
        if(isPossible(grid,x,y,num)){
            grid[x][y] = num;
            if(sudokuSolver(grid,x,y+1))
                return true;
        }
        grid[x][y] = 0;
    }
    return false;
}

void printSudoku(int grid[][N]){
    cout<<endl;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(grid[i][j] == 0)
                cout<<"- ";
            else
                cout<<grid[i][j]<<" ";
            if((j+1)%((int)sqrt(N))==0 && (j+1) != N) cout<<"| ";
        }
        cout<<endl;
        if((i+1)%((int)sqrt(N))==0 && (i+1) != N) cout<<endl;
    }
    cout<<endl;
}

int main(){
    int grid[N][N] = {0};
    int i,j;
    cout<<"\nINPUT THE SUDOKU\nInstructions:\n1. Enter numbers separated by whitespaces.\n2. Enter '0' for empty places): "<<endl<<endl;
    while(true){
        for(i=0;i<N;i++){
            cout<<"Fill Row "<<i+1<<": ";
            for(j=0;j<N;j++)
                cin>>grid[i][j];
            cout<<"Row "<<i+1<<" Completed"<<endl;
        }
        cout<<"Entered Sudoku: "<<endl;
        printSudoku(grid);
        cout<<endl<<"Continue?(Press 'Y' for Yes) : ";
        char ch;
        cin>>ch;
        if(ch=='Y'||ch=='y'){
            if(!isSudokuUnsolved(grid)){
                cout<<endl<<"Complete Sudoku. No Empty Space(s) found."<<endl;
                cout<<"Would you like to check if the Entered Sudoku is Correct or Not?(Press 'Y' for Yes) : ";
                char ch;
                cin>>ch;
                if(ch=='Y'||ch=='y'){
                    if(sudokuChecker(grid))
                        cout<<endl<<"The Sudoku is CORRECT"<<endl;
                    else
                        cout<<endl<<"The Sudoku is INCORRECT"<<endl;
                    cout<<endl<<"Fill New Sudoku?(Press 'Y' for Yes) : ";
                    char ch;
                    cin>>ch;
                    if(ch=='y'||ch=='Y') continue;
                    else return 0;
                }
                else return 0;    
            }
            if(isSudokuInvalid(grid)){
                cout<<endl<<"Refill the Sudoku?(Press 'Y' for Yes) : ";
                char ch;
                cin>>ch;
                if(ch=='y'||ch=='Y') continue;
                else return 0;
            }
            else break;
        }
    }
    if(sudokuSolver(grid,0,0)){
        cout<<"ANSWER:"<<endl;
        printSudoku(grid);
    }
    else
        cout<<"Unsolvable Sudoku!"<<endl;
    return 0;
}