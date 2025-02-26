#include <iostream>
#include <conio.h>
#include <thread>
#include <chrono>
#include <windows.h>
#include <fstream>
#include <cstdlib>
//#include <mmsystem.h>//sound
#include <ctime> 
#include <limits> // check validity for inputs (data type)
using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"      
#define YELLOW  "\033[33m"      
#define BLUE    "\033[34m"    
#define MAGENTA "\033[35m"    
#define CYAN    "\033[36m" 
#pragma comment(lib , "winmm.lib")



struct GAME{
    string name;
    int score = 0;
    double time = 0;
    char theme = '1';
};

struct BULLET{
    int x;
    int y;
    bool active = 0;
};

struct ENEMY_BULLET {
    int x;
    int y;
    bool active = false; 
};


struct BOMBS {
    int x;
    int y;
    bool active = false;
};


time_t start_time;
int health = 3;
const int game = 100;
const int MAX_BULLET = 1;
const int MAX_BOMBS = 1;
const int MAX_ENEMY_BULLET = 7;
int enemy_step = 0;
bool moveRight = true; 
int enemy_speed = 2;   
int screen_hight = 20;
int screen_width = 20;
const string  PLAYER = "🅯";
const string E1 = "㉈";
const string E2 = "㉉";
const string E3 = "㉋";
const string E4 = "🞋";
const string SHOOT = "•";
const string ENENMY_SHOOT = "↓";


bool special_enemy_active = false;
int special_enemy_x = 0; 
int special_enemy_y = 0;
int special_enemy_speed = 1;
int special_enemy_timer = 0;
BULLET bullet[MAX_BULLET];
ENEMY_BULLET enemy_bullets[MAX_ENEMY_BULLET];

BOMBS bombs[MAX_BOMBS];
GAME current_game;
string** game_board = nullptr;

void printCharacterByCharacter(const string& text, int delay);
void How_to_play();
void board_makear();
void time_and_score();
void health_bar();
void display_board();
void heart_board();
void star_board();
void triangle_board();
void free_board();
void hide_cursor();
void displayMenu(const int currentOption, const string options[], const string descriptions[], const int totalOptions);
void main_menu();
void show_cursor();
void newgame();
void themes();
void move_player(int direction_x);
void pause_menu(bool& running);
void reset_cursor();
void game_loop(char& theme);
void play_shoot_sound();
void player_shoots();
void move_bullets();
void move_enemies(bool& running);
void move_special_enemy();
void handle_special_enemy();
void health_bar();
void save_game();
void savedata(const string& playerName, int score);
void load_game();
void display_leaderboard();
void enemy_shoots();
void move_enemy_bullets(bool& running);
bool check_win();
bool check_win2();
void getValidatedInput();
void load_game();
bool check_board();
void move_boomb();
void reset_game_info();
void board_makear2();
void display_board2();
void heart_board2();
void star_board2();
void triangle_board2();
void move_bullets2();
void game_loop2(char&  theme);
void displayLoadingAnimation();
bool check_board2();
void move_enemies2(bool&running);
void enemy_shoots2();
void player_shoot_bomb();
void handle_store(bool& running);
void handle_bombs();
void explode_bomb(int bomb_x, int bomb_y);

int main()
{
    system("cls");
    hide_cursor();
    main_menu();
    show_cursor();
    return 0;

}

void hide_cursor() 
{
    cout << "\033[?25l"; 
    cout.flush();        
}

void displayLoadingAnimation() 
{
    const char* loadingChars = "|/-\\";
    for (int i = 0; i < 10; i++) 
	{
        cout << "\rLoading... " << GREEN << loadingChars[i % 4] << RESET << flush;
        Sleep(100); 
    }
    cout << "\rLoading complete!    " << endl; 
}

void displayMenu(const int currentOption, const string options[], const string descriptions[], const int totalOptions) 
{
    //PlaySound(TEXT("space-266642 (online-audio-converter.com).wav") , NULL , SND_FILENAME | SND_ASYNC | SND_LOOP);
    system("cls");
    cout <<GREEN << R"( 
                            (_)                   | |              
  ___ _ __   __ _  ___ ___   _ _ ____   ____ _  __| | ___ _ __ ___ 
 / __| '_ \ / _` |/ __/ _ \ | | '_ \ \ / / _` |/ _` |/ _ \ '__/ __|
 \__ \ |_) | (_| | (_|  __/ | | | | \ V / (_| | (_| |  __/ |  \__ \
 |___/ .__/ \__,_|\___\___| |_|_| |_|\_/ \__,_|\__,_|\___|_|  |___/
     | |                                                           
     |_|                                                           
)" << RESET << endl;

    cout <<CYAN<<"╔════════════════╗" << endl;

    for (int i = 0; i < totalOptions; i++) 
	{
        if (i == currentOption) 
		{
            cout <<CYAN<<" \033[1;37;42m " << options[i] <<CYAN<<" \033[0m     " << endl;
        } 
		else 
		{
            cout <<CYAN<<"   " << options[i] << "      " << endl;
        }
    }
    cout <<CYAN<<"╚════════════════╝" << endl;
    cout <<GREEN<<"\n" << "Description: " << descriptions[currentOption] << RESET<<endl;
    //PlaySound(0 , 0 , 0);
}

void main_menu()
{
  
  const int totalOptions = 5;
    string options[totalOptions] = 
	{
        "New Game",
        "Load Game",
        "Leaderboard",
        "How to Play",
        "Exit"
    };
    string descriptions[totalOptions] = 
	{
        "Start a new game from scratch.",
        "Load a previously saved game.",
        "View the top scores and achievements.",
        "Learn how to play the game.",
        "Exit the program."
    };
    int currentOption = 0;
   // playSound();
  
    while (true) {
        displayMenu(currentOption, options, descriptions, totalOptions);
        char input = _getch();
        if (input == 'w' || input == 'W') {
            Beep(523, 100);
            currentOption--;
            if (currentOption < 0) currentOption = totalOptions - 1;
        } else if (input == 's' || input == 'S') {
            Beep(523, 100);
            currentOption++;
            if (currentOption >= totalOptions) currentOption = 0;
        } else if (input == '\r') {
            Beep(600, 150);
            system("cls");
            displayLoadingAnimation();
            cout << "You selected: " << options[currentOption] << endl;
            switch (currentOption) {
                case 0:
                    newgame();
                    break;
                case 1:
                    load_game();
                    break;
                case 2:
                    display_leaderboard();
                    break;
                case 3:
                    How_to_play();
                    break;
                case 4:
                    cout<<RED<<"GOODBYE"<<RESET <<"🖐🏻"<<endl;
                    return;
            }
            break;
        }
        Sleep(100);
    }
}


void show_cursor() 
{
    cout << "\033[?25h"; 
    cout.flush();       
}

void printCharacterByCharacter(const string& text, int delay = 50)  
{ 
    for (char c : text)  
 { 
        cout <<BLUE<<c; 
        cout.flush();  
        this_thread::sleep_for(chrono::milliseconds(delay)); 
    } 
} 

void How_to_play()
{
    system("cls");
    const string spaceInvadersInstructions = R"( 
 
The goal of Space Invaders is to defeat waves of descending aliens while avoiding their attacks. You must eliminate all the aliens before they reach the bottom of the screen. 
 
Controls: 
 
• Move Left/Right: Use the left and right arrow keys to move your spaceship horizontally. 
 
• Shoot: Press the spacebar to fire bullets at the aliens. 
 
Gameplay: 
 
1. Start the Game: Begin by pressing the start button. The game will display the first wave of aliens. 
 
2. Aliens Movement: Aliens move horizontally across the screen and gradually descend. They will change direction when they hit the edge of the screen. 
 
3. Shooting Aliens: Aim and shoot at the aliens. Each alien has a different point value, and some may take multiple hits to defeat. 
 
4. Defensive Barriers: Use the barriers on the screen for cover. They can absorb some shots from the aliens but will be destroyed over time. 
 
5. Levels: After clearing a wave, a new wave will appear, often with increased speed and difficulty. 
 
6. Game Over: The game ends when an alien reaches the bottom of the screen or when you lose all your lives. 
 
Tips: 
 
• Stay Mobile: Keep moving to avoid enemy fire and to position yourself better for shooting. 
 
• Aim for Higher Points: Target the more valuable aliens first to maximize your score. 
 
• Practice Timing: Learn the patterns of the aliens to improve your shooting accuracy. 
 
Enjoy your battle against the invaders! 
Goodluck soldier 😊 
 
)"; 
 
    printCharacterByCharacter(spaceInvadersInstructions, 50); 
    cout <<endl; 
    cout<<GREEN<<"press a key to return to the menu"<<RESET<<endl;
    char key = getch();
    main_menu();
}

void newgame()
{
    reset_game_info();
    start_time = time(0);
    system("cls");
    cout<<GREEN<<"                    ╔═══╦════════════════╗"<<endl;
    cout<<"                    ║1. ║   QUICK GAME   ║"<<endl;
    cout<<"                    ║2. ║ CUSTOMIZE GAME ║"<<endl;
    cout<<"                    ║3. ║ RETURN TO MENU ║"<<endl;
    cout<<"                    ╚═══╩════════════════╝"<<RESET<<endl;\
    char option = getch();
    string name;
    char theme = '1';
    theme = current_game.theme;
    current_game.score = 0;
    current_game.time = 0;
    screen_hight = 20;
    screen_width = 20;
    
    
    switch (option)
    {
        
        case '1':
            cout<<MAGENTA<<"ENTER YOUR NAME : "<<endl;
            cin >> name;
            current_game.name = name;
            cout<<RESET<<endl;
             system("cls");
             board_makear();
             game_loop(theme);


            break;
        
        case '2':
            cout<<"please choose your game board themes "<<endl;
            themes();
            theme = getch();
            cout<<MAGENTA<<"ENTER YOUR NAME : "<<endl;
            cin >> name;
            current_game.name = name;
            cout <<"PLEASE CUSTOMIZE YOUR BOARD SIZE (SQUARE BOARD ONLY)"<<endl;
            cout<<"screen_hight : " ; 
            cin >> screen_hight;
            getValidatedInput();
            cout<<endl<<"screen_width : ";
            cin >> screen_width;
            getValidatedInput();
            while(screen_hight != screen_width || screen_width > 40 || screen_hight > 40) 
            {
                cout<<RED<<"WE NEED SAME NUMBER  AND SMALLER THAN 40 TO MAKE YOUR BOARD : "<<endl;
                 cout<<MAGENTA<<"screen_hight : " ; 
                cin >> screen_hight;
                getValidatedInput();
                cout<<endl<<"screen_width : ";
                cin >> screen_width;
                getValidatedInput();

            }

            cout<<RESET<<endl;
            system("cls");
            board_makear();
            game_loop(theme);
            
            break;
        
        case '3':
            main_menu();
            break;

        default :
            newgame();
            break;

    }
}

void themes()
{
    
    
        cout<<"1. classic board"<<endl;
        cout<<MAGENTA<<"╔═════╗"<<endl;
        cout<<"║     ║"<<endl;
        cout<<"╚═════╝"<<RESET<<endl;
        cout<<"2.hearts board"<<endl;
        cout<<RED<<" ♡♡♡♡♡♡♡"<<endl;
        cout<<endl;
        cout<<endl;
        cout<<" ♡♡♡♡♡♡♡"<<RESET<<endl;
        cout<<"3. triangles board"<<endl;
        cout<<BLUE<<" ⏶⏶⏶⏶⏶⏶⏶"<<endl;
        cout<<endl;
        cout<<endl;
        cout<<" ⏷⏷⏷⏷⏷⏷⏷"<<RESET<<endl;
        cout<<"4. stars board"<<endl;
        cout<<YELLOW<<" ✮✮✮✮✮✮✮"<<endl;
        cout<<endl;
        cout<<endl;
        cout<<" ✮✮✮✮✮✮✮"<<RESET<<endl;

    
}
void display_leaderboard()
{
	system("cls");
    ifstream file("scoreboard.txt");
    const int maxplayers = 100;
    string name[maxplayers];
    int scores[maxplayers];
    int count = 0;
    if (file.is_open() )
    {
        while (file >> name[count] >> scores[count])
        {
            count++;
        }
        file.close();
    }
    else
    {
        cout << "Error: Could not open leaderboard file." << endl;
        return;
    }

    for (int i = 0; i < count - 1; ++i)
    {
        for (int j = 0; j < count - i - 1; ++j)
        {
            if (scores[j] < scores[j + 1])
            {
        	int tempScore = scores[j];
            scores[j] = scores[j + 1];
            scores[j + 1] = tempScore;
            string tempName = name[j];
            name[j] = name[j + 1];
            name[j + 1] = tempName;
            }
        }
    }

    cout <<MAGENTA<<"Leaderboard:" << endl;
    cout <<CYAN<<"-----------------------" << endl;
    for (int i = 0; i < count; ++i)
    {
        cout <<MAGENTA<<name[i] << " : " << scores[i] <<RESET<< endl;
        cout <<CYAN<<"-----------------------" << endl;
    }
    if (count == 0)
    {
        cout <<RED<<"No leaderboard data available." << endl;
    }
    cout<<GREEN<<"press a key to return to the menu"<<RESET<<endl;
    char key = getch();
    main_menu();
}



void board_makear()
{
    if (game_board != nullptr) 
    {
        free_board();
    }

     game_board = new string*[screen_hight];
    for (int i = 0; i < screen_hight; i++) 
    {
        game_board[i] = new string[screen_width];
    }

     for (int i = 0; i < screen_hight; i++) {
        for (int j = 0; j < screen_width; j++) {
            game_board[i][j] = ' '; 
        }
    }

    game_board[screen_hight - 1][screen_width / 2] = PLAYER;
    for (int i = 0 ; i < 4; i++) 
    {
        for  (int j = 0; j < screen_width /2; j++) 
        {
            if(i == 1) game_board[1][j] = E3;
            else if(i == 2 ) game_board[2][j] = E2;
            else if (i == 3) game_board[3][j] = E1;
        }
    }

    for(int i = screen_hight-3 ; i > screen_hight - 5 ; i-- )
    {
        for(int j = 0 ; j < screen_width ; j +=2)
        {
            game_board[i][j] = "3";
            
        }
    }
}




void time_and_score()
{
    reset_cursor();
    time_t now = time(0);
    int elapsed_time = static_cast<int>(difftime(now, start_time));
    current_game.time = elapsed_time;
    cout << GREEN << "Score: " << current_game.score <<endl;
    cout << YELLOW << "Time: " << elapsed_time << "s" << RESET <<endl;
    
    
}


void display_board()
{
    
    int h = 2 * screen_hight;

    while(h != -3)
    {
        if(h == 2 * screen_hight) cout<<MAGENTA<<"╔";
        else if(h == -2 ) cout<<"╗"<<RESET<<endl;
        else cout<<"═";
        h--;

    }

    for (int i = 0; i < screen_hight; i++) 
    {
        for (int j = 0; j < screen_width; j++) 
        {
            if (j == 0) cout<<MAGENTA<<"║";
            if(game_board[i][j]== E3) cout<<YELLOW<<game_board[i][j]<<" ";
            else if(game_board[i][j] == E2) cout<<GREEN<<game_board[i][j]<<" ";
            else if(game_board[i][j] == E1) cout <<BLUE<<game_board[i][j]<<" ";
            else if((i == screen_hight - 3 || i == screen_hight  - 4) && game_board[i][j] == "3" ) cout<<CYAN<<"╳" <<" ";
            else if((i == screen_hight - 3 || i == screen_hight  - 4) && game_board[i][j] == "2" ) cout<<YELLOW<<"╳" <<" ";
            else if((i == screen_hight - 3 || i == screen_hight  - 4) && game_board[i][j] == "1" ) cout<<MAGENTA<<"╳" <<" ";
            else if((i == screen_hight - 3 || i == screen_hight  - 4) && game_board[i][j] == "0" ) cout<<RED<<"╳" <<" ";
            else if(game_board[i][j] == SHOOT)cout<<MAGENTA<<game_board[i][j]<<" ";
            else if(game_board[i][j] == E4)cout<<RED<<game_board[i][j]<<" ";
            else cout <<RESET<<game_board[i][j] <<" ";
            if(j == screen_width - 1 ) cout<<MAGENTA<<" ║"<<RESET;
        }
        cout << endl;
    }

    h = 2 * screen_hight;
    while(h != -3)
    {
        if(h == 2 * screen_hight) cout<<MAGENTA<<"╚";
        else if(h == -2 ) cout<<"╝"<<RESET<<endl;
        else cout<<"═";
        h--;

    }
}

void health_bar()
{
   
    if(health > 0)
    {
        cout << "   " << BLUE << "Health: ";
        for (int i = 2; 0 <= i ; i--) 
        {
            switch (i)
            {
                case 0 :
                    
                    if(health > i)
                        cout<< "🧡"<<"  ";
                    else 
                        cout<< " "<<"  ";

                    break;
                case 1 :
                    if(health > i)
                        cout<< "💛"<<"  ";
                    else 
                        cout<< " "<<"  ";

                    break;
                case 2 :
                    if(health > i)
                        cout<<"💚"<<"  ";
                    else 
                        cout<< " "<<"  ";
                    break;
            }

        }
        cout<<endl;
       
    }
    else
    {
        cout<<RED<<"╔══════════════════╗"<<endl;
        cout<<"║    GAME OVER     ║"<<endl;
        cout<<"╚══════════════════╝"<<RESET<<endl;
        cout<<GREEN<<"press a key to return to the menu"<<RESET<<endl;
        char key = getch();
        main_menu();
    }

        
}

void savedata(const string& playerName, int score)
{
    {
    ofstream file("scoreboard.txt", std::ios::app);
    if (file.is_open())
    {
        file << playerName << " " << score << endl;
        file.close();
    }
    else
    {
        cout << "Error: Unable to save leaderboard." << endl;
    }
}
}

void save_game() 
{
    ofstream file("save_game.txt" , std::ios::out);

    if (!file.is_open()) 
    {
        cout << RED << "Error: Could not save the game!" << RESET << endl;
        return;
    }
    file<<"Screen hight "<<screen_hight<<endl;
    file<<"Screen width "<<screen_width<<endl;
    file<<"Theme  "<<current_game.theme<<endl;
    file << "Name  " << current_game.name << endl;
    file << "Score  " << current_game.score << endl;
    file << "Health  " << health << endl;
    file << "TimeElapsed  " << difftime(time(0), start_time) << endl;


    file << "Bullets  " << endl;
    for (int i = 0; i < MAX_BULLET; i++) 
    {
        file << bullet[i].x << " " << bullet[i].y << " " << bullet[i].active << endl;
    }

    
    file << "GameBoard : " << endl;
    for (int i = 0; i < screen_hight; i++) 
    {
        for (int j = 0; j < screen_width; j++) 
        {
            // 
            file << game_board[i][j] << " ";
        }
        file << endl;
    }
    file.close();
    cout << GREEN << "Game saved successfully!" << endl;
    cout<<"press a key to return to the menu ..."<<RESET<<endl;
    char key = getch();
}


void free_board()
{
    for (int i = 0; i < screen_hight; i++) 
    {
        delete[] game_board[i];
    }
    delete[] game_board;
    game_board = nullptr;
}

void move_player(int direction) 
{
    int player_x = -1;
    for (int j = 0; j < screen_width; j++) 
    {
        if (game_board[screen_hight - 1][j] == PLAYER) 
        {
            player_x = j;
            break;
        }
    }

    if (player_x == -1) return;

    game_board[screen_hight - 1][player_x] = " ";

    int new_x = player_x + direction;
    if (new_x >= 0 && new_x < screen_width) 
    {
        game_board[screen_hight - 1][new_x] = PLAYER;
    } 
    else 
    {
        game_board[screen_hight - 1][player_x] = PLAYER;
    }
}


void pause_menu(bool& running)
{
    system("cls");
    cout<<BLUE<<"╔═══╦═══════════════╗"<<endl;
    cout<<"║1. ║     RESUME    ║"<<endl;
    cout<<"║2. ║ SAVE AND EXIT ║"<<endl;
    cout<<"║3. ║    STORE	    ║"<<endl;
    cout<<"║4. ║     EXIT      ║"<<endl;
    cout<<"╚═══╩═══════════════╝"<<RESET<<endl;\
    char option = getch();
    switch (option)
    {
        case '1' :
            system("cls");
            break;
        case '2' :
            save_game();
            running = 0;
            savedata(current_game.name, current_game.score);
            current_game.score = 0;
            bullet[0].active = false;
            free_board();
            main_menu();
            
            break;
        case '3':
            handle_store(running);
            break;
        case '4' :
            running = 0;
            savedata(current_game.name, current_game.score);
            current_game.score = 0;
            bullet[0].active = false;
            free_board();
            main_menu();
            
            break;
        default :
            pause_menu(running);
            break;
            
    }

}


void reset_cursor() 
{
    cout << "\033[H"; 
    cout.flush();
}

void game_loop(char&  theme ) 
{
   
    int game_speed = 35;
    bool running = true;
    current_game.time= 0;
    current_game.score = 0;
    while (running) 
	{
        reset_cursor();
        time_and_score();
        switch (theme)
        {
            case '1' :
                display_board();
                break;
            case '2' :
                heart_board();
                break;
            case '3' :
                triangle_board();
                break;
            case '4' :
                star_board();
                break;
            default :
                newgame();
                break;

        }
      
        
        move_bullets();
        handle_bombs();
        move_enemies(running);
        move_enemy_bullets(running);
        move_special_enemy();
        handle_special_enemy();
        check_win();
        health_bar();
        if(!check_win)
        {
            running = false;
        }
	    
		
        srand(time(0));
        if (rand() % 10 < 2) 
        {
            enemy_shoots();
        }

        if (_kbhit()) 
		{ 
            char key =tolower(getch());
             
            switch (key) 
			{
                case 'a':
                    move_player(-1); 
                    break;
                case 'd':
                    move_player(1); 
                    break;
                case ' ':
                    player_shoots(); 
                    break;
                case 'b':
               
                        player_shoot_bomb();
                    
                    
                    break;
                case 'p':
                    pause_menu(running); 
                    break;
                
            }
        }
        if(current_game.score % 60 == 0) game_speed -= 10;

        this_thread::sleep_for(chrono::milliseconds(game_speed)); 
         if(check_board())
        {
            
            cout<<GREEN<<"Perfect "<<current_game.name<<" you are done this level"<<endl;
            cout<<"Score : "<<current_game.score<<endl;
            cout<<"Time : "<<current_game.time<<endl;
            cout<<"Do you want go to next level? (press Y for yes or any key to back menu)"<<RESET<<endl;
            char key = tolower(getch());
            if(key == 'y')
            {
                system("cls");
                free_board();
                reset_game_info();
                board_makear2();
                running = false;
                bullet[1].active = false;
                for(int i = 0 ; i < MAX_ENEMY_BULLET ; i++)
                {
                    enemy_bullets[i].active = false;
                }
                game_loop2(theme);
                break;
            }
            else
            {
                main_menu();
            }
        }
        
    }

    
    
}


void play_shoot_sound() 
{
    Beep(1000, 100); 
}

void player_shoots() 
{
    for (int i = 0; i < MAX_BULLET; i++) 
	{
        if (!bullet[i].active) 
		{
            for (int j = 0; j < screen_width; j++) 
			{
                if (game_board[screen_hight - 1][j] == PLAYER)
				{
                    bullet[i] = {j, screen_hight - 2, true};
                    game_board[bullet[i].y][bullet[i].x] = SHOOT;
                    play_shoot_sound();
                    break;
                }
            }
            break;
        }
    }
}



void move_bullets() 
{


    for (int i = 0; i < MAX_BULLET; i++) 
	{
       
        if (bullet[i].active) 
		{
            game_board[bullet[i].y][bullet[i].x] = " ";
            if (bullet[i].y > 0) 
			{
                bullet[i].y--;
                if (game_board[bullet[i].y][bullet[i].x] == E1) 
				{
                    game_board[bullet[i].y][bullet[i].x] = " "; 
                    bullet[i].active = false; 
                    current_game.score += 10;
                } 
				else if (game_board[bullet[i].y][bullet[i].x] == E2)
				{
                    game_board[bullet[i].y][bullet[i].x] = " ";
                    bullet[i].active = false;
                    current_game.score += 20;
                } 
				else if (game_board[bullet[i].y][bullet[i].x] == E3) 
				{
                    game_board[bullet[i].y][bullet[i].x] = " ";
                    bullet[i].active = false;
                    current_game.score += 40;
                } 
				else if (game_board[bullet[i].y][bullet[i].x] == "3") 
				{
                    game_board[bullet[i].y][bullet[i].x] = "2";
                    bullet[i].active = false;
                }
                else if (game_board[bullet[i].y][bullet[i].x] == "2") 
				{
                    game_board[bullet[i].y][bullet[i].x] = "1";
                    bullet[i].active = false;
                }
                else if (game_board[bullet[i].y][bullet[i].x] == "1") 
				{
                    game_board[bullet[i].y][bullet[i].x] = "0";
                    bullet[i].active = false;
                }
                else if (game_board[bullet[i].y][bullet[i].x] == "0") 
				{
                    game_board[bullet[i].y][bullet[i].x] = " ";
                    bullet[i].active = false;
                }
                else if(game_board[bullet[i].y][bullet[i].x] == E4)
                {
                    game_board[bullet[i].y][bullet[i].x] = " ";
                    bullet[i].active = false;
                    current_game.score += 100;
                }
                else if(game_board[bullet[i].y][bullet[i].x] == ENENMY_SHOOT)
                {
                    game_board[bullet[i].y][bullet[i].x] = " ";
                    bullet[i].active = false;

                }
				else 
				{
                    game_board[bullet[i].y][bullet[i].x] = SHOOT;
                }
            }
			else 
			{
                bullet[i].active = false;
            }
        }
    }
}

void move_enemies(bool& running) 
{
    if (enemy_step < enemy_speed) 
	{
        enemy_step++; 
        return; 
    }
    enemy_step = 0;
    bool atEdge = false;
    if (moveRight) 
	{
        for (int i = 1; i <= screen_hight - 3 && !atEdge; i++) 
		{ 
            for (int j = screen_width - 1; j >= 0 && !atEdge; j--)
			{
                if (game_board[i][j] == E1 || game_board[i][j] == E2 || game_board[i][j] == E3) 
				{
                    if (j + 1 < screen_width)
					{
                        game_board[i][j + 1] = game_board[i][j];
                        game_board[i][j] = " ";
                    }
					else 
					{
                        atEdge = true;
                    }
                }
            }
        }
    } 
	else 
	{
        for (int i = 1; i < screen_hight - 4 && !atEdge; i++) 
		{
     	   for (int j = 0; j < screen_width && !atEdge; j++) 
			{
                if (game_board[i][j] == E1 || game_board[i][j] == E2 || game_board[i][j] == E3) 
				{
                    if (j - 1 > 0) 
					{
                        game_board[i][j - 1] = game_board[i][j];
                        game_board[i][j] = " ";
                    } 
					else 
					{
                        atEdge = true;
                    }
                }
            }
        }
    }

    if (atEdge) 
	{
        moveRight = !moveRight;
        for (int i = screen_hight - 3; i >= 1; i--) 
		{
            for (int j = 0; j < screen_width; j++)
			{
                if (game_board[i][j] == E1 || game_board[i][j] == E2 || game_board[i][j] == E3) 
				{
                    if (i + 1 < screen_hight) 
					{
                        game_board[i + 1][j] = game_board[i][j];
                        game_board[i][j] = " ";
                    } 
					else 
					{
                     
                        cout << RED << "GAME OVER! The enemies have reached the bottom!" << RESET << endl;
                        cout<<GREEN<<"press a key to return to the menu"<<RESET<<endl;
                        char key = getch();
                        main_menu();
                        
                    }
                }
            }
        }
    }
}



void enemy_shoots() 
{
    static int shoot_delay = 0;  // شمارنده برای تنظیم سرعت شلیک
    shoot_delay++;
    if (shoot_delay < 5) 
    { // تنظیم تاخیر شلیک (عدد بیشتر = سرعت کمتر)
        return;
    }
    shoot_delay = 0; // ریست شمارنده

    srand(time(0));
    int num_shots = 5; // تعداد تیرهایی که هر بار شلیک می‌شوند
    int chosen_columns[num_shots];

    // انتخاب ستون‌های تصادفی برای شلیک
    for (int i = 0; i < num_shots; i++) 
	{
        chosen_columns[i] = rand() % screen_width;
    }
    // ایجاد تیر برای هر ستون انتخاب‌شده
    for (int col : chosen_columns) 
	{
        for (int i = 0; i < MAX_ENEMY_BULLET; i++) 
		{
            if (!enemy_bullets[i].active) 
			{
                for (int row = 0; row < screen_hight; row++) 
				{  // پیدا کردن دشمن برای شلیک
                    if (game_board[row][col] == E1) 
					{
                        enemy_bullets[i] = {col, row + 1, true};
                        game_board[row + 1][col] = ENENMY_SHOOT;
                        break;
                    } 
					else if (game_board[row][col] == E2) 
					{
                        enemy_bullets[i] = {col, row + 2, true};
                        game_board[row + 2][col] = ENENMY_SHOOT;
                        break;
                    } 
					else if (game_board[row][col] == E3) 
					{
                        enemy_bullets[i] = {col, row + 3, true};
                        game_board[row + 3][col] = ENENMY_SHOOT;
                        break;
                    }
                }
                break;
            }
        }
    }
}


void move_enemy_bullets(bool& running) 
{
    for (int i = 0; i < MAX_ENEMY_BULLET; i++) 
	{
        if (enemy_bullets[i].active) 
		{
            game_board[enemy_bullets[i].y][enemy_bullets[i].x] = " "; // حذف ردپای تیر در موقعیت قبلی
            if (enemy_bullets[i].y < screen_hight - 1) 
			{
                enemy_bullets[i].y++;
                string& cell = game_board[enemy_bullets[i].y][enemy_bullets[i].x];
                if (cell == PLAYER) 
				{  // برخورد به بازیکن
                    if (health < 0) 
					{
                        running = false;
                        cout << RED << "Game Over!" << RESET << endl;
                        cout << GREEN << "Press a key to return to the menu." << RESET << endl;
                        char key = getch();
                        main_menu();
                    }

                    else
                    {
                        health--;
                        game_board[screen_hight - 1][screen_width/2] = PLAYER;
                    }
                } 
				else if (cell == "3") 
				{ // برخورد با مانع سطح 3
                    cell = "2";
                    enemy_bullets[i].active = false;
                } 
				else if (cell == "2") 
				{ // برخورد با مانع سطح 2
                    cell = "1";
                    enemy_bullets[i].active = false;
                } 
				else if (cell == "1") 
				{ // برخورد با مانع سطح 1
                    cell = "0";
                    enemy_bullets[i].active = false;
                } 
				else if (cell == "0") 
				{ // حذف مانع
                    cell = " ";
                    enemy_bullets[i].active = false;
                } 
				else if (cell == SHOOT) 
				{ // برخورد با تیر بازیکن
                    enemy_bullets[i].active = false;
                } 
				else 
				{
                    game_board[enemy_bullets[i].y][enemy_bullets[i].x] = ENENMY_SHOOT;
                }
            }
			else 
			{
                enemy_bullets[i].active = false; // غیرفعال کردن تیر وقتی به پایین صفحه می‌رسد
            }
        }
    }
}


void spawn_special_enemy() 
{
    if (special_enemy_active) return;
    special_enemy_y = 0;
    special_enemy_x = 1;
    special_enemy_active = true;
    game_board[special_enemy_y][special_enemy_x] = E4;
}

int special_enemy_move_timer = 0;

void move_special_enemy() 
{
    if (!special_enemy_active) return;
    if (special_enemy_move_timer > 0) 
	{
        special_enemy_move_timer--;
        return;
    }
    special_enemy_move_timer = 2; 
    game_board[special_enemy_y][special_enemy_x] = " ";
    special_enemy_x += special_enemy_speed;
    if (special_enemy_x >= screen_width || special_enemy_x < 0) 
	{
        special_enemy_active = false;
        return;
    }

	
        game_board[special_enemy_y][special_enemy_x] = E4;
    
}


void handle_special_enemy() 
{
    if (special_enemy_timer > 0) 
    {
        special_enemy_timer--;
    } 
    else 
    {
        spawn_special_enemy();
        special_enemy_timer = rand() % 400 + 200;
    }
}

void heart_board()
{
    int h = 2 * screen_width;
    while(h != -3)
    {
         cout<<RED<<"♡";
        h--;

    }
    cout<<endl;

    for (int i = 0; i < screen_hight; i++) 
    {
        for (int j = 0; j < screen_width; j++) 
        {
            
            if(game_board[i][j]== E3) cout<<YELLOW<<game_board[i][j]<<" ";
            else if(game_board[i][j] == E2) cout<<GREEN<<game_board[i][j]<<" ";
            else if(game_board[i][j] == E1) cout <<BLUE<<game_board[i][j]<<" ";
            else if((i == screen_hight - 3 || i == screen_hight  - 4) && game_board[i][j] == "3" ) cout<<CYAN<<"╳" <<" ";
            else if((i == screen_hight - 3 || i == screen_hight  - 4) && game_board[i][j] == "2" ) cout<<YELLOW<<"╳" <<" ";
            else if((i == screen_hight - 3 || i == screen_hight  - 4) && game_board[i][j] == "1" ) cout<<MAGENTA<<"╳" <<" ";
            else if((i == screen_hight - 3 || i == screen_hight  - 4) && game_board[i][j] == "0" ) cout<<RED<<"╳" <<" ";
            else if(game_board[i][j] == SHOOT)cout<<MAGENTA<<game_board[i][j]<<" ";
            else if(game_board[i][j] == E4)cout<<RED<<game_board[i][j]<<" ";
            else cout <<RESET<<game_board[i][j] <<" ";
            
        }
        cout << endl;

   
        
    }
    h = 2 * screen_width;
     while(h != -3)
    {
        
       cout<<RED<<"♡";
        h--;

    }
    cout<<RESET<<endl;

   
    
}

void star_board()
{
    int h = 2 * screen_width;
    while(h != -3)
    {
         cout<<YELLOW<<"✰";
        h--;

    }
    cout<<endl;

    for (int i = 0; i < screen_hight; i++) 
    {
        for (int j = 0; j < screen_width; j++) 
        {
            
            if(game_board[i][j]== E3) cout<<YELLOW<<game_board[i][j]<<" ";
            else if(game_board[i][j] == E2) cout<<GREEN<<game_board[i][j]<<" ";
            else if(game_board[i][j] == E1) cout <<BLUE<<game_board[i][j]<<" ";
            else if((i == screen_hight - 3 || i == screen_hight  - 4) && game_board[i][j] == "3" ) cout<<CYAN<<"╳" <<" ";
            else if((i == screen_hight - 3 || i == screen_hight  - 4) && game_board[i][j] == "2" ) cout<<YELLOW<<"╳" <<" ";
            else if((i == screen_hight - 3 || i == screen_hight  - 4) && game_board[i][j] == "1" ) cout<<MAGENTA<<"╳" <<" ";
            else if((i == screen_hight - 3 || i == screen_hight  - 4) && game_board[i][j] == "0" ) cout<<RED<<"╳" <<" ";
            else if(game_board[i][j] == SHOOT)cout<<MAGENTA<<game_board[i][j]<<" ";
            else if(game_board[i][j] == E4)cout<<RED<<game_board[i][j]<<" ";
            else cout <<RESET<<game_board[i][j] <<" ";
            
        }
        cout << endl;

   
        
    }
    h = 2 * screen_width;
     while(h != -3)
    {
        
       cout<<YELLOW<<"✰";
        h--;

    }
    cout<<RESET<<endl;

   
    
}

void triangle_board()
{
     int h = 2 * screen_width;
    while(h != -3)
    {
         cout<<BLUE<<"⏶";
        h--;

    }
    cout<<endl;

    for (int i = 0; i < screen_hight; i++) 
    {
        for (int j = 0; j < screen_width; j++) 
        {
            
            if(game_board[i][j]== E3) cout<<YELLOW<<game_board[i][j]<<" ";
            else if(game_board[i][j] == E2) cout<<GREEN<<game_board[i][j]<<" ";
            else if(game_board[i][j] == E1) cout <<BLUE<<game_board[i][j]<<" ";
               else if((i == screen_hight - 3 || i == screen_hight  - 4) && game_board[i][j] == "3" ) cout<<CYAN<<"╳" <<" ";
            else if((i == screen_hight - 3 || i == screen_hight  - 4) && game_board[i][j] == "2" ) cout<<YELLOW<<"╳" <<" ";
            else if((i == screen_hight - 3 || i == screen_hight  - 4) && game_board[i][j] == "1" ) cout<<MAGENTA<<"╳" <<" ";
            else if((i == screen_hight - 3 || i == screen_hight  - 4) && game_board[i][j] == "0" ) cout<<RED<<"╳" <<" ";
            else if(game_board[i][j] == SHOOT)cout<<MAGENTA<<game_board[i][j]<<" ";
            else if(game_board[i][j] == E4)cout<<RED<<game_board[i][j]<<" ";
            else cout <<RESET<<game_board[i][j] <<" ";
        }
        cout << endl;

   
        
    }
    h = 2 * screen_width;
     while(h != -3)
    {
        
       cout<<BLUE<<"⏷";
        h--;

    }
    cout<<RESET<<endl;

}

bool check_win()
{
    bool is_win = true;
    if(health == 0) is_win = false;
    for(int j = 0 ; j < screen_width ; j++)
    {
        if(game_board[screen_hight-4][j] == E1 || game_board[screen_hight-4][j] == E2 || game_board[screen_hight-4][j] == E3 )
        {
            cout<<RED<<"GAME OVER"<<endl;
            cout<<GREEN<<"press a key to return to the menu"<<RESET<<endl;
            char key = getch();
            is_win = false;
            bullet[0].active = false;
            savedata(current_game.name, current_game.score);
            free_board();
            main_menu();
        }
    }

    return is_win;
}

void getValidatedInput() 
{
    int input;
    while (true) 
    { 
        
       

        
        if (cin.fail()) { 
            cin.clear(); 
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            cout<<endl;
            cout <<RED<<"Invalid input! Please enter an integer" <<endl;
            cout<<GREEN<<"press any key"<<RESET<<endl;
            char key = getch();
            newgame();
        } 
       else 
       {
        return;
       }
    }
}

void load_game() 
{
    ifstream file("save_game.txt");

    if (!file.is_open()) 
    {
        cout << RED << "Error: Could not load the game!" << RESET << endl;
        return;
    }
    string temp; 
    file>>temp>>screen_hight;
    cout << screen_hight << '\n';
    file>>temp>>screen_width;
    file>>temp>>current_game.theme;
    file >> temp >> current_game.name;          
    file >> temp >> current_game.score;        
    file >> temp >> health;                    
    file >> temp;                               
    double timeElapsed;
    file >> timeElapsed;
    start_time = time(0) - static_cast<time_t>(timeElapsed); 

    file >> temp;                               
    for (int i = 0; i < MAX_BULLET; i++) 
    {
        file >> bullet[i].x >> bullet[i].y >> bullet[i].active; 
    }

    file >> temp;                               
    for (int i = 0; i < screen_hight; i++) 
    {
        for (int j = 0; j < screen_width; j++) 
        {
            // 
            file >> game_board[i][j];          
        }
    }

    file.close(); 

    cout << GREEN << "Game loaded successfully!" << RESET << endl;
    cout << "Press a key to return to the game..." << endl;
    char key = getch(); 
    game_loop(current_game.theme);
}

bool check_board()
{
    bool clean = false;
    for(int i = 1 ; i < screen_hight  ; i++)
    {
        for(int j = 0 ; j < screen_width ; j++)
        {
            if(game_board[i][j] == E1 || game_board[i][j] == E2 || game_board[i][j] == E3)
            {

                return false;
            }
        }
    }

    clean =  true;
    return clean;
}




void reset_game_info()
{
    screen_hight = 20;
    screen_width = 20;
    health = 3;
    current_game.score =0;
    current_game.theme = '1';
    current_game.time = 0;
    for(int i = 0 ; i < MAX_BULLET ; i++)
    {
        bullet[i].active = false;
    }
    for(int i = 0 ; i < MAX_ENEMY_BULLET ; i++)
    {
        enemy_bullets[i].active = false;
    }

}

void board_makear2()
{
    if (game_board != nullptr) 
    {
        free_board();
    }

     game_board = new string*[screen_hight];
    for (int i = 0; i < screen_hight; i++) 
    {
        game_board[i] = new string[screen_width];
    }

     for (int i = 0; i < screen_hight; i++) {
        for (int j = 0; j < screen_width; j++) {
            game_board[i][j] = ' '; 
        }
    }

    game_board[screen_hight - 1][screen_width / 2] = PLAYER;
    for (int i = 0 ; i < 4; i++) 
    {
        for  (int j = 0; j < screen_width /2; j++) 
        {
            if(i == 1) game_board[1][j] = "9";
            else if(i == 2 ) game_board[2][j] = "5";
            else if (i == 3) game_board[3][j] = "7";
        }
    }

    for(int i = screen_hight-3 ; i > screen_hight - 5 ; i-- )
    {
        for(int j = 0 ; j < screen_width ; j +=2)
        {
            game_board[i][j] = "3";
            
        }
    }
}

void display_board2()
{
    
    int h = 2 * screen_hight;

    while(h != -3)
    {
        if(h == 2 * screen_hight) cout<<MAGENTA<<"╔";
        else if(h == -2 ) cout<<"╗"<<RESET<<endl;
        else cout<<"═";
        h--;

    }

    for (int i = 0; i < screen_hight; i++) 
    {
        for (int j = 0; j < screen_width; j++) 
        {
            if (j == 0) cout<<MAGENTA<<"║";
            if(game_board[i][j]== "9") cout<<YELLOW<<E3<<" ";
            else if(game_board[i][j] == "5" || game_board[i][j] == "4" ) cout<<GREEN<<E2<<" ";
            else if(game_board[i][j] == "7" ||game_board[i][j] == "6" ) cout <<BLUE<<E1<<" ";
            else if((i == screen_hight - 3 || i == screen_hight  - 4) && game_board[i][j] == "3" ) cout<<CYAN<<"╳" <<" ";
            else if((i == screen_hight - 3 || i == screen_hight  - 4) && game_board[i][j] == "2" ) cout<<YELLOW<<"╳" <<" ";
            else if((i == screen_hight - 3 || i == screen_hight  - 4) && game_board[i][j] == "1" ) cout<<MAGENTA<<"╳" <<" ";
            else if((i == screen_hight - 3 || i == screen_hight  - 4) && game_board[i][j] == "0" ) cout<<RED<<"╳" <<" ";
            else if(game_board[i][j] == SHOOT)cout<<MAGENTA<<game_board[i][j]<<" ";
            else if(game_board[i][j] == E4)cout<<RED<<game_board[i][j]<<" ";
            else cout <<RESET<<game_board[i][j] <<" ";
            if(j == screen_width - 1 ) cout<<MAGENTA<<" ║"<<RESET;
        }
        cout << endl;
    }

    h = 2 * screen_hight;
    while(h != -3)
    {
        if(h == 2 * screen_hight) cout<<MAGENTA<<"╚";
        else if(h == -2 ) cout<<"╝"<<RESET<<endl;
        else cout<<"═";
        h--;

    }
}

void heart_board2()
{
    int h = 2 * screen_width;
    while(h != -3)
    {
         cout<<RED<<"♡";
        h--;

    }
    cout<<endl;

    for (int i = 0; i < screen_hight; i++) 
    {
        for (int j = 0; j < screen_width; j++) 
        {
            
            if(game_board[i][j]== "9") cout<<YELLOW<<E3<<" ";
            else if(game_board[i][j] == "5" || game_board[i][j] == "4" ) cout<<GREEN<<E2<<" ";
            else if(game_board[i][j] == "7" ||game_board[i][j] == "6" ) cout <<BLUE<<E1<<" ";
            else if((i == screen_hight - 3 || i == screen_hight  - 4) && game_board[i][j] == "3" ) cout<<CYAN<<"╳" <<" ";
            else if((i == screen_hight - 3 || i == screen_hight  - 4) && game_board[i][j] == "2" ) cout<<YELLOW<<"╳" <<" ";
            else if((i == screen_hight - 3 || i == screen_hight  - 4) && game_board[i][j] == "1" ) cout<<MAGENTA<<"╳" <<" ";
            else if((i == screen_hight - 3 || i == screen_hight  - 4) && game_board[i][j] == "0" ) cout<<RED<<"╳" <<" ";
            else if(game_board[i][j] == SHOOT)cout<<MAGENTA<<game_board[i][j]<<" ";
            else if(game_board[i][j] == E4)cout<<RED<<game_board[i][j]<<" ";
            else cout <<RESET<<game_board[i][j] <<" ";
            
        }
        cout << endl;

   
        
    }
    h = 2 * screen_width;
     while(h != -3)
    {
        
       cout<<RED<<"♡";
        h--;

    }
    cout<<RESET<<endl;

   
    
}

void star_board2()
{
    int h = 2 * screen_width;
    while(h != -3)
    {
         cout<<YELLOW<<"✰";
        h--;

    }
    cout<<endl;

    for (int i = 0; i < screen_hight; i++) 
    {
        for (int j = 0; j < screen_width; j++) 
        {
            
            if(game_board[i][j]== "9") cout<<YELLOW<<E3<<" ";
            else if(game_board[i][j] == "5" || game_board[i][j] == "4" ) cout<<GREEN<<E2<<" ";
            else if(game_board[i][j] == "7" ||game_board[i][j] == "6" ) cout <<BLUE<<E1<<" ";
            else if((i == screen_hight - 3 || i == screen_hight  - 4) && game_board[i][j] == "3" ) cout<<CYAN<<"╳" <<" ";
            else if((i == screen_hight - 3 || i == screen_hight  - 4) && game_board[i][j] == "2" ) cout<<YELLOW<<"╳" <<" ";
            else if((i == screen_hight - 3 || i == screen_hight  - 4) && game_board[i][j] == "1" ) cout<<MAGENTA<<"╳" <<" ";
            else if((i == screen_hight - 3 || i == screen_hight  - 4) && game_board[i][j] == "0" ) cout<<RED<<"╳" <<" ";
            else if(game_board[i][j] == SHOOT)cout<<MAGENTA<<game_board[i][j]<<" ";
            else if(game_board[i][j] == E4)cout<<RED<<game_board[i][j]<<" ";
            else cout <<RESET<<game_board[i][j] <<" ";
            
        }
        cout << endl;

   
        
    }
    h = 2 * screen_width;
     while(h != -3)
    {
        
       cout<<YELLOW<<"✰";
        h--;

    }
    cout<<RESET<<endl;

   
    
}

void triangle_board2()
{
     int h = 2 * screen_width;
    while(h != -3)
    {
         cout<<BLUE<<"⏶";
        h--;

    }
    cout<<endl;

    for (int i = 0; i < screen_hight; i++) 
    {
        for (int j = 0; j < screen_width; j++) 
        {
            
            if(game_board[i][j]== "9") cout<<YELLOW<<E3<<" ";
            else if(game_board[i][j] == "5" || game_board[i][j] == "4" ) cout<<GREEN<<E2<<" ";
            else if(game_board[i][j] == "7" ||game_board[i][j] == "6" ) cout <<BLUE<<E1<<" ";
            else if((i == screen_hight - 3 || i == screen_hight  - 4) && game_board[i][j] == "3" ) cout<<CYAN<<"╳" <<" ";
            else if((i == screen_hight - 3 || i == screen_hight  - 4) && game_board[i][j] == "2" ) cout<<YELLOW<<"╳" <<" ";
            else if((i == screen_hight - 3 || i == screen_hight  - 4) && game_board[i][j] == "1" ) cout<<MAGENTA<<"╳" <<" ";
            else if((i == screen_hight - 3 || i == screen_hight  - 4) && game_board[i][j] == "0" ) cout<<RED<<"╳" <<" ";
            else if(game_board[i][j] == SHOOT)cout<<MAGENTA<<game_board[i][j]<<" ";
            else if(game_board[i][j] == E4)cout<<RED<<game_board[i][j]<<" ";
            else cout <<RESET<<game_board[i][j] <<" ";
        }
        cout << endl;

   
        
    }
    h = 2 * screen_width;
     while(h != -3)
    {
        
       cout<<BLUE<<"⏷";
        h--;

    }
    cout<<RESET<<endl;

}


void move_bullets2() 
{


    for (int i = 0; i < MAX_BULLET; i++) 
	{
       
        if (bullet[i].active) 
		{
            game_board[bullet[i].y][bullet[i].x] = " ";
            if (bullet[i].y > 0) 
			{
                bullet[i].y--;
                if (game_board[bullet[i].y][bullet[i].x] == "7") 
				{
                    game_board[bullet[i].y][bullet[i].x] = "6"; 
                    bullet[i].active = false; 
                    current_game.score += 10;
                } 
                else if (game_board[bullet[i].y][bullet[i].x] == "6")
                {
                    game_board[bullet[i].y][bullet[i].x] = " "; 
                    bullet[i].active = false; 
                    current_game.score += 10;
                } 

                else if (game_board[bullet[i].y][bullet[i].x] == "4")
                {
                    game_board[bullet[i].y][bullet[i].x] = " "; 
                    bullet[i].active = false; 
                    current_game.score += 20;
                } 

				else if (game_board[bullet[i].y][bullet[i].x] == "5")
				{
                    game_board[bullet[i].y][bullet[i].x] = "4";
                    bullet[i].active = false;
                    current_game.score += 20;
                } 
				else if (game_board[bullet[i].y][bullet[i].x] == "9") 
				{
                    game_board[bullet[i].y][bullet[i].x] = " ";
                    bullet[i].active = false;
                    current_game.score += 40;
                } 
				else if (game_board[bullet[i].y][bullet[i].x] == "3") 
				{
                    game_board[bullet[i].y][bullet[i].x] = "2";
                    bullet[i].active = false;
                }
                else if (game_board[bullet[i].y][bullet[i].x] == "2") 
				{
                    game_board[bullet[i].y][bullet[i].x] = "1";
                    bullet[i].active = false;
                }
                else if (game_board[bullet[i].y][bullet[i].x] == "1") 
				{
                    game_board[bullet[i].y][bullet[i].x] = "0";
                    bullet[i].active = false;
                }
                else if (game_board[bullet[i].y][bullet[i].x] == "0") 
				{
                    game_board[bullet[i].y][bullet[i].x] = " ";
                    bullet[i].active = false;
                }
                else if(game_board[bullet[i].y][bullet[i].x] == E4)
                {
                    game_board[bullet[i].y][bullet[i].x] = " ";
                    bullet[i].active = false;
                    current_game.score += 100;
                }
                else if(game_board[bullet[i].y][bullet[i].x] == ENENMY_SHOOT)
                {
                    game_board[bullet[i].y][bullet[i].x] = " ";
                    bullet[i].active = false;

                }
				else 
				{
                    game_board[bullet[i].y][bullet[i].x] = SHOOT;
                }
            }
			else 
			{
                bullet[i].active = false;
            }
        }
    }
}

void game_loop2(char&  theme ) 
{
   
    int game_speed = 35;
    bool running = true;
    current_game.time= 0;
    current_game.score = 0;
    while (running) 
	{
        reset_cursor();
        time_and_score();
        switch (theme)
        {
            case '1' :
                display_board2();
                break;
            case '2' :
                heart_board2();
                break;
            case '3' :
                triangle_board2();
                break;
            case '4' :
                star_board2();
                break;
            default :
                newgame();
                break;

        }
      
        
        move_bullets2();
        handle_bombs();
        move_enemies2(running);
        move_enemy_bullets(running);
        move_special_enemy();
        handle_special_enemy();
        check_win2();
        health_bar();
        if(!check_win2)
        {
            running = false;
        }
	    
		
        srand(time(0));
        if (rand() % 10 < 3) 
        {
            enemy_shoots2();
        }

        if (_kbhit()) 
		{ 
            char key =tolower(getch());
             
            switch (key) 
			{
                case 'a':
                    move_player(-1); 
                    break;
                case 'd':
                    move_player(1); 
                    break;
                case ' ':
                    player_shoots(); 
                    break;
                case 'b':
                    player_shoot_bomb();
                    break;
                case 'p':
                    pause_menu(running); 
                    break;
                
            }
        }
        if(current_game.score % 60 == 0) game_speed -= 10;

        this_thread::sleep_for(chrono::milliseconds(game_speed)); 
         if(check_board2())
        {
            //running = 0;
            cout<<GREEN<<"Perfect "<<current_game.name<<" you are done this level"<<endl;
            cout<<"Score : "<<current_game.score<<endl;
            cout<<"Time : "<<current_game.time<<endl;
            cout<<"press a key"<<RESET<<endl;
            char key = getch();
            main_menu();
        }
    }

    
    
}

bool check_win2()
{
    bool is_win = true;
    if(health == 0) is_win = false;
    for(int j = 0 ; j < screen_width ; j++)
    {
        if(game_board[screen_hight-4][j] == "7" || game_board[screen_hight-4][j] == "6" || game_board[screen_hight-4][j] == "5"|| game_board[screen_hight-4][j] == "4"  || game_board[screen_hight-4][j] == "9")
        {
            cout<<RED<<"GAME OVER"<<endl;
            cout<<GREEN<<"press a key to return to the menu"<<RESET<<endl;
            char key = getch();
            is_win = false;
            bullet[0].active = false;
            savedata(current_game.name, current_game.score);
            free_board();
            main_menu();
        }
    }

    return is_win;
}

bool check_board2()
{
    bool clean = false;
    for(int i = 1 ; i < screen_hight  ; i++)
    {
        for(int j = 0 ; j < screen_width ; j++)
        {
            if(game_board[i][j] == "7" || game_board[i][j] == "6" || game_board[i][j] == "5"|| game_board[i][j] == "4"  || game_board[i][j] == "9")
            {

                return false;
            }
        }
    }

    clean =  true;
    return clean;
}

void move_enemies2(bool& running) 
{
    if (enemy_step < enemy_speed) 
	{
        enemy_step++; 
        return; 
    }
    enemy_step = 0;
    bool atEdge = false;
    if (moveRight) 
	{
        for (int i = 1; i <= screen_hight - 3 && !atEdge; i++) 
		{ 
            for (int j = screen_width - 1; j >= 0 && !atEdge; j--)
			{
                if (game_board[i][j] == "7" || game_board[i][j] == "6" || game_board[i][j] == "5"|| game_board[i][j] == "4"  || game_board[i][j] == "9")
				{
                    if (j + 1 < screen_width)
					{
                        game_board[i][j + 1] = game_board[i][j];
                        game_board[i][j] = " ";
                    }
					else 
					{
                        atEdge = true;
                    }
                }
            }
        }
    } 
	else 
	{
        for (int i = 1; i < screen_hight - 4 && !atEdge; i++) 
		{
     	   for (int j = 0; j < screen_width && !atEdge; j++) 
			{
                if (game_board[i][j] == "7" || game_board[i][j] == "6" || game_board[i][j] == "5"|| game_board[i][j] == "4"  || game_board[i][j] == "9")
				{
                    if (j - 1 > 0) 
					{
                        game_board[i][j - 1] = game_board[i][j];
                        game_board[i][j] = " ";
                    } 
					else 
					{
                        atEdge = true;
                    }
                }
            }
        }
    }

    if (atEdge) 
	{
        moveRight = !moveRight;
        for (int i = screen_hight - 3; i >= 1; i--) 
		{
            for (int j = 0; j < screen_width; j++)
			{
                if (game_board[i][j] == "7" || game_board[i][j] == "6" || game_board[i][j] == "5"|| game_board[i][j] == "4"  || game_board[i][j] == "9")
				{
				{
                    if (i + 1 < screen_hight) 
					{
                        game_board[i + 1][j] = game_board[i][j];
                        game_board[i][j] = " ";
                    } 
					else 
					{
                     
                        cout << RED << "GAME OVER! The enemies have reached the bottom!" << RESET << endl;
                        cout<<GREEN<<"press a key to return to the menu"<<RESET<<endl;
                        char key = getch();
                        main_menu();
                        
                    }
                }
            }
        }
    }
}
}

void enemy_shoots2() 
{
    static int shoot_delay = 0;  // شمارنده برای تنظیم سرعت شلیک
    shoot_delay++;
    if (shoot_delay < 5) { // تنظیم تاخیر شلیک (عدد بیشتر = سرعت کمتر)
 return;
    }
    shoot_delay = 0; // ریست شمارنده

    srand(time(0));
    int num_shots = 5; // تعداد تیرهایی که هر بار شلیک می‌شوند
    int chosen_columns[num_shots];

    // انتخاب ستون‌های تصادفی برای شلیک
    for (int i = 0; i < num_shots; i++) 
	{
        chosen_columns[i] = rand() % screen_width;
    }
    // ایجاد تیر برای هر ستون انتخاب‌شده
    for (int col : chosen_columns) 
	{
        for (int i = 0; i < MAX_ENEMY_BULLET; i++) 
		{
            if (!enemy_bullets[i].active) 
			{
                for (int row = 0; row < screen_hight; row++) 
				{  // پیدا کردن دشمن برای شلیک
                    if (game_board[row][col] == "7" ||game_board[row][col] == "6") 
					{
                        enemy_bullets[i] = {col, row + 1, true};
                        game_board[row + 1][col] = ENENMY_SHOOT;
                        break;
                    } 
					else if (game_board[row][col] == "5" || game_board[row][col] == "4" ) 
					{
                        enemy_bullets[i] = {col, row + 2, true};
                        game_board[row + 2][col] = ENENMY_SHOOT;
                        break;
                    } 
					else if (game_board[row][col] == "9") 
					{
                        enemy_bullets[i] = {col, row + 3, true};
                        game_board[row + 3][col] = ENENMY_SHOOT;
                        break;
                    }
                }
                break;
            }
        }
    }
}

void player_shoot_bomb() 
{
    for (int i = 0; i < MAX_BOMBS; i++) 
	{
        if (!bombs[i].active) 
		{
            for (int j = 0; j < screen_width; j++) 
			{
                if (game_board[screen_hight - 1][j] == PLAYER) 
				{
                    bombs[i] = {j, screen_hight - 2, true};
                    game_board[bombs[i].y][bombs[i].x] = "⯐";
                    return;
                }
            }
        }
    }
}

void handle_store(bool& running) 
{
    system("cls");
    cout << "bomb mikhay? (Y/N)" << endl;
    char choice = toupper(getch());
    switch (choice) {
        case 'N':
            system("cls");
            pause_menu(running);
            break;
        case 'Y':
            if (current_game.score >= 150) 
			{
                //current_game.score -= 150;
                for(int i = 0 ; i < MAX_BOMBS ; i++)
                {
                    if (bombs[i].active == false)
                    {
                        current_game.score -= 150;
                        bombs[i].active = true;
                        break;
                    }
                    
                }
                cout << GREEN << "bomb kharidari shod!" << RESET << endl;
            } 
			else 
			{
                cout << RED << "naderi dadash!" << RESET << endl;
            }
            break;
        default:
            cout << "invalid input,pls try agian." << endl;
            handle_store(running);
            break;
    }
    Sleep(2000);
    system("cls");
    pause_menu(running);
}

void explode_bomb(int bomb_x, int bomb_y) 
{
    int dx[] = {0, 0, -1, 1, -1, -1, 1, 1};
    int dy[] = {-1, 1, 0, 0, -1, 1, -1, 1}; 
    for (int i = 0; i < 8; i++) 
	{
        int new_x = bomb_x + dx[i];
        int new_y = bomb_y + dy[i];
        if (new_x >= 0 && new_x < screen_width && new_y >= 0 && new_y < screen_hight) 
		{
            if (game_board[new_y][new_x] == E1 || 
                game_board[new_y][new_x] == E2 || 
                game_board[new_y][new_x] == E3 ||
                game_board[new_y][new_x] == E4) 
			{
                game_board[new_y][new_x] = " ";
                current_game.score += 30;
            } 
			else if (game_board[new_y][new_x] == "3" || 
                       game_board[new_y][new_x] == "2" || 
                       game_board[new_y][new_x] == "1") 
					   {
                if (game_board[new_y][new_x] == "3") game_board[new_y][new_x] = "2";
                else if (game_board[new_y][new_x] == "2") game_board[new_y][new_x] = "1";
                else if (game_board[new_y][new_x] == "1") game_board[new_y][new_x] = " ";
            	}
        }
    }
    if (bomb_y >= 0 && bomb_y < screen_hight && bomb_x >= 0 && bomb_x < screen_width) 
	{
        game_board[bomb_y][bomb_x] = " ";
    }
}


void handle_bombs() 
{
    for (int i = 0; i < MAX_BOMBS; i++) 
	{
        if (bombs[i].active) 
		{
            if (bombs[i].y <= 0 || game_board[bombs[i].y][bombs[i].x] == E1 ||
                game_board[bombs[i].y][bombs[i].x] == E2 || 
                game_board[bombs[i].y][bombs[i].x] == E3 || 
                game_board[bombs[i].y][bombs[i].x] == E4 ||
                game_board[bombs[i].y][bombs[i].x] == "3" ||
                game_board[bombs[i].y][bombs[i].x] == "2" || game_board[bombs[i].y][bombs[i].x] == "1") 
				{
                explode_bomb(bombs[i].x, bombs[i].y);
                bombs[i].active = false;
            	} 
			else 
			{
                game_board[bombs[i].y][bombs[i].x] = " ";
                bombs[i].y--;
                if (bombs[i].y >= 0) 
				{
                    game_board[bombs[i].y][bombs[i].x] = "⯐";
                }
            }
        }
    }
}



/*void explode_bomb2(int bomb_x, int bomb_y) 
{
    int dx[] = {0, 0, -1, 1, -1, -1, 1, 1};
    int dy[] = {-1, 1, 0, 0, -1, 1, -1, 1}; 
    for (int i = 0; i < 8; i++) 
	{
        int new_x = bomb_x + dx[i];
        int new_y = bomb_y + dy[i];
        if (new_x >= 0 && new_x < screen_width && new_y >= 0 && new_y < screen_hight) 
		{
            if (game_board[new_y][new_x] == "9" || 
                game_board[new_y][new_x] ==  "7"|| 
                game_board[new_y][new_x] == "6" ||
                game_board[new_y][new_x] == "5" ||
                game_board[new_y][new_x] ==  "4"||  
                game_board[new_y][new_x] == E4 ) 
			{
                game_board[new_y][new_x] = " ";
                current_game.score += 30;
            } 
			else if (game_board[new_y][new_x] == "3" || 
                       game_board[new_y][new_x] == "2" || 
                       game_board[new_y][new_x] == "1") 
					   {
                if (game_board[new_y][new_x] == "3") game_board[new_y][new_x] = "2";
                else if (game_board[new_y][new_x] == "2") game_board[new_y][new_x] = "1";
                else if (game_board[new_y][new_x] == "1") game_board[new_y][new_x] = " ";
            	}
        }
    }
    if (bomb_y >= 0 && bomb_y < screen_hight && bomb_x >= 0 && bomb_x < screen_width) 
	{
        game_board[bomb_y][bomb_x] = " ";
    }
}*/

/*void handle_bombs2() 
{
    for (int i = 0; i < MAX_BOMBS; i++) 
	{
        if (bombs[i].active) 
		{
            if (bombs[i].y <= 0 || game_board[new_y][new_x] == "9" || 
                game_board[new_y][new_x] ==  "7"|| 
                game_board[new_y][new_x] == "6" ||
                game_board[new_y][new_x] == "5" ||
                game_board[new_y][new_x] ==  "4"||
                game_board[bombs[i].y][bombs[i].x] == "3" ||
                game_board[bombs[i].y][bombs[i].x] == "2" || game_board[bombs[i].y][bombs[i].x] == "1") 
				{
                explode_bomb2(bombs[i].x, bombs[i].y);
                bombs[i].active = false;
            	} 
			else 
			{
                game_board[bombs[i].y][bombs[i].x] = " ";
                bombs[i].y--;
                if (bombs[i].y >= 0) 
				{
                    game_board[bombs[i].y][bombs[i].x] = "⯐";
                }
            }
        }
    }
}*/