#ifndef AGENT_HPP
#define	AGENT_HPP

#include "Maze.hpp"
#include "Utility.hpp"

/**
 * エージェント(キャラクター)のクラス
 */
class Agent {
    int state, action, nextState, nextAction; //今の状態、今とった行動、次の状態、次の行動
    int numState, numAction; //状態数,行動数
    double **Q; //評価値を記録しておく2次元配列
    Maze *maze; //迷路へのポインタ
public:
    static const double DISCOUNT_RATE, //割引率
    LEARNING_RATE, //学習率
    RANDOM_RATE; //ランダムの行動発生率

    Agent(Maze* maze);//メモリ確保、Qの初期化など
    ~Agent();//メモリ解放
    int selectBestAction()const;//最も評価値の高い行動を返す
    int selectAction()const;//行動選択
    void init();//エージェントをスタートに戻す
    void step();//エージェントの1回の行動
};

#endif	/* AGENT_HPP */

