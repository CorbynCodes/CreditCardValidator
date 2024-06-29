#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>
using namespace std;
const int ROWS = 5;
const int COLS = 5;
int displayedLowerBound = -1;
int displayedUpperBound = -1;

enum menuChoice
{
    display_left,
    display_right,
    Guess,
    Reset,
    Exit
};
void classRoomID()
{
    cout << "Name: [Corbyn Ledbetter]" << endl;
    cout << "EUID: [crl0227]" << endl;
    cout << "Email: [corbynledbetter@my.unt.edu]" << endl;
    cout << "Department: [Computer Science/Engineering]" << endl;
    cout << "Course: [CSCE 1030]" << endl;
}

string getName()
{
    string name;
    bool validName = false; // creating the boolean type to make the process alot easier for me to understand the problem.
    while (!validName)
    {
        cout << "Please enter your name: ";
        getline(cin, name);
        validName = true;
        for (char c : name)
        {
            if (!isalpha(c) && !isspace(c))
            {
                validName = false;
                break;
            }
        }
        if (!validName)
        {
            cout << "Invalid name. Pleas try again again\n";
        }
    }
    for (int i = 0; i < name.length(); i++)
    {
        if (i == 0 || name[i - 1] == ' ')
        {
            name[i] = toupper(name[i]);
        }
        else
        {
            name[i] = tolower(name[i]);
        }
    }
    return name;
}

void genShowMatrix(int visible[5][5])
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            visible[i][j] = -1; // setting the matrix to -1
        }
    }
}

void genHideMatrix(int hidden[5][5], int lowerbound, int upperbound)
{
    srand(time(NULL));
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            hidden[i][j] = rand() % (upperbound - lowerbound + 1) + lowerbound;
        }
    }
}

void showMatrix(int matrix[5][5])
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}



void setdisplayLeft(int visible[5][5], int hidden[5][5], int lowerBound, int upperBound)
{
    if(displayedUpperBound != -1)
    {
        cout << "You have already displayed the upper bound. You cannot display the lower bound." << endl;
        return;
    }
    int smaller = 300;
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            smaller = min(smaller, hidden[i][j]);
        }
    }
    for(int i = 0; i < ROWS; i++)
    {
        bool flag = false;
        for(int j = 0; j < COLS; j++)
        {
            if(hidden[i][j] == smaller)
            {
                flag = true;
                visible[i][j] = smaller;
                displayedLowerBound = smaller;
                break;
            }
        }
        if(flag)
            break;
    }
    // showMatrix(visible);
    cout << "A correct guess will only earn 1 point and an incorrect guess will lose 10 points in the game." << endl;
}


void setdisplayRight(int visible[5][5], int hidden[5][5], int lowerBound, int upperBound)
{
    if(displayedLowerBound != -1)
    {
        cout << "You have already displayed the lower bound. You cannot display the upper bound." << endl;
        return;
    }
    int larger = 99;
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            larger = max(larger, hidden[i][j]);
        }
    }
    for(int i = 0; i < ROWS; i++)
    {
        bool flag = false;
        for(int j = 0; j < COLS; j++)
        {
            if(hidden[i][j] == larger)
            {
                flag = true;
                visible[i][j] = larger;
                displayedUpperBound = larger;
                break;
            }
        }
        if(flag)
            break;
    }
    // showMatrix(visible);
    cout << "A correct guess will only earn 1 point and an incorrect guess will lose 10 points in the game." << endl;
}
void elminate(int row_index, int col_index, int visible[][5], int hidden[][5])
{
    for (int col = 0; col < 5; col++)
    {
        visible[row_index][col] = 0;
        hidden[row_index][col] = 0;
    }
    for (int row = 0; row < 5; row++)
    {
        visible[row][col_index] = 0;
        hidden[row][col_index] = 0;
    }
}

bool allZeros(int hidden[][5], int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (hidden[i][j] != 0)
            {
                return false; // if any non-zero is found, return false
            }
        }
    }
    return true; // all elements are zero, return true.
}

void guess(int visible[][5], int hidden[][5], int &points, bool leftBoundReveled, bool rightBoundReveled)
{
    int row_index = -1;
    int col_index = -1;
    cout << "Guess the values in the hidden array: " << endl;
    int guess;
    cin >> guess;

    bool foundMatch = false;
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (hidden[i][j] == guess)
            {
                foundMatch = true;
                row_index = i;
                col_index = j;
                break;
            }
        }
        if (foundMatch)
        {
            break;
        }
    }

    // int points = 0;
    if (foundMatch)
    {
        cout << "Congratulations! You've found a match at row " << row_index << " and column " << col_index << endl;
        elminate(row_index, col_index, visible, hidden);
        if(displayedLowerBound != -1|| displayedUpperBound != -1)
        {
            points += 1;
        }
        else
        {
            points += 5;
        }
    }
    else
    {
        cout << "Sorry, you've guessed incorrectly." << endl;
        if(displayedLowerBound != -1|| displayedUpperBound != -1)
        {
            points -= 10;
        }
        else
        {
            points -= 5;
        }
    }

    cout << "Your points balance is now " << points << "." << endl;
}
void initialize(int visible[5][5], int hidden[5][5], int lowerBound, int upperBound)
{
    /*
    Generate two seeded random integers: one in the range of 100 to 199 inclusive,
representing a lower bound, and the other in the range of 200 to 299 inclusive,
representing an upper bound.
    */
    srand(time(NULL));
    lowerBound = rand() % 100 + 100;
    upperBound = rand() % 100 + 200;
    displayedLowerBound = -1;
    displayedUpperBound = -1;

    genHideMatrix(hidden, lowerBound, upperBound);
    genShowMatrix(visible);
}

menuChoice getMenuChoice()
{
    int choice;
    cout << "1. Display the left bound" << endl;
    cout << "2. Display the right bound" << endl;
    cout << "3. Guess" << endl;
    cout << "4. Quit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    cout << endl;

    switch (choice)
    {
    case 1:
        return display_left;
    case 2:
        return display_right;
    case 3:
        return Guess;
    case 4:
        return Exit;
    default:
        cout << "Invalid choice. Please try again." << endl;
        return getMenuChoice();
    }
}

int main()
{
    classRoomID();
    srand(time(NULL));
    int rows, cols;
    int points = 100;
    int lowerBound, upperBound;
    int visible[5][5];
    int hidden[5][5];
    int visibleLeft, visibleRight;

    initialize(visible, hidden, lowerBound, upperBound);
    string playerName = getName();
    cout << "Welcome, " << playerName << "!" << endl;

    bool gameover = false;
    while (!gameover)
    {
        showMatrix(visible);
        // showMatrix(hidden);
        menuChoice choice = getMenuChoice();

        switch (choice)
        {
        case display_left:
            setdisplayLeft(visible, hidden, lowerBound, upperBound);
            break;
        case display_right:
            setdisplayRight(visible, hidden, lowerBound, upperBound);
            break;
        case Guess:
            guess(visible, hidden, points, lowerBound != -1, upperBound != -1);
            if (allZeros(hidden, ROWS, COLS))
            {
                cout << "Congratulations! You've won the game!" << endl;
                cout << "Do you want to play again? (Y/N)" << endl;
                char playAgain;
                cin >> playAgain;
                if (tolower(playAgain) == 'y')
                {
                    initialize(visible, hidden, lowerBound, upperBound);
                }
                else
                {
                    gameover = true;
                }
            }
            break;
        case Reset:
            initialize(visible, hidden, lowerBound, upperBound);
            points = -1;
            cout << "Points balance : " << points << endl;
            break;
        case Exit:
            gameover = true;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }

    }
    cout << "Goodbye, " << playerName << "! Your final points balance is " << points << "." << endl;
    return 0;
}