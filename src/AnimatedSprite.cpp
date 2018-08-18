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

#include "inc/AnimatedSprite.hpp"
#include "inc/GameEngine.hpp"

#include <iostream>

namespace BirdFlappy
{

void AnimatedSprite::setSpriteRect( const sf::FloatRect& rect )
{
    m_sprite.setPosition( rect.left, rect.top );
    m_sprite.setSize( sf::Vector2f( rect.width,  rect.height ) );
}

void AnimatedSprite::addAnimationFrame( const AnimationFrame& frame )
{
    bool needResetAnimation = ( m_currentFrame == m_animation.end() );
    m_animation.push_back( frame );

    if ( needResetAnimation )
    {
        m_currentFrame = m_animation.begin();
        m_sprite.setTexture( m_currentFrame->texture );
    }
}

void AnimatedSprite::reset()
{
    m_animate = true;
    m_clock.restart();
    m_currentFrame = m_animation.begin();
}

void AnimatedSprite::stop()
{
    m_animate = false;
}

void AnimatedSprite::start()
{
    m_clock.restart();
    m_animate = true;
}

const sf::RectangleShape& AnimatedSprite::getSprite() const
{
    return m_sprite;
}

void AnimatedSprite::process()
{
    if ( m_animation.size() > 0 )
    {
        if ( m_currentFrame->texture != nullptr )
        {
            if ( m_animate && ( m_clock.getElapsedTime() >= m_currentFrame->animationTime ) )
            {
                m_clock.restart();
                ++m_currentFrame;
                if ( m_currentFrame == m_animation.end() )
                {
                    m_currentFrame = m_animation.begin();
                }

                m_sprite.setTexture( m_currentFrame->texture );
                m_sprite.setTextureRect( m_currentFrame->textureRect );
            }

            GameEngine::get().getRenderWindow().draw( m_sprite );
        }
        else
        {
            std::cerr << "One animation frame is null" << std::endl;
            ++m_currentFrame;
            m_clock.restart();

            if ( m_currentFrame == m_animation.end() )
            {
                m_currentFrame = m_animation.begin();
            }
        }
    }
}

}

