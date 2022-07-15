#ifndef TEXTRENDERER_HPP_
#define TEXTRENDERER_HPP_

#include "../ECS/EntityManager.hpp"
#include "../Game/Enum.hpp"

namespace Renderer {
    class TextRenderer : public ECS::Component {
        public:
            TextRenderer(const char *text, int posX, int posY, int fontSize, Color color) :
            _text(text), _posX(posX), _posY(posY), _fontSize(fontSize), _color(color) {}
            ~TextRenderer() = default;
            void draw() override
            {
                MyRayLib::myDrawText(_text, _posX, _posY, _fontSize, _color);
            }
        protected:
            const char *_text;
            int _posX;
            int _posY;
            int _fontSize;
            Color _color;
    };
}

#endif /* !TEXTRENDERER_HPP_ */
