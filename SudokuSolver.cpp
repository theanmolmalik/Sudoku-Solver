#include <iostream>
using namespace std;

int isfilled(int suduko[][9], int r, int c)
{
    int i, j, count = 0;
    for (i = 0; i < r; i++)
    {
        for (j = 0; j < c; j++)
        {
            if (suduko[i][j] != 0)
                count++;
        }
    }
    return count;
}

bool isvalid(int suduko[][9], int r, int c)
{
    if (suduko[r][c] != 0)
    {
        for (int x = 0; x < 9; x++)
        {
            if (x != c)
            { 
                if (suduko[r][x] == suduko[r][c])
                    return false;
            }
        }
        for (int x = 0; x < 9; x++)
        {
            if (x != r)
            { 
                if (suduko[x][c] == suduko[r][c])
                    return false;
            }
        }
        int Start_Row = r - r % 3;
        int Start_Column = c - c % 3;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            { 
                if ((i + Start_Row) != r && (j + Start_Column) != c)
                {
                    if (suduko[i + Start_Row][j + Start_Column] == suduko[r][c])
                        return false;
                }
            }
        }
    }
    return true;
}

bool safe(int suduko[][9], int r, int c, int n)
{
    for (int x = 0; x < 9; x++)
    {
        if (suduko[r][x] == n)
            return false;
    }
    for (int x = 0; x < 9; x++)
    {
        if (suduko[x][c] == n)
            return false;
    }

    int Start_Row = r - r % 3;
    int Start_Column = c - c % 3;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (suduko[i + Start_Row][j + Start_Column] == n)
                return false;
        }
    }
    return true;
}

bool solving_suduko(int suduko[][9], int r, int c)
{
    if (r == 8 && c == 9)
        return true;
    if (c == 9)
    {
        r++;
        c = 0;
    }

    if (suduko[r][c] > 0)
        return solving_suduko(suduko, r, c + 1);
    for (int n = 1; n <= 9; n++)
    {
        if (safe(suduko, r, c, n))
        {
            suduko[r][c] = n;
            if (solving_suduko(suduko, r, c + 1))
                return true;
        }

        suduko[r][c] = 0;
    }
    return false;
}

int main()
{
    cout << "WELCOME TO SUDUKO SOLVER" << endl
         << endl;
    int ele, j, n, i, c = 0;
    int suduko[9][9] = {0};
    cout << "This is 9*9 suduko solver\n\nHow many elements you want to enter" << endl;
    cin >> n;
    cout << "\nEnter position of  ith row separated by space jth column and then separated by space  enter value to be put" << endl;

    for (int x = 0; x < n; x++)
    {
        cin >> i >> j;
        cin >> ele;
        suduko[i][j] = ele;
    }
    cout << "Intial Suduko" << endl;
    for (int m = 0; m < 9; m++)
    {
        for (int n = 0; n < 9; n++)
        {
            if (suduko[m][n] == 0)
                cout << "_"
                     << "  ";
            else
                cout << suduko[m][n] << "  ";
        }
        cout << endl;
    }
    cout << endl;
    int k;
    k = isfilled(suduko, 9, 9);
    if (k == 81)
        cout << "Suduko is completely filled" << endl;

    else
    {
        for (i = 0; i < 9; i++)
        {
            for (j = 0; j < 9; j++)
            {
                if (isvalid(suduko, i, j))
                    continue;
                else
                {
                    c = 1;
                    break;
                }
            }
        }
        if (c == 1)
            cout << "\nInvalid Suduko";

        else
        {
            if (solving_suduko(suduko, 0, 0))
            {
                cout << "Solved Suduko" << endl;
                for (int i = 0; i < 9; i++)
                {

                    for (int j = 0; j < 9; j++)
                    {
                        cout << suduko[i][j] << "   ";
                    }
                    cout << endl;
                }
                cout << endl;
            }
            else
            {
                cout << "Not Solvable";
            }
        }
    }
    return 0;
}