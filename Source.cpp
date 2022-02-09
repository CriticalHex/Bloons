#include <SFML/Graphics.hpp>
#include <vector>
#include<iostream>
#include "Source.h"


//create a struct: structs are like classes, but no functions (just variables)
struct point {
    int x;
    int y;
};

class Bloon
{
public:
    Bloon(int x, int y);
    ~Bloon();
    void move(std::vector<point>myPath, std::vector<Bloon*>BloonBag, std::vector<Bloon*>::iterator iter);
    void draw(sf::RenderWindow& window);

private:
    int xpos;
    int ypos;
    int currPath;
    sf::Texture redBloon;
    sf::IntRect bloon;
    sf::Sprite bloonRed;
};




int map[16][16] = {
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,1,1,1,1,0,1,1,1,1,1,0,
    0,0,0,0,0,1,0,0,1,0,1,0,0,0,1,0,
    0,0,0,0,0,1,0,0,1,0,1,0,0,0,1,0,
    1,1,1,1,1,1,1,1,1,0,1,0,0,0,1,0,
    0,0,0,0,0,1,0,0,0,0,1,0,0,0,1,0,
    0,0,1,1,1,1,1,1,1,1,1,0,0,0,1,0,
    0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,
    0,0,1,0,0,1,0,0,1,1,1,1,1,1,1,0,
    0,0,1,1,1,1,0,0,1,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0
};


int main()
{
    //set up path points using the struct we made
    struct point p1;
    p1.x = 9*50;
    p1.y = 6*50;
    struct point p2;
    p2.x = 9*50;
    p2.y = 3*50;
    struct point p3;
    p3.x = 6*50;
    p3.y = 3*50;
    struct point p4;
    p4.x = 6*50;
    p4.y = 11*50;
    struct point p5;
    p5.x = 3*50;
    p5.y = 11*50;
    struct point p6;
    p6.x = 3*50;
    p6.y = 8*50;
    struct point p7;
    p7.x = 11*50;
    p7.y = 8*50;
    struct point p8;
    p8.x = 11*50;
    p8.y = 3*50;
    struct point p9;
    p9.x = 15*50;
    p9.y = 3*50;
    struct point p10;
    p10.x = 15*50;
    p10.y = 10*50;
    struct point p11;
    p11.x = 9*50;
    p11.y = 10*50;
    struct point p12;
    p12.x = 9*50;
    p12.y = 16*50;


    //set up vector to hold path points, push path points into it
    std::vector <point> pathPoints;
    pathPoints.push_back(p1);
    pathPoints.push_back(p2);
    pathPoints.push_back(p3);
    pathPoints.push_back(p4);
    pathPoints.push_back(p5);
    pathPoints.push_back(p6);
    pathPoints.push_back(p7);
    pathPoints.push_back(p8);
    pathPoints.push_back(p9);
    pathPoints.push_back(p10);
    pathPoints.push_back(p11);
    pathPoints.push_back(p12);

    std::vector<Bloon*> BloonBag;
    std::vector<Bloon*>::iterator iter;


    // create game window
    sf::RenderWindow window(sf::VideoMode(800, 800), "bloons");

    sf::Texture stone;
    stone.loadFromFile("stone.png");
    sf::Sprite path;
    path.setTexture(stone);

    sf::Texture grass;
    grass.loadFromFile("grass.png");
    sf::Sprite field;
    field.setTexture(grass);

    

    int currPath = 0; //begin heading towards the first point in the pathing vector
    int ticker = 0;

    for (int i = 0; i < 10; i++) {
        Bloon* bloon = new Bloon(-50 - (i * 50), 7 * 50);
        BloonBag.push_back(bloon);
    }

    /*Bloon bloon1 = Bloon(-50, 7 * 50);
    Bloon bloon2 = Bloon(-100, 7 * 50);
    Bloon bloon3 = Bloon(-150, 7 * 50);
    Bloon bloon4 = Bloon(-200, 7 * 50);*/

    // GAME LOOP----------------------------------------------------------------------------------------
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }



        //pathing algorithm*******************************************************************
        //this works by moving the x and y coord of our baloon towards the (x,y) of the next point in the path
        //the path is stored as a series of points in a vector called "pathPoints"

        ticker++; //slow dem bloons down
        if (ticker % 2 == 0) { //make 30 bigger to slow down baloon more

            for (iter = BloonBag.begin(); iter != BloonBag.end(); iter++) 
                (*iter)->move(pathPoints,BloonBag,iter);
            
        }//end pathing algorithm**************************************************************

        // Render section----------------------------------------------------------------
        window.clear(sf::Color::Black);

        for (int rows = 0; rows < 16; rows++)
            for (int cols = 0; cols < 16; cols++) {
                if (map[rows][cols] == 1) {
                    path.setPosition(cols * 50, rows * 50);
                    window.draw(path);
                }
                if (map[rows][cols] == 0) {
                    field.setPosition(cols * 50 + 5, rows * 50 + 5);
                    window.draw(field);
                }
            }

        for (iter = BloonBag.begin(); iter != BloonBag.end(); iter++)
            (*iter)->draw(window);
        window.display();
    }

    return 0;//buh bye
}

Bloon::Bloon(int x, int y)
{
    xpos = x;
    ypos = y;
    currPath = 0;
    redBloon.loadFromFile("bloon.png");
    bloon = sf::IntRect(0, 0, 50, 50);
    bloonRed = sf::Sprite(redBloon, bloon);
}

Bloon::~Bloon()
{
}

void Bloon::move(std::vector<point>myPath,std::vector<Bloon*>BloonBag, std::vector<Bloon*>::iterator iter) {
    //first check if you're at the turning point, move to next point if you are
    if ((xpos == myPath[currPath].x) && (ypos == myPath[currPath].y))
        if (currPath < myPath.size() - 1) //don't walk off end of vector!
            currPath++; //iterate to next point
    

    //if not there yet, move our x towards x position of next junction
    if (xpos < myPath[currPath].x) {
        //std::cout << xpos << " > ";
        xpos += 1;
        //std::cout << xpos << ".\n";
    }
    if (xpos > myPath[currPath].x) {
        //std::cout << xpos << " > ";
        xpos -= 1;
        //std::cout << xpos << ".\n";
    }
    //and move our y towards y position of next junction
    if (ypos < myPath[currPath].y) {
        //std::cout << ypos << " > ";
        ypos += 1;
        //std::cout << ypos << ".\n";
    }
    if (ypos > myPath[currPath].y) {
        //std::cout << ypos << " > ";
        ypos -= 1;
        //std::cout << ypos << ".\n";
    }
    for (iter = BloonBag.begin(); iter != BloonBag.end(); iter++)
        if (xpos == 9 * 50 && ypos == 16 * 50) { 
                (*iter)->~Bloon();
        }
}

void Bloon::draw(sf::RenderWindow& window) {
    //std::cout << xpos << ", " << ypos << "\n";
    bloonRed.setPosition(xpos-50, ypos-50);
    window.draw(bloonRed);
}