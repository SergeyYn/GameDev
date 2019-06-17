#include <SFML/Graphics.hpp>//подключение граф. библиотеки
#include <SFML/Audio.hpp>//подключение аудио библиотеки
#include <iostream>
#include <sstream>

using namespace sf;

int menu(RenderWindow & app) {//функция главного меню
	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;//текстуры кнопок и фона
	menuTexture1.loadFromFile("images/15-puzzle_Play.png");//здесь и далее loadFromFile - загрузка из файлов (здесь текстур)
	menuTexture2.loadFromFile("images/15-puzzle_How.png");
	menuTexture3.loadFromFile("images/15-puzzle_Quit.png");
	aboutTexture.loadFromFile("images/15-puzzle_INFO.png");
	menuBackground.loadFromFile("images/15-puzzle_MAIN_MENU.png");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);// создание спрайтов на основе загруженных текстур
	bool isMenu = 1;//переменная для выхода из меню
	int menuNum = 0;//переменная выбора пункта меню
	menu1.setPosition(0, 0);//здесь и далее - setPosition(х,у) - задание позиции на экране
	menu2.setPosition(0, 0);
	menu3.setPosition(0, 0);
	menuBg.setPosition(0, 0);
    Event a;
    while (app.pollEvent(a)){
        if (a.type == Event::Closed)
            app.close();
    }

	while (isMenu)//пока мы в меню
	{
		menu1.setColor(Color::White);//здесь и далее - setColor - установка цвета (White - стандартный из текстуры)
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = 0;
		app.clear(Color::White);//очистка экрана белым цветом

		if (IntRect(160, 160, 320, 80).contains(Mouse::getPosition(app))) { menu1.setColor(Color::Black); menuNum = 1; }//если в заданном участке есть курсор, заливаем кнопку черным и присваиваем
		//значение пункта
		if (IntRect(160, 280, 320, 80).contains(Mouse::getPosition(app))) { menu2.setColor(Color::Black); menuNum = 2; }
		if (IntRect(160, 400, 320, 80).contains(Mouse::getPosition(app))) { menu3.setColor(Color::Black); menuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left))//если нажата лкм
		{
			if (menuNum == 1) isMenu = false;//если нажали первую кнопку, то выходим из меню
			if (menuNum == 2) {//2 кнопка - вывод информации пока не нажат ескейп
                app.draw(about);
                app.display();
                while (!Keyboard::isKeyPressed(Keyboard::Escape));
            }
			if (menuNum == 3){//3 кнопка - закрывание программы
                app.close();
                isMenu = false;
            }
		}

		app.draw(menuBg);//здесь и далее draw - отрисовка спрайтов
		app.draw(menu1);
		app.draw(menu2);
		app.draw(menu3);
		app.display();//здесь и далее - вывод отрисованных элементов
	}
	return menuNum;//возвращаем пункт меню для послед. исп.
}

int main()
{
    RenderWindow app(VideoMode(640,740), "15-Puzzle!");//создание окна

    Music music;//создание объекта типа музыка
    music.openFromFile("music.ogg");//загружаем файл
    music.play();//воспроизводим музыку
    music.setLoop(true);//зацикливаем её

	app.setFramerateLimit(240);//увеличение частоты кадров для плавности анимации

    // далее - загрузка всех необходимых текстур и создание соответствующих спрайтов
	Texture t;
    t.loadFromFile("images/15-puzzle-GAME.png");
    Texture aboutTexture;
    aboutTexture.loadFromFile("images/15-puzzle_INFO.png");
    Sprite about;
    about.setTexture(aboutTexture);

    Sprite Lower;
	Lower.setTexture(t);
	Lower.setTextureRect(IntRect(0,640,640,100));

	Texture back_button;
	back_button.loadFromFile("images/15-puzzle-bttnBack.png");
	Sprite Back;
	Back.setTexture(back_button);
	Texture info_button;
	info_button.loadFromFile("images/15-puzzle-bttnHelp.png");
	Sprite Info;
	Info.setTexture(info_button);

	Texture won;
	won.loadFromFile("images/15-puzzle-WON.png");
	Sprite won_scr;
	won_scr.setTexture(won);

    //загрузка и установка шрифта
    Font Bauhaus;
    Bauhaus.loadFromFile("BAUHS93.ttf");
    Text text;
    text.setFont(Bauhaus);
    text.setFillColor(Color::White);

	int w = 160;//задание ширины ячейки
	int grid[6][6] = {-1};//создание сетки для проверки
	int grid_rand[6][6] = {-1};//создание игровой сетки
	Sprite sprite[16];//спрайт плиток

    int n = 0;
	for (int i=0;i<4;i++){//циклы заполнения плиток и сеток
        for (int j=0;j<4;j++){
            sprite[n].setTexture(t);
            sprite[n].setTextureRect(IntRect(i*w,j*w,w,w));
            grid[j+1][i+1]=n;
            grid_rand[j+1][i+1]=n;
            n++;
        }
	}

    int score_count;//счечик ходов
    int menu_check = menu(app);//переменная для прекращения прогр., первый запуск меню

        while (app.isOpen()&&menu_check!=3)//пока окно открыто и не выбран выход
        {
            score_count = 0;
            int flag=1, flag_back=1;//флажки для прекращения циклов
            for (int k=0;k<100;k++){//генератор случайной игровой сетки
                int j = rand() % 4;
                int i = rand() % 4;
                int a = grid_rand[4][3];
                grid_rand[4][3] = grid_rand[i+1][j+1];
                grid_rand[i+1][j+1] = a;
            }
            while(flag_back!=0&&flag!=0){//пока нет условия выхода
                text.setCharacterSize(40);//задание размера шрифта
                Event e;
                while (app.pollEvent(e))
                {
                    if (e.type == Event::Closed)
                        app.close();
                    if (Mouse::isButtonPressed(Mouse::Left)){//если нажата лкм
                        Vector2i pos = Mouse::getPosition(app);//получаем позицию мыши по х и у
                        int x = pos.x/w + 1;
                        if(pos.y>640){//если вне зоны плиток то выходим из цикла
                            break;
                        }
                        int y = pos.y/w + 1;
                        int dx=0;
                        int dy=0;
                        if (grid_rand[y+1][x]==15){//если сверху пустая плитка то смещение вверх; далее аналогично
                        //х и у поменяны местами в матрице в связи со спецификой графической системы координат
                            score_count++;
                            dx=0;
                            dy=1;
                        }
                        if (grid_rand[y-1][x]==15){
                            score_count++;
                            dx=0;
                            dy=-1;
                        }
                        if (grid_rand[y][x+1]==15){
                            score_count++;
                            dx=1;
                            dy=0;
                        }
                        if (grid_rand[y][x-1]==15){
                            score_count++;
                            dx=-1;
                            dy=0;
                        }
                        //перестановка элементов в игровой сетке
                        int n = grid_rand[y][x];
                        grid_rand[y][x] = 15;
                        grid_rand[y+dy][x+dx] = n;
                        //анимация плиток
                        sprite[15].move(-dx*w,-dy*w);//передвижение пустой плитки
                        float speed=5;//скорость перемещния
                        for (int i=0;i<w;i+=speed){
                            sprite[n].move(speed*(dx),speed*(dy));//передвижение плитки с числом
                            app.draw(sprite[15]);
                            app.draw(sprite[n]);
                            app.display();
                        }
                    }
                if(Keyboard::isKeyPressed(Keyboard::S)){//если нажата клавиша S то идет перемегивание плиток и сброс счетчика
                    score_count=0;
                    for (int k=0;k<20;k++){
                        int j = rand() % 4;
                        int i = rand() % 4;
                        int a = grid_rand[4][3];
                        grid_rand[4][3] = grid_rand[i+1][j+1];
                        grid_rand[i+1][j+1] = a;
                    }
                }

                }

                flag = 0;
                for (int j=0;j<4;j++){//цикл проверки правильности расстановки элементов
                    for (int i=0;i<4;i++){
                        if(grid_rand[i+1][j+1]!=grid[i+1][j+1]){
                            flag = 1;
                        }
                    }
                }
                app.clear(Color::White);
                for (int j=0;j<4;j++){//отрисовка всех плиток
                    for (int i=0;i<4;i++){
                        int n = grid_rand[i+1][j+1];
                        sprite[n].setPosition(j*w,i*w);
                        app.draw(sprite[n]);
                    }
                }
                Lower.setPosition(0,640);
                app.draw(Lower);//отрисовка нижней части
                Back.setColor(Color::White);
                Info.setColor(Color::White);
                if (IntRect(40, 643, 84, 84).contains(Mouse::getPosition(app))){
                    Back.setColor(Color::Black);
                    if (Mouse::isButtonPressed(Mouse::Left)){//если нажата кнопка назад, то выход в гл. меню
                        flag_back = 0;
                    }
                }
                else if (IntRect(519, 643, 84, 84).contains(Mouse::getPosition(app))){
                    Info.setColor(Color::Black);
                    if (Mouse::isButtonPressed(Mouse::Left)){//если нажата кнопка ?, то отображение подсказки
                        app.clear(Color::White);
                        app.draw(about);
                        text.setCharacterSize(41);
                        std::ostringstream output;
                        output << "Press S to shuffle tiles.";
                        text.setString(output.str());
                        text.setPosition(98,440);
                        app.draw(text);
                        app.display();
                        while (!Keyboard::isKeyPressed(Keyboard::Escape));
                    }
                }
                std::ostringstream output;//создание буфера
                output << " " <<score_count;//заполнение буфера переменной количества ходов
                text.setString(output.str());//заполнение текстовой переменной буфером
                text.setPosition(405, 655);
                app.draw(Back);
                app.draw(Info);
                app.draw(text);
                app.display();
            }
            if(flag==0){//если все плитки на местах
                    //вывод победного изображения и количества ходов
                    app.draw(won_scr);
                    text.setCharacterSize(60);
                    std::ostringstream output;
                    output << " " <<score_count;
                    text.setString(output.str());
                    text.setPosition(250 , 285);
                    app.draw(text);
                    app.display();
                    while (!Keyboard::isKeyPressed(Keyboard::Escape));
            }
            menu_check=menu(app);//вызов меню
            app.display();//отображение всех отрисованных элементов
        }
    return 0;
}
