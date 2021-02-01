#include "Agent.hpp"

const double Agent::DISCOUNT_RATE = 0.95; //割引率
const double Agent::LEARNING_RATE = 0.1; //学習率
const double Agent::RANDOM_RATE = 0.01; //ランダムの行動発生率

/**
 * コンストラクタ
 * @param maze 迷路のアドレス
 */
Agent::Agent(Maze *maze) {

    this->maze = maze;
    numState = maze->getNumState();
    numAction = maze->getNumAction();

    srand((unsigned) time(NULL));

    //評価値をすべて0にする
    Q = new double*[numState];
    for (int i = 0; i < numState; ++i)
        Q[i] = new double[numAction];
    for (int s = 0; s < numState; ++s)
        for (int a = 0; a < numAction; ++a)
            Q[s][a] = 0.0;
}

/**
 * デストラクタ。メモリ解放する。
 */
Agent::~Agent() {
    for (int i = 0; i < numState; ++i)
        delete[]Q[i];
    delete[]Q;
}

/**
 * 最も評価値の高い行動を選択する。
 * @return 
 */
int Agent::selectBestAction() const {
    int s = maze->getState(), bestAction = 0;
    //評価値の最も高い行動を探す
    for (int a = 1; a < numAction; ++a) {
        if (Q[s][a] > Q[s][bestAction])
            bestAction = a;
    }
    return bestAction;
}

/**
 * エージェントの行動選択
 * @return 
 */
int Agent::selectAction() const {
    //一定の確率で、ベストでない動きをする。
    if (((double) rand() / RAND_MAX) < RANDOM_RATE)
        return rand() % numAction;
    return selectBestAction();
}

/**
 *  迷路をスタートからにする。
 */
void Agent::init() {
    maze->fromStart(); //キャラクターをスタートに配置
    state = maze->getState(); //キャラクターの状態のナンバーを取得
}

/**
 *  エージェントの1ステップ。(行動、評価値Qの更新。)
 */
void Agent::step() {
    action = selectAction(); //行動の選択。ベストアクションとは限らない。
    maze->move(action); //選択された行動に従い動く。ただし、壁がある場合は無視される。
    nextState = maze->getState(); //移動後の状態のナンバーを取得
    nextAction = selectBestAction(); //ベストアクションを選択
    //Q[s][a] += (学習率)*(報酬 + (割引率)*(max{Q[s'][a']})-Q[s][a]);
    Q[state][action] += LEARNING_RATE * (maze->reward() + DISCOUNT_RATE * Q[nextState][nextAction] - Q[state][action]);
    state = nextState; //移動後の状態のナンバーを現在の場所ナンバーに記録
}
