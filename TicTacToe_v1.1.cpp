#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
#endif

#include <bits/stdc++.h>
#include <thread>
#include <chrono>
#include <random>

using namespace std;

random_device rd;
mt19937 gen(rd());

class TicTacToe {
public:
    struct Move {
        int row;
        int col;
    };

    void clearRow(int num) {
        while (num--) {
            cout << "\033[A\033[2K\r";
        } 
    }

    void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    string input() {
        // Buffer handler
        #ifdef _WIN32
            while (_kbhit()) {
                _getch(); 
            }
        #else
            tcflush(STDIN_FILENO, TCIFLUSH); 
        #endif
        cin.clear();
        
        string data;
        getline(cin, data);
        return data;
    }

    void invalidInputWarning() {
        cout << invalidInputWarningText[random(0, (int)invalidInputWarningText.size() - 1)];
        this_thread::sleep_for(chrono::milliseconds(500));
    }

    int random(int low, int high) {
        uniform_int_distribution<> range(low, high);
        return range(gen);
    }

    void startMenu() {
        loadingScreen(random(1, 3));

        cout << " _ _ _ _ _ _ _ _ _   _ _ _    _ _ _\n";
        cout << "|                 | |_   _|  / _ _/\n";
        cout << "|                 |   | |   / /\n";
        cout << "|_ _ _       _ _ _|  _| |_  \\ \\_ _\n";
        cout << "      |     |       |_ _ _|  \\_ __\\\n";
        cout << "      |     |       ___       _ _ _\n";
        cout << "      |     |      / _ \\     / _ _/\n";
        cout << "      |     |     / /_\\ \\   / /\n";
        cout << "      |     |    /  _ _  \\  \\ \\_ _\n";
        cout << "      |     |   /__/   \\__\\  \\_ __\\\n";
        cout << "      |     |     __ __     ______\n";
        cout << "      |     |    / _ _ \\   |  __ _|\n";
        cout << "      |     |   / /   \\ \\  | |_ __\n";
        cout << "      |     |  ( (     ) ) |  __ _|\n";
        cout << "      |     |   \\ \\_ _/ /  | |_ __\n";
        cout << "      |     |    \\__ __/   |______|\n";
        cout << "      |     |\n";
        cout << "      |_ _ _|           v.1.1\n\n";
        cout << "=======================================\n\n";
        cout << "             [1] New game\n\n";
        cout << "             [2] Credit\n\n";
        cout << "             [3] Exit\n\n";

        string playerInput;

        while (true) { 
            cout << ">>> Input: ";
            playerInput = input();

            if (playerInput == "1" || playerInput == "2" || playerInput == "3") {
                break;
            }
            
            invalidInputWarning();
            clearRow(2);
        }

        if (playerInput == "1") {
            selectionMenu();
        }
        else if (playerInput == "2") {
            creditMenu();              
        }
        else if (playerInput == "3") {
            exitingGame(random(1, 2));
        }
    }

    void selectionMenu() {
        loadingScreen(random(1, 2));

        string firstPlayerInput;
        string difficulty;

        cout << "Creating a game...\n\n";
        cout << "Who to play first?\n";
        cout << "[1] Player\n";
        cout << "[2] Bot\n";
        cout << "[3] Random\n\n";
        
        while (true) {
            cout << ">>> Your choice: ";
            firstPlayerInput = input();
            
            if (firstPlayerInput == "1" || firstPlayerInput == "2" || firstPlayerInput == "3") {
                break;
            }

            invalidInputWarning();
            clearRow(2);
        }

        if (firstPlayerInput == "1") {
                firstPlayer = 1;
        }
        else if (firstPlayerInput == "2") {
            firstPlayer = 2;
        }
        else if (firstPlayerInput == "3") {
            firstPlayer = random(1, 2);
        }

        loadingScreen(random(1, 2));

        cout << "Creating a game...\n\n";
        cout << "Choose a difficulty.\n";
        cout << "[1] -- Baby --\n";
        cout << "The Bot plays randomly (because babies don't know how to play Tic Tac Toe, duh).\n\n";
        cout << "[2] -- Easy --\n";
        cout << "The Bot plays passively.\n\n";
        cout << "[3] -- Normal --\n";
        cout << "The Bot plays decently, though it makes mistakes sometimes.\n\n";
        cout << "[4] -- Hard --\n";
        cout << "The Bot is VERY smart. It makes few to no mistakes.\n\n";
        cout << "[5] -- IMPOSSIBLE --\n";
        cout << "You will be annihilated.\n\n";
        
        while (true) {
            cout << ">>> Your choice: ";
            difficulty = input();

            if (difficulty == "1" || difficulty == "2" || difficulty == "3" || difficulty == "4" || difficulty == "5") {
                break;
            }
            
            invalidInputWarning();
            clearRow(2);
        }

        botDifficulty = stoi(difficulty);

        playerScore = botScore = 0;

        initGame();
    }

    void endMenu(char result) {
        loadingScreen(1);

        if (result == 'D') {
            playerScore += 0.5;
            botScore += 0.5;

            cout << "It's a Draw!\n\n";
            cout << "Player and Bot both get 0.5 points.\n\n";
        }
        else if (result == 'X') {
            ++playerScore;

            cout << "Player Won!\n\n";
            cout << "Player gets 1 point.\n\n";
        }
        else {
            ++botScore;

            cout << "You Lost!\n\n";
            cout << "Bot gets 1 point.\n\n";
        }

        cout << "[1] Rematch.\n";
        cout << "[2] New game.\n";
        cout << "[3] Back to Start.\n\n";

        string playerInput;

        while (true) {
            cout << ">>> Input: ";
            playerInput = input();

            if (playerInput == "1" || playerInput == "2" || playerInput == "3") {
                break;
            }

            invalidInputWarning();
            clearRow(2);
        }

        if (playerInput == "1") {
            initGame();
        }
        else if (playerInput == "2") {
            selectionMenu();
        }
        else if (playerInput == "3") {
            startMenu();
        }
    }

    void creditMenu() {
        loadingScreen(1);

        cout << "========== CREDIT ==========\n\n";
        cout << "Lead Developer: Nguyen Tien Dat.\n";
        cout << "Programmer: Nguyen Tien Dat.\n";
        cout << "Game Designer: Nguyen Tien Dat.\n";
        cout << "Sound Designer: Nguyen Tien Dat.\n";
        cout << "Graphic Designer: Nguyen Tien Dat.\n";
        cout << "Tester: Nguyen Tien Dat.\n";
        cout << "Writer: Nguyen Tien Dat.\n\n";

        cout << "Player: You\n\n";

        cout << "'I made this garbage in 2 days lol' - Nguyen Tien Dat\n\n\n";

        string anyInput;

        cout << "[Press any key(s) + Enter (or just Enter) to go back]\n\n";
        
        anyInput = input();

        startMenu();
    }

    void initGame() {
        loadingScreen(random(1, 3));

        board = vector<vector<char>>(3, vector<char>(3, '-'));
        currentPlayer = firstPlayer;
        char result = '-';

        cout << "Player vs Bot (" << difficultyName[botDifficulty - 1] << ")\n";
        cout << "Score: " << playerScore << " - " << botScore << "\n\n";
        cout << "-------------------------------------------------\n\n";

        while (result == '-') {
            result = checkWinner();

            if (result != '-') {
                break;
            }

            displayBoard();

            if (currentPlayer == 1) {
                cout << "Your turn.\n\n";
                string row, col;

                while (true) {
                    cout << ">>> Row: ";
                    row = input();
                    cout << ">>> Column: ";
                    col = input();

                    if (isValidMove(row, col)) {
                        board[row[0] - '0'][col[0] - '0'] = 'X';
                        clearRow(9);
                        break;
                    }

                    invalidInputWarning();
                    clearRow(3);
                }
            }
            else {
                botIsThinking(random(1, 3));
                botMakeMove();
                clearRow(5);
            }

            currentPlayer = (currentPlayer == 1 ? 2 : 1);
        }

        endMenu(result);
    }

    void displayBoard() {
        for (int i = 0; i <= 3; i++) {
            for (int j = 0; j <= 3; j++) {
                if (i == 0 && j == 0) {
                    cout << ' ';
                }
                else if (i == 0) {
                    cout << j - 1;
                }
                else if (j == 0) {
                    cout << i - 1;
                }
                else {
                    cout << board[i - 1][j - 1];
                }
                
                if (j == 0) {
                    cout << "  ";
                }
                else if (i > 0 && 0 < j && j < 3) {
                    cout << " | ";
                }
                else {
                    cout << "   ";
                }
            }
            cout << '\n';
        }
        cout << '\n';
    }

    void loadingScreen(int loopTime) {
        string text = getRandomText(loadingScreenText);

        string text1 = ">> " + text + ".  \r";
        string text2 = ">> " + text + ".. \r";
        string text3 = ">> " + text + "...\r";

        clearScreen();
        while (loopTime--) {
            cout << text1 << flush;
            this_thread::sleep_for(chrono::milliseconds(300));
            
            cout << text2 << flush;
            this_thread::sleep_for(chrono::milliseconds(300));
            
            cout << text3 << flush;
            this_thread::sleep_for(chrono::milliseconds(300));
        }
        clearScreen();
    }

    void exitingGame(int loopTime) {
        string text = getRandomText(exitingGameText);

        string text1 = ">> " + text + ".  \r";
        string text2 = ">> " + text + ".. \r";
        string text3 = ">> " + text + "...\r";

        clearScreen();
        while (loopTime--) {
            cout << text1 << flush;
            this_thread::sleep_for(chrono::milliseconds(300));
            
            cout << text2 << flush;
            this_thread::sleep_for(chrono::milliseconds(300));
            
            cout << text3 << flush;
            this_thread::sleep_for(chrono::milliseconds(300));
        }
        clearScreen();
    }

    void botIsThinking(int loopTime) {
        string text = getRandomText(botIsThinkingText);

        string text1 = ">> " + text + ".  \r";
        string text2 = ">> " + text + ".. \r";
        string text3 = ">> " + text + "...\r";

        while (loopTime--) {    
            cout << text1 << flush;
            this_thread::sleep_for(chrono::milliseconds(500));

            cout << text2 << flush;
            this_thread::sleep_for(chrono::milliseconds(500));

            cout << text3 << flush;
            this_thread::sleep_for(chrono::milliseconds(500));

            cout << string((int)text3.size(), ' ') << '\r' << flush;
        }
    }

    string getRandomText(const vector<pair<string,int>>& texts) {
        int num = random(1, 100);

        for (pair<string,int> text : texts) {
            if (num <= text.second) {
                return text.first;
            }
            num -= text.second;
        }

        return texts[0].first;
    }

    bool isValidMove(string row, string col) {
        for (char ch : row) {
            if (ch < '0' || '9' < ch) {
                return false;
            }
        }
        for (char ch : col) {
            if (ch < '0' || '9' < ch) {
                return false;
            }
        }

        if (stoi(row) >= 3 || stoi(col) >= 3) {
            return false;
        }
        if (board[stoi(row)][stoi(col)] != '-') {
            return false;
        }
        return true;
    }   

    char checkWinner() {
        for (int i = 0; i < 3; ++i) {
            if (board[i][0] != '-' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
                return board[i][0];
            }
            if (board[0][i] != '-' && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
                return board[0][i]; 
            }
        }

        if (board[0][0] != '-' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
            return board[0][0];
        }
        if (board[0][2] != '-' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
            return board[0][2];
        }

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == '-') {
                    return '-';
                }
            }
        }

        return 'D';
    }

    int minimax(int depth, bool isMax) {
        char score = checkWinner();
        if (score == 'O') {
            return 10 - depth;
        }
        if (score == 'X') {
            return depth - 10;
        }
        if (score == 'D') {
            return 0;
        }

        if (isMax) {
            int best = -1000;
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if (board[i][j] == '-') {
                        board[i][j] = 'O';
                        best = max(best, minimax(depth + 1, false));
                        board[i][j] = '-';
                    }
                }
            }
            return best;
        } 
        else {
            int best = 1000;
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if (board[i][j] == '-') {
                        board[i][j] = 'X';
                        best = min(best, minimax(depth + 1, true));
                        board[i][j] = '-';
                    }
                }
            }
            return best;
        }
    }

    Move findBestMove() {
        int bestVal = -1000;
        Move bestMove = {-1, -1};

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == '-') {
                    board[i][j] = 'O';
                    int moveVal = minimax(0, false);
                    board[i][j] = '-';

                    if (moveVal > bestVal) {
                        bestMove.row = i;
                        bestMove.col = j;
                        bestVal = moveVal;
                    }
                }
            }
        }
        return bestMove;
    }

    void botMakeMove() {
        vector<Move> validMoves;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == '-') {
                    validMoves.push_back({i, j});
                }
            }
        }

        Move finalMove = {-1, -1};
        
        // BABY
        if (botDifficulty == 1) {
            finalMove = validMoves[random(0, validMoves.size() - 1)];
        }

        // EASY
        else if (botDifficulty == 2) {
            for (Move move : validMoves) {
                board[move.row][move.col] = 'O';
                if (checkWinner() == 'O') {
                    finalMove = move;
                    board[move.row][move.col] = '-';
                    break;
                }
                board[move.row][move.col] = '-';
            }
            if (finalMove.row == -1) {
                for (Move move : validMoves) {
                    board[move.row][move.col] = 'X';
                    if (checkWinner() == 'X') {
                        finalMove = move;
                        board[move.row][move.col] = '-';
                        break;
                    }
                    board[move.row][move.col] = '-';
                }
            }
            if (finalMove.row == -1) {
                finalMove = validMoves[random(0, validMoves.size() - 1)];
            }
        }

        // NORMAL
        else if (botDifficulty == 3) {
            if (random(1, 100) <= 40) {
                finalMove = validMoves[random(0, validMoves.size() - 1)];
            } 
            else {
                finalMove = findBestMove();
            }
        }

        // HARD
        else if (botDifficulty == 4) {
            if (random(1, 100) <= 20) {
                finalMove = validMoves[random(0, validMoves.size() - 1)];
            } 
            else {
                finalMove = findBestMove();
            }
        }

        // IMPOSSIBLE
        else if (botDifficulty == 5) {
            finalMove = findBestMove();
        }

        board[finalMove.row][finalMove.col] = 'O';
    }

private:
    vector<vector<char>> board;

    const vector<string> invalidInputWarningText = {
        "Invalid input!\n",
        "That's not an option!\n",
        "Invalid. Try again!\n",
        "No.\n",
        "Nuh uh.\n",
        "What are you doing?\n",
        "Stop it.\n"
    };

    const vector<string> difficultyName = {
        "Baby",
        "Easy",
        "Normal",
        "Hard",
        "IMPOSSIBLE"
    };

    const vector<pair<string, int>> loadingScreenText = {
        {"Loading", 56},
        {"Getting resources", 10},
        {"Please wait", 10},
        {"Making you wait for eternity", 9},
        {"Playing animation that wastes your time", 5},
        {"Getting snacks", 5},
        {"Doing something", 5},
    };

    const vector<pair<string,int>> botIsThinkingText = {
        {"Bot is thinking", 30},
        {"Bot is making a move", 30},
        {"Bot is making a decision", 30},
        {"Running algorithms", 10},
    };

    const vector<pair<string,int>> exitingGameText {
        {"Exiting", 21},
        {"Closing game", 21},
        {"Quitting", 21},
        {"See you later", 15},
        {"Goodbye", 15},
        {"Stay safe", 7},
    };

    int botDifficulty;

    int firstPlayer;
    int currentPlayer;

    float playerScore;
    float botScore;
};   

int main() {
    TicTacToe game;

    game.startMenu();

    return 0;
}
