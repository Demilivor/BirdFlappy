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

#include "inc/Button.hpp"
#include "inc/GameEngine.hpp"

#include <iostream>
#include <stdexcept>

namespace BirdFlappy
{

namespace Gui
{
void Button::setNormalTexture( const sf::Texture* normalTexture )
{
    m_normalTexture = normalTexture;
    if ( m_state == Normal )
    {
        m_sprite.setTexture( m_normalTexture );
    }
}

void Button::setHoverTexture( const sf::Texture* hoverTexture  )
{
    m_hoverTexture = hoverTexture;
    if ( m_state == Hover )
    {
        m_sprite.setTexture( m_hoverTexture );
    }
}

void Button::setPressedTexture( const sf::Texture* pressedTexture )
{
    m_pressedTexture = pressedTexture;
    if ( m_state == Pressed )
    {
        m_sprite.setTexture( m_pressedTexture );
    }
}

void Button::setButtonRect( const sf::FloatRect& buttonRect )
{
    m_sprite.setSize( sf::Vector2f( buttonRect.width,  buttonRect.height ) );
    m_sprite.setPosition( buttonRect.left, buttonRect.top );
}

void Button::setFont( const sf::Font& font )
{
    m_text.setFont( font );
}

void Button::setFontSize( unsigned int size )
{
    m_text.setCharacterSize( size );
}

void Button::setFontStyle( sf::Text::Style fontStyle )
{
    m_text.setStyle( fontStyle );
}

void Button::setTextPosition( const sf::Vector2f& textPosition )
{
	m_text.setPosition( textPosition );
}

void Button::setFontColor( const sf::Color& color )
{
    m_text.setColor( color );
}

void Button::setCallback( Callback callback )
{
	m_callback = std::move( callback );
}

void Button::setText( const std::string& text )
{
	m_text.setString( text );

	m_text.setOrigin( ( m_text.getLocalBounds().width / 2.f ),
                      ( m_text.getLocalBounds().height / 2.f ) );
}

Button::State Button::getState( ) const
{
    return m_state;
}

void Button::setState( Button::State state )
{
    m_state = state;

    switch ( m_state )
    {
        case Normal:
        {
            if ( m_normalTexture )
            {
                m_sprite.setTexture( m_normalTexture );
            }

            break;
        }
        case Pressed:
        {
            if ( m_pressedTexture )
            {
                m_sprite.setTexture( m_pressedTexture );
            }

            break;
        }
        case Hover:
        {
            if ( m_hoverTexture )
            {
                m_sprite.setTexture( m_hoverTexture );
            }
            break;
        }
    }
}

void Button::process()
{
    draw();
}

void Button::handleEvent( const sf::Event& event)
{
    switch ( event.type )
    {
        case sf::Event::MouseMoved:
        {
            sf::RenderWindow& renderWindow = GameEngine::get().getRenderWindow();
            sf::Vector2f mousePos = renderWindow.mapPixelToCoords( sf::Vector2i( event.mouseMove.x,
                                                                                 event.mouseMove.y ) );
            bool mouseAtButton = m_sprite.getGlobalBounds().contains( mousePos );
            if (  m_state == Normal )
            {
                if ( mouseAtButton )
                {
                    setState( Hover );
                }
            }
            else if ( m_state == Hover && !mouseAtButton )
            {
                setState( Normal );
            }

            break;
        }
        case sf::Event::MouseButtonPressed:
        {
            sf::RenderWindow& renderWindow = GameEngine::get().getRenderWindow();
            sf::Vector2f mousePos = renderWindow.mapPixelToCoords( sf::Vector2i( event.mouseButton.x,
                                                                                 event.mouseButton.y ) );
            if ( ( m_state != Pressed ) &&
                 ( event.mouseButton.button == sf::Mouse::Button::Left ) &&
                  m_sprite.getGlobalBounds().contains( mousePos ) )
            {
                setState( Pressed );
                if ( m_callback )
                {
                    m_callback();
                    setState( Normal );
                }
            }
            break;
        }
        case sf::Event::MouseButtonReleased:
        {
            if  ( m_state == Pressed )
            {
                sf::RenderWindow& renderWindow = GameEngine::get().getRenderWindow();
                sf::Vector2f mousePos = renderWindow.mapPixelToCoords( sf::Vector2i( event.mouseButton.x,
                                                                                     event.mouseButton.y ) );
                if ( ( event.mouseButton.button == sf::Mouse::Button::Left ) &&
                       m_sprite.getGlobalBounds().contains( mousePos ) )
                {
                      setState( Hover );
                }
                else
                {
                    setState( Normal );
                }
            }
            break;
        }
    }
}

void Button::draw( ) const
{
	GameEngine::get().getRenderWindow().draw( m_sprite );
	GameEngine::get().getRenderWindow().draw( m_text );
}

}

}
