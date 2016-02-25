#include "MyStrategy.h"

#define PI 3.14159265358979323846
#define _USE_MATH_DEFINES

#include <cmath>
#include <cstdlib>

using namespace model;
using namespace std;

double lastX = 0, lastY = 0;

int isToBack = 0, stuckDelay = 300;

const int PREPARE_TO_TURN_RIGHT = 0, PREPARE_TO_TURN_LEFT = 1, TURN_RIGHT = 2, TURN_LEFT = 3;
const double EPS = 2.0;

bool stuckStrategy(const Car& self, Move& move) {
    if ((fabs(self.getX() - lastX) < EPS) && (fabs(self.getY() - lastY) < EPS) && (stuckDelay <= 0)) {
        isToBack = 150;
        stuckDelay = 100;
    }
    if (isToBack > 30) {
        move.setEnginePower(-1.0);
        --isToBack;
        return true;
    }
    if (isToBack > 0) {
        move.setBrake(true);
        --isToBack;
        return true;
    }
    move.setBrake(false);
    --stuckDelay;
    return false;
}

int getNextStrategy(const Car& self, const World& world, const Game& game, Move& move) {
    int currentTileIndex = self.getNextWaypointIndex();
    std::vector< std::vector<int> > currentWaypoints(4);
    for (int i = 0; i < 4; ++i) {
        currentWaypoints[i] = world.getWaypoints()[(currentTileIndex + i) % world.getWaypoints().size()];

    }

    //for (int i = 0)


    return 0;
}

void MyStrategy::move(const Car& self, const World& world, const Game& game, Move& move) {
    if (stuckStrategy(self,  move)) {
        return;
    }
    lastX = self.getX(), lastY = self.getY();
    //int nextStrategy = getNextStrategy(self, game);
    double nextWaypointX = (self.getNextWaypointX() + 0.5) * game.getTrackTileSize();
    double nextWaypointY = (self.getNextWaypointY() + 0.5) * game.getTrackTileSize();

    double cornerTileOffset = 0.25 * game.getTrackTileSize();

    switch (world.getTilesXY()[self.getNextWaypointX()][self.getNextWaypointY()]) {
        case LEFT_TOP_CORNER:
            nextWaypointX += cornerTileOffset;
            nextWaypointY += cornerTileOffset;
            break;
        case RIGHT_TOP_CORNER:
            nextWaypointX -= cornerTileOffset;
            nextWaypointY += cornerTileOffset;
            break;
        case LEFT_BOTTOM_CORNER:
            nextWaypointX += cornerTileOffset;
            nextWaypointY -= cornerTileOffset;
            break;
        case RIGHT_BOTTOM_CORNER:
            nextWaypointX -= cornerTileOffset;
            nextWaypointY -= cornerTileOffset;
            break;
    }

    double angleToWaypoint = self.getAngleTo(nextWaypointX, nextWaypointY);
    double speedModule = hypot(self.getSpeedX(), self.getSpeedY());

    move.setWheelTurn(angleToWaypoint * 32.0 / PI);
    move.setEnginePower(0.85);

    if (speedModule * speedModule * abs(angleToWaypoint) > 2.5 * 2.5 * PI) {
        move.setBrake(true);
    }


}

MyStrategy::MyStrategy() { }
