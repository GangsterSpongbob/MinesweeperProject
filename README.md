# MinesweeperProject

### Description:
#### Project No. 7 - Minesweeper

A take on the classic game Minesweeper. The idea of the game is to uncover all tiles without mines while avoiding uncovering any tiles that do contain mines. To do so evety tile that does not contain a mine insted contains a number showing how many adjacent mined tiles it has (if it has none the number is 0 but is not shown). This specific version of the game has a couple of minor tweaks including:

1. Minefield is pre-generated and there is never a 100% guarantee that the first opened tile is not a mine. Furthermore, that means that not all fields are solvable.
2. The remaining mines counter only counts marks on tiles that the player has placed. It does not in any way reflect on the actual number of mines on the field.
3. The minimum number of tiles is 9 (3x3 grid) and since the maximum number of mines is 3 x n (where n is the size of the field), which means that can be a 9-tile field in which every tile contains a mine (which is in fact easily solvable).

The game is made c++ and its GUI consists of built-in just console output operations.

##### Author - Angel Ivanov
