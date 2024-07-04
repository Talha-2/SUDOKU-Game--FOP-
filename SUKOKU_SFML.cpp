#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m" 
#ifdef _WIN32
#include <conio.h>
#define CLEAR_COMMAND "cls"
#else
#include <unistd.h>
#include <term.h>
#define CLEAR_COMMAND "clear"
#endif

using namespace std;

const int GRID_SIZE = 9;
const int CELL_SIZE = 60;
const int GRID_OFFSET = 20;
const int WINDOW_SIZE = CELL_SIZE * GRID_SIZE + GRID_OFFSET * 2;




void clearScreen() {
    // Clear the console screen
    std::system(CLEAR_COMMAND);
}


void showHelp() {
    clearScreen();
    cout << CYAN << setw(50) << "Sudoku Game Help\n" << RESET << endl;

    cout <<setw(0)<< "----------------\n\n" << endl;
    cout << CYAN  <<" 1. Sudoku Objective : \n\n\n" << RESET << endl;
 
    cout << "   The goal of Sudoku is to fill a 9x9 grid with numbers so that each row, each column, and each of the nine 3x3 sub-grids (also known as 'boxes') contains all of the digits from 1 to 9.\n\n\n" << endl;
    cout << CYAN  << "2. Game Setup: \n\n\n" << RESET << endl;
   
    cout << "   - The Sudoku grid is divided into a 9x9 square grid, with each square containing a number or an empty cell." << endl;
    cout << "   - Some cells will already have numbers pre-filled, called 'givens,' which cannot be changed." << endl;
    cout << "   - Your task is to fill in the remaining empty cells with numbers while following the Sudoku rules.\n\n\n" << endl;
    cout << CYAN  << "3. Sudoku Rules: \n\n\n" << RESET << endl;
   
    cout << "   - Each row must contain all the numbers from 1 to 9, without repetition." << endl;
    cout << "   - Each column must contain all the numbers from 1 to 9, without repetition." << endl;
    cout << "   - Each 3x3 box must contain all the numbers from 1 to 9, without repetition.\n\n\n" << endl;
    cout << CYAN  << "4. Game Controls: \n\n\n" << RESET << endl;
    cout << "   - Use the mouse cursor to navigate to a specific cell." << endl;
    cout << "   - To fill a cell, select the desired number and place it in the appropriate cell." << endl;
    cout << "   - Remember, the pre-filled givens cannot be changed.\n\n\n" << endl;
    cout << CYAN  << "5. Strategies: \n\n\n" << RESET << endl;

    cout << "   - Start by looking for any obvious numbers that can only fit in one cell within a row, column, or box." << endl;
    cout << "   - Use the process of elimination to determine the possible numbers for each empty cell." << endl;
    cout << "   - Apply logic and deduction to narrow down the possibilities and fill in the remaining cells.\n\n\n" << endl;
    cout << CYAN  << "6. Tips: \n\n\n" << RESET << endl;
    cout << "   - Take your time and analyze the puzzle carefully. Rushing can lead to errors." << endl;
    cout << "   - Keep track of the numbers you have already placed in each row, column, and box." << endl;
    cout << "   - Look for patterns and use the process of elimination to narrow down possibilities." << endl;
    cout << "   - Practice regularly to improve your skills and become a Sudoku master!\n\n\n" << endl;
    cout << endl;
  

  
    // Provide an option to return to the main menu
    cout << "Press any key to return to the main menu." << std::endl;
    cin.ignore();
    cin.get();
}

int chooseDifficultyLevel() {
    clearScreen();
    int difficulty;
    bool validInput = false;
   
    cout << GREEN << "Choose difficulty level:\n" << RESET << endl;
    cout << BLUE<< " 1. Easy  " << RESET << endl;
    cout << YELLOW << " 2. Medium " << RESET << endl;
    cout << RED << " 3. Hard " << RESET << endl;
        
       
       

    do {
        cin >> difficulty;

        if (cin.fail() || difficulty < 1 || difficulty >3) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid input \n\n." << endl;
        }
        else {
            validInput = true;
        }
    } while (!validInput);



    // Provide an option to return to the main menu
    cout << "Press any key to return to the main menu." << endl;
    cin.ignore();
    cin.get();

    return difficulty;



}

bool validity_check(int sudoku_board[][GRID_SIZE], int row, int col, int num)
{
    for (int i = 0; i < GRID_SIZE; i++)
    {
        if (sudoku_board[row][i] == num || sudoku_board[i][col] == num) {
            return false;
        }
    }

    int box_start_row = row - row % 3;
    int box_start_col = col - col % 3;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++) {
            if (sudoku_board[i + box_start_row][j + box_start_col] == num) {
                return false;
            }
        }
    }

    return true;
}


bool solveSudoku(int sudoku_board[][GRID_SIZE], int row, int col) {
    if (col == GRID_SIZE) {
        col = 0;
        if (++row == GRID_SIZE) {
            // Found a solution
            return true;
        }
    }

    if (sudoku_board[row][col] != 0)
    {
        return solveSudoku(sudoku_board, row, col + 1);
    }

    for (int num = 1; num <= GRID_SIZE; num++) {
        if (validity_check(sudoku_board, row, col, num)) {
            sudoku_board[row][col] = num;
            if (solveSudoku(sudoku_board, row, col + 1)) {
                return true;
            }
            sudoku_board[row][col] = 0;
        }
    }

    return false;
}

bool isUniqueSolution(int sudoku_board[][GRID_SIZE]) {
    int copy[GRID_SIZE][GRID_SIZE] = {};

    // Create a copy of the original Sudoku board
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            copy[i][j] = sudoku_board[i][j];
        }
    }

    // Solve the copied Sudoku board and check if it has a unique solution
    return solveSudoku(copy, 0, 0);
}


bool generate_puzzle(int sudoku_board[][GRID_SIZE], int difficulty) {
    solveSudoku(sudoku_board, 0, 0);

    int cellsToRemove = 0;
    switch (difficulty) {
    case 1:
        cellsToRemove = 15;  // Easy level
        break;
    case 2:
        cellsToRemove = 35;  // Medium level
        break;
    case 3:
        cellsToRemove = 50;  // Hard level
        break;
    default:
        cellsToRemove = 35;  // Medium level (default)
        break;
    }

    srand(static_cast<unsigned int>(time(0)));

    int count = 0;
    while (count < cellsToRemove) {
        int randomRow = rand() % GRID_SIZE;
        int randomCol = rand() % GRID_SIZE;

        if (sudoku_board[randomRow][randomCol] != 0) {
            int temp = sudoku_board[randomRow][randomCol];
            sudoku_board[randomRow][randomCol] = 0;

            // Check if the puzzle still has a unique solution
            int backupBoard[GRID_SIZE][GRID_SIZE] = {};
            for (int i = 0; i < GRID_SIZE; i++) {
                for (int j = 0; j < GRID_SIZE; j++) {
                    backupBoard[i][j] = sudoku_board[i][j];
                }
            }

            if (!isUniqueSolution(backupBoard)) {
                sudoku_board[randomRow][randomCol] = temp;
            }
            else {
                count++;
            }
        }
    }

    // Check if the final puzzle has a unique solution
    int backupBoard[GRID_SIZE][GRID_SIZE] = {};
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            backupBoard[i][j] = sudoku_board[i][j];
        }
    }

    return isUniqueSolution(backupBoard);
}


void playGame(sf::RenderWindow& window, int difficulty) {
    int sudoku_board[GRID_SIZE][GRID_SIZE] = { 0 };

    generate_puzzle(sudoku_board, difficulty);

    // loading font from the file 
    sf::Font font;
    if (!font.loadFromFile("digitalism.ttf")) {
        std::cerr << "Error loading font file." << std::endl;
        return;
    }

    // Creates an sf::Text object named 'text' with an empty string, a specified font, and a character size of 32 pixels
    sf::Text text("", font, 32);
    // Creating black color text
    text.setFillColor(sf::Color::Black);

    // Creates a yellow block on the cell which is selected by the user
    sf::RectangleShape selectedCell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    selectedCell.setFillColor(sf::Color(255, 255, 0, 128));  // Yellow with transparency

    // Indicated as -1 so that no block is selected
    int selectedRow = -1;
    int selectedCol = -1;

    // if the user wants to quit from the window
    


        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                // Determine when the left button of the mouse is pressed
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        // Get the current mouse location with respect to the window
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        // Calculate column index
                        int col = (mousePos.x - GRID_OFFSET) / CELL_SIZE;
                        // Calculate row index
                        int row = (mousePos.y - GRID_OFFSET) / CELL_SIZE;
                        // Check if the selected cell is in valid bounds and is empty
                        if (row >= 0 && row < GRID_SIZE && col >= 0 && col < GRID_SIZE && sudoku_board[row][col] == 0) {
                            selectedRow = row;
                            selectedCol = col;
                        }
                    }
                }

                if (event.type == sf::Event::TextEntered) {
                    // Ensures a valid cell has been selected and checks if entered text is between '1' and '9'
                    if (selectedRow != -1 && selectedCol != -1 && event.text.unicode >= '1' && event.text.unicode <= '9') {
                        int num = event.text.unicode - '0';
                        // Function call to check validity according to rules
                        if (validity_check(sudoku_board, selectedRow, selectedCol, num)) {
                            sudoku_board[selectedRow][selectedCol] = num;
                        }
                    }
                }
            }

            window.clear(sf::Color::White);

            // Draw horizontal lines
            for (int i = 0; i <= GRID_SIZE; i++) {
                sf::RectangleShape line(sf::Vector2f(CELL_SIZE * GRID_SIZE, 2));
                line.setPosition(GRID_OFFSET, GRID_OFFSET + i * CELL_SIZE);
                if (i % 3 == 0) {
                    line.setFillColor(sf::Color::Red);  // Change color every third line
                }
                else {
                    line.setFillColor(sf::Color::Cyan);
                }
                window.draw(line);
            }

            // Draw vertical lines
            for (int i = 0; i <= GRID_SIZE; i++) {
                sf::RectangleShape line(sf::Vector2f(2, CELL_SIZE * GRID_SIZE));
                line.setPosition(GRID_OFFSET + i * CELL_SIZE, GRID_OFFSET);
                if (i % 3 == 0) {
                    line.setFillColor(sf::Color::Red);  // Change color every third line
                }
                else {
                    line.setFillColor(sf::Color::Cyan);

                }
                window.draw(line);
            }

            // Display numbers
            for (int i = 0; i < GRID_SIZE; i++) {
                for (int j = 0; j < GRID_SIZE; j++) {
                    if (sudoku_board[i][j] != 0) {
                        text.setString(std::to_string(sudoku_board[i][j]));
                        text.setPosition(GRID_OFFSET + j * CELL_SIZE + 20, GRID_OFFSET + i * CELL_SIZE + 8);
                        window.draw(text);
                    }
                }
            }

            // Highlight selected block
            if (selectedRow != -1 && selectedCol != -1) {
                selectedCell.setPosition(GRID_OFFSET + selectedCol * CELL_SIZE, GRID_OFFSET + selectedRow * CELL_SIZE);
                window.draw(selectedCell);
            }

            // Check if Sudoku board is complete
            bool isComplete = true;
            for (int i = 0; i < GRID_SIZE; i++) {
                for (int j = 0; j < GRID_SIZE; j++) {
                    if (sudoku_board[i][j] == 0) {
                        isComplete = false;
                        break;
                    }
                }
                if (!isComplete) {
                    break;
                }
            }

            if (isComplete) {
                window.clear(sf::Color::White);
                sf::Text completionText("Congratulations! You have won the game.", font, 32);
                completionText.setPosition(GRID_OFFSET, WINDOW_SIZE - GRID_OFFSET - 40);
                completionText.setFillColor(sf::Color::Green);
                window.draw(completionText);
            }

            window.display();
        }
    
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "SUDOKU GAME");

    int difficulty=2;
    bool start_game = false;
    bool start=false, exitLoop = false;

        int choice;

           
            while (!exitLoop) 
            {
                bool validInput = false;
                clearScreen();
                cout << YELLOW << setw(50) << "--------- SUDOKU GAME ---------\n\n\n" << RESET;
                cout << MAGENTA << setw(20) << "---MAIN MENU---\n\n\n" << RESET;
                cout <<
                    "1. Start Game\n"
                    "2. Help\n"
                    "3. Choose Difficulty Level\n"
                    "4. Exit" <<endl;
                
                do {

                    cin >> choice;
                    if (cin.fail()||choice<0||choice>4)
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. Please enter a valid input.\n\n" << endl;
                    }
                    else {
                        validInput = true;
                    }
                }while(!validInput);


                switch (choice)
                {
                case 1:
                    clearScreen();
                    cout << "Sudoku game started!" << endl;                                  
                    playGame(window, difficulty);
                    break;
                   
                    
                case 2:
                    showHelp();
                    break;
                case 3:
                    difficulty = chooseDifficultyLevel();
                    break;
                case 4:
                    clearScreen();
                    cout << YELLOW << setw(50) << "Exiting the game. Goodbye!" << RESET;  
                    system("pause>0");
                    return 0;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                }
            }
       

        playGame(window, difficulty);
            
        
        return 0;

}