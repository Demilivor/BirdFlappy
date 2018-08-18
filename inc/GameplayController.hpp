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

#include "inc/Bird.hpp"
#include "inc/ScoresTable.hpp"
#include "inc/Button.hpp"
#include "inc/RepeatableTextureRect.hpp"
#include "inc/PipesGenerator.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <memory>

namespace BirdFlappy
{

class GameplayController : public GameObject
{
public:
    enum State
    {
        Started,
        Paused,
        PlayerDead
    };

    GameplayController( );

    void process( ) override;
    void handleEvent( const sf::Event& event );
    void reset( ) override;

    void updateScores();
    void pause();
    void resume();

private:
    static constexpr float PLAYER_SIZE                  = 100.f;
    static constexpr float PLAYER_COLLISION_SIZE        = PLAYER_SIZE - 40.f;
    static constexpr float SIDES_FALL_PENALTY           = 15.f;
    static constexpr float PIPE_MOVE_SPEED              = -300.f;
    static constexpr sf::Int32 BACKGROUND_PIXEL_PER_MS  = 90;
    static constexpr sf::Int32 CLOUDS_PIXEL_PER_MS      = 25 ;

    Gui::Button m_exitButton;
    Gui::Button m_restartButton;
    Gui::Button m_pauseButton;
    Gui::Button m_resumeButton;

    sf::Text m_scoreText;
    RepeatableTextureRect m_backGround;
    RepeatableTextureRect m_clouds;
    Bird m_player;
    PipesGenerator m_pipesGenerator;

    uint32_t m_curScore         = 0;
    State m_state               = Started;
    sf::Clock m_clock;
    sf::Sound m_sound;

    void createButtons( );

    void playerDeath();
};

}
