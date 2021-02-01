#ifndef MAZE_HPP
#define	MAZE_HPP

#include "Utility.hpp"

/**
 * 迷路クラス
 */
class Maze {
    Point startPoint, goalPoint, nowPoint;//スタート点、ゴール点、現在位置
    int **maze;//迷路の2次元配列
    int row, col, numState, numAction; //行、列、状態数、行動数
public:
    const static int UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3, //上下左右
            FLOOR = 0, WALL = 1; //床、壁    
    Maze(int row, int col, int type);//メモリ確保、迷路作成関数呼び出し
    ~Maze();//メモリ解放
    void maze0();//複数経路が存在する迷路の作成
    void maze1();//ゴールまでが1通りの迷路作成
    double reward()const;//報酬を与える関数
    void move(int action);//actionに従い行動する
    bool isGoal()const;//現在ゴールにいるかどうか
    bool isWall(int x, int y)const;//(x,y)が壁かどうか
    int getNumState()const;//状態数を返す
    int getNumAction()const;//行動数を返す
    int getState()const;//現在の状態を返す
    void fromStart();//エージェントをスタートに戻す
    void draw()const;//迷路の描画
    bool createFinish()const;//迷路作成完了かどうか(maze1()で用いる)
};

#endif	/* MAZE_HPP */

