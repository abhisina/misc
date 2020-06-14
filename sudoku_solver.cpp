#include <iostream>
#include <vector>
#include <string>

typedef std::vector<int> Point;
typedef std::vector<std::vector<char>> Grid;

bool isValid(const char num, const Point& point, const Grid& grid)
{
    // Check row
    for(int i = 0 ; i < 9 ; ++i)
    {
        if(num == grid[i][point[1]] && i != point[0])
        {
            return false;
        }
    }
    // Check column
    for(int i = 0 ; i < 9 ; ++i)
    {
        if(num == grid[point[0]][i] && i != point[1])
        {
            return false;
        }
    }
    // Check sub square
    const int start_i = 3 * (point[0] / 3);
    const int start_j = 3 * (point[1] / 3);
    for(int i = start_i ; i < 3 + start_i ; ++i)
    {
        for(int j = start_j ; j < 3 + start_j ; ++j)
        {
            if(num == grid[i][j] && i != point[0] && j != point[1])
            {
                return false;
            }
        }
    }
    return true;
}

Point getNextPoint(Grid& grid)
{
    for(int i = 0 ; i < 9 ; ++i)
    {
        for(int j = 0 ; j < 9 ; ++j)
        {
            if(grid[i][j] == '0')
            {
                return {i, j};
            }
        }
    }
    return {9, 9};
}

void PrintGrid(const Grid& grid)
{
    for(int i = 0 ; i < 9 ; ++i)
    {
        if(i % 3 == 0 && i != 0)
        {
            std::cout << "---------------------\n";
        }
        for(int j = 0 ; j < 9 ; ++j)
        {
            if(j % 3 == 0 && j != 0)
            {
                std::cout << "| ";
            }
            std::cout << grid[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

Grid getGrid()
{
#if 0
    return {
        {'1', '0', '2', '0', '3', '4', '0', '0', '0'},
        {'7', '8', '0', '2', '0', '5', '3', '0', '9'},
        {'0', '3', '0', '0', '0', '0', '0', '8', '2'},
        {'0', '0', '0', '0', '8', '7', '0', '9', '0'},
        {'0', '4', '0', '9', '0', '2', '0', '3', '0'},
        {'0', '7', '0', '1', '4', '0', '0', '0', '0'},
        {'4', '6', '0', '0', '0', '0', '0', '2', '0'},
        {'9', '0', '3', '4', '0', '8', '0', '5', '7'},
        {'0', '0', '0', '3', '7', '0', '9', '0', '4'}
    };
#endif
#if 0
    return {
        { '1', '0', '0', '0', '0', '6', '0', '0', '0' },
        { '0', '7', '0', '0', '5', '0', '0', '0', '8' },
        { '3', '4', '0', '7', '0', '0', '6', '0', '0' },
        { '0', '0', '9', '0', '0', '0', '0', '4', '0' },
        { '4', '0', '0', '9', '0', '8', '0', '0', '3' },
        { '0', '8', '0', '0', '0', '0', '2', '0', '0' },
        { '0', '0', '4', '0', '0', '3', '0', '8', '9' },
        { '9', '0', '0', '0', '1', '0', '0', '3', '0' },
        { '0', '0', '0', '4', '0', '0', '0', '0', '7' },
    };
#endif
#if 1
    return {
        { '4', '3', '0', '0', '7', '0', '0', '0', '0' },
        { '8', '0', '2', '1', '4', '3', '0', '0', '0' },
        { '9', '0', '0', '2', '0', '0', '0', '0', '0' },
        { '0', '8', '0', '0', '0', '0', '3', '0', '0' },
        { '0', '4', '9', '5', '0', '1', '6', '7', '0' },
        { '0', '0', '7', '0', '0', '0', '0', '1', '0' },
        { '0', '0', '0', '0', '0', '5', '0', '0', '6' },
        { '0', '0', '0', '9', '3', '4', '2', '0', '7' },
        { '0', '0', '0', '0', '1', '0', '0', '8', '3' },
    };
#endif
}

bool solve(Grid& grid)
{
    Point point = getNextPoint(grid);
    if(point[0] == 9 || point[1] == 9)
    {
        return true;
    }

    for(char ch = (1 + '0') ; ch <= (9 + '0') ; ++ch)
    {
        if(isValid(ch, point, grid))
        {
            grid[point[0]][point[1]] = ch;
            if( solve(grid) )
            {
                return true;
            }

            grid[point[0]][point[1]] = '0';
        }        
    }
    return false;
}

int main()
{
    Grid grid = getGrid();
    PrintGrid(grid);
    solve(grid);
    PrintGrid(grid);
}