#include <bangtal>
#include <vector>
#include <ctime>
#include <time.h>
#include <string>
#include <windows.h>
#include <iostream>
#include "Number.h"

#define EMPTY 0


using namespace std;
using namespace bangtal;

extern ScenePtr mainScene;
extern SoundPtr mainSound;
extern int level;

ScenePtr numberScene;
ScenePtr number_ex;
SoundPtr numberSound;
vector<NumberPtr> answer;
vector<NumberPtr> input;
vector<ObjectPtr> heart;
ObjectPtr item;
ObjectPtr num_start;

int life = 3;
int turn = 1;

const string images[17] = {
	"images/numberGame/empty.png",
	"images/numberGame/1.png",
	"images/numberGame/2.png",
	"images/numberGame/3.png",
	"images/numberGame/4.png",
	"images/numberGame/5.png",
	"images/numberGame/6.png",
	"images/numberGame/7.png",
	"images/numberGame/8.png",
	"images/numberGame/9.png",
	"images/numberGame/10.png",
	"images/numberGame/11.png",
	"images/numberGame/12.png",
	"images/numberGame/13.png",
	"images/numberGame/14.png",
	"images/numberGame/15.png",
	"images/numberGame/16.png",
};

const string heartImage = "images/numberGame/heart.png";
const string emptyHeart = "images/numberGame/emptyHeart.png";

int coord[16][2] = {
	{120 , 460},
	{220 , 460},
	{320 , 460},
	{420 , 460},
	{120 , 360},
	{220 , 360},
	{320 , 360},
	{420 , 360},
	{120 , 260},
	{220 , 260},
	{320 , 260},
	{420 , 260},
	{120 , 160},
	{220 , 160},
	{320 , 160},
	{420 , 160},
};

int emptyCoord[16][2] = {
	{760 , 460},
	{860 , 460},
	{960 , 460},
	{1060 , 460},
	{760 , 360},
	{860 , 360},
	{960 , 360},
	{1060 , 360},
	{760 , 260},
	{860 , 260},
	{960 , 260},
	{1060 , 260},
	{760 , 160},
	{860 , 160},
	{960 , 160},
	{1060 , 160},
};

int heartCoord[3][2] = {
	{10, 600},
	{90, 600},
	{170, 600}

};

void wrong() {
	for (int i = 0; i < 16;i++) input[i]->setImage(images[EMPTY]);
	turn = 1;
	heart[--life]->setImage(emptyHeart);
}


void initBoard() {
	bool used[17];

	for (int i = 0;i < 17;i++) used[i] = false;
	for (int i = 0;i < 16;i++) {
		int num = 0;
		do {
			num = rand() % 16 + 1;
		} while (used[num]);

		answer.push_back(Number::create(images[num], numberScene, coord[i][0], coord[i][1], true, num));
		input.push_back(Number::create(images[EMPTY], numberScene, emptyCoord[i][0], emptyCoord[i][1], false, num));
		input[i]->setOnMouseCallback([&](ObjectPtr ptr, int x, int y, MouseAction action) -> bool {
			NumberPtr number;
			for (int i = 0; i < 16;i++) {
				if (ptr == input[i]) number = input[i];
			}
			if (number->getNumber() == turn) {
				number->setImage(images[turn]);
				turn++;
				if (turn == 17) {
					level = 3;
					numberSound->stop();
					mainSound->play();
					enterScene(mainScene->ID());
					showMessage("클리어! \n HINT : 'A'");
				}
			}
			else {
				wrong();
				if (life == 0) {
					for (int k = 0; k < 16; k++) {
						input[k]->hide();
					}
					item->hide();
					showMessage("다시 도전하세요.");
					enterScene(number_ex->ID());
				}
			}
			return true;
			});
		used[num] = true;
	}

	for (int i = 0;i < 3;i++) {
		heart.push_back(Object::create(heartImage, numberScene, heartCoord[i][0], heartCoord[i][1], true));
	}
	item = Object::create("Images/numberGame/item.png", numberScene, 50, 50, false);
	
	item->setOnMouseCallback([&](ObjectPtr ptr, int x, int y, MouseAction action) -> bool {
		item->hide();
		auto time = Timer::create(10.0f);

		for (int i = 0;i < 16;i++) {
			input[i]->hide();
			answer[i]->show();
		}

		time->setOnTimerCallback([&](TimerPtr pt) -> bool {

			for (int i = 0;i < 16;i++) {
				input[i]->show();
				answer[i]->hide();
			}
			item->hide();
			hideTimer();
			return true;
		});

		showTimer(time);
		time->start();


		return true;
	});
	
}


void number_main() {

	numberScene = Scene::create("숫자 게임", "Images/numberGame/background.jpg");
	numberSound = Sound::create("music/2.mp3");
	numberSound->play();

	number_ex = Scene::create("", "Images/numberGame/numberExplain.jpg");

	num_start = Object::create("Images/start.png", number_ex, 800, 0, true);

	num_start->setOnMouseCallback([&](ObjectPtr obj, int x, int y, MouseAction action)->bool {
		auto timer = Timer::create(10.0f);

		timer->setOnTimerCallback([&](TimerPtr ptr) -> bool {
			for (int i = 0;i < 16;i++) {
				answer[i]->hide();
				input[i]->show();
			}
			item->show();
			hideTimer();
			return true;
		});
		showTimer(timer);
		timer->start();
		life = 3;
		heart.clear();
		answer.clear();
		input.clear();
		initBoard();
		enterScene(numberScene->ID());

		return true;
	});


	enterScene(number_ex->ID());



}


