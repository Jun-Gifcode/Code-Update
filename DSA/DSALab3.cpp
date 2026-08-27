#include <iostream>
using namespace std;

class GuessingGame {
private:
    string playerName;
    int secretNumbers[3];
    int score;
    bool isRunning;

public:
    // Default constructor - sets fixed secret numbers
    GuessingGame() {
        secretNumbers[0] = 7;   // Easy level
        secretNumbers[1] = 35;  // Medium level
        secretNumbers[2] = 82;  // Hard level
        score = 0;
        playerName = "";
        isRunning = true;
    }

    // Parameterized constructor
    GuessingGame(string name) {
        secretNumbers[0] = 7;   // Easy level
        secretNumbers[1] = 35;  // Medium level
        secretNumbers[2] = 82;  // Hard level
        score = 0;
        playerName = name;
        isRunning = true;
    }

    // Get player name
    string getPlayerName() {
        return playerName;
    }

    // Set player name
    void setPlayerName(string name) {
        playerName = name;
    }

    // Get score
    int getScore() {
        return score;
    }

    // Display the main menu
    void displayMenu() {
        if (playerName.empty()) {
            cout << "Enter your name: ";
            cin >> playerName;
        }

        cout << "\n========== NUMBER GUESSING GAME ==========\n\n";
        cout << "1. Easy    (1-10, 5 attempts)\n";
        cout << "2. Medium  (1-50, 7 attempts)\n";
        cout << "3. Hard    (1-100, 10 attempts)\n";
        cout << "4. Display Scores\n";
        cout << "5. Exit\n";
        cout << "\nEnter your choice: ";
    }

    // Display score
    void displayScore() {
        cout << "\n========== SCORE ==========\n";
        cout << "Player: " << playerName << endl;
        cout << "Current Score: " << score << endl;
        cout << "============================\n";
    }

    // Start the game based on difficulty level
    void startGame(int level) {
        if (level < 1 || level > 3) {
            cout << "Invalid difficulty level!\n";
            return;
        }

        int maxAttempts;
        int maxNumber;
        string levelName;

        // Set game parameters based on level
        switch(level) {
            case 1:
                maxAttempts = 5;
                maxNumber = 10;
                levelName = "EASY";
                break;
            case 2:
                maxAttempts = 7;
                maxNumber = 50;
                levelName = "MEDIUM";
                break;
            case 3:
                maxAttempts = 10;
                maxNumber = 100;
                levelName = "HARD";
                break;
        }

        cout << "\nYou selected " << levelName << " level.\n";
        cout << "Guess a number between 1 and " << maxNumber << ".\n";
        cout << "You have " << maxAttempts << " attempts.\n\n";

        int secretNumber = secretNumbers[level - 1];
        int guess;
        int attempts = 0;
        bool guessedCorrectly = false;

        // Game loop
        while (attempts < maxAttempts && !guessedCorrectly) {
            cout << "Enter your guess: ";
            cin >> guess;

            // Validate input
            if (guess < 1 || guess > maxNumber) {
                cout << "Please enter a number between 1 and " << maxNumber << "!\n";
                continue;
            }

            attempts++;

            if (guess == secretNumber) {
                cout << "\nCongratulations, " << playerName << "!\n";
                cout << "You guessed the correct number in " << attempts << " attempts!\n";
                guessedCorrectly = true;
                
                // Calculate score based on attempts used
                int scoreEarned = maxAttempts - attempts + 1;
                if (scoreEarned < 0) scoreEarned = 0;
                score += scoreEarned;
                cout << "You earned " << scoreEarned << " points!\n";
                cout << "Total Score: " << score << "\n";
            } else if (guess < secretNumber) {
                cout << "Too low! Try again. (Attempts used: " << attempts << "/" << maxAttempts << ")\n";
            } else {
                cout << "Too high! Try again. (Attempts used: " << attempts << "/" << maxAttempts << ")\n";
            }
        }

        if (!guessedCorrectly) {
            cout << "\nGame Over!\n";
            cout << "The secret number was: " << secretNumber << "\n";
            cout << "Better luck next time, " << playerName << "!\n";
        }
    }

    // Main game controller - handles the menu loop
    void run() {
        int choice;
        
        cout << "Welcome to the Number Guessing Game!\n";
        
        do {
            displayMenu();
            cin >> choice;

            switch(choice) {
                case 1:
                case 2:
                case 3:
                    startGame(choice);
                    break;
                case 4:
                    displayScore();
                    break;
                case 5:
                    cout << "\nExiting the game. Goodbye, " << playerName << "!\n";
                    isRunning = false;
                    break;
                default:
                    cout << "\nInvalid choice. Please try again.\n";
            }

            if (choice >= 1 && choice <= 4) {
                cout << "\nPress Enter to continue...";
                cin.ignore();
                cin.get();
            }

        } while (isRunning);
    }
};

int main() {
    // Create game object - no random number needed!
    GuessingGame game;
    
    // Run the game - all logic is inside the class
    game.run();

    return 0;
}