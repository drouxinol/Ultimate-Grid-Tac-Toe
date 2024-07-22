!Ultimate Tic-Tac-Toe!



Project Summary:
This project was developed as part of the Programming course in the Bachelor's degree in Computer Engineering. The goal was to create an interactive game called Ultimate Tic-Tac-Toe using the C programming language.

Ultimate Tic-Tac-Toe consists of a fixed 3x3 matrix, where each of the nine positions is a Tic-Tac-Toe game in itself. The available game modes are Multiplayer (two players) and Singleplayer (one player against the computer). The first move randomly determines the board to be played, but subsequent moves depend on the position where the piece was placed in the previous turn. For example, placing a piece in position (1,1) on board 9 directs the next player to board 5.

![Imagem1](https://github.com/user-attachments/assets/1e70b71e-f693-4aa5-8db4-823de384433c)


Program Features:
Before the game starts, the program checks for the existence of a binary file to import a previously saved game. If found, the player can choose to import the game; otherwise, a new game begins. After each move, the program checks for a win or draw on the played board. When a player wins a board, they play again to keep the game dynamic. The won board is marked and becomes unavailable for future moves.

The game continues until there is a winner, determined when a line of won boards (horizontal, vertical, or diagonal) is formed in the main matrix. To facilitate this verification, an auxiliary matrix stores the winning letters of the boards. If a line in the auxiliary matrix contains the same letter, the game is won by that player. 

Data Structures Used:
Two main data structures were used:

    Matrix: Represents the Tic-Tac-Toe boards, containing variables like letra_venc to store the winner's letter, continua to indicate board availability, and the board's matrix itself.
    Linked List: Stores information about each move, with variables for specific details and a pointer to the next cell in the list.

User Manual:
The game is simple to play. At the beginning, the player can choose to import a saved game. The game modes are Multiplayer and Singleplayer. After selecting the game mode, a menu offers three options:

    Play, inserting the piece in a valid position.
    Check the last x moves, where x is defined by the player.
    Exit the game, saving the progress in a binary file and recording all moves in a text file.

Conclusion:
Developing Ultimate Tic-Tac-Toe in C was an enriching experience. Implementing nine interlinked boards added complexity to the game, requiring precise logic for rules and interactions. The project included flexible game modes, allowing both player competitions and challenges against the computer.

