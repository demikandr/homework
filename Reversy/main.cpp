#include <iostream>
#include <stack>
#include <vector>
#include <assert.h>
/* Обход дерева с альфа-бета отсечением — Функция score_alphabeta
   вычисляет score(depth) более оптимально, нежели score_simple:
   score_alphabeta(-INFTY, +INFTY, depth ) = score (depth).
*/

int INF = 100000;

std::stack evristics;
std::stack<std::vector<std::vector<int> > >  fields;

struct Move{
    int x, y;
    public:
        Move& operator+=(const Move& rhs) // compound assignment (does not need to be a member,
        {                           // but often is, to modify the private members)
            this->x += rhs.x;
            this->y += rhs.x;
            return *this; // return the result by reference
        }

        // friends defined inside class body are inline and are hidden from non-ADL lookup
        friend Move operator+(Move lhs,       // passing lhs by value helps optimize chained a+b+c
                           const Move& rhs) // otherwise, both parameters may be const references.
        {
            lhs += rhs; // reuse compound assignment
            return lhs; // return the result by value (uses move constructor)
        }

};

int getColor(const Move& move) {
    if ((move.x >= 0) && (move.x < N) && (move.y >= 0) && (move.y < N)) {
        return fields.top()[move.x][move.y];
    }
    return -1;
}

int redraw(const & Move move, const Move& dMove, int color) {
    switch (getColor(move)) {
        case -1:
            return -1;
        case
    }
}

bool isCorrectMove(const Move& move) {
    int isCorrectMove = false;
    for (int dx = -1; dx < 2; ++dx) {
        for (int dy = -1; dy < 2; ++dy) {
            Move dMove = {dx, dy};
            if (getColor(move + dMove) != -1) {
                if (redraw(move, dMove, getColor(move)) != -1) {
                    isCorrectMove = true;
                }
            }

        }
    }
    return isCorrectMove;
}

int main() {
    int x, y, player;
    std::string s;
    std::cin >> s >> player;
    while (std::cin >> s >> x >> y) {
        doMove(player, x, y);
        findBestMove(player);
        std::cout << x << ' ' << y << std::endl ;
    }
    return 0;
}