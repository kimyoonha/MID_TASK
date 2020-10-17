#include <bangtal>
#include <vector>
#include <ctime>
#include <time.h>
#include <string>
#include <windows.h>
#include <iostream>
#include "Number.h"

using namespace std;
using namespace bangtal;

extern ScenePtr mainScene;
extern int level;

ScenePtr miniOne, miniTwo;
ScenePtr miniMain;
SoundPtr miniSound;
SoundPtr clearSound;
ScenePtr oneEx, twoEx;
ObjectPtr obj;

int miniLevel = 1;


void mini_main() {


	miniMain = Scene::create("", "Images/mini/main.jpg");
	miniOne = Scene::create("", "Images/mini/one.jpg");
	miniTwo = Scene::create("", "Images/mini/two.jpg");

	oneEx = Scene::create("", "Images/mini/oneEx.jpg");
	miniSound = Sound::create("music/mini.mp3");
	clearSound = Sound::create("music/clear.mp3");
	miniSound->play();

	auto pan = Object::create("Images/empty.png", miniMain, 0, 0, true);
	auto onePan = Object::create("Images/empty.png", miniOne, 0, 0, true);
	auto twoPan = Object::create("Images/empty.png", miniTwo, 0, 0, true);

	obj = Object::create("Images/final.jpg", miniMain, 0, 0, false);

	obj->setOnKeypadCallback([&](ObjectPtr ptr) -> bool {
		miniSound->stop();
		clearSound->play();
		obj->show();

		return true;
	});


	pan->setOnMouseCallback([&](ObjectPtr ptr, int x, int y, MouseAction) -> bool {
		if (y < 185) {
			if (miniLevel > 1) {
				showMessage("이미 클리어한 스테이지입니다.");
				return true;
			}
			enterScene(miniOne->ID());
		}
		else if (y < 355) {
			if (miniLevel == 1) {
				showMessage("1단계를 클리어하고 오세요.");
				return true;
			}
			else if (miniLevel > 2) {
				showMessage("이미 클리어한 스테이지입니다.");
				return true;
			}
			enterScene(miniTwo->ID());
		}
		else {
			if (miniLevel < 3) {
				showMessage("더 클리어하고 오세요");
				return true;
			}

			showKeypad("CAU", obj);
			
		}
		return true;
	});

	onePan->setOnMouseCallback([&](ObjectPtr ptr, int x, int y, MouseAction) -> bool {
		cout << x << " " << y << endl;
		if (x > 880 && x < 935 && y > 180 && y < 250) {
			miniLevel = 2;
			enterScene(miniMain->ID());
			showMessage("정답! 2단계만 클리어하면 돼요!");
		}
		return true;
		
		});

	twoPan->setOnMouseCallback([&](ObjectPtr ptr, int x, int y, MouseAction) -> bool {
		if (x > 700 && x < 850 && y < 225 && y > 150) {
			showMessage("정답! 드디어 푸앙이를 구출할 수 있게 되었어요 ! \n HINT : 'U'");
			miniLevel = 3;
			enterScene(miniMain->ID());
		}
		else showMessage("다시 도전하세요.");
		return true;
		});

	


	enterScene(miniMain->ID());
}

