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

#include "inc/Bird.hpp"

namespace BirdFlappy
{

void Bird::reset()
{
    AnimatedSprite::reset();
    m_clock.restart();
    m_sprite.setRotation( INITIAL_ANGLE );
    m_speed = INITIAL_SPEED;
    m_move = true;
}

void Bird::setPosition( const sf::Vector2f& position )
{
    m_sprite.setPosition( position );

	m_sprite.setOrigin( ( m_sprite.getLocalBounds().width / 2.f ),
                        ( m_sprite.getLocalBounds().height / 2.f ) );
}

sf::Vector2f Bird::getPosition() const
{
    return m_sprite.getPosition( );
}

void Bird::jump( )
{
    m_speed = m_jumpBoost;
}

void Bird::start()
{
    sf::Time time = m_clock.restart();
    AnimatedSprite::start();
    m_move = true;
}

void Bird::stop()
{
    AnimatedSprite::stop();
    m_move = false;
}

void Bird::process( )
{
    if ( m_move )
    {
        sf::Time time = m_clock.restart();
        float seconds = ((float)time.asMilliseconds() / 1000.f);

        float speed = m_speed +  m_acceleration;
        move( ( speed * seconds ) );

        float angle = ( speed > 0 ) ? ( m_angleSpeed * seconds ) :
                                      -( m_angleSpeed * seconds );

        addAngle( angle );

        m_speed += m_acceleration * seconds;
    }

    AnimatedSprite::process();
}

float Bird::getAngleSpeed() const
{
    return m_angleSpeed;
}

float Bird::addAngle( float angle )
{
    float newAngle = m_sprite.getRotation();
    newAngle += angle;

    if ( ( newAngle > MIN_ANGLE  ) && ( newAngle < 180.f ) )
    {
        newAngle = MIN_ANGLE;
    }
    else if  ( ( newAngle < MAX_ANGLE ) && ( newAngle > 180.f ) )
    {
        newAngle = MAX_ANGLE;
    }

    m_sprite.setRotation( newAngle );
    m_collisionDetector.setRotation( newAngle );
    return newAngle;
}

void Bird::move( float speed )
{
    if ( speed > MAX_SPEED )
    {
        speed = MAX_SPEED;
    }
    else if ( speed < MIN_SPEED )
    {
        speed = MIN_SPEED;
    }

    m_sprite.move( 0.f, speed );

    m_collisionDetector.setPosition( m_sprite.getPosition() );
}

void Bird::setCollisionDetectorSize( const sf::Vector2f& size )
{
    m_collisionDetector.setSize( size );

    m_collisionDetector.setOutlineColor( sf::Color::Green );
    m_collisionDetector.setOutlineThickness( 5.f );

    m_collisionDetector.setOrigin( ( m_collisionDetector.getLocalBounds().width / 2.f ),
                                   ( m_collisionDetector.getLocalBounds().height / 2.f ) );
}

const sf::RectangleShape& Bird::getCollisionDetector() const
{
    return m_collisionDetector;
}

}
