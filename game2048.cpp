#include<iostream>
#include<vector>
#include<ctime>
#include<cstdlib>
using namespace std;
class Game_2048
{undefined
public:
    Game_2048();
    ~Game_2048();
    void introduction();
    bool judgeOver();                            //判断游戏是否结束
    void reSize();
    void printBoard();                          //打印函数
    void getRand();                              //随机在棋盘上生成2，4；
    void slide();                                //滑动
private:
    int m=4, n=4;
    char op;                                   //用户操作
    vector< vector<int> >     board;                                //棋盘
    vector<int>  row;
    bool judgeInsert(int x,int y);
    bool judgeSlide();                               //判断是否能滑动，（未写完）
    void copyBoard(vector< vector<int> > &newBoard,vector< vector<int> > &board);
    void inputOp();
    char getOp();                            //返回操作符

    bool judgeLeftSlide(bool mark=true);
    void leftSlide();                            //左滑动

    bool judgeRightSlide(bool mark = true);
    void rightSlide();

    bool judgeUpSlide(bool mark = true);
    void upSlide();

    bool judgeDownSlide(bool mark = true);
    void downSlide();

    void reStart();
    void enlarge();                             //将值扩大二倍
};

int main()
{undefined
    Game_2048 NB;
    NB.introduction();
    NB.getRand();
    NB.printBoard();
    while (!NB.judgeOver())
    {undefined
        NB.slide();
        NB.getRand();
        NB.printBoard();
    } 
    cout << "游戏结束！！！\n";
    system("pause");
    return 0;

}

void Game_2048::introduction()
{undefined
    cout << "这是一个2048游戏,规则如下：\n";
    cout << "上划：W；\n下滑：S；\n左划：A；\n右划：D；\n退出：Q；\n重新开始：R；\n请输入下次操作，\n";
}

void Game_2048::slide()
{undefined
    inputOp();
    switch (getOp())
    {undefined
    case 'a':
    case 'A':
        if (judgeLeftSlide())
            do
                leftSlide();
            while (judgeLeftSlide(false));
        else
        {undefined
            cout << "无法左滑动，请重试！！！\n";
            slide();
        }
        break;
    case 'd':
    case 'D':
        if (judgeRightSlide())
            do
                rightSlide();
        while (judgeRightSlide(false));        
        else
        {undefined
            cout << "无法右滑动，请重试！！！\n";
            slide();
        }
        break;
    case 'w':
    case 'W':
        if(judgeUpSlide())
            do
            upSlide();
        while (judgeUpSlide(false));
        else
        {undefined
            cout << "无法上滑动，请重试！！！\n";
            slide();
        }
        break;
    case 's':
    case 'S':
        if(judgeDownSlide())
            do    
                downSlide();
            while (judgeDownSlide(false));
        else
        {undefined
            cout << "无法下滑动，请重试！！！\n";
            slide();
        }
        break;
    case 'p':
    case 'P':
        enlarge();
        break;
    case 'q':
    case 'Q':
        exit(0);
        break;
    case 'r':
    case 'R':
        reStart();
        break;
    default:
        cout << "输入错误，作为惩罚，随机生成一个数！\n";
        break;
    }
}


void Game_2048::reStart()
{undefined
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {undefined
            board[i][j] = 0;
        }
}

void Game_2048::enlarge()
{undefined
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
        {undefined
            board[i][j] *= 2;
        }
}


char Game_2048::getOp()
{undefined
    return op;
}

void Game_2048::upSlide()
{undefined
    for (int j = 0; j < n; j++)
        for (int i = m - 1; i > 0; i--) {                              //n-1!!
            if (board[i][j] != 0 && board[i - 1][j] == 0)            //移动
            {undefined
                    board[i - 1][j] = board[i][j];
                    board[i][j] = 0;
            }
        }
    for (int j = 0; j < n; j++)
        for (int i = m - 1; i > 0; i--) {undefined
            if (board[i][j] != 0 && board[i-1][j] == board[i][j])  //覆盖
            {undefined
                board[i-1][j] += board[i][j];
                board[i][j] = 0;
            }
        }
}

bool Game_2048::judgeUpSlide(bool mark)
{undefined
    if (mark)
    {undefined
        for (int i = 0; i < m; i++)
            for (int j = n - 1; j > 0; j--)
            {undefined
                if (board[i][j] == 0)
                return true;
            }
    }
    for (int j = 0; j < n; j++)
        for (int i = m - 1; i > 0; i--) {                              //n-1!!
            if (board[i][j] != 0 && board[i - 1][j] == 0)            //移动
                return true;
            if (board[i][j] != 0 && board[i - 1][j] == board[i][j])  //覆盖
                return true;
        }
    return false;
}

bool Game_2048::judgeDownSlide(bool mark)
{undefined
    if (mark) {undefined
        for (int i = 0; i < m; i++)
            for (int j = n - 1; j > 0; j--)
                {undefined
                    if (board[i][j] == 0)
                        return true;
                }
        
    }
    for (int j = 0; j < n; j++)
                for (int i = 0; i < m - 1; i++) {                              //n-1!!
                    if (board[i][j] != 0 && board[i + 1][j] == 0)            //移动
                        return true;
                    if (board[i][j] != 0 && board[i + 1][j] == board[i][j])  //覆盖
                        return true;

                }
    return false;
}

void Game_2048::downSlide()
{undefined
    for (int j = 0; j < n; j++)
        for (int i = 0; i < m - 1; i++) {                         
            if (board[i][j] != 0 && board[i + 1][j] == 0)            //移动
            {undefined
                    board[i + 1][j] = board[i][j];
                    board[i][j] = 0;
            }
        }
    for (int j = 0; j < n; j++)
        for (int i = 0; i < m - 1; i++) {undefined
            if (board[i][j] != 0 && board[i + 1][j] == board[i][j])  //覆盖
            {undefined
                board[i + 1][j] += board[i][j];
                board[i][j] = 0;
            }
        }
}


void Game_2048::rightSlide()
{undefined
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n - 1; j++) {                              //n-1!!
            if (board[i][j] != 0 && board[i][j + 1] == 0)            //移动
            {undefined
                    board[i][j + 1] = board[i][j];
                    board[i][j] = 0;
            }
        }
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n - 1; j++) {undefined
            if (board[i][j] != 0 && board[i][j + 1] == board[i][j])  //覆盖
            {undefined
                board[i][j + 1] += board[i][j];
                board[i][j] = 0;
            }
        }
}

bool Game_2048::judgeRightSlide(bool mark )
{undefined
    if (mark) {undefined
        for (int i = 0; i < m; i++)
            for (int j = n - 1; j > 0; j--)
            {undefined
                if (board[i][j] == 0)
                    return true;
            }
    }
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n - 1; j++) {                              //n-1!!
            if (board[i][j] != 0 && board[i][j + 1] == board[i][j])  //覆盖
                return true;
            if (board[i][j] != 0 && board[i][j + 1] == 0)
                return true;
        }
    return false;
}

void Game_2048::leftSlide()
{undefined
    for (int i = 0; i < m; i++)
        for (int j = 1; j < n; j++) {                              //n-1!!
            if (board[i][j] != 0 && board[i][j - 1] == 0)            //移动
            {undefined
                    board[i][j - 1] = board[i][j];
                    board[i][j] = 0;
            }
        }
    for (int i = 0; i < m; i++)
        for (int j = 1; j < n; j++) {undefined
            if (board[i][j] != 0 && board[i][j - 1] == board[i][j])  //覆盖
            {undefined
                board[i][j - 1] += board[i][j];
                board[i][j] = 0;
            }
        }
}

bool Game_2048::judgeLeftSlide(bool mark)
{undefined
    if (mark) {undefined
        for (int i = 0; i < m; i++)
                for (int j = n - 1; j > 0; j--)
                {undefined
                    if (board[i][j] == 0)
                        return true;
                }
    }
    for (int i = 0; i < m; i++)
        for (int j = n - 1; j > 0; j--) {                              //n-1!!
            if (board[i][j] != 0 && board[i][j - 1] == 0)            //移动
                return true;
            if (board[i][j] != 0 && board[i][j - 1] == board[i][j])  //覆盖
                return true;
        }
    return false;
}

bool Game_2048::judgeOver()
{undefined
    if (op == 'q' || op == 'Q')
        return true;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {undefined
            if (board[i][j] == 2048)
            {undefined
                printBoard();
                cout << "有数字达到了2048，恭喜！！！\n";
                return true;
            }    
        }

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {undefined
             if (board[i][j] == 0)
                return false;
        }
    if (judgeSlide())
        return false;
    else
    {undefined
        cout << "无法再滑动\n";
        return true;
    }
        
}

bool Game_2048::judgeSlide()
{undefined
    vector< vector<int> >     copyBoard;                                //棋盘
    vector<int>  copyRow;
    for (int i = 0; i < n; i++) {undefined
        copyRow.push_back(0);
    }
    for (int i = 0; i < m; i++) {undefined
        copyBoard.push_back(copyRow);
    }
    copyBoard = board;
    upSlide();
    downSlide();
    leftSlide();
    rightSlide();
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
        {undefined
            if (board[i][j] == 0) {undefined
                board = copyBoard;
                return true;
            }    
        }
    return false;
}

void Game_2048::copyBoard(vector< vector<int> >& newBoard, vector< vector<int> >&     board)
{undefined
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            newBoard[i][j] = board[i][j];
}

bool Game_2048::judgeInsert(int x,int y)
{undefined
    if (board[x][y] == 0)
        return true;
    else
        return false;
}
void Game_2048::getRand()
{undefined
    srand(time(0));
    int x, y,val;
    do
    {undefined
        x = rand() % m;
        y = rand() % n;
    } while (!judgeInsert(x,y));
    val = (rand() % 2 + 1)*2;
    board[x][y] = val;

}

void Game_2048::inputOp()
{undefined
    cin >> op;
}
void Game_2048::reSize()
{undefined
    cout << "请输入棋盘大小m*n\n";
    cin >> m >> n;
    Game_2048();
}

Game_2048::~Game_2048()
{undefined
}

Game_2048::Game_2048()
{undefined
    for (int i = 0; i < n; i++){undefined
        row.push_back(0);
    }
    for (int i = 0; i < m; i++){undefined
        board.push_back(row);
    }
}
void Game_2048::printBoard()
{undefined
    cout << "\n--------------\n";
    for (int i = 0; i < m; i++) {undefined
        for (int j = 0; j < n; j++) {undefined
            cout << board[i][j];
            if (j < n-1)
            {undefined
                cout << "—";
            }
            if (j == n-1 && i < m-1)
            {undefined
                cout << endl;
                int count = 0;
                while (count++ < n-1)
                {undefined
                    cout << "|  ";
                }
                cout << "|" << endl;
            }
        }
    }

    cout << "\n--------------\n" ;
}

