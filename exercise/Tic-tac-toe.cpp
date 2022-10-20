#include <windows.h>

#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>

using namespace std;

/**
 * @brief 定义四种情况，人机进行对弈
 *
 */
enum players
{
    Computer,
    Human,
    Draw,
    None
};

/**
 * @brief 可能赢的情况，一行、一列、对角
 *
 */
const int iWin[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};
/**
 * @brief 井字棋类
 *
 */
class ttt
{
public:
    /**
     * @brief Construct a new ttt object
     *
     */
    ttt()
    {
        reset();
    }

    /**
     * @brief 游戏函数
     *
     */
    void play()
    {
        int res = Draw;
        while (true)
        {
            drawGrid();
            while (true)
            {
                if ((_p + _base) % 2)
                    getHumanMove();
                else
                    getComputerMove();
                drawGrid();
                res = checkVictory();
                if (res != None)
                    break;
                ++_p;
            }

            if (res == Human)
                cout << "CONGRATULATIONS HUMAN --- You won!";
            else if (res == Computer)
                cout << "NOT SO MUCH A SURPRISE --- I won!";
            else
                cout << "It's a draw!";

            cout << endl
                 << endl;

            string r;

            cout << "Play again(Y/n)?";
            cin >> r;
            if (r != "Y" && r != "y")
                return;
            reset();
        }
    }

private:
    /**
     * @brief 棋局最开始的状态函数
     *
     */
    void reset()
    {
        _base = rand() % 2;
        _p = 0;
        for (int i = 0; i < 9; ++i)
        {
            _field[i] = None;
        }
    }

    /**
     * @brief 分别给格子进行赋值
     *
     */
    void drawGrid()
    {
        system("cls");
        COORD c = {0, 2};
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);

        cout << " 1 | 2 | 3 " << endl;
        cout << "---+---+---" << endl;
        cout << " 4 | 5 | 6 " << endl;
        cout << "---+---+---" << endl;
        cout << " 7 | 8 | 9 " << endl
             << endl
             << endl;

        int f = 0;
        for (short int y = 0; y < 5; y += 2)
        {
            for (short int x = 1; x < 11; x += 4)
            {
                if (_field[f] != None)
                {
                    COORD c = {(short)0, (short)0};
                    c.X = x;
                    c.Y = y + 2;
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
                    string o = _field[f] == Computer ? "X" : "O";
                    cout << o;
                }
                ++f;
            }
        }
        c.Y = 9;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    }

    /**
     * @brief 判断当前棋局是否可以判断输赢
     *
     * @return int
     */
    int checkVictory()
    {
        for (int i = 0; i < 8; ++i)
        {
            if (_field[iWin[i][0]] != None &&
                _field[iWin[i][0]] == _field[iWin[i][1]] &&
                _field[iWin[i][1]] == _field[iWin[i][2]])
            {
                return _field[iWin[i][0]];
            }
        }

        int i = 0;
        for (int f = 0; f < 9; ++f)
        {
            if (_field[f] != None)
                ++i;
        }

        if (i == 9)
            return Draw;

        return None;
    }

    /**
     * @brief 轮到人走棋
     *
     */
    void getHumanMove()
    {
        string m;
        cout << "Your turn : enter your move (1-9)";
        while (true)
        {
            cin >> m;
            if (_field[atoi(m.c_str()) - 1] != None)
                cout << "Invalid move. Try again!" << endl;
            else
                break;
        }
        _field[atoi(m.c_str()) - 1] = Human;
    }

    /**
     * @brief 轮到Computer走棋
     *
     */
    void getComputerMove()
    {
        // auto CursorVisableSwitch = [](int visable) -> void
        // {
        //     CONSOLE_CURSOR_INFO cursor_info = {1, visable};
        //     SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
        // };
        // CursorVisableSwitch(false);

        // COORD position;
        // /**
        //  * @brief 获取当前光标位置
        //  *
        //  */
        // auto GetCursorPosition = [&position]() -> void
        // {
        //     CONSOLE_SCREEN_BUFFER_INFO csbi;
        //     if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
        //     {
        //         position.X = csbi.dwCursorPosition.X;
        //         position.Y = csbi.dwCursorPosition.Y;
        //     }
        // };

        // /**
        //  * @brief 移动光标到目标位置
        //  *
        //  */
        // auto moveCursorPosition = [](COORD destination) -> void
        // {
        //     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), destination);
        // };

        drawGrid();
        cout << "Computer turn :";
        for (int i = 0; i < 3; ++i)
        {
            sleep(1);
            cout << " ...";
        }

        sleep(1);

        int move = 0;
        do
        {
            move = rand() % 9;
        } while (_field[move] != None);

        if (_p == 1 && _field[4] != None)
        {
            while (!(move == 1 || move == 3 || move == 5 || move == 7))
                move = rand() % 9;
        }

        for (int i = 0; i < 8; ++i)
        {
            int try1 = iWin[i][0], try2 = iWin[i][1], try3 = iWin[i][2];

            if (_field[try1] != None && _field[try1] == _field[try2] &&
                _field[try3] == None)
            {
                move = try3;
                if (_field[try1] == Computer)
                    break;
            }

            if (_field[try1] != None && _field[try1] == _field[try3] &&
                _field[try2] == None)
            {
                move = try2;
                if (_field[try1] == Computer)
                    break;
            }

            if (_field[try2] != None && _field[try2] == _field[try3] &&
                _field[try1] == None)
            {
                move = try1;
                if (_field[try2] == Computer)
                    break;
            }
        }
        _field[move] = Computer;
    }

    int _p;        //计数器，用来判断当前玩家是谁
    int _base;     //判断谁先下 0Cumputer 1Huamn
    int _field[9]; //格子状态
};

int main()
{
    srand(GetTickCount());
    ttt tic;
    tic.play();
    return 0;
}