#include <bangtal>
#include <vector>
#include <ctime>
#include <time.h>
#include <string>
#include <windows.h>
#include <iostream>

#include "Ball.h"
#include "Button.h"

#define RED "red"
#define GREEN "green"
#define BLUE "blue"
#define PINK "pink"
#define EMPTY "empty"

using namespace bangtal;
using namespace std;

extern ScenePtr mainScene;
extern SoundPtr mainSound;
extern int level;

ScenePtr scene;
ScenePtr ball_ex;
SoundPtr ballSound;
ObjectPtr start;

vector<vector<pair<int, int>>> coord;
vector<ObjectPtr> buttons;
vector<vector<BallPtr>> balls;
pair<int, int> clicked = make_pair(-1, -1);
TimerPtr timer;

bool cleared = false;

const string color[5] = { RED, GREEN, BLUE, PINK, EMPTY };
const string image[5] = {
	"Images/BallGame/red.png",
	"Images/BallGame/green.png",
	"Images/BallGame/blue.png",
	"Images/BallGame/pink.png",
	"Images/BallGame/empty.png"
};

const string buttonImage[5] = {
	"Images/BallGame/buttons/A.png",
	"Images/BallGame/buttons/B.png",
	"Images/BallGame/buttons/C.png",
	"Images/BallGame/buttons/D.png",
	"Images/BallGame/buttons/E.png"
};

const string clickedImage[5] = {
	"Images/BallGame/buttons/clickA.png",
	"Images/BallGame/buttons/clickB.png",
	"Images/BallGame/buttons/clickC.png",
	"Images/BallGame/buttons/clickD.png",
	"Images/BallGame/buttons/clickE.png"
};

const int buttonX[5] = {
	225, 400, 575, 750, 925
};


void initBallCoordinate() {
	const int NUM = 5;

	vector<pair<int, int>> lineCoord;
	lineCoord.push_back(make_pair(225, 130));
	lineCoord.push_back(make_pair(225, 230));
	lineCoord.push_back(make_pair(225, 330));
	lineCoord.push_back(make_pair(225, 430));
	coord.push_back(lineCoord);
	lineCoord.clear();

	lineCoord.push_back(make_pair(400, 130));
	lineCoord.push_back(make_pair(400, 230));
	lineCoord.push_back(make_pair(400, 330));
	lineCoord.push_back(make_pair(400, 430));
	coord.push_back(lineCoord);
	lineCoord.clear();

	lineCoord.push_back(make_pair(575, 130));
	lineCoord.push_back(make_pair(575, 230));
	lineCoord.push_back(make_pair(575, 330));
	lineCoord.push_back(make_pair(575, 430));
	coord.push_back(lineCoord);
	lineCoord.clear();

	lineCoord.push_back(make_pair(750, 130));
	lineCoord.push_back(make_pair(750, 230));
	lineCoord.push_back(make_pair(750, 330));
	lineCoord.push_back(make_pair(750, 430));
	coord.push_back(lineCoord);
	lineCoord.clear();

	lineCoord.push_back(make_pair(925, 130));
	lineCoord.push_back(make_pair(925, 230));
	lineCoord.push_back(make_pair(925, 330));
	lineCoord.push_back(make_pair(925, 430));
	coord.push_back(lineCoord);
	lineCoord.clear();
};

void initGame() {
	initBallCoordinate();

	vector<BallPtr> line;

	for (int i = 0; i < 5;i++) {
		auto button = Button::create(buttonImage[i], scene, buttonX[i], 30);
		buttons.push_back(button);
	}

	for (int i = 0; i < 5;i++) {
		for (int j = 0;j < 4;j++) {
			int x = coord[i][j].first;
			int y = coord[i][j].second;
			auto ball = Ball::create(image[i], color[i], scene, x, y, true);
			if (j == 3) ball->setTop(true);
			if (i == 4) ball->setEmpty(true);
			line.push_back(ball);
		}
		balls.push_back(line);
		line.clear();
	}

	for (int times = 0; times < 1000;times++) {
		int from = rand() % 5;
		int to = rand() % 5;

		if (from == to) continue;

		int fromIndex = -1;
		int toIndex = -1;
		int colorIndex = -1;

		for (int i = 3;i >= 0;i--) {
			if (!balls[from][i]->isEmpty()) {
				fromIndex = i;
				for (int j = 0;j < 4;j++) {
					if (balls[from][i]->getColor() == color[j]) colorIndex = j;
				}
				break;
			}
		}
		for (int i = 0;i < 4;i++) {
			if (balls[to][i]->isEmpty()) {
				toIndex = i;
				break;
			}
		}

		if (fromIndex == -1 || toIndex == -1) continue;

		if (fromIndex != 0) {
			balls[from][fromIndex-1]->setTop(true);
		}

		if (toIndex != 0) {
			balls[to][toIndex-1]->setTop(false);
		}
		balls[from][fromIndex]->setImage(image[4]);
		balls[from][fromIndex]->setColor(color[4]);
		balls[from][fromIndex]->setEmpty(true);
		balls[to][toIndex]->setImage(image[colorIndex]);
		balls[to][toIndex]->setColor(color[colorIndex]);
		balls[to][toIndex]->setEmpty(false);
		balls[to][toIndex]->setTop(true);
	}

	for (int i = 0; i < 5;i++) {
		auto button = buttons[i];
		button->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action) -> bool {
			int line = -1;
			for (int i = 0; i < 5;i++) {
				if (buttons[i] == object) line = i;
			}

			if (clicked.first == line) return true;
			if (clicked.first == -1) {
				if (balls[line][0]->isEmpty()) return true;
				for (int i = 3;i >= 0;i--) {
					if (!balls[line][i]->isEmpty()) {
						clicked = make_pair(line, i);
						buttons[line]->setImage(clickedImage[line]);
						return true;
					}
				}
			}
			else {
				if (!balls[line][3]->isEmpty()) return true;

				for (int i = 0;i < 4;i++) {
					if (balls[line][i]->isEmpty()) {
						int colorIndex = -1;
						int x = clicked.first;
						int y = clicked.second;
						for (int j = 0;j < 4;j++) if (color[j] == balls[x][y]->getColor()) colorIndex = j;
						balls[x][y]->setImage(image[4]);
						balls[x][y]->setColor(color[4]);
						balls[x][y]->setEmpty(true);
						balls[line][i]->setImage(image[colorIndex]);
						balls[line][i]->setColor(color[colorIndex]);
						balls[line][i]->setEmpty(false);
						buttons[x]->setImage(buttonImage[x]);
						clicked = make_pair(-1, -1);

						break;
					}
				}

				for (int i = 0;i < 5;i++) {
					string color = balls[i][0]->getColor();
					for (int j = 1; j < 4;j++) {
						if (balls[i][j]->getColor() != color) return true;
					}
				}
				showMessage("클리어!\n HINT : 'C'");
				stopTimer(timer->ID());
				hideTimer();
				level = 2;
				ballSound->stop();
				mainSound->play();
				enterScene(mainScene->ID());
			}
			return true;
			});
	}

	timer->set(180.0f);
	showTimer(timer);

	timer->setOnTimerCallback([&](TimerPtr ptr) -> bool {

		showMessage("시간이 초과되었어요. 다시 시도해주세요.");
		hideTimer();
		for (int i = 0; i < 5; i++) {
			buttons[i]->hide();
			for (int j = 0; j < 4; j++) {
				balls[i][j]->hide();

			}
		}
		enterScene(ball_ex->ID());
		return true;
	});

	timer->start();
}

void ball_main() {

	ball_ex = Scene::create("", "Images/BallGame/ballExplain.jpg");
	scene = Scene::create("공 옮기기", "Images/BallGame/background.jpg");
	ballSound = Sound::create("music/1.mp3");

	ballSound->play();
	timer = Timer::create(180.0f);
	start = Object::create("Images/start.png", ball_ex, 800, 0, true);

	start->setOnMouseCallback([&](ObjectPtr obj, int x, int y, MouseAction action)->bool {
		auto size = balls.size();
		
		for (int i = 0; i < size; i++) {
			coord[i].clear();
			balls[i].clear();
			coord[i].size();
			balls[i].size();
		}
		coord.clear();
		buttons.clear();
		balls.clear();
		clicked = make_pair(-1, -1);
		cleared = false;

		initGame();
		enterScene(scene->ID());

		return true;
	});


	enterScene(ball_ex->ID());
}