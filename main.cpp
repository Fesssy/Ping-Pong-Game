#include <iostream>
#include <time.h>
#include <conio.h>

using namespace std;

// Enumeration type for directions of ball
enum Directions
{
    STOP = 0,
    LEFT,
    UPLEFT,
    DOWNLEFT,
    RIGHT,
    UPRIGHT,
    DOWNRIGHT
};

// Class which containing properties of balls
class Ball
{
    // x and y co-ordinate
    int x, y;

    // Direction for ball
    Directions direction;

public:
    Ball()
    {
        // Non-Parameterized constructor - setting ball in center without moving
        x = 20;
        y = 10;
        direction = STOP;
    }

    void Reset()
    {
        // Resetting ball to initial position and state
        x = 20;
        y = 10;
        direction = STOP;
    }

    void Change_direction(Directions d)
    {
        // Changing the direction of ball depending on the parameter
        direction = d;
    }

    // Returning Direction and co-ordinates
    inline Directions get_direction()
    {
        return direction;
    }
    inline int get_x()
    {
        return x;
    }
    inline int get_y()
    {
        return y;
    }

    // Function to move the ball according to direction
    void Move()
    {
        switch (direction)
        {
        case STOP:
            break;

        case LEFT:
            x--;
            break;

        case RIGHT:
            x++;
            break;

        case UPLEFT:
            x--;
            y--;
            break;

        case UPRIGHT:
            x++;
            y--;
            break;

        case DOWNLEFT:
            x--;
            y++;
            break;

        case DOWNRIGHT:
            x++;
            y--;
            break;

        default:
            break;
        }
    }
};

// Class containing properties of paddle / player
class Paddle
{
    // x and y co-ordinates
    int x, y;
    int ox, oy;

public:
    Paddle(int pos_x, int pos_y)
    {
        // Parameterized Constructor - setting the position
        ox = x = pos_x;
        oy = y = pos_y;
    }

    void Reset()
    {
        x = ox;
        y = oy;
    }

    // Returning co-ordinates
    inline int get_x()
    {
        return x;
    }
    inline int get_y()
    {
        return y;
    }

    // Paddle Movements
    inline void move_up()
    {
        y--;
    }
    inline void move_down()
    {
        y++;
    }
};

// Game Manager to setup the game (Drawing, Logical unit, Input Processing) and to manage it.
class Game_manager
{
    // Declaring dimension of the game
    int width, height;

    // Declaring the state of the game
    bool quit;

    // Declaring pointer to players(Paddle)
    Paddle *player1, *player2;

    // Declaring pointer to the ball
    Ball *ball;

    // Recording scores
    int score1, score2;

    // Co-ordinates variable
    int ball_x, ball_y, player1_x, player1_y, player2_x, player2_y;

public:
    // Default parameter
    Game_manager()
    {
        srand(time(NULL));
        width = 40;
        height = 20;
        quit = false;
        score1 = score2 = 0;
        player1 = new Paddle(2, 7);
        player2 = new Paddle(width - 2, 7);
        ball = new Ball();
    }

    // Storing co-ordinates
    void get_coordinates()
    {
        ball_x = ball->get_x();
        ball_y = ball->get_y();
        player1_x = player1->get_x();
        player1_y = player1->get_y();
        player2_x = player2->get_x();
        player2_y = player2->get_y();
    }

    // Destructor - to free up space
    ~Game_manager()
    {
        delete ball, player1, player2;
    }

    // Displaying the game
    void Draw()
    {
        // Clearing the screen
        system("cls");

        // Invoking function to storing co-ordinates
        get_coordinates();

        // Upper Wall
        // '\xB2' -> a character from windows for displaying wall
        for (int i = 0; i < width + 1; i++)
            cout << "\xB2";

        cout << endl;

        // Side Walls, ball and players
        //  i -> y co-ordinate
        //  j -> x co-ordinate
        for (int i = 0; i < height + 1; i++)
        {
            for (int j = 0; j < width + 1; j++)
            {
                // Left Side wall
                if (j == 0)
                    cout << "\xB2";

                // Displaying Ball
                else if (ball_x == j && ball_y == i)
                    cout << "o";

                // Displaying player(paddle)
                // player1
                else if (player1_x == j && player1_y == i)
                    cout << "\xDB";

                else if (player1_x == j && player1_y + 1 == i)
                    cout << "\xDB";

                else if (player1_x == j && player1_y + 2 == i)
                    cout << "\xDB";

                else if (player1_x == j && player1_y + 3 == i)
                    cout << "\xDB";

                // player2
                else if (player2_x == j && player2_y == i)
                    cout << "\xDB";

                else if (player2_x == j && player2_y + 1 == i)
                    cout << "\xDB";

                else if (player2_x == j && player2_y + 2 == i)
                    cout << "\xDB";

                else if (player2_x == j && player2_y + 3 == i)
                    cout << "\xDB";

                // Empty spaces
                else
                    cout << " ";

                // Right Side Wall
                if (j == width - 1)
                    cout << "\xB2";
            }

            cout << endl;
        }

        // Bottom walls
        for (int i = 0; i < width + 1; i++)
            cout << "\xB2";

        cout << endl;

        // Displaying score
        cout << "Score for Player 1 : " << score1 << endl;
        cout << "Score for Player 2 : " << score2 << endl;

        cout << "\n Enter 'q' to quit the game.";
    }

    // Input Processor - managing the inputs by user / player
    void Input()
    {
        // Mainly we are going to deal with movement of paddle
        // Therefore adding all movements related thing here for less complication

        // Making ball move
        ball->Move();

        // When a key is enter
        if (_kbhit())
        {
            // Storing the key pressed
            char key = _getch();

            // Paddle movements according to key
            if (key == 'w' && player1_y > 0)
                player1->move_up();
            if (key == 's' && player1_y + 3 < 41)
                player1->move_down();
            if (key == 'o' && player2_y > 0)
                player2->move_up();
            if (key == 'l' && player2_y + 3 < 41)
                player2->move_down();

            // Changing the direction of ball
            if (ball->get_direction() == STOP)
                ball->Change_direction(Directions(rand() % 6 + 1));

            // Quitting the game
            if (key == 'q')
                quit = true;
        }
    }

    // Logical unit of the game
    void Logic()
    {
        // Collision of ball with player
        // As paddle body is 4 unit long
        for (int i = 0; i < 4; i++)
        {
            // Collision with player1
            if (ball_x == player1_x + 1 && ball_y == player1_y + i)
                ball->Change_direction(Directions(rand() % 3 + 4));

            // Collision with player2
            if (ball_x == player2_x - 1 && ball_y == player2_y + i)
                ball->Change_direction(Directions(rand() % 3 + 1));
        }

        // Collision with walls

        // Collision with up and down walls
        if (ball_y == 0)
            ball->Change_direction(ball->get_direction() == UPRIGHT ? DOWNRIGHT : DOWNLEFT);
        if (ball_y == height)
            ball->Change_direction(ball->get_direction() == DOWNRIGHT ? UPRIGHT : UPLEFT);

        // Collision with side walls
        if (ball_x == 1)
            Scoreup(player2);
        if (ball_x == width - 2)
            Scoreup(player1);
    }

    // Score function to update scores
    void Scoreup(Paddle *player)
    {
        if (player == player1)
            score1++;
        if (player == player2)
            score2++;

        ball->Reset();
        player1->Reset();
        player2->Reset();
    }

    void run()
    {
        while (!quit)
        {
            Draw();
            Input();
            Logic();
        }
    }
};

int main()
{
    Game_manager Game;
    Game.run();
    return 0;
}
