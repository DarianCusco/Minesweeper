#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include "Board.h"
#include "Random.h"
#include "TextureManager.h"
#include "Tile.h"
#include <map>
  
using namespace std;

Board LoadBoard(string filename)
{
    fstream file;
    file.open(filename);

    int width;
    int height;
    int minecount;

    if (file.is_open())
    {
        string temp;
        getline(file, temp);
        width = stoi(temp);

        getline(file, temp);
        height = stoi(temp);

        getline(file, temp);
        minecount = stoi(temp);

        Board tempboard(width, height, minecount);
        return tempboard;
    }
}

bool Clicked(sf::RenderWindow& window, sf::Sprite& sprite)
{
    sf::Vector2f clickLocation = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    return sprite.getGlobalBounds().contains(clickLocation);
}

int main()
{
    //Sets up board and window
    Board board = LoadBoard("boards/config.cfg");
    sf::RenderWindow window(sf::VideoMode(board.getWidth() * 32, (board.getHeight() * 32) + 100), "MineSweeper");

    

    //load all textures
    sf::Sprite debug(TextureManager::GetTexture("debug"));
    sf::Sprite digits(TextureManager::GetTexture("digits"));
    sf::Sprite happyface(TextureManager::GetTexture("face_happy"));
    sf::Sprite loseface(TextureManager::GetTexture("face_lose"));
    sf::Sprite winface(TextureManager::GetTexture("face_win"));
    sf::Sprite flag(TextureManager::GetTexture("flag"));
    sf::Sprite mine(TextureManager::GetTexture("mine"));
    sf::Sprite test1(TextureManager::GetTexture("test_1"));
    sf::Sprite test2(TextureManager::GetTexture("test_2"));
    sf::Sprite test3(TextureManager::GetTexture("test_3"));
    sf::Sprite hiddentile(TextureManager::GetTexture("tile_hidden"));
    sf::Sprite revealedtile(TextureManager::GetTexture("tile_revealed"));



    sf::Sprite num1(TextureManager::GetTexture("number_1"));
    sf::Sprite num2(TextureManager::GetTexture("number_2"));
    sf::Sprite num3(TextureManager::GetTexture("number_3"));
    sf::Sprite num4(TextureManager::GetTexture("number_4"));
    sf::Sprite num5(TextureManager::GetTexture("number_5"));
    sf::Sprite num6(TextureManager::GetTexture("number_6"));
    sf::Sprite num7(TextureManager::GetTexture("number_7"));
    sf::Sprite num8(TextureManager::GetTexture("number_8"));
    
    map<int, sf::Sprite> numSprites;
    numSprites.emplace(1, num1);
    numSprites.emplace(2, num2);
    numSprites.emplace(3, num3);
    numSprites.emplace(4, num4);
    numSprites.emplace(5, num5);
    numSprites.emplace(6, num6);
    numSprites.emplace(7, num7);
    numSprites.emplace(8, num8);


    //Buttons
    happyface.setPosition(((board.getWidth() * 32) / 2) - 32, (board.getHeight() * 32));
    test1.setPosition(((board.getWidth() * 32) / 2) + 160, (board.getHeight() * 32));
    test2.setPosition(((board.getWidth() * 32) / 2) + 224, (board.getHeight() * 32));
    test3.setPosition(((board.getWidth() * 32) / 2) + 288, (board.getHeight() * 32));
    debug.setPosition(((board.getWidth() * 32) / 2) + 96, (board.getHeight() * 32));

    //Game Conditions
    bool debugMode = false;
    bool gameWon = false;
    bool gameLost = false;
    bool testcalled = false;
    int minesleft = board.getMineCount();

    //Default Tile
    Tile tile(hiddentile, revealedtile, mine, flag, false, false, false);
    vector<Tile> rowTile;

    //Game board
    vector<vector<Tile>> gameBoard;

    //sets board
    for (int i = 0; i < board.getWidth(); i++)
    {
        for (int j = 0; j < board.getHeight(); j++)
        {
            rowTile.push_back(tile);
        }
            
        gameBoard.push_back(rowTile);
        rowTile.clear();
    }

    map<int, sf::Sprite> digitSprite;
    sf::Vector2i rectSize(21, 32);

    sf::Vector2i position0(0, 0);
    sf::Sprite digit0 = tile.makeRect(digits, position0, rectSize);
    digitSprite.emplace(0, digit0);

    sf::Vector2i position1(21, 0);
    sf::Sprite digit1 = tile.makeRect(digits, position1, rectSize);
    digitSprite.emplace(1, digit1);

    sf::Vector2i position2(42, 0);
    sf::Sprite digit2 = tile.makeRect(digits, position2, rectSize);
    digitSprite.emplace(2, digit2);

    sf::Vector2i position3(63, 0);
    sf::Sprite digit3 = tile.makeRect(digits, position3, rectSize);
    digitSprite.emplace(3, digit3);

    sf::Vector2i position4(84, 0);
    sf::Sprite digit4 = tile.makeRect(digits, position4, rectSize);
    digitSprite.emplace(4, digit4);

    sf::Vector2i position5(105, 0);
    sf::Sprite digit5 = tile.makeRect(digits, position5, rectSize);
    digitSprite.emplace(5, digit5);

    sf::Vector2i position6(126, 0);
    sf::Sprite digit6 = tile.makeRect(digits, position6, rectSize);
    digitSprite.emplace(6, digit6);

    sf::Vector2i position7(147, 0);
    sf::Sprite digit7 = tile.makeRect(digits, position7, rectSize);
    digitSprite.emplace(7, digit7);

    sf::Vector2i position8(168, 0);
    sf::Sprite digit8 = tile.makeRect(digits, position8, rectSize);
    digitSprite.emplace(8, digit8);

    sf::Vector2i position9(189, 0);
    sf::Sprite digit9 = tile.makeRect(digits, position9, rectSize);
    digitSprite.emplace(9, digit9);

    sf::Vector2i positionNeg(210, 0);
    sf::Sprite digitNeg = tile.makeRect(digits, positionNeg, rectSize);
    digitSprite.emplace(-1, digitNeg);
    
    while (window.isOpen())
    {
        window.clear(sf::Color(255, 255, 255));
        sf::Vector2i position = sf::Mouse::getPosition();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
            while (board.getMineCount() > 0 && !testcalled)
            {
                int x = Random::rollInt(0, (board.getWidth() - 1));
                int y = Random::rollInt(0, (board.getHeight() - 1));

                if (!gameBoard[x][y].IsMine())
                {
                    gameBoard[x][y].setMine(true);
                    board.lowerMineCount();
                }
            }
            
            if (event.type = sf::Event::MouseButtonPressed)
                sf::Vector2i position = sf::Mouse::getPosition(window);

                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (Clicked(window, happyface))
                    {
                        cout << "Clicked on Happy Face" << endl;
                        for (int i = 0; i < board.getWidth(); i++)
                        {
                            for (int j = 0; j < board.getHeight(); j++)
                            {
                                gameBoard[i][j].setMine(false);
                                gameBoard[i][j].setFlagged(false);
                                gameBoard[i][j].setReveal(false);
                                gameBoard[i][j].setChecked(false);
                            }
                        }
                        gameLost = false;
                        gameWon = false;
                        testcalled = false;
                        debugMode = false;
                        board = LoadBoard("boards/config.cfg");
                        minesleft = board.getMineCount();
                        board.setMineCount(minesleft);

                        
                    }

                    if (Clicked(window, debug))
                    {
                        debugMode = true;
                        cout << "Clicked on Debug" << endl;
                    }
                    if (Clicked(window, test1))
                    {
                        testcalled = true;
                        board.loadTestBoard("boards/testboard1.brd", gameBoard);
                        minesleft = board.getMineCount();
                        board.setMineCount(minesleft);

                    }
                    if (Clicked(window, test2))
                    {
                        testcalled = true;
                        board.loadTestBoard("boards/testboard2.brd", gameBoard);
                        minesleft = board.getMineCount();
                        board.setMineCount(minesleft);

                    }
                    if (Clicked(window, test3))
                    {
                        testcalled = true;
                        board.loadTestBoard("boards/testboard3.brd", gameBoard);
                        minesleft = board.getMineCount();
                        board.setMineCount(minesleft);


                    }
                    if (!gameWon && !gameLost)
                    {
                        for (int i = 0; i < board.getHeight(); i++)
                        {
                            for (int j = 0; j < board.getWidth(); j++)
                            {
                                if (Clicked(window, gameBoard[j][i].getHidden()))
                                {
                                    cout << "Clicked on Tile" << endl;

                                    if (gameBoard[j][i].IsMine())
                                    {
                                        gameBoard[j][i].setReveal(true);
                                        gameLost = true;
                                        cout << "bomb" << endl;
                                    }
                                    else
                                    {
                                        gameBoard[j][i].setReveal(true);
                                        board.tileReveal(gameBoard, j, i);
                                        cout << "not a mine" << endl;
                                    }
                                }
                            }
                        }
                    }
            }
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    if (!gameLost && !gameWon)
                    {
                        for (int i = 0; i < board.getWidth(); i++)
                        {
                            for (int j = 0; j < board.getHeight(); j++)
                            {
                                if (Clicked(window, gameBoard[i][j].getHidden()))
                                {
                                    if (!gameBoard[i][j].IsFlagged())
                                    {
                                        gameBoard[i][j].setFlagged(true);
                                        cout << "Flag set" << endl;
                                        minesleft--;
                                    }
                                    else
                                    {
                                        gameBoard[i][j].setFlagged(false);
                                        cout << "Flag Removed" << endl;
                                        minesleft++;
                                    }
                                }
                            }
                        }
                    }
                }
        }
        
        string stringMines = to_string(minesleft);

        //If theres one digit
        if (stringMines[0] == '-')
        {
            digitSprite[-1].setPosition(0, board.getHeight() * 32);
            window.draw(digitSprite[-1]);
        }
        if (stringMines.length() == 1)
        {
            int strnum = int(stringMines[0]) - 48;
            digitSprite[strnum].setPosition(0, board.getHeight() * 32);
            window.draw(digitSprite[int(strnum)]);

            
        }
        if (stringMines.length() == 2)
        {
            int strnum1 = int(stringMines[0]) - 48;
            digitSprite[strnum1].setPosition(0, board.getHeight() * 32);
            window.draw(digitSprite[int(strnum1)]);

            int strnum2 = int(stringMines[1]) - 48;
            digitSprite[strnum2].setPosition(21, board.getHeight() * 32);
            window.draw(digitSprite[int(strnum2)]);
        }
        if (stringMines.length() == 3)
        {
            int strnum1 = int(stringMines[0]) - 48;
            digitSprite[strnum1].setPosition(0, board.getHeight() * 32);
            window.draw(digitSprite[int(strnum1)]);

            int strnum2 = int(stringMines[1]) - 48;
            digitSprite[strnum2].setPosition(21, board.getHeight() * 32);
            window.draw(digitSprite[int(strnum2)]);


            int strnum3 = int(stringMines[2]) - 48;
            digitSprite[strnum3].setPosition(42, board.getHeight() * 32);
            window.draw(digitSprite[int(strnum3)]);
        }
        if (stringMines.length() == 4)
        {
            int strnum1 = int(stringMines[0]) - 48;
            digitSprite[strnum1].setPosition(0, board.getHeight() * 32);
            window.draw(digitSprite[int(strnum1)]);

            int strnum2 = int(stringMines[1]) - 48;
            digitSprite[strnum2].setPosition(21, board.getHeight() * 32);
            window.draw(digitSprite[int(strnum2)]);


            int strnum3 = int(stringMines[2]) - 48;
            digitSprite[strnum3].setPosition(42, board.getHeight() * 32);
            window.draw(digitSprite[int(strnum3)]);

            int strnum4 = int(stringMines[3]) - 48;
            digitSprite[strnum4].setPosition(63, board.getHeight() * 32);
            window.draw(digitSprite[int(strnum4)]);
        }





        for (int i = 0; i < board.getWidth(); i++)
        {
            for (int j = 0; j < board.getHeight(); j++)
            {
                gameBoard[i][j].getHidden().setPosition(i * 32, j * 32);
                window.draw(gameBoard[i][j].getHidden());

                int minesNear = board.minesNearby(gameBoard, i, j);

                if (gameBoard[i][j].isRevealed())
                {
                    if (gameBoard[i][j].IsMine())
                    {
                        gameBoard[i][j].getMine().setPosition(i * 32, j * 32);
                        window.draw(gameBoard[i][j].getMine());
                    }
                    
                    else
                    {
                        gameBoard[i][j].getRevealed().setPosition(i * 32, j * 32);
                        window.draw(gameBoard[i][j].getRevealed());
                        if (minesNear!= 0)
                        {
                            window.draw(gameBoard[i][j].getNum());
                        }
                    }

                    if (minesNear > 0)
                    {
                        numSprites[minesNear].setPosition(i * 32, j * 32);
                        window.draw(numSprites[minesNear]);
                    }
                
                }
                else
                {
                    if (gameBoard[i][j].IsFlagged())
                    {
                        gameBoard[i][j].getFlag().setPosition(i * 32, j * 32);
                        window.draw(gameBoard[i][j].getFlag());
                    }
                }
                if (debugMode == true)
                {
                    if (gameBoard[i][j].IsMine())
                    {
                        gameBoard[i][j].getMine().setPosition(i * 32, j * 32);
                        window.draw(gameBoard[i][j].getMine());
                    }
                }
                if (gameLost == true)
                {
                    loseface.setPosition(((board.getWidth() * 32) / 2) - 32, (board.getHeight() * 32));
                    window.draw(loseface);

                    if (gameBoard[i][j].IsMine())
                    {
                        gameBoard[i][j].getMine().setPosition(i * 32, j * 32);
                        window.draw(gameBoard[i][j].getMine());
                    }
                }
                if ((board.getTileCount() - 1) == 0)
                {
                    gameWon = true;
                    winface.setPosition(((board.getWidth() * 32) / 2) - 32, (board.getHeight() * 32));
                }
            }
        }
        if (gameLost != true)
            window.draw(happyface);
        if (gameWon == true)
            window.draw(winface);

        window.draw(test1);
        window.draw(test2);
        window.draw(test3);
        window.draw(debug);

        window.display();
    }
    return 0;
}
