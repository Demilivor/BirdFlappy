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

#include <string>

#include <functional>
#include <memory>

namespace BirdFlappy
{

namespace Gui
{

class Button : public GameObject
{
public:
    typedef std::shared_ptr<Button>		Ptr;
    typedef std::function<void()>		Callback;

    enum State
    {
        Normal,
        Hover,
        Pressed,
        Unknown
    };

public:
    void setRenderTarget( sf::RenderTarget& renderTarget );
    void setNormalTexture( const sf::Texture* normalTexture );
    void setHoverTexture( const sf::Texture* hoverTexture );
    void setPressedTexture( const sf::Texture* pressedTexture );
    void setButtonRect( const sf::FloatRect& buttonRect );
    void setFont( const sf::Font& font );
    void setFontSize( unsigned int size );
    void setFontStyle( sf::Text::Style fontStyle );
    void setTextPosition( const sf::Vector2f& textPosition );
    void setFontColor( const sf::Color& color );

    void setCallback( Callback callback ) ;
    void setText( const std::string& text );
    State getState() const;

    virtual void handleEvent( const sf::Event& event );
    void process() override;

protected:
    virtual void draw( )  const;

private:
    Callback				m_callback{ nullptr };
    State                   m_state{ Normal };
    sf::RectangleShape		m_sprite{};
    sf::Text				m_text{};

    const sf::Texture*      m_normalTexture  = nullptr;
    const sf::Texture*      m_hoverTexture   = nullptr;
    const sf::Texture*      m_pressedTexture = nullptr;

    void setState( State state );
};

}

}
