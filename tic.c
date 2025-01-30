#include <stdio.h>

#define PLAYER 'X'
#define AI 'O'
#define EMPTY ' '

void printBoard(char board[3][3]);
int checkWinner(char board[3][3]);
int isMovesLeft(char board[3][3]);
int minimax(char board[3][3], int depth, int isMax);
void bestMove(char board[3][3]);
void makeMove(char board[3][3], int move, char player);

void printBoard(char board[3][3]){
	printf("\n");
	for (int row = 0; row < 3; row++){
		for (int col = 0; col < 3; col++){
			printf(" %c ", board[row][col]);
			if (col < 2) printf("|");
		}
		printf("\n");
		if (row < 2) printf("---|---|---\n");
	}
	printf("\n");
}

int checkWinner(char board[3][3]){
	for (int row = 0; row < 3; row++){
		if (board[row][0] == board[row][1] && board[row][1] == board[row][2]){
			if (board[row][0] == PLAYER) return 10;
			else if (board[row][0] == AI) return -10;
			}
	}
	
	for (int col = 0; col < 3; col++){
		if (board[0][col] == board[1][col] && board[1][col] == board[2][col]){
			if (board[0][col] == PLAYER) return 10;
			else if (board[0][col] == AI) return -10;
		}
	}
	
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2]){
		if (board[0][0] == PLAYER) return 10; 
		else if (board[0][0] == AI) return -10;
	}
	if (board[0][2] == board[1][1] && board[1][1] == board[2][0]){
		if (board[0][2] == PLAYER) return 10;
		else if (board[0][2] == AI) return -10;
	}
	return 0;
}

int isMovesLeft(char board[3][3]){
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (board[i][j] == EMPTY)
				return 1;
	return 0;
}

int minimax(char board[3][3], int depth, int isMax){
	int score = checkWinner(board);
	if (score == -10) return score;
	if (score == 10) return score;
	if (!isMovesLeft(board)) return 0;
	if (isMax){
		int best = -1000;
		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++){
				if (board[i][j] == EMPTY){
					board[i][j] = AI;
					int moveScore = minimax(board, depth + 1, 0);
					best = (best > moveScore) ? best : moveScore;
					board[i][j] = EMPTY;
				}
			}
		}
		return best;
	}else{
		int best = 1000;
		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++){
				if (board[i][j] == EMPTY){
					board[i][j] = PLAYER;
					int moveScore = minimax(board, depth + 1, 1);
					best = (best < moveScore) ? best : moveScore;
					board[i][j] = EMPTY;
				}
			}
		}
		return best;
	}
}

void bestMove(char board[3][3]){
	int bestVal = -1000;
	int row = -1, col = -1;

	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			if (board[i][j] == EMPTY){
			board[i][j] = AI;
			if (checkWinner(board) == -10) {
				return;
			}
			board[i][j] = EMPTY;
			}
		}
	}
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			if (board[i][j] == EMPTY){
				board[i][j] = PLAYER;
				if (checkWinner(board) == 10){
					board[i][j] = AI;
					return;
				}
				board[i][j] = EMPTY;
			}
		}
	}
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			if (board[i][j] == EMPTY){
				board[i][j] = AI;
				int moveVal = minimax(board, 0, 0);
				board[i][j] = EMPTY;
				if (moveVal > bestVal) {
					row = i;
					col = j;
					bestVal = moveVal;
				}
			}
		}
	}
	if (row != -1 && col != -1){
		board[row][col] = AI;
	}
}

void makeMove(char board[3][3], int move, char player){
	board[move / 3][move % 3] = player;
}

int main(){
	char board[3][3] = {
		{EMPTY, EMPTY, EMPTY},
		{EMPTY, EMPTY, EMPTY},
		{EMPTY, EMPTY, EMPTY}};

	int move;
	
	printf("Jogo da velha\n");
	printBoard(board);
	
	while (1){
		printf("\nDigite sua jogada (1-9, 0 para sair)\n");
		scanf("%d", &move);
		
		if (move == 0){
			printf("Jogo finalizado.\n");
			break;
		}
		
		if (move < 1 || move > 9 || board[(move-1)/3][(move-1)%3] != EMPTY){
			printf("Jogada inválida.\n");
			continue;
		}
		
		makeMove(board, move - 1, PLAYER);
		printBoard(board);
		
		if (checkWinner(board) == 10){
			printf("O jogador vence!\n");
			break;
		} else if (!isMovesLeft(board)){
			printf("Empate!\n");
			break;
		}
		bestMove(board);
		printBoard(board);
		
		if (checkWinner(board) == -10){
			printf("A IA vence!\n");
			break;
		}else if (!isMovesLeft(board)){
			printf("Empate\n");
			break;
		}
	}
	
	return 0;
}
