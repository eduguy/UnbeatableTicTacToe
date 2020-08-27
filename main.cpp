#include <iostream>
#include <utility>
#include <vector>
using namespace std;

vector<vector<string>> data;
bool isOver;
bool isXTurn;
int input;

void newData()
{
    vector<string> temp;
    temp.push_back("N");
    temp.push_back("N");
    temp.push_back("N");
    data.push_back(temp);
    data.push_back(temp);
    data.push_back(temp);
    // cout << "MOD" << endl;
}

void printData()
{
    cout << "-----" << endl;
    cout << "|" << data[0][0] << data[0][1] << data[0][2] << "|" << endl;
    cout << "|" << data[1][0] << data[1][1] << data[1][2] << "|" << endl;
    cout << "|" << data[2][0] << data[2][1] << data[2][2] << "|" << endl;
    cout << "-----" << endl;
}

void getInput()
{
    int x;
    int y;
    cout << "What coordinate is your next move?" << endl;
    cout << "X" << endl;
    cin >> x;
    cout << "y" << endl;
    cin >> y;

    if (data[y][x] == "N")
    {
        if (isXTurn)
        {
            data[y][x] = "X";
        }
        else
        {
            data[y][x] = "O";
        }
        isXTurn = !isXTurn;
    }
    else
    {
        cout << "Space already full, try again" << endl;
        printData();
        getInput();
    }
}

void gameOver()
{
    isOver = true;
    if (!isXTurn)
    {
        printData();

        cout << "X WINS" << endl;
    }
    else
    {
        printData();

        cout << "O WINS" << endl;
    }
    exit(0);
}
//data[Y VALUE][X VALUE]

void checkIsWinner()
{
    //check rows
    for (int i = 0; i < 3; i++)
    {
        if ((data[i][0] == "X" && data[i][1] == "X" && data[i][2] == "X") || (data[i][0] == "O" && data[i][1] == "O" && data[i][2] == "O"))
        {
            cout << "ROW" << endl;

            gameOver();
        }
    }

    //check columns
    for (int i = 0; i < 3; i++)
    {
        if ((data[0][i] == "X" && data[1][i] == "X" && data[2][i] == "X") || (data[0][i] == "O" && data[1][i] == "O" && data[2][i] == "O"))
        {
            cout << "COLUMN" << endl;

            gameOver();
        }
    }

    //check diagnals

    if ((data[0][0] == "X" && data[1][1] == "X" && data[2][2] == "X") || (data[0][0] == "O" && data[1][1] == "O" && data[2][2] == "O"))
    {
        cout << "LTOR" << endl;

        gameOver();
    }
    if ((data[0][2] == "X" && data[1][1] == "X" && data[2][0] == "X") || (data[0][2] == "O" && data[1][1] == "O" && data[2][0] == "O"))
    {
        cout << "RTOL" << endl;

        gameOver();
    }
}

void checkIsBoardFull()
{
    for (vector<string> vec : data)
    {
        for (string str : vec)
        {
            if (str == "N")
            {
                return;
            }
        }
    }
    printData();
    cout << "The game ends in a tie!" << endl;
    isOver = true;
}

void getRandomInput()
{
    int x = rand() % 3;
    int y = rand() % 3;

    if (data[y][x] == "N")
    {
        if (isXTurn)
        {
            data[y][x] = "X";
        }
        else
        {
            data[y][x] = "O";
        }
        isXTurn = !isXTurn;
        cout << "AI makes it's move at (" << x << "," << y << ")." << endl;
    }
    else
    {
        getRandomInput();
    }
}

bool checkWinnerAI(vector<vector<string>> temp)
{
    //check rows
    for (int i = 0; i < 3; i++)
    {
        if ((temp[i][0] == "X" && temp[i][1] == "X" && temp[i][2] == "X") || (temp[i][0] == "O" && temp[i][1] == "O" && temp[i][2] == "O"))
        {
            cout << "ROW" << endl;

            return true;
        }
    }

    //check columns
    for (int i = 0; i < 3; i++)
    {
        if ((temp[0][i] == "X" && temp[1][i] == "X" && temp[2][i] == "X") || (temp[0][i] == "O" && temp[1][i] == "O" && temp[2][i] == "O"))
        {
            cout << "COLUMN" << endl;

            return true;
        }
    }

    //check diagnals

    if ((temp[0][0] == "X" && temp[1][1] == "X" && temp[2][2] == "X") || (temp[0][0] == "O" && temp[1][1] == "O" && temp[2][2] == "O"))
    {
        cout << "LTOR" << endl;

        return true;
    }
    if ((temp[0][2] == "X" && temp[1][1] == "X" && temp[2][0] == "X") || (temp[0][2] == "O" && temp[1][1] == "O" && temp[2][0] == "O"))
    {
        cout << "RTOL" << endl;

        return true;
    }

    return false;
}

bool checkTieAI(vector<vector<string>> temp)
{
    for (vector<string> vec : temp)
    {
        for (string str : vec)
        {
            if (str == "N")
            {
                return false;
            }
        }
    }
    return true;
}

int getPerfectInput(vector<vector<string>> temp, int depth, bool isOTurn)

{
    if (checkWinnerAI(temp))
    {
        if (isOTurn)
        {
            return -(-10 - depth);
        }
        else
        {
            return -(10 - depth);
        }
    }
    else if (checkTieAI(temp))
    {
        return 0;
    }
    else
    {

        if (isOTurn)
        {
            int bestMoveScore = -100;

            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (temp[i][j] == "N")
                    {
                        //i want to maximize the score of O
                        temp[i][j] = "O";
                        int maxScore = getPerfectInput(temp, depth++, false);
                        // temp[i][j] = "N";
                        bestMoveScore = max(maxScore, bestMoveScore);
                    }
                }
            }
            return bestMoveScore;
        }
        else
        {
            int bestMoveScore = 100;
            //minimize
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (temp[i][j] == "N")
                    {
                        temp[i][j] = "X";
                        int minScore = getPerfectInput(temp, depth++, true);
                        // temp[i][j] = "N";

                        bestMoveScore = min(minScore, bestMoveScore);
                    }
                }
            }

            return bestMoveScore;
        }

        // return getPerfectInput(temp, depth++, !isOTurn);
    }
    //if (checkwinner(temp))
    // {
    //     return (-10 - depth) or (10-depth) depdning on if O or X won;
    // }
    //else if (gameTIe) {
    //     return 0-depth;
    // }
    // else {
    // vector vec = getMove(temp, isOTurn);
    // getPerfectInput(vecotrwithrandommove, depth++,~isturn);
    // }
}

void getMove()
{
    int moveX;
    int moveY;
    int bestScoreSoFar = -1000; //arbitrary
    vector<vector<string>> temp1 = data;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (temp1[i][j] == "N")
            {
                temp1[i][j] = "O";
                int score = getPerfectInput(temp1, 0, false);
                temp1[i][j] = "N";

                if (score > bestScoreSoFar)
                {
                    bestScoreSoFar = score;
                    moveX = j;
                    moveY = i;
                }
            }
        }
    }
    isXTurn = !isXTurn;
    cout << "AI makes it's move at (" << moveX << "," << moveY << ")." << endl;
    data[moveY][moveX] = "O";

    //get all unused spaces
    // for (unused spaces :board) {
    //     fill with X/O,
    //     getperfectmove with all the board options
    // }}

    //return the temp board that gives the highest score
    //replace global board with temp board
}

int main()
{
    cout << "Hello. Welcome to my tic tac toe game! Press 1 for 1 player and 2 for 2 player!" << endl;
    isXTurn = true;
    newData();
    cin >> input;
    if (input == 2) //will use this to switch between single and multiplayer mode
    {
        cout << "Welcome to the 2 player version. X goes first. You can begin!" << endl;
        while (!isOver)
        {
            printData();
            getInput();
            checkIsBoardFull();
            checkIsWinner();
        }
    }
    else if (input == 1)
    {
        cout << "Welcome to the 1 player version against AI. You go first as X. You can begin!" << endl;
        while (!isOver)
        {
            printData();
            getInput();
            // cout << "got your input" << endl;
            checkIsWinner();
            checkIsBoardFull();
            getRandomInput();
            // cout << "got cpu input" << endl;
            checkIsWinner();
            checkIsBoardFull();
        }
    }
    else
    {
        cout << "Welcome to the 1 player version against unbeatable AI. You go first as X. You can begin!" << endl;

        while (!isOver)
        {
            printData();
            getInput();
            checkIsWinner();
            checkIsBoardFull();
            getMove();
            checkIsWinner();
            checkIsBoardFull();
        }
    }
    return 0;
    exit(0);
}
