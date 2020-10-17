#include <bangtal>
#include <vector>
#include <ctime>
#include <time.h>
#include <string>
#include <iostream>

using namespace bangtal;
using namespace std;

extern void number_main();
extern void ball_main();
extern void mini_main();

ScenePtr mainScene;
SoundPtr mainSound;
ObjectPtr pan;
int level = 1;

int main() {
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);



	mainScene = Scene::create("", "Images/main.jpg");
	mainSound = Sound::create("music/main.mp3");
	mainSound->play();

	pan = Object::create("Images/empty.png", mainScene, 0, 0, true);

	pan->setOnMouseCallback([&](ObjectPtr ptr, int x, int y, MouseAction) -> bool {
		cout << x << " " << y << endl;
		if ((x > 120 && x < 350) && (y < 300 && y > 200)) {
			if (level > 1) {
				showMessage("이미 클리어한 스테이지에요.");
				return true;
			}
			mainSound->stop();
			ball_main();
		}
		else if ((x > 600 && x < 850) && (y < 350 && y > 280)) {
			if (level == 1) {
				showMessage("1단계를 클리어하고 오세요.");
				return true;
			}
			else if (level > 2) {
				showMessage("이미 클리어한 스테이지에요.");
				return true;

			}
			mainSound->stop();
			number_main();
		}
		else if ((x > 980 && x < 1200) && (y < 320 && y > 270)) {
			if (level < 3) {
				showMessage("더 클리어하고 오세요");
				return true;
			}
			mainSound->stop();
			mini_main();
		}

		return true;
	});

	

	startGame(mainScene);

	return 0;
}