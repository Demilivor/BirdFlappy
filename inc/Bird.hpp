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

#include <SFML/Graphics.hpp>

#include <memory>

namespace BirdFlappy
{

class Bird : public AnimatedSprite
{
public:
    void process( ) override;
    void reset() override;

    float getSpeed() const;
    float getAngleSpeed() const;
    float addAngle( float angle );
    void setPosition( const sf::Vector2f& position );
    sf::Vector2f getPosition() const;
    void jump( );

    void setCollisionDetectorSize( const sf::Vector2f& size );
    const sf::RectangleShape& getCollisionDetector() const;

    void start();
    void stop();
    void move( float speed );

private:
    // reduced rectangle for better collision quality
    sf::RectangleShape m_collisionDetector;

    static constexpr float INITIAL_ANGLE    = -30.0f;
    static constexpr float INITIAL_SPEED    = -1500.0f;
    static constexpr float MAX_ANGLE        = 290.f; // up
    static constexpr float MIN_ANGLE        = 70.f; // fall

    static constexpr float MAX_SPEED        = 5000.f;
    static constexpr float MIN_SPEED        = -5000.f;

    float m_jumpBoost                       = -2050.0f;
    float m_speed                           = INITIAL_SPEED;
    float m_acceleration                    = 1400.0f;

    float m_angleSpeed                      = 260.0f;
    bool  m_alive                           = true;
    bool  m_move                            = true;
    sf::Clock m_clock;
};

}

