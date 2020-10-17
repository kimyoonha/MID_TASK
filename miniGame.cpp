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
				showMessage("�̹� Ŭ������ ���������Դϴ�.");
				return true;
			}
			enterScene(miniOne->ID());
		}
		else if (y < 355) {
			if (miniLevel == 1) {
				showMessage("1�ܰ踦 Ŭ�����ϰ� ������.");
				return true;
			}
			else if (miniLevel > 2) {
				showMessage("�̹� Ŭ������ ���������Դϴ�.");
				return true;
			}
			enterScene(miniTwo->ID());
		}
		else {
			if (miniLevel < 3) {
				showMessage("�� Ŭ�����ϰ� ������");
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
			showMessage("����! 2�ܰ踸 Ŭ�����ϸ� �ſ�!");
		}
		return true;
		
		});

	twoPan->setOnMouseCallback([&](ObjectPtr ptr, int x, int y, MouseAction) -> bool {
		if (x > 700 && x < 850 && y < 225 && y > 150) {
			showMessage("����! ���� Ǫ���̸� ������ �� �ְ� �Ǿ���� ! \n HINT : 'U'");
			miniLevel = 3;
			enterScene(miniMain->ID());
		}
		else showMessage("�ٽ� �����ϼ���.");
		return true;
		});

	


	enterScene(miniMain->ID());
}

