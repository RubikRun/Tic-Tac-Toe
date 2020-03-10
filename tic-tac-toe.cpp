#include <iostream>
#include <vector>
using namespace std;

int const MAXBOARDSIZE = 100;
char const EmptySymbol = '.';

struct Board;
struct Player;
struct Cell;

struct Cell
{
    int row, col;

    Cell(int row, int col)
    {
        this->row = row;
        this->col = col;
    }
    Cell(){}
};

bool BoardSizeIsValid(int boardSize)
{
    return (boardSize > 0 && boardSize < MAXBOARDSIZE);
}

struct Board
{
    int size;
    char grid[MAXBOARDSIZE][MAXBOARDSIZE];

    Board()
    {
        int boardSize;
        cout << "Enter board size: ";
        while (true)
        {
            cin >> boardSize;
            if (BoardSizeIsValid(boardSize))
            {
                break;
            }
            cout << "Not a valid board size. Should be an integer greater than 0 and less than " << MAXBOARDSIZE << "." << endl;
            cout << "Try again: ";
        }
        size = boardSize;

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                grid[i][j] = EmptySymbol;
            }
        }
    }

    void Print();

    bool ApplyPlayerMove(Player& player, Cell& cell);

    bool CellIsValid(Cell& cell);

    bool PlayerIsWinner(Player& player);
};

void Board::Print()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

bool Board::CellIsValid(Cell& cell)
{
    return (cell.row >= 0 && cell.row < size && cell.col >= 0 && cell.col < size);
}

struct Player
{
    int id;
    char symbol;

    Player(int id, char symbol)
    {
        this->id = id;
        this->symbol = symbol;
    }

    void MakeMove(Board& board);
};

void Player::MakeMove(Board& board)
{
    cout << "Player #" << id << ", it's your turn. Choose a cell: ";
    
    Cell cell;
    while (true)
    {
        cin >> cell.row >> cell.col;

        if (board.CellIsValid(cell))
        {
            if (board.ApplyPlayerMove(*this, cell))
            {
                break;
            }
            cout << "This cell is already taken." << endl;
        }
        else
        {
            cout << "Not a valid cell in a " << board.size << "x" << board.size << " board." << endl;
        }
        cout << "Try again: ";
    }
}

bool Board::ApplyPlayerMove(Player& player, Cell& cell)
{
    if (grid[cell.row][cell.col] != EmptySymbol)
    {
        return false;
    }
    grid[cell.row][cell.col] = player.symbol;
    return true;
}

bool Board::PlayerIsWinner(Player& player)
{
    bool isWinner;
    for (int i = 0; i < size; i++)
    {
        isWinner = true;
        for (int j = 0; j < size; j++)
        {
            if (grid[i][j] != player.symbol)
            {
                isWinner = false;
                break;
            }
        }
        if (isWinner)
        {
            return true;
        }

        isWinner = true;
        for (int j = 0; j < size; j++)
        {
            if (grid[j][i] != player.symbol)
            {
                isWinner = false;
                break;
            }
        }
        if (isWinner)
        {
            return true;
        }
    }

    isWinner = true;
    for (int i = 0; i < size; i++)
    {
        if (grid[i][i] != player.symbol)
        {
            isWinner = false;
            break;
        }
    }
    if (isWinner)
    {
        return true;
    }

    isWinner = true;
    for (int i = 0; i < size; i++)
    {
        if (grid[i][size - 1 - i] != player.symbol)
        {
            isWinner = false;
            break;
        }
    }
    if (isWinner)
    {
        return true;
    }

    return false;
}

int main()
{
    Board board;
    board.Print();

    vector<Player> players;
    players.push_back(*(new Player(1, 'X')));
    players.push_back(*(new Player(2, 'O')));

    int turn = 0;
    while (true)
    {
        players[turn].MakeMove(board);
        board.Print();
        if(board.PlayerIsWinner(players[turn]))
        {
            cout << "Player #" << players[turn].id << " is the winner!" << endl;
            cout << "The end." << endl;
            return 0;
        }

        turn = (turn + 1) % 2;
    }

    return 0;
}