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

#include "inc/GameEngine.hpp"

#include "inc/MainMenu.hpp"
#include "inc/GameplayController.hpp"

#include <memory>
#include <iostream>
#include <sstream>
#include <cassert>

namespace BirdFlappy
{

const std::string GameEngine::SCORES_TABLE_FILENAME = "scores.db";
GameEngine* GameEngine::s_gameEngine = nullptr;

sf::RenderWindow& GameEngine::getRenderWindow( )
{
    return m_window;
}

const GameResources& GameEngine::getGameResources( ) const
{
    return m_gameResources;
}

ScoresTable& GameEngine::getScoresTable()
{
    return m_scoresTable;
}

ErrorCode GameEngine::gameMainLoop()
{
    ErrorCode result = NoError;
    sf::Event event;

    sf::View view;
    view.setSize( GLOBAL_VIEW_WIDTH, GLOBAL_VIEW_HEIGHT  );
    view.setCenter( view.getSize().x / 2, view.getSize().y / 2 );

    while ( m_gameInProgress && m_window.isOpen() )
    {
        while ( m_window.pollEvent( event ) )
        {
            switch ( m_state )
            {
                case Menu:
                {
                    m_mainMenu->handleEvent( event );
                    break;
                }
                case Gameplay:
                {
                    m_gameplayController->handleEvent( event );
                    break;
                }
            }
        }

        m_window.clear();
        m_window.setView( view );

        switch ( m_state )
        {
            case Menu:
            {
                m_mainMenu->process();
                break;
            }
            case Gameplay:
            {
                m_gameplayController->process();
                break;
            }
        }

        m_window.display();
    }

    return result;
}

void GameEngine::startGameplay()
{
    m_mainMenu.reset();
    m_gameplayController.reset( new GameplayController( ) );
    m_state = Gameplay;
}

void GameEngine::enterMainMenu()
{
    m_gameplayController.reset();
    m_mainMenu.reset( new MainMenu(  ) );
    m_state = Menu;
}

void GameEngine::createGameWindow( const std::string& windowLabel )
{
    m_window.create( sf::VideoMode::getDesktopMode(),windowLabel, sf::Style::Fullscreen );
    m_window.setFramerateLimit( 60 );
    m_gameInProgress = true;
}

void GameEngine::requestExit()
{
    // m_window still could be used in this iteration, just mark window, that it requires closing.
    m_gameInProgress = false;
}

ErrorCode GameEngine::loadGameResources()
{
    if ( !m_gameResources.font.loadFromFile( "content/fonts/cnr.otf" ) )
    {
        std::cerr << "content/fonts/cnr.otf loading failed" << std::endl;
        return ResourceLoadingFailed;
    }

    if ( !m_gameResources.menuBackgroundTexture.loadFromFile( "content/images/MenuBackGround.png" ) )
    {
        std::cerr << "content/images/MenuBackGround.png loading failed" << std::endl;
        return ResourceLoadingFailed;
    }

    if ( !m_gameResources.gameplayBackgroundTexture.loadFromFile( "content/images/GamePlayBackground.png" ) )
    {
        std::cerr << "content/images/GamePlayBackground.png loading failed" << std::endl;
        return ResourceLoadingFailed;
    }

    if ( !m_gameResources.normalButTexture.loadFromFile( "content/images/NormalButton.png" ) )
    {
        std::cerr << "content/images/NormalButton.png loading failed" << std::endl;
        return ResourceLoadingFailed;
    }
    if ( !m_gameResources.hoverButTexture.loadFromFile( "content/images/HoverButton.png" ) )
    {
        std::cerr << "content/images/HoverButton.png loading failed"  << std::endl;
        return ResourceLoadingFailed;
    }

    if ( !m_gameResources.cloudsTexure.loadFromFile( "content/images/Clouds.png" ) )
    {
        std::cerr << "content/images/Clouds.png loading failed" << std::endl;
        return ResourceLoadingFailed;
    }

    if ( !m_gameResources.pipeTexure.loadFromFile( "content/images/Pipe.png" ) )
    {
        std::cerr << "content/images/Pipe.png loading failed" << std::endl;
        return ResourceLoadingFailed;
    }

    m_gameResources.gameplayBackgroundTexture.setRepeated( true );
    m_gameResources.cloudsTexure.setRepeated( true );

    bool loadAnimation = true;
    size_t index       = 1;
    std::list<sf::Texture>::iterator texture;
    do
    {
        // std::to_string( index ) is not working, gcc bug
        std::stringstream ss;
        ss << index;
        std::string filename = "content/images/bird/frame-" + ss.str() + ".png";
        texture = m_gameResources.birdAnimation.emplace( m_gameResources.birdAnimation.end() );
        loadAnimation = texture->loadFromFile( filename );
        ++index;
    } while ( loadAnimation );

    // Remove last texture, because it's file not exist
    m_gameResources.birdAnimation.erase( texture );

    if (!m_gameResources.theme.loadFromFile( "content/sounds/theme.ogg" ) )
    {
        std::cerr << "content/sounds/Theme.ogg loading failed" << std::endl;
        return ResourceLoadingFailed;
    }

    if (!m_gameResources.soundOnDeath.loadFromFile( "content/sounds/death.ogg" ) )
    {
        std::cerr << "content/sounds/Death.ogg loading failed" << std::endl;
        return ResourceLoadingFailed;
    }

    return NoError;
}

GameEngine::GameEngine()
{
    assert ( s_gameEngine == nullptr );
    s_gameEngine = this;
}

GameEngine::~GameEngine()
{
    m_scoresTable.storeToFile( SCORES_TABLE_FILENAME );
    s_gameEngine = nullptr;
}

GameEngine& GameEngine::get()
{
    if ( s_gameEngine == nullptr )
    {
        s_gameEngine = new GameEngine();
    }

    return *s_gameEngine;
}

void GameEngine::destroy()
{
    delete s_gameEngine;
}

ErrorCode GameEngine::start(  )
{
    createGameWindow( "BirdFlappy" );
    m_scoresTable.loadFromFile( SCORES_TABLE_FILENAME );
    ErrorCode result = loadGameResources();
    if ( result == NoError)
    {
        m_gameTheme.setBuffer( m_gameResources.theme );
        m_gameTheme.setLoop( true );
        m_gameTheme.play();
        enterMainMenu( );
        result = gameMainLoop();
    }

    return result;
}

ErrorCode start(  )
{
    GameEngine& engine = GameEngine::get();
    ErrorCode result = engine.start();
    GameEngine::destroy();
    return result;
}

}

