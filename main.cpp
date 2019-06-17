#include <SFML/Graphics.hpp>//����������� ����. ����������
#include <SFML/Audio.hpp>//����������� ����� ����������
#include <iostream>
#include <sstream>

using namespace sf;

int menu(RenderWindow & app) {//������� �������� ����
	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;//�������� ������ � ����
	menuTexture1.loadFromFile("images/15-puzzle_Play.png");//����� � ����� loadFromFile - �������� �� ������ (����� �������)
	menuTexture2.loadFromFile("images/15-puzzle_How.png");
	menuTexture3.loadFromFile("images/15-puzzle_Quit.png");
	aboutTexture.loadFromFile("images/15-puzzle_INFO.png");
	menuBackground.loadFromFile("images/15-puzzle_MAIN_MENU.png");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);// �������� �������� �� ������ ����������� �������
	bool isMenu = 1;//���������� ��� ������ �� ����
	int menuNum = 0;//���������� ������ ������ ����
	menu1.setPosition(0, 0);//����� � ����� - setPosition(�,�) - ������� ������� �� ������
	menu2.setPosition(0, 0);
	menu3.setPosition(0, 0);
	menuBg.setPosition(0, 0);
    Event a;
    while (app.pollEvent(a)){
        if (a.type == Event::Closed)
            app.close();
    }

	while (isMenu)//���� �� � ����
	{
		menu1.setColor(Color::White);//����� � ����� - setColor - ��������� ����� (White - ����������� �� ��������)
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = 0;
		app.clear(Color::White);//������� ������ ����� ������

		if (IntRect(160, 160, 320, 80).contains(Mouse::getPosition(app))) { menu1.setColor(Color::Black); menuNum = 1; }//���� � �������� ������� ���� ������, �������� ������ ������ � �����������
		//�������� ������
		if (IntRect(160, 280, 320, 80).contains(Mouse::getPosition(app))) { menu2.setColor(Color::Black); menuNum = 2; }
		if (IntRect(160, 400, 320, 80).contains(Mouse::getPosition(app))) { menu3.setColor(Color::Black); menuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left))//���� ������ ���
		{
			if (menuNum == 1) isMenu = false;//���� ������ ������ ������, �� ������� �� ����
			if (menuNum == 2) {//2 ������ - ����� ���������� ���� �� ����� ������
                app.draw(about);
                app.display();
                while (!Keyboard::isKeyPressed(Keyboard::Escape));
            }
			if (menuNum == 3){//3 ������ - ���������� ���������
                app.close();
                isMenu = false;
            }
		}

		app.draw(menuBg);//����� � ����� draw - ��������� ��������
		app.draw(menu1);
		app.draw(menu2);
		app.draw(menu3);
		app.display();//����� � ����� - ����� ������������ ���������
	}
	return menuNum;//���������� ����� ���� ��� ������. ���.
}

int main()
{
    RenderWindow app(VideoMode(640,740), "15-Puzzle!");//�������� ����

    Music music;//�������� ������� ���� ������
    music.openFromFile("music.ogg");//��������� ����
    music.play();//������������� ������
    music.setLoop(true);//����������� �

	app.setFramerateLimit(240);//���������� ������� ������ ��� ��������� ��������

    // ����� - �������� ���� ����������� ������� � �������� ��������������� ��������
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

    //�������� � ��������� ������
    Font Bauhaus;
    Bauhaus.loadFromFile("BAUHS93.ttf");
    Text text;
    text.setFont(Bauhaus);
    text.setFillColor(Color::White);

	int w = 160;//������� ������ ������
	int grid[6][6] = {-1};//�������� ����� ��� ��������
	int grid_rand[6][6] = {-1};//�������� ������� �����
	Sprite sprite[16];//������ ������

    int n = 0;
	for (int i=0;i<4;i++){//����� ���������� ������ � �����
        for (int j=0;j<4;j++){
            sprite[n].setTexture(t);
            sprite[n].setTextureRect(IntRect(i*w,j*w,w,w));
            grid[j+1][i+1]=n;
            grid_rand[j+1][i+1]=n;
            n++;
        }
	}

    int score_count;//������ �����
    int menu_check = menu(app);//���������� ��� ����������� �����., ������ ������ ����

        while (app.isOpen()&&menu_check!=3)//���� ���� ������� � �� ������ �����
        {
            score_count = 0;
            int flag=1, flag_back=1;//������ ��� ����������� ������
            for (int k=0;k<100;k++){//��������� ��������� ������� �����
                int j = rand() % 4;
                int i = rand() % 4;
                int a = grid_rand[4][3];
                grid_rand[4][3] = grid_rand[i+1][j+1];
                grid_rand[i+1][j+1] = a;
            }
            while(flag_back!=0&&flag!=0){//���� ��� ������� ������
                text.setCharacterSize(40);//������� ������� ������
                Event e;
                while (app.pollEvent(e))
                {
                    if (e.type == Event::Closed)
                        app.close();
                    if (Mouse::isButtonPressed(Mouse::Left)){//���� ������ ���
                        Vector2i pos = Mouse::getPosition(app);//�������� ������� ���� �� � � �
                        int x = pos.x/w + 1;
                        if(pos.y>640){//���� ��� ���� ������ �� ������� �� �����
                            break;
                        }
                        int y = pos.y/w + 1;
                        int dx=0;
                        int dy=0;
                        if (grid_rand[y+1][x]==15){//���� ������ ������ ������ �� �������� �����; ����� ����������
                        //� � � �������� ������� � ������� � ����� �� ���������� ����������� ������� ���������
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
                        //������������ ��������� � ������� �����
                        int n = grid_rand[y][x];
                        grid_rand[y][x] = 15;
                        grid_rand[y+dy][x+dx] = n;
                        //�������� ������
                        sprite[15].move(-dx*w,-dy*w);//������������ ������ ������
                        float speed=5;//�������� ����������
                        for (int i=0;i<w;i+=speed){
                            sprite[n].move(speed*(dx),speed*(dy));//������������ ������ � ������
                            app.draw(sprite[15]);
                            app.draw(sprite[n]);
                            app.display();
                        }
                    }
                if(Keyboard::isKeyPressed(Keyboard::S)){//���� ������ ������� S �� ���� ������������� ������ � ����� ��������
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
                for (int j=0;j<4;j++){//���� �������� ������������ ����������� ���������
                    for (int i=0;i<4;i++){
                        if(grid_rand[i+1][j+1]!=grid[i+1][j+1]){
                            flag = 1;
                        }
                    }
                }
                app.clear(Color::White);
                for (int j=0;j<4;j++){//��������� ���� ������
                    for (int i=0;i<4;i++){
                        int n = grid_rand[i+1][j+1];
                        sprite[n].setPosition(j*w,i*w);
                        app.draw(sprite[n]);
                    }
                }
                Lower.setPosition(0,640);
                app.draw(Lower);//��������� ������ �����
                Back.setColor(Color::White);
                Info.setColor(Color::White);
                if (IntRect(40, 643, 84, 84).contains(Mouse::getPosition(app))){
                    Back.setColor(Color::Black);
                    if (Mouse::isButtonPressed(Mouse::Left)){//���� ������ ������ �����, �� ����� � ��. ����
                        flag_back = 0;
                    }
                }
                else if (IntRect(519, 643, 84, 84).contains(Mouse::getPosition(app))){
                    Info.setColor(Color::Black);
                    if (Mouse::isButtonPressed(Mouse::Left)){//���� ������ ������ ?, �� ����������� ���������
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
                std::ostringstream output;//�������� ������
                output << " " <<score_count;//���������� ������ ���������� ���������� �����
                text.setString(output.str());//���������� ��������� ���������� �������
                text.setPosition(405, 655);
                app.draw(Back);
                app.draw(Info);
                app.draw(text);
                app.display();
            }
            if(flag==0){//���� ��� ������ �� ������
                    //����� ��������� ����������� � ���������� �����
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
            menu_check=menu(app);//����� ����
            app.display();//����������� ���� ������������ ���������
        }
    return 0;
}
