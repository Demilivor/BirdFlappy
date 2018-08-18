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

#include "inc/GameObject.hpp"

#include <SFML/Graphics.hpp>

#include <memory>

namespace BirdFlappy
{

class RepeatableTextureRect : public GameObject
{
public:
    void process() override;

    void setSpriteRect( const sf::FloatRect& spriteRect );
    void setTexture( const sf::Texture* texure, const sf::IntRect& rect  );
    void setTimePerPixel( sf::Time timePerPixel );
    void reset() override;
    void stop();
    void start();

private:
    sf::IntRect m_rect;
    sf::IntRect m_initialRect;
    sf::Time m_timePerPixel = sf::Time::Zero;
    sf::RectangleShape m_sprite;
    sf::Clock m_clock;
    bool m_animate = true;
};

}
