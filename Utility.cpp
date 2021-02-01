#include "Utility.hpp"

/**
 * 座標の値をセット
 * @param i
 * @param j
 */
void Point::set(int i, int j) {
    x = i, y = j;
}

/**
 * 座標が(i,j)と一致する場合true
 * @param i
 * @param j
 * @return 
 */
bool Point::equal(int i, int j) const {
    return (x == i && y == j);
}

/**
 * 演算子のオーバーロード(座標が等しい場合true)
 * @param point
 * @return 
 */
bool Point::operator==(const Point& point) const {
    return (x == point.x && y == point.y);
}

/**
 * 0からmax-1までの値をランダムに返す
 * @param max 
 * @return 
 */
int getRandom(int max) {
    return rand() % max;
}

/**
 * 指定時間休む
 * @param t 休憩時間
 */
void sleep(double t) {
    time_t t1, t2;
    t1 = t2 = clock();
    while ((double) (t2 - t1) / CLOCKS_PER_SEC < t)
        t2 = clock();
}
