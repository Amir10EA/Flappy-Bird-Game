class CheckersBoard{
public:
 CheckersBoard();
 void move(int fromRow, int fromCol, int toRow, int toCol){
 unsigned short temp = board[fromRow]; 
 board[fromRow] &= ~(board[fromRow] << fromCol*2 && 3U);
 board[toRow] &= ~((board[toRow] << toCol*2) && 3U);
 board[toRow] &= ((board[toRow] << toCol*2) || (temp << fromCol*2 && 3));   
 }

private:
 unsigned short board[8];
};