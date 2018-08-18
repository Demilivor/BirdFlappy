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

#include "inc/MainMenu.hpp"
#include "inc/GameEngine.hpp"

#include <stdexcept>
#include <sstream>

namespace BirdFlappy
{

MainMenu::MainMenu(  )
{
    m_backGround.setTexture( &GameEngine::get().getGameResources().menuBackgroundTexture );
    m_backGround.setPosition( 0.f, 0.f );

    m_backGround.setSize( sf::Vector2f( GameEngine::GLOBAL_VIEW_WIDTH,
                                        GameEngine::GLOBAL_VIEW_HEIGHT ) );

    createButtons( );
    createScoresTable( );
}

void MainMenu::createButtons(  )
{
    float yCenter = GameEngine::GLOBAL_VIEW_HEIGHT / 2.0f;
    sf::FloatRect buttonRect;
    buttonRect.width     = BUTTON_WIDTH;
    buttonRect.height    = BUTTON_HEIGHT;
    buttonRect.left      = ( ( GameEngine::GLOBAL_VIEW_WIDTH / 2.0f ) - ( buttonRect.width / 2.0f ) );
    buttonRect.top       = yCenter - BUTTON_DISTANCE;

    sf::Vector2f textPosition;
    textPosition.x = buttonRect.left + ( buttonRect.width / 2.f );
    textPosition.y = buttonRect.top  + ( buttonRect.height / 4.f );

    const GameResources& resources = GameEngine::get().getGameResources();

    m_startButton.setNormalTexture( &resources.normalButTexture );
    m_startButton.setHoverTexture( &resources.hoverButTexture );
    m_startButton.setButtonRect( buttonRect );
    m_startButton.setFont( resources.font );
    m_startButton.setFontSize( BUTTON_DEFAULT_TEXT_SIZE );
    m_startButton.setFontStyle( sf::Text::Bold );
    m_startButton.setTextPosition(  textPosition );
    m_startButton.setFontColor( sf::Color::Green );

    m_startButton.setText( "Start" );
    m_startButton.setCallback( []()
    {
        GameEngine::get().startGameplay();
    });

    buttonRect.top  = yCenter;
    textPosition.y  = buttonRect.top + ( buttonRect.height / 4.f );

    m_scoresButton.setNormalTexture( &resources.normalButTexture );
    m_scoresButton.setHoverTexture( &resources.hoverButTexture );
    m_scoresButton.setButtonRect( buttonRect );
    m_scoresButton.setFont( resources.font );
    m_scoresButton.setFontSize( BUTTON_DEFAULT_TEXT_SIZE );
    m_scoresButton.setFontStyle( sf::Text::Bold );
    m_scoresButton.setTextPosition(  textPosition );
    m_scoresButton.setFontColor( sf::Color::Green );
    m_scoresButton.setText( "Scores" );
    m_scoresButton.setCallback( [&]()
    {
        m_state = ScoresMenu;
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

    m_exitButton.setCallback( []()
    {
        GameEngine::get().requestExit();
    });

    m_backButton.setNormalTexture( &resources.normalButTexture );
    m_backButton.setHoverTexture( &resources.hoverButTexture );
    m_backButton.setButtonRect( buttonRect );
    m_backButton.setFont( resources.font );
    m_backButton.setFontSize( BUTTON_DEFAULT_TEXT_SIZE );
    m_backButton.setFontStyle( sf::Text::Bold );
    m_backButton.setTextPosition(  textPosition );
    m_backButton.setFontColor( sf::Color::Green );

    m_backButton.setText( "Back" );
    m_backButton.setCallback( [&]()
    {
        m_state = LobbyMenu;
    } );
}

void MainMenu::createScoresTable( )
{
    const GameResources& resources = GameEngine::get().getGameResources();
    sf::Color color = sf::Color::Cyan;
    color.a = 50;

    m_scoresBackGround.setFillColor( color );
    m_scoresBackGround.setSize( sf::Vector2f( 600.f, 450.f ) );
    m_scoresBackGround.setOutlineColor( sf::Color::Green );
    m_scoresBackGround.setOutlineThickness( 6.0f );
    m_scoresBackGround.setOrigin( -(GameEngine::GLOBAL_VIEW_WIDTH / 2.0f) + ( m_scoresBackGround.getSize().x / 2.0f ),
                                  -300);

    m_scoresLabelText.setFont( resources.font );
    m_scoresLabelText.setColor( sf::Color::Yellow );
    m_scoresLabelText.setCharacterSize( BUTTON_DEFAULT_TEXT_SIZE );
    m_scoresLabelText.setString( "Scores" );
    m_scoresLabelText.setPosition( GameEngine::GLOBAL_VIEW_WIDTH / 2.0f, 220  );
    m_scoresLabelText.setOrigin( ( m_scoresLabelText.getLocalBounds().width / 2.f ),
                                 ( m_scoresLabelText.getLocalBounds().height / 2.f ) );

    m_scoresValuesText.setFont( resources.font );
    m_scoresValuesText.setColor( sf::Color::Green );
    m_scoresValuesText.setCharacterSize( 55 );
    m_scoresValuesText.setPosition( GameEngine::GLOBAL_VIEW_WIDTH / 2.0f, 320  );

    std::stringstream ss;
    for ( uint32_t score : GameEngine::get().getScoresTable().getScores() )
    {
        if ( score > 0)
        {
            ss << score << '\n';
        }
        else
        {
            break;
        }
    }

    m_scoresValuesText.setString( ss.str() );
    m_scoresValuesText.setOrigin( ( m_scoresValuesText.getLocalBounds().width / 2.f ),
                                    m_scoresValuesText.getOrigin().y );
}

void MainMenu::process( )
{
    GameEngine::get().getRenderWindow().draw( m_backGround );
    switch ( m_state )
    {
        case LobbyMenu:
        {
            m_startButton.process();
            m_scoresButton.process();
            m_exitButton.process();
            break;
        }
        case ScoresMenu:
        {
            sf::RenderWindow& renderWindow = GameEngine::get().getRenderWindow();
            renderWindow.draw( m_scoresBackGround );
            renderWindow.draw( m_scoresLabelText );
            renderWindow.draw( m_scoresValuesText );

            m_backButton.process();
            break;
        }
    }
}

void MainMenu::handleEvent( const sf::Event& event)
{
    switch ( m_state )
    {
        case LobbyMenu:
        {
            m_startButton.handleEvent( event );
            m_scoresButton.handleEvent( event );
            m_exitButton.handleEvent( event );
            break;
        }
        case ScoresMenu:
        {
            if ( ( event.type == sf::Event::KeyPressed ) &&
                 ( event.key.code == sf::Keyboard::Escape ) )
            {
                m_state = LobbyMenu;
            }

            m_backButton.handleEvent( event );
            break;
        }
    }
}

}
