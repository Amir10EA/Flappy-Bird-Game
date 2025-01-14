class CheckersBoard{
public:
 CheckersBoard();
 void move(int fromRow, int fromCol, int toRow, int toCol);

private:
 unsigned short board[8];
};

void CheckersBoard::move(int fromRow, int fromCol, int toRow, int toCol){
unsigned short mask = (board[fromRow] >> fromCol*2) & 3U;
board[fromRow] &= ~(3U << fromCol*2);
board[toRow] &= ~(3U << toRow*2);
board[toRow] |= (mask << toCol*2);
}