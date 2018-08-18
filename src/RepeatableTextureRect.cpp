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

#include "inc/RepeatableTextureRect.hpp"
#include "inc/GameEngine.hpp"

namespace BirdFlappy
{

void RepeatableTextureRect::setSpriteRect( const sf::FloatRect& rect )
{
    m_sprite.setPosition( rect.left, rect.top );
    m_sprite.setSize( sf::Vector2f( rect.width,  rect.height ) );
}

void RepeatableTextureRect::setTexture( const sf::Texture* texure, const sf::IntRect& rect )
{
    m_sprite.setTexture( texure );
    if ( texure )
    {
        m_initialRect = m_rect = rect;
        m_sprite.setTextureRect( m_rect );
    }
    else
    {
        m_initialRect = m_rect = sf::IntRect();
    }
}

void RepeatableTextureRect::setTimePerPixel( sf::Time timePerPixel )
{
    m_timePerPixel = timePerPixel;
}

void RepeatableTextureRect::reset()
{
    m_clock.restart();

    const sf::Texture* texure = m_sprite.getTexture();
    m_rect = m_initialRect;
    m_animate = true;
}

void RepeatableTextureRect::stop()
{
    m_animate = false;
}

void RepeatableTextureRect::start()
{
    m_clock.restart();
    m_animate = true;
}

void RepeatableTextureRect::process()
{
    if ( m_sprite.getTexture() != nullptr )
    {
        if (  m_animate && ( m_clock.getElapsedTime() > m_timePerPixel ) )
        {
            int moveDistance  = ( m_clock.getElapsedTime() / m_timePerPixel );
            m_rect.left += moveDistance;
            m_rect.width += moveDistance;
            m_clock.restart();
            m_sprite.setTextureRect( m_rect );
        }

        GameEngine::get().getRenderWindow().draw( m_sprite );
    }

}

}

