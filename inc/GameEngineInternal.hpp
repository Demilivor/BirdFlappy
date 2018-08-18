/*
 * Copyright (c) 2017 Alexey Gerasimchuk
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include "inc/GameEngine.hpp"
#include "inc/GameResources.hpp"

#include <SFML/Graphics.hpp>


#include <string>

namespace BirdFlappy
{

static constexpr float BUTTON_DISTANCE  = 220.f;
static constexpr float BUTTON_WIDTH     =  400.f;
static constexpr float BUTTON_HEIGHT    =  100.f;
static constexpr unsigned int BUTTON_DEFAULT_TEXT_SIZE  = 80;
static constexpr float PAUSE_BUTTON_WIDTH = BUTTON_WIDTH / 2.f;
static constexpr float PAUSE_BUTTON_HEIGHT = BUTTON_HEIGHT / 2.f;
static constexpr float PAUSE_BUTTON_POSITION_X = 1550;
static constexpr float PAUSE_BUTTON_POSITION_Y = 100;

namespace GameEngine
{
    static constexpr unsigned int GLOBAL_VIEW_WIDTH         = 1920;
    static constexpr unsigned int GLOBAL_VIEW_HEIGHT        = 1080;
    static constexpr size_t SCORES_TABLE_SIZE               = 5;


    void createGameWindow( const std::string& windowLabel );
    ErrorCode gameMainLoop();
    void stopGame();
    void startGameplay();
    void enterMainMenu();
    ErrorCode loadGameResources();
    void closeWindow();
    const GameResources& getGameResources( );
    sf::RenderWindow& getRenderWindow();
    ScoresTable& getScoresTable();
}

}
