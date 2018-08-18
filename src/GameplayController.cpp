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

#include "inc/GameplayController.hpp"
#include "inc/GameEngine.hpp"

#include "thirdParty/collision/Collision.hpp"

#include <sstream>

namespace BirdFlappy
{

GameplayController::GameplayController( ) :
    m_pipesGenerator{ GameEngine::get().getGameResources().pipeTexure }
{
    createButtons( );
    const GameResources& resources = GameEngine::get().getGameResources();
    m_scoreText.setFont( resources.font );
    m_scoreText.setColor( sf::Color::Yellow );
    m_scoreText.setCharacterSize( BUTTON_DEFAULT_TEXT_SIZE );
    m_scoreText.setString( "0" );
    m_scoreText.setPosition( GameEngine::GLOBAL_VIEW_WIDTH / 2.0f, 128.f  );

    sf::IntRect textureRect{};
    textureRect.width =  GameEngine::get().getRenderWindow().getSize().x;
    textureRect.height = GameEngine::get().getRenderWindow().getSize().y;
    m_backGround.setTexture( &resources.gameplayBackgroundTexture, textureRect );

    sf::FloatRect fullscreenRect{};
    fullscreenRect.width  = GameEngine::GLOBAL_VIEW_WIDTH;
    fullscreenRect.height = GameEngine::GLOBAL_VIEW_HEIGHT;

    m_backGround.setSpriteRect( fullscreenRect );

    m_clouds.setTexture( &resources.cloudsTexure, textureRect );
    m_clouds.setSpriteRect( fullscreenRect );

    for ( const sf::Texture& animationFrameTex : resources.birdAnimation )
    {
        AnimatedSprite::AnimationFrame animationFrame;
        animationFrame.animationTime        = sf::milliseconds(70);
        animationFrame.texture              = &animationFrameTex;
        animationFrame.textureRect.width    = animationFrameTex.getSize().x;
        animationFrame.textureRect.height   = animationFrameTex.getSize().y;

        m_player.addAnimationFrame( animationFrame );
    }

    sf::FloatRect playerRect{};
    playerRect.width = PLAYER_SIZE;
    playerRect.height = PLAYER_SIZE;

    m_player.setSpriteRect( playerRect );

    m_player.setCollisionDetectorSize( sf::Vector2f( PLAYER_COLLISION_SIZE, PLAYER_COLLISION_SIZE ) );

    m_sound.setBuffer( resources.soundOnDeath );

    reset();
}

void GameplayController::createButtons(  )
{
    const GameResources& resources = GameEngine::get().getGameResources();

    float yCenter = GameEngine::GLOBAL_VIEW_HEIGHT / 2.0f;
    sf::FloatRect buttonRect;
    buttonRect.width     = BUTTON_WIDTH;
    buttonRect.height    = BUTTON_HEIGHT;
    buttonRect.left      = ( ( GameEngine::GLOBAL_VIEW_WIDTH / 2.0f ) - ( buttonRect.width / 2.0f ) );
    buttonRect.top       = yCenter - BUTTON_DISTANCE;

    sf::Vector2f textPosition;
    textPosition.x = buttonRect.left + ( buttonRect.width / 2.f );
    textPosition.y = buttonRect.top  + ( buttonRect.height / 4.f );


    m_resumeButton.setNormalTexture( &resources.normalButTexture );
    m_resumeButton.setHoverTexture( &resources.hoverButTexture );
    m_resumeButton.setButtonRect( buttonRect );
    m_resumeButton.setFont( resources.font );
    m_resumeButton.setFontSize( BUTTON_DEFAULT_TEXT_SIZE );
    m_resumeButton.setFontStyle( sf::Text::Bold );
    m_resumeButton.setTextPosition(  textPosition );
    m_resumeButton.setFontColor( sf::Color::Green );

    m_resumeButton.setText( "Resume" );
    m_resumeButton.setCallback( [this]()
    {
        this->resume();
    } );

    buttonRect.top  = yCenter;
    textPosition.y  = buttonRect.top + ( buttonRect.height / 4.f );

    m_restartButton.setNormalTexture( &resources.normalButTexture );
    m_restartButton.setHoverTexture( &resources.hoverButTexture );
    m_restartButton.setButtonRect( buttonRect );
    m_restartButton.setFont( resources.font );
    m_restartButton.setFontSize( BUTTON_DEFAULT_TEXT_SIZE );
    m_restartButton.setFontStyle( sf::Text::Bold );
    m_restartButton.setTextPosition(  textPosition );
    m_restartButton.setFontColor( sf::Color::Green );
    m_restartButton.setText( "Restart" );
    m_restartButton.setCallback( [this]()
    {
        if ( this->m_state != PlayerDead )
        {
            // In case of dead player, score already stored
            this->updateScores();
        }

        this->reset();
    } );

    buttonRect.top  = yCenter + BUTTON_DISTANCE;
    textPosition.y  = buttonRect.top + ( buttonRect.height / 4.f );

    m_exitButton.setNormalTexture( &resources.normalButTexture );
    m_exitButton.setHoverTexture( &resources.hoverButTexture );
    m_exitButton.setButtonRect( buttonRect );
    m_exitButton.setFont( resources.font );
    m_exitButton.setFontSize( BUTTON_DEFAULT_TEXT_SIZE );
    m_exitButton.setFontStyle( sf::Text::Bold );
    m_exitButton.setTextPosition(  textPosition );
    m_exitButton.setFontColor( sf::Color::Green );
    m_exitButton.setText( "Exit" );

    m_exitButton.setCallback( [=]()
    {
        if ( this->m_state != PlayerDead )
        {
            // In case of dead player, score already stored
            this->updateScores();
        }
        GameEngine::get().enterMainMenu();
    } );

    buttonRect.width    = PAUSE_BUTTON_WIDTH;
    buttonRect.height   = PAUSE_BUTTON_HEIGHT;
    buttonRect.left     = PAUSE_BUTTON_POSITION_X;
    buttonRect.top      = PAUSE_BUTTON_POSITION_Y;

    textPosition.x  = buttonRect.left + ( buttonRect.width / 2.f );
    textPosition.y  = buttonRect.top + ( buttonRect.height / 4.f );

    m_pauseButton.setNormalTexture( &resources.normalButTexture );
    m_pauseButton.setHoverTexture( &resources.hoverButTexture );
    m_pauseButton.setButtonRect( buttonRect );
    m_pauseButton.setFont( resources.font );
    m_pauseButton.setFontSize( BUTTON_DEFAULT_TEXT_SIZE / 2 );
    m_pauseButton.setFontStyle( sf::Text::Bold );
    m_pauseButton.setTextPosition(  textPosition );
    m_pauseButton.setFontColor( sf::Color::Green );
    m_pauseButton.setText( "Pause" );

    m_pauseButton.setCallback( [&]()
    {
        pause();
    } );
}

void GameplayController::reset( )
{
    m_state = Started;
    m_clock.restart();
    m_state = Started;
    m_backGround.setTimePerPixel( sf::milliseconds( BACKGROUND_PIXEL_PER_MS ) );
    m_clouds.setTimePerPixel( sf::milliseconds( CLOUDS_PIXEL_PER_MS ) );

    m_backGround.reset();
    m_clouds.reset();
    m_player.reset();

    sf::Vector2f position;
    position.x = 200.f;
    position.y = GameEngine::GLOBAL_VIEW_HEIGHT * 0.25;
    m_player.setPosition( position );
    m_curScore = 0;

    m_pipesGenerator.reset();
}

void GameplayController::pause( )
{
    m_state = Paused;
    m_backGround.stop();
    m_clouds.stop();
    m_player.stop();
    m_pipesGenerator.stop();
}

void GameplayController::resume( )
{
    m_state = Started;
    m_clock.restart();
    m_backGround.start();
    m_clouds.start();
    m_player.start();
    m_pipesGenerator.start();
}

void GameplayController::updateScores()
{
    GameEngine::get().getScoresTable().addScore( m_curScore );
}

void GameplayController::playerDeath()
{
    m_state = PlayerDead;
    m_pipesGenerator.stop();
    updateScores();

    m_sound.play();
}

void GameplayController::process()
{
    m_backGround.process( );
    m_clouds.process();

    float period = (float)m_clock.restart().asMilliseconds();
    if ( m_state == Started )
    {
        ++m_curScore;
        // std::to_string not work, gcc bug
        std::stringstream ss;
        ss << m_curScore;
        m_scoreText.setString( ss.str() );

        if ( ( ( m_player.getPosition().y - SIDES_FALL_PENALTY ) > GameEngine::GLOBAL_VIEW_HEIGHT )  ||
             ( (  m_player.getPosition().y +  SIDES_FALL_PENALTY ) < 0.f ) )
        {
            playerDeath();
        }
    }

    m_pipesGenerator.process();

    for ( auto& pipe : m_pipesGenerator.getSprites() )
    {
        if ( m_state == Started )
        {
            pipe.move( PIPE_MOVE_SPEED * ( period / 1000.f ), 0.f );

            if ( collision::areColliding( m_player.getCollisionDetector(), pipe ) )
            {
                playerDeath();
            }
        }

        GameEngine::get().getRenderWindow().draw( pipe );
    }

    m_player.process();
    GameEngine::get().getRenderWindow().draw( m_scoreText );

    switch ( m_state )
    {
        case Started:
        {
            m_pauseButton.process();
            break;
        }
        case PlayerDead:
        {
            m_exitButton.process();
            m_restartButton.process();
            break;
        }
        case Paused:
        {
            m_exitButton.process();
            m_restartButton.process();
            m_resumeButton.process();
            break;
        }
    }
}

void GameplayController::handleEvent( const sf::Event& event )
{
    switch ( m_state )
    {
        case Started:
        {
            m_pauseButton.handleEvent( event );
            if ( event.type == sf::Event::KeyPressed )
            {
                if ( event.key.code == sf::Keyboard::Space )
                {
                    m_player.jump();
                }
                else if ( event.key.code == sf::Keyboard::Escape )
                {
                    pause();
                }
            }

            break;
        }
        case PlayerDead:
        {
            m_exitButton.handleEvent( event );
            m_restartButton.handleEvent( event );
            break;
        }
        case Paused:
        {
            m_exitButton.handleEvent( event );
            m_restartButton.handleEvent( event );
            m_resumeButton.handleEvent( event );
            break;
        }
    }
}

}
