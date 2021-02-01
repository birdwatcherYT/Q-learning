#include "Maze.hpp"

/**
 * コンストラクタ
 * @param row 行
 * @param col 列
 * @param type 迷路の種類
 */
Maze::Maze(int row, int col, int type) {
    //画面クリア
    std::cout << "\x1b[2J";

    this->row = row;
    this->col = col;
    //状態数は迷路の位置の数
    numState = row * col;
    //行動数は上下左右
    numAction = 4;

    srand((unsigned) time(NULL));
    //迷路の動的確保
    maze = new int*[row];
    for (int i = 0; i < row; ++i)
        maze[i] = new int[col];

    if (type == 0) maze0();
    else maze1();
}

/**
 * デストラクタ(メモリ開放)
 */
Maze::~Maze() {
    for (int i = 0; i < row; ++i)
        delete[]maze[i];
    delete[]maze;
}

/**
 * 迷路作成(複数のルートがある場合)
 */
void Maze::maze0() {

    //ゴールとスタートの位置決定
    startPoint.set(1, 1);
    goalPoint.set(row - 2, col - 2);
    //スタートから始める
    fromStart();

    //すべて床(道)にする
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < col; ++j)
            maze[i][j] = FLOOR;

    //周りを壁で囲む
    for (int i = 0; i < col; ++i) {
        maze[0][i] = WALL;
        maze[row - 1][i] = WALL;
    }
    for (int i = 0; i < row; ++i) {
        maze[i][0] = WALL;
        maze[i][col - 1] = WALL;
    }

    // 内壁を1つおきに作る
    for (int i = 0; i < row; i += 2)
        for (int j = 0; j < col; j += 2)
            maze[i][j] = WALL;

    //内壁からランダムに各方向に壁を作る
    for (int i = 2; i < row - 1; i += 2) {
        for (int j = 2; j < col - 1; j += 2) {
            switch (getRandom(4)) {
                case UP:
                    maze[i - 1][j] = WALL;
                    break;
                case DOWN:
                    maze[i + 1][j] = WALL;
                    break;
                case LEFT:
                    maze[i][j - 1] = WALL;
                    break;
                case RIGHT:
                    maze[i][j + 1] = WALL;
                    break;
            }
        }
    }
}

/**
 * 穴掘り法による迷路(経路は1本)
 */
void Maze::maze1() {

    //スタートとゴールの決定
    startPoint.set(2, 2);
    goalPoint.set(row - 3, col - 3);
    //スタートから開始
    fromStart();

    //すべて壁にする
    for (int i = 0; i < row; ++i)
        for (int j = 0; j < col; ++j)
            maze[i][j] = WALL;

    //周りを床(道)で囲む。こうすることで、インデックスのオーバーフローを考慮しなくて良い。
    for (int i = 0; i < col; ++i) {
        maze[0][i] = FLOOR;
        maze[row - 1][i] = FLOOR;
    }
    for (int i = 0; i < row; ++i) {
        maze[i][0] = FLOOR;
        maze[i][col - 1] = FLOOR;
    }

    int i = 2, j = 2, count = 0,
            countMax = 10000; //ループの回数Max
    maze[i][j] = FLOOR; //スタートを床にする

    //各方向に行けるかどうかのフラグ
    bool right, left, up, down;

    while (!createFinish()) {
        right = left = up = down = true;

        while (right || left || up || down) {
            int dir = getRandom(4);
            switch (dir) {
                case UP:
                    if (isWall(i - 2, j)) {
                        //2つ床をつくる
                        maze[--i][j] = FLOOR;
                        maze[--i][j] = FLOOR;
                    } else {
                        up = false;
                    }
                    break;
                case DOWN:
                    if (isWall(i + 2, j)) {
                        //2つ床をつくる
                        maze[++i][j] = FLOOR;
                        maze[++i][j] = FLOOR;
                    } else {
                        down = false;
                    }
                    break;
                case LEFT:
                    if (isWall(i, j - 2)) {
                        //2つ床をつくる
                        maze[i][--j] = FLOOR;
                        maze[i][--j] = FLOOR;
                    } else {
                        left = false;
                    }
                    break;
                case RIGHT:
                    if (isWall(i, j + 2)) {
                        //2つ床をつくる
                        maze[i][++j] = FLOOR;
                        maze[i][++j] = FLOOR;
                    } else {
                        right = false;
                    }
                    break;
            }
        }

        if (count < countMax) {
            //壁じゃない位置をランダムで選択
            do {
                //(偶数,偶数)の座標を取得
                i = getRandom(row / 2 - 2) * 2 + 2;
                j = getRandom(col / 2 - 2) * 2 + 2;
            } while (isWall(i, j));
            ++count;
        } else {//ランダムで手に負えなくなったときの救済処理
            bool flag = false;
            for (i = 2; i < row - 1; i += 2) {
                for (j = 2; j < col - 1; j += 2) {
                    //(偶数,偶数)で壁かつ、そこへアクセスする経路が無い場合
                    if (isWall(i, j) && isWall(i + 1, j) && isWall(i - 1, j) && isWall(i, j + 1) && isWall(i, j - 1)) {
                        //道を作る
                        if (!isWall(i + 2, j) && i + 3 < row)
                            i = i + 2;
                        else if (!isWall(i - 2, j) && i - 3 > 0)
                            i = i - 2;
                        else if (!isWall(i, j + 2) && j + 3 < col)
                            j = j + 2;
                        else if (!isWall(i, j - 2) && j - 3 > 0)
                            j = j - 2;
                        flag = true;
                        break;
                    }
                }
                if (flag) break;
            }
        }
    }
}

/**
 * 穴掘り法において迷路作成終了したかどうか
 * @return 迷路作成終了したかどうか
 */
bool Maze::createFinish() const {
    for (int i = 2; i < row - 1; i += 2)
        for (int j = 2; j < col - 1; j += 2)
            if (isWall(i, j)) return false;
    return true;
}

/**
 * 報酬を与える
 * @return 
 */
double Maze::reward() const {
    if (isGoal()) return 0.0;
    else return -1.0;
}

/**
 * キャラクターをactionの方向に動かす。ただし、その方向が壁の時は何もしない。
 * @param action
 */
void Maze::move(int action) {
    switch (action) {
        case UP:
            if (!isWall(nowPoint.x - 1, nowPoint.y))
                --nowPoint.x;
            break;
        case DOWN:
            if (!isWall(nowPoint.x + 1, nowPoint.y))
                ++nowPoint.x;
            break;
        case LEFT:
            if (!isWall(nowPoint.x, nowPoint.y - 1))
                --nowPoint.y;
            break;
        case RIGHT:
            if (!isWall(nowPoint.x, nowPoint.y + 1))
                ++nowPoint.y;
            break;
    }
}

/**
 * キャラクターがゴールにいるかどうか
 * @return 
 */
bool Maze::isGoal() const {
    return (nowPoint == goalPoint);
}

/**
 * (x,y)が壁であるかどうか
 * @param x
 * @param y
 * @return 
 */
bool Maze::isWall(int x, int y) const {
    return (maze[x][y] == WALL);
}

/**
 * 取りうる状態の数
 * @return 
 */
int Maze::getNumState() const {
    return numState;
}

/**
 * 取れる行動の数
 * @return 
 */
int Maze::getNumAction() const {
    return numAction;
}

/**
 * 現在の状態の番号を返す
 * @return 
 */
int Maze::getState() const {
    return nowPoint.x * col + nowPoint.y;
}

/**
 * スタートから始める
 */
void Maze::fromStart() {
    nowPoint = startPoint;
}

/**
 * 迷路を画面に表示
 */
void Maze::draw() const {
    using namespace std;
    cout << "\x1b[0;0H";
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (isWall(i, j))
                cout << "W";
            else if (nowPoint.equal(i, j))
                cout << "A";
            else if (startPoint.equal(i, j))
                cout << "S";
            else if (goalPoint.equal(i, j))
                cout << "G";
            else
                cout << " ";
        }
        cout << endl;
    }
}

