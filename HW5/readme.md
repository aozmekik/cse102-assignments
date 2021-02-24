# CSE102 – Computer Programming (Spring 2018)

# Homework #

## Handed out : 11:30am Wednesday April 5, 2018.

## Due : 11:55pm Sunday April 15, 2018.

**Hand-in Policy** : Via Moodle. No late submissions will be accepted.
**Collaboration Policy** : No collaboration is permitted.
**Grading** : This homework will be graded on the scale of 100.

**Description** : In this homework, you will implement Turkish Draughts board game. The rules of the game
are listed below.
1) There is a 8x8 board.
2) Each player starts with 16 men (white and black) placed on all the squares of the second and
third rows (see Figure 1). All the squares are used.
3) Men ́s moves: They move one square horizontally or vertically forwards, never backwards (see
Figure 2).
4) Kings moves: They move and jump vertically and horizontally any number of squares (see Figure
2 ).
5) A man captures by jumping to a vacant square in the moveable direction (rule 3) beyond a piece
of the opponent.
6) A king captures by jumping to a vacant square beyond an adverse piece, any distance away.
7) Maximum capture compulsory: If there are two or more different chances to make capture, it is
compulsory to make the move that captures the maximum amount of the opponent ́s pieces.
8) Taking away the captured pieces: Captured pieces are taken away from the board.
9) If a player has no legal move he loses the game. This may come about either by being eliminated
or being blocked completely – no moves left.

You must use the functions listed below. You may add other functions if you think there is need for it.

**typedef enum {white_man, black_man, white_king, black_king, empty} piece;**
You must use this enumeration to define the pieces on the board.

**typedef enum {white = 10, black = 20} player;**
You must use this enumeration to define the players.

**void init_board(piece board[][8]);**
This function initializes the board as mentioned in the second rule.

**int move(piece board[][8], int from_x, int from_y, int to_x, int to_y, player p);**
This function checks if the given player p can move a piece belonging to it from location (from_x,
from_y) to location (to_x,to_y). If the players move is not allowed the function returns:
 -1: The player p is trying to move a piece that does not belong to him.
 -2: The move is not allowed.
 n>=0: The move is allowed and it is executed with n of opponents pieces captured.

**int check_end_of_game(piece board[][8]);**
This function checks if the game has been completed after the move. It returns:
 -1: Game continues.
 white: White wins the game.


```
 black: Black wins the game.
```
**void display_board(piece board[][8]);**
This function displays the board in current state. The following symbols should be used for
printing:
 ‘-‘: Empty squares.
 ‘b’: The regular black pieces.
 ‘B’: The black kings.
 ‘w’: The regular white pieces.
 ‘W’: The white kings.
Sample outputs are shown below:

**void sample_game_1();**
This function should use the above functions to play end-to-end a game. You may want to find a
famous game and replay it in this function.

**void sample_game_2();**
This function should use the above functions to play the game given in the following gif
animation.
[http://damaakademisi.com/wp-content/uploads/2009/02/10puan_1.gif](http://damaakademisi.com/wp-content/uploads/2009/02/10puan_1.gif)


```
Figure 1 Starting position.
```
_Figure 2 Men’s (left) and king’s (right) moves._


