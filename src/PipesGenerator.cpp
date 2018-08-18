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
#include "inc/PipesGenerator.hpp"

#include <random>
#include <ctime>

namespace BirdFlappy
{

std::vector<PipesGenerator::Level> PipesGenerator::s_levelVariants =
{
    {
        .pipes =
        {
            {
                .size = {150.f, 1000.f},
                .position = {2100.0f, 400.f},
                .rotation = 180.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {2500.0f, 450.f},
                .rotation = 0.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {3200.0f, 400.f},
                .rotation = 180.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {3600.0f, 450.f},
                .rotation = 0.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {4100.0f, 450.f},
                .rotation = 30.f,
            },
            {
                .size = {150.f, 650.f},
                .position = {4700.0f, 340.f},
                .rotation = 210.f,
            },
             {
                .size = {150.f, 1000.f},
                .position = {5300.0f, 350.f},
                .rotation = 180.f,
            },

            {
                .size = {150.f, 1000.f},
                .position = {5700.0f, 325.f},
                .rotation = 0.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {6100.0f, 300.f},
                .rotation = 0.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {6450.0f, 375.f},
                .rotation = 0.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {6750.0f, 375.f},
                .rotation = 0.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {7000.0f, 400.f},
                .rotation = 0.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {7700.0f, 365.f},
                .rotation = 180.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {8150.0f, 365.f},
                .rotation = 0.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {8450.0f, 375.f},
                .rotation = 0.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {8700.0f, 400.f},
                .rotation = 0.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {9300.0f, 450.f},
                .rotation = 180.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {9650.0f, 375.f},
                .rotation = 0.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {10300.0f, 710.f},
                .rotation = 0.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {10450.0f, 390.f},
                .rotation = 180.f,
            },
        },
        .time = sf::seconds( 37 ),
    },
    {
        .pipes =
        {
            {
                .size = {150.f, 1000.f},
                .position = {2100.0f, 700.f},
                .rotation = 180.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {2500.0f, 600.f},
                .rotation = 180.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {2700.0f, 700.f},
                .rotation = 210.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {3100.0f, 600.f},
                .rotation = 330.f,
            },
            {
                .size       = {150.f, 1000.f},
                .position   = {3750.0f, 600.f},
                .rotation   = 210.f,
            },
            {
                .size       = {150.f, 1000.f},
                .position   = {4000.0f, 700.f},
                .rotation   = 210.f,
            },
            {
                .size       = {150.f, 1000.f},
                .position   = {4300.0f, 600.f},
                .rotation   = 210.f,
            },
            // corridor
            {
                .size = {150.f, 1000.f},
                .position = {4800.0f, 800.f},
                .rotation = 0.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {4950.0f, 400.f},
                .rotation = 180.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {4950.0f, 750.f},
                .rotation = 0.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {5100.0f, 350.f},
                .rotation = 180.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {5100.0f, 700.f},
                .rotation = 0.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {5250.0f, 300.f},
                .rotation = 180.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {5250.0f, 650.f},
                .rotation = 0.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {5400.0f, 250.f},
                .rotation = 180.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {5400.0f, 650.f},
                .rotation = 0.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {5550.0f, 250.f},
                .rotation = 180.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {5550.0f, 650.f},
                .rotation = 0.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {5700.0f, 250.f},
                .rotation = 180.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {5700.0f, 700.f},
                .rotation = 0.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {5850.0f, 300.f},
                .rotation = 180.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {5850.0f, 750.f},
                .rotation = 0.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {6000.0f, 350.f},
                .rotation = 180.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {6000.0f, 800.f},
                .rotation = 0.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {6150.0f, 400.f},
                .rotation = 180.f,
            },

            // up/down up/down
            {
                .size = {150.f, 1000.f},
                .position = {6700.0f, 350.f},
                .rotation = 0.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {7350.0f, 600.f},
                .rotation = 180.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {7750.0f, 350.f},
                .rotation = 0.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {8350.0f, 600.f},
                .rotation = 180.f,
            },
        },
        .time = sf::seconds( 30 ),
    },
    {
        .pipes =
        {
            // down sling
            { // right
                .size = {150.f, 1000.f},
                .position = {2700.0f, 500.f},
                .rotation = 30.f,
            },
            {   // left
                .size = {150.f, 1000.f},
                .position = {2100.0f, 600.f},
                .rotation = 330.f,
            },
            { // mid
                .size = {150.f, 1000.f},
                .position = {2400.0f, 500.f},
                .rotation = 0.f,
            },
            // top sling
            {
                .size = {150.f, 1000.f},
                .position = {3100.0f, 400.f},
                .rotation = 210.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {3700.0f, 400.f},
                .rotation = 150.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {3400.0f, 400.f},
                .rotation = 180.f,
            },

            // top mid top low
            {
                .size = { 150.f, 1000.f},
                .position = {4100.0f, 350.f},
                .rotation = 0.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {4600.0f, 800.f},
                .rotation = 0.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {4750.0f, 500.f},
                .rotation = 180.f,
            },
            {
                .size = { 150.f, 1000.f},
                .position = {5100.0f, 350.f},
                .rotation = 0.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = { 5700.0f, 700.f},
                .rotation = 180.f,
            },

            // top sling
            {
                .size = {150.f, 1000.f},
                .position = {6200.0f, 400.f},
                .rotation = 210.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {6800.0f, 400.f},
                .rotation = 150.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {6500.0f, 400.f},
                .rotation = 180.f,
            },
            // bridge
            {
                .size = { 150.f, 1000.f},
                .position = {7200.0f, 350.f},
                .rotation = 0.f,
            },
            {
                .size = { 150.f, 1000.f},
                .position = {7350.0f, 350.f},
                .rotation = 0.f,
            },
            {
                .size = { 150.f, 1000.f},
                .position = {7500.0f, 350.f},
                .rotation = 0.f,
            },
            {
                .size = { 150.f, 1000.f},
                .position = {7650.0f, 350.f},
                .rotation = 0.f,
            },
             {
                .size = {150.f, 1000.f},
                .position = { 8350.0f, 700.f},
                .rotation = 180.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {8650.0f, 600.f},
                .rotation = 180.f,
            },
            { // right
                .size = {150.f, 1500.f},
                .position = {9300.0f, 250.f},
                .rotation = 30.f,
            },
        },
        .time = sf::seconds( 34 ),
    },
        {
        .pipes =
        {
            // gates '<'
            {
                .size = {150.f, 1000.f},
                .position = {2100.0f, 500.f},
                .rotation = 315.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {2250.0f, 150.f},
                .rotation = 225.f,
            },
            // down top down
            {
                .size = {150.f, 1000.f},
                .position = {3000.0f, 500.f},
                .rotation = 180.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {3550.0f, 259.f},
                .rotation = 0,
            },
            {
                .size = {150.f, 1000.f},
                .position = {4150.0f, 7500.f},
                .rotation = 180.f,
            },

            // gates >
            {
                .size = {150.f, 2000.f},
                .position = {4300.0f, 750.f},
                .rotation = 30.f,
            },
            {   // left
                .size = {150.f, 2000.f},
                .position = {4450.0f, 400.f},
                .rotation = 150.f,
            },

            // down bridge
            {
                .size = {150.f, 1000.f},
                .position = {4950.0f, 750.f},
                .rotation = 180.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {5100.0f, 750.f},
                .rotation = 180.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = {5250.0f, 750.f},
                .rotation = 180.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = { 5400.0f, 750.f},
                .rotation = 180.f,
            },
            // top mid down mid top
            {
                .size = {150.f, 1000.f},
                .position = { 5950.0f, 275.f},
                .rotation = 0.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = { 6500.0f, 800.f},
                .rotation = 0.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = { 6650.0f, 500.f},
                .rotation = 180.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = { 7200.0f, 750.f},
                .rotation = 180.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = { 7550.0f, 800.f},
                .rotation = 0.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = { 7700.0f, 500.f},
                .rotation = 180.f,
            },
           {
                .size = {150.f, 1000.f},
                .position = { 8050.0f, 350.f},
                .rotation = 0.f,
            },
            // botton -> top stairs
            {
                .size = {150.f, 1000.f},
                .position = { 8500.0f, 900.f},
                .rotation = 0.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = { 8650.0f, 500.f},
                .rotation = 180.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = { 8650.0f, 850.f},
                .rotation = 0.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = { 8800.0f, 450.f},
                .rotation = 180.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = { 8800.0f, 800.f},
                .rotation = 0.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = { 8950.0f, 400.f},
                .rotation = 180.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = { 8950.0f, 750.f},
                .rotation = 0.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = { 9100.0f, 350.f},
                .rotation = 180.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = { 9100.0f, 650.f},
                .rotation = 0.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = { 9250.0f, 200.f},
                .rotation = 180.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = { 9250.0f, 550.f},
                .rotation = 0.f,
            },
            {
                .size = {150.f, 1000.f},
                .position = { 9400.0f,150.f},
                .rotation = 180.f,
            },
            // down sling
            { // right
                .size = {150.f, 1000.f},
                .position = {10300.0f, 400.f},
                .rotation = 30.f,
            },
            {   // left
                .size = {150.f, 1000.f},
                .position = {9600.0f, 500.f},
                .rotation = 330.f,
            },
            { // mid
                .size = {150.f, 1000.f},
                .position = {9900.0f, 300.f},
                .rotation = 0.f,
            },

        },
        .time = sf::seconds( 36 ),
    },

};

PipesGenerator::PipesGenerator(  const sf::Texture& pipeTexture  ) :
    m_pipeTexture( pipeTexture )
{
}

void PipesGenerator::process()
{
    if ( m_work )
    {
        if ( ( m_clock.getElapsedTime() + m_timeAtPause ) > s_levelVariants[m_currentLevel].time )
        {
            startRandomLevel();
        }
    }
}

void PipesGenerator::startRandomLevel()
{
    m_clock.restart();
    m_timeAtPause = sf::Time::Zero;
    m_generatedPipes.clear();
    std::mt19937 gen( time(0) );
    std::uniform_int_distribution<size_t> uid( 0, s_levelVariants.size() -1 );

    m_currentLevel = uid( gen );

    for ( const PipeParams& pipeParams : s_levelVariants[m_currentLevel].pipes )
    {
        auto pipeSprite = m_generatedPipes.emplace( m_generatedPipes.end() );
        pipeSprite->setPosition( pipeParams.position );
        pipeSprite->setSize( pipeParams.size );
        pipeSprite->setRotation( pipeParams.rotation );
        pipeSprite->setTexture( &m_pipeTexture );
    }
}

void PipesGenerator::start()
{
    m_work = true;
    m_clock.restart();
}

void PipesGenerator::stop()
{
    m_timeAtPause = m_clock.getElapsedTime();
    m_work        = false;
}

void PipesGenerator::reset()
{
    m_work = true;
    startRandomLevel();
    m_clock.restart();
}

std::list<sf::RectangleShape>& PipesGenerator::getSprites()
{
    return m_generatedPipes;
}

}
