#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int main()
{
	// Генератор случайных чисел
	srand(time(0));

	RenderWindow app(VideoMode(400, 400), "Minesweeper!");

	// Ширина клетки
	int w = 32;
	int gridLogic[12][12];
	int gridView[12][12];
	int flagGrid[12][12];// 0 - закрыто, 1 - открыто, 2 - флаг.

	for (int count = 0; count < 12; count++) {
		for (int COUNT = 0; COUNT < 12; COUNT++) {
			flagGrid[count][COUNT] = 0;
		}
	}

	// Загрузка текстуры и создание спрайта
	Texture t;
	t.loadFromFile("tiles.jpg");
	Sprite s(t);

	for (int i = 1; i <= 10; i++){
		for (int j = 1; j <= 10; j++)
		{
			gridView[i][j] = 10;
			if (rand() % 5 == 0)  gridLogic[i][j] = 9;
			else gridLogic[i][j] = 0;
		}
	}

	// Подсчет мин вокруг каждой клетки
	for (int i = 1; i <= 10; i++) {
		for (int j = 1; j <= 10; j++)
		{
			int n = 0;
			if (gridLogic[i][j] == 9) continue;
			if (gridLogic[i + 1][j] == 9) n++;
			if (gridLogic[i][j + 1] == 9) n++;
			if (gridLogic[i - 1][j] == 9) n++;
			if (gridLogic[i][j - 1] == 9) n++;
			if (gridLogic[i + 1][j + 1] == 9) n++;
			if (gridLogic[i - 1][j - 1] == 9) n++;
			if (gridLogic[i - 1][j + 1] == 9) n++;
			if (gridLogic[i + 1][j - 1] == 9) n++;
			gridLogic[i][j] = n;
		}
	}


	while (app.isOpen())
	{
		// Получаем координаты мышки относительно окна нашего приложения
		Vector2i pos = Mouse::getPosition(app);
		int x = pos.x / w;
		int y = pos.y / w;

		Event e;
		while (app.pollEvent(e)){
			if (e.type == Event::Closed) {
				app.close();
			}
			// Была нажата кнопка мыши…?
			if (e.type == Event::MouseButtonPressed) {
				// Если это - левая кнопка мыши, то открываем клетку
				if (e.key.code == Mouse::Left) {
					if (flagGrid[x][y] == 0) {
						gridView[x][y] = gridLogic[x][y];
						flagGrid[x][y] = 1;
						if (gridLogic[x][y] == 0) {


							for (int count = 1; count <= 12; count++) {
								if (x + count >= 12) break;
								else {
									if (gridLogic[x + count][y] == 0) {
										gridView[x + count][y] = gridLogic[x+count][y];
										flagGrid[x + count][y] = 1;
									}
									else if (gridLogic[x + count][y] < 9 && gridLogic[x + count][y] > 0) {
										gridView[x + count][y] = gridLogic[x + count][y];
										flagGrid[x + count][y] = 1;
										break;
									}
								}
							}


							for (int count = 1; count <= 12; count++) {
								if (x - count <= 0) break;
								else{
									if (gridLogic[x - count][y] == 0) {
										gridView[x - count][y] = gridLogic[x - count][y];
										flagGrid[x - count][y] = 1;
									}
									else if (gridLogic[x - count][y] < 9 && gridLogic[x - count][y] > 0) {
										gridView[x - count][y] = gridLogic[x - count][y];
										flagGrid[x - count][y] = 1;
										break;
									}
								}
							}


							for (int count = 1; count <= 12; count++) {
								if (y + count >= 12) break;
								else {
									if (gridLogic[x][y + count] == 0) {
										gridView[x][y + count] = gridLogic[x][y + count];
										flagGrid[x][y + count] = 1;
									}
									else if (gridLogic[x][y + count] < 9 && gridLogic[x][y + count] > 0) {
										gridView[x][y + count] = gridLogic[x][y + count];
										flagGrid[x][y + count] = 1;
										break;
									}
								}
							}


							for (int count = 1; count <= 12; count++) {
								if (y - count <= 0) break;
								else {
									if (gridLogic[x][y - count] == 0) {
										gridView[x][y - count] = gridLogic[x][y - count];
										flagGrid[x][y - count] = 1;
									}
									else if (gridLogic[x][y - count] < 9 && gridLogic[x][y - count] > 0) {
										gridView[x][y - count] = gridLogic[x][y - count];
										flagGrid[x][y - count] = 1;
										break;
									}
								}
							}

/*
							for (int count = 1; count <= 12; count++) {
								if (y + count >= 12 || x + count >= 12) break;
								else {
									if (gridLogic[x+count][y + count] == 0) {
										gridView[x + count][y + count] = gridLogic[x + count][y + count];
										flagGrid[x + count][y + count] = 1;
									}
									else if (gridLogic[x + count][y + count] < 9 && gridLogic[x + count][y + count] > 0) {
										gridView[x + count][y + count] = gridLogic[x + count][y + count];
										flagGrid[x + count][y + count] = 1;
										break;
									}
									else if (gridLogic[x + count][y + count] == 9) {
										break;
									}
								}
							}


							for (int count = 1; count <= 12; count++) {
								if (y + count >= 12 || x - count <= 0) break;
								else {
									if (gridLogic[x - count][y + count] == 0) {
										gridView[x - count][y + count] = gridLogic[x - count][y + count];
										flagGrid[x - count][y + count] = 1;
									}
									else if (gridLogic[x - count][y + count] < 9 && gridLogic[x - count][y + count] > 0) {
										gridView[x - count][y + count] = gridLogic[x - count][y + count];
										flagGrid[x - count][y + count] = 1;
										break;
									}
									else if (gridLogic[x - count][y + count] == 9) {
										break;
									}
								}
							}


							for (int count = 1; count <= 12; count++) {
								if (y - count <= 0 || x - count <= 0) break;
								else {
									if (gridLogic[x - count][y - count] == 0) {
										gridView[x - count][y - count] = gridLogic[x - count][y - count];
										flagGrid[x - count][y - count] = 1;
									}
									else if (gridLogic[x - count][y - count] < 9 && gridLogic[x - count][y - count] > 0) {
										gridView[x - count][y - count] = gridLogic[x - count][y - count];
										flagGrid[x - count][y - count] = 1;
										break;
									}
									else if (gridLogic[x - count][y - count] == 9) {
										break;
									}
								}
							}


							for (int count = 1; count <= 12; count++) {
								if (y - count <= 0 || x + count >= 12) break;
								else {
									if (gridLogic[x + count][y - count] == 0) {
										gridView[x + count][y - count] = gridLogic[x + count][y - count];
										flagGrid[x + count][y - count] = 1;
									}
									else if (gridLogic[x + count][y - count] < 9 && gridLogic[x + count][y - count] > 0) {
										gridView[x + count][y - count] = gridLogic[x + count][y - count];
										flagGrid[x + count][y - count] = 1;
										break;
									}
									else if (gridLogic[x + count][y - count] == 9) {
										break;
									}
								}
							}
*/

						}
					}
					else if (flagGrid[x][y] == 2 || flagGrid[x][y] == 1) {
						continue;
					}
				}
				// Если это – правая кнопка мыши, то отображаем флажок
				else if (e.key.code == Mouse::Right) {
					if (flagGrid[x][y] == 0) {
						gridView[x][y] = 11;
						flagGrid[x][y] = 2;
					}
					else if (flagGrid[x][y] == 2) {
						gridView[x][y] = 10;
						flagGrid[x][y] = 0;
					}
					else if (flagGrid[x][y] == 1) {
						continue;
					}
				}
			}
		}

		// Устанавливаем белый фон
		app.clear(Color::White);

		for (int i = 1; i <= 10; i++) {
			for (int j = 1; j <= 10; j++)
			{
				if (gridView[x][y] == 9) gridView[i][j] = gridLogic[i][j];

				// Вырезаем из спрайта нужный нам квадратик текстуры
				s.setTextureRect(IntRect(gridView[i][j] * w, 0, w, w));

				// Устанавливаем его заданную позицию…
				s.setPosition(i*w, j*w);

				// … и отрисовываем
				app.draw(s);
			}
		}
		// Отображаем всю композицию на экране
		app.display();
	}

	return 0;
}
