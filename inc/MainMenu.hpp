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

#include "inc/Button.hpp"
#include "inc/GameObject.hpp"
#include "inc/ScoresTable.hpp"

#include <SFML/Graphics.hpp>

#include <memory>

namespace BirdFlappy
{

class MainMenu : public GameObject
{
public:
    enum State
    {
        LobbyMenu,
        ScoresMenu
    };

    MainMenu( );

    void process( ) override;
    void handleEvent( const sf::Event& event );

private:
    Gui::Button m_startButton{ };
    Gui::Button m_scoresButton{ };
    Gui::Button m_exitButton{ };
    Gui::Button m_backButton{ };

    sf::RectangleShape m_backGround;
    sf::RectangleShape m_scoresBackGround;
    sf::Text m_scoresLabelText;
    sf::Text m_scoresValuesText;

    State m_state = LobbyMenu;

    void createButtons( );
    void createScoresTable( );
};

}
