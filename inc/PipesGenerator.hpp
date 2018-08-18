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

#include <list>
#include <vector>

namespace BirdFlappy
{

class PipesGenerator : public GameObject
{
public:
    explicit PipesGenerator(  const sf::Texture& pipeTexture  );

    void process() override;

    void start();
    void stop();
    void reset() override;

    std::list<sf::RectangleShape>& getSprites();

private:
    struct PipeParams
    {
        sf::Vector2f size;
        sf::Vector2f position;
        float rotation;
    };

    struct Level
    {
        std::list<PipeParams> pipes;
        sf::Time time;
    };

    static std::vector<Level> s_levelVariants;
    std::list<sf::RectangleShape> m_generatedPipes;

    void startRandomLevel();

    const sf::Texture& m_pipeTexture;

    size_t m_currentLevel  = 0;
    sf::Time m_timeAtPause = sf::Time::Zero;
    sf::Clock m_clock;
    bool m_work = true;
};

}
