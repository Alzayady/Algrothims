class Solution {
public:
    bool takenInRow[10][10]{false};
bool takenInCol[10][10]{false};
bool takenInSqu[10][10]{false};
bool valid(int i, int j){
    return i<9 && j<9;
}
int sq(int x,int y){
   int row=x/3;
   int col=y/3;
   return row*3+col;
}

bool solve(vector<vector<char>>& board , int x, int y){
    if(board[x][y] =='.'){
        for(char i='1';i<='9';i++) {
            if(!takenInRow[x][i-'1'] &&
            !takenInCol[y][i-'1'] &&
            !takenInSqu[(sq(x,y))][i-'1']){
                board[x][y]=i;
                takenInRow[x][i-'1'] = true;
                takenInCol[y][i-'1'] = true;
                takenInSqu[(sq(x,y))][i-'1']= true;
               
                if(x==8 && y==8) return true;
                 if(valid(x,y+1) ){
                   if (  solve(board,x,y+1)) return true;
                     takenInRow[x][i-'1'] = false;
                     takenInCol[y][i-'1'] = false;
                     takenInSqu[(sq(x,y))][i-'1'] = false;
                     board[x][y] = '.';
                     continue;
                 } 
                   if( solve(board,x+1,0)) return true;
                    takenInRow[x][i-'1'] = false;
                    takenInCol[y][i-'1'] = false;
                    takenInSqu[(sq(x,y))][i-'1'] = false;
                    board[x][y] = '.';
            }
        }
    } else{
        if(x==8&&y==8)return true;
        if(valid(x,y+1) ){
            return solve(board,x,y+1);
        }
        return solve(board,x+1,0) ;
    }
    return false;
}
void solveSudoku(vector<vector<char>>& board) {
    for(int i=0;i<board.size();i++){
        for(int j=0;j<board[0].size();j++){
            if(board[i][j]!='.'){
                takenInRow[i][board[i][j]-'1']=true;
                takenInCol[j][board[i][j]-'1']=true;
                takenInSqu[sq(i,j)][board[i][j]-'1']= true;
            }
        }
    }
    solve(board,0,0);
}
};
