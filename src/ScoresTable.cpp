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

#include "inc/ScoresTable.hpp"

#include <fstream>
#include <algorithm>
#include <limits>

namespace BirdFlappy
{

ScoresTable::ScoresTable( size_t countOfScores ) noexcept :
    m_scores( countOfScores, 0u )
{
}

bool ScoresTable::loadFromFile( const std::string& fileName )
{
    std::ifstream stream( fileName, std::ios::binary );
    bool result = true;
    if ( stream.good() )
    {
        for ( size_t i = 0; ( i < m_scores.size() ) && !stream.eof(); ++i )
        {
            stream.read( reinterpret_cast<char*>(&m_scores[i]), sizeof( uint32_t ) );
        }

        std::sort( m_scores.begin(), m_scores.end(), std::greater<uint32_t>() );
    }
    else
    {
        result = false;
    }

    return result;
}

bool ScoresTable::storeToFile( const std::string& fileName )
{
    std::ofstream stream( fileName, std::ios::binary );
    bool result = true;
    if ( stream.good() )
    {
        for ( size_t i = 0; i < m_scores.size(); ++i )
        {
            stream.write( reinterpret_cast<char*>(&m_scores[i]), sizeof( uint32_t ) );
        }
    }
    else
    {
        result = false;
    }

    return result;
}

const std::vector<uint32_t>& ScoresTable::getScores() const
{
    return m_scores;
}

size_t ScoresTable::addScore( uint32_t scoreValue )
{
    size_t i = 0;
    bool found = false;

    for ( ; (i < m_scores.size() ) && !found ; ++i )
    {
        if ( m_scores[i] < scoreValue )
        {
            for ( size_t j = m_scores.size() - 1; j > i; --j )
            {
                m_scores[j] = m_scores[j-1];
            }

            m_scores[i] = scoreValue;
            found = true;
        }
    }

    return found ? i : std::numeric_limits<size_t>::max();
}

}
