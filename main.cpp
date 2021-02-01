#include "Agent.hpp"
using namespace std;

/*
 * 強化学習Q-learningによる迷路の最短経路探索
 */

int main() {
    const int ROW = 9, COL = 21, //迷路作成の都合上、どちらも必ず奇数
            STEP_MAX = 10000, //移動する回数の上限
            LOOP_MAX = 1000; //ループの上限
    const double SLEEP_TIME = 0.01; //描画の間隔(s)
    int type; //迷路の種類

    cout << "0:複数経路の迷路,  1:一本道の迷路" << endl;
    cin >> type;

    Maze maze(ROW, COL, type);
    Agent agent(&maze);
    int step;

    cout << "\x1b[" << ROW + 1 << ";0H"; //迷路の下に情報を表示するために、迷路の下まで移動
    cout << "loop : 0  step : -" << endl;

    for (int loop = 1; loop <= LOOP_MAX; ++loop) {
        step = 0;
        agent.init();
        while (!maze.isGoal() && step < STEP_MAX) {
            agent.step(); //エージェントの1ステップ(行動、評価値の更新)
            maze.draw(); //迷路描画
            ++step;
            sleep(SLEEP_TIME);
        }
        cout << "\x1b[K"; //行末までをクリア
        cout << "loop : " << loop << "  step : " << step << endl;
    }
    return 0;
}
