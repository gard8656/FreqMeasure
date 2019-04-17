#pragma once
#include "Display/Painter.h"


namespace Display
{
    namespace Primitives
    {
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        class Rectangle
        {
        public:
            Rectangle(int width, int height);
            void Draw(int x, int y, Color color = Color::Number);
        private:
            int width;
            int height;
        };
    }
}
