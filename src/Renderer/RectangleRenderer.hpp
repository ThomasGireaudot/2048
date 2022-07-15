#ifndef RECTANGLERENDERER_HPP_
#define RECTANGLERENDERER_HPP_

#include "../ECS/EntityManager.hpp"
#include <map>
#include <time.h>
#include <string>
#include <iostream>
#include <stack>

namespace Renderer {
    class RectangleRenderer : public ECS::Component {
        public:
            RectangleRenderer(int posX, int posY, int width, int height, Color color) :
            _posX(posX), _posY(posY), _width(width), _height(height), _color(color) {}
            RectangleRenderer(int width, int height, Color color) :
            _width(width), _height(height), _color(color) {}
            RectangleRenderer(int posX, int posY, int width, int height) :
            _posX(posX), _posY(posY), _width(width), _height(height) {}
            ~RectangleRenderer() = default;
            void draw () override
            {
                MyRayLib::myDrawRectangle(_posX, _posY, _width, _height, _color);
                if (_lines)
                    MyRayLib::myDrawRectangleLines(_posX, _posY, _width, _height, _color);
            }
            void setLines(bool lines, Color linesColor)
            {
                _lines = lines;
                _linesColor = linesColor;
            }
            void setColor(Color color)
            {
                _color = color;
            }
        protected:
            int _posX;
            int _posY;
            int _width;
            int _height;
            Color _color;
            bool _lines;
            Color _linesColor;
    };
    class MapRectangleRenderer : public RectangleRenderer {
        public:
            MapRectangleRenderer(int width, int height, Color color) :
            RectangleRenderer(width, height, color) {}
            ~MapRectangleRenderer() = default;
            void addPosition(Vector2 position)
            {
                positions.push_back(position);
            }
            void draw() override
            {
                for (auto pos : positions) {
                    MyRayLib::myDrawRectangle(pos.x, pos.y, _width, _height, _color);
                    if (_lines)
                        MyRayLib::myDrawRectangleLines(pos.x, pos.y, _width, _height, _linesColor);
                }
            }
        private:
            std::vector<Vector2> positions;
    };
    static std::map<int, Color> tilesColorMap = {
        {2, Color{238, 228, 218, 255}},
        {4, Color{237, 224, 200, 255}},
        {8, Color{242, 177, 121, 255}},
        {16, Color{245, 149, 99, 255}},
        {32, Color{246, 125, 95, 255}},
        {64, Color{246, 94, 59, 255}},
        {128, Color{237, 207, 114, 255}},
        {256, Color{237, 204, 97, 255}},
        {512, Color{237, 200, 80, 255}},
        {1024, Color{236, 196, 64, 255}},
        {2048, Color{235, 192, 48, 255}}
    };
    static std::vector<Color> textColors = {
        Color{249, 246, 242, 255},
        Color{119, 110, 101, 255}
    };
    static std::map<int, int> fontSize = {
        {2, 100},
        {4, 100},
        {8, 100},
        {16, 90},
        {32, 90},
        {64, 90},
        {128, 80},
        {256, 80},
        {512, 80},
        {1024, 60},
        {2048, 60}
    };
    class Tile : public RectangleRenderer {
        public:
            Tile(std::string value, Vector2 pos, Vector2 size) : _value(value),
            RectangleRenderer(pos.x, pos.y, size.x, size.y), _pos_x(pos.x), _pos_y(pos.y)
            {
                _stackable = true;
            }
            ~Tile() = default;
            void draw()
            {
                Color color = tilesColorMap[stoi(_value)];
                Color text_color = (stoi(_value) < 8) ? textColors[1] : textColors[0];
                int font_size = fontSize[stoi(_value)];
                int text_size = MyRayLib::myMeasureText(_value.c_str(), font_size);
                float pos_x = _pos_x + (_width / 2) - (text_size / 2);
                float pos_y = _pos_y + (_height / 2) - (font_size / 2);

                MyRayLib::myDrawRectangle(_pos_x, _pos_y, _width, _height, color);
                MyRayLib::myDrawText(_value.c_str(), pos_x, pos_y, font_size, text_color);
            }
            int getValue()
            {
                return (stoi(_value));
            }
            void setPos(Vector2 pos)
            {
                _pos_x = pos.x;
                _pos_y = pos.y;
                _posX = pos.x;
                _posY = pos.y;
            }
            Vector2 getPos()
            {
                return (Vector2{_pos_x, _pos_y});
            }
            void setStackable(bool stackable)
            {
                _stackable = stackable;
            }
            bool isStackable()
            {
                return (_stackable);
            }
            void setSpeed(float speed)
            {
                _speed = speed;
            }
            float getSpeed()
            {
                return (_speed);
            }
            void setNext(float next)
            {
                _next = next;
            }
            float getNext()
            {
                return (_next);
            }
            void setValue(std::string value)
            {
                _value = value;
            }
        private:
            float _speed;
            float _pos_x;
            float _pos_y;
            std::string _value;
            bool _stackable;
            float _next;
    };
    class GameTiles : public ECS::Component {
        public:
            GameTiles(int width, int height, Color color) :
            _width(width), _height(height), _color(color), _score(0)
            {
                srand(time(NULL));
            }
            ~GameTiles() = default;
            std::vector<Tile*> setOneColumnFromLines(float x_index)
            {
                std::vector<Tile*> col;

                for (auto tile : _line1)
                    if (tile->getPos().x == x_index)
                        col.push_back(tile);
                for (auto tile : _line2)
                    if (tile->getPos().x == x_index)
                        col.push_back(tile);
                for (auto tile : _line3)
                    if (tile->getPos().x == x_index)
                        col.push_back(tile);
                for (auto tile : _line4)
                    if (tile->getPos().x == x_index)
                        col.push_back(tile);
                return (col);
            }
            void setColumnsFromLines()
            {
                float x_index = _min_x;

                _column1 = setOneColumnFromLines(x_index);
                x_index += _between_tile;
                _column2 = setOneColumnFromLines(x_index);
                x_index += _between_tile;
                _column3 = setOneColumnFromLines(x_index);
                x_index += _between_tile;
                _column4 = setOneColumnFromLines(x_index);
            }
            std::vector<Tile*> setOneLineFromColumns(float y_index)
            {
                std::vector<Tile*> line;

                for (auto tile : _column1)
                    if (tile->getPos().y == y_index)
                        line.push_back(tile);
                for (auto tile : _column2)
                    if (tile->getPos().y == y_index)
                        line.push_back(tile);
                for (auto tile : _column3)
                    if (tile->getPos().y == y_index)
                        line.push_back(tile);
                for (auto tile : _column4)
                    if (tile->getPos().y == y_index)
                        line.push_back(tile);
                return (line);
            }
            void setLinesFromColumns()
            {
                float y_index = _min_y;

                _line1 = setOneLineFromColumns(y_index);
                y_index += _between_tile;
                _line2 = setOneLineFromColumns(y_index);
                y_index += _between_tile;
                _line3 = setOneLineFromColumns(y_index);
                y_index += _between_tile;
                _line4 = setOneLineFromColumns(y_index);
            }
            void slideLeft_setSpeedAndNextPos(std::vector<Tile*> tmp, Tile *tile)
            {
                float move_number =
                    (tile->getPos().x == _min_x) ? 0 :
                    (tile->getPos().x == _min_x + _between_tile) ? 1 :
                    (tile->getPos().x == _min_x + (_between_tile * 2)) ? 2 : 3;
                int index;

                for (auto tmp_tile : tmp)
                    if (tmp_tile->getPos().x < tile->getPos().x)
                        move_number--;
                for (index = 0; tmp[index]; index++)
                    if (tmp[index] == tile)
                        break;
                if (index != 0 && tmp[index - 1]->isStackable() &&
                    tmp[index - 1]->getValue() == tile->getValue()) {
                    move_number++;
                    if (tile->getPos().x - (_between_tile * move_number) > tmp[index - 1]->getNext())
                        move_number++;
                    tile->setStackable(false);
                }
                if (index != 0 && !tmp[index - 1]->isStackable())
                    move_number++;
                tile->setSpeed(move_number);
                tile->setNext(tile->getPos().x - (_between_tile * move_number));
            }
            bool slideLeft_setPos(Tile *tile)
            {
                bool end = true;

                if (tile->getPos().x > tile->getNext()) {
                    end = false;
                    tile->setPos(Vector2{tile->getPos().x - tile->getSpeed() * 20, tile->getPos().y});
                } else
                    tile->setPos(Vector2{tile->getNext(), tile->getPos().y});
                return (end);
            }
            void slideLeft_stackLine(std::vector<Tile*> &line)
            {
                std::vector<Tile*>::iterator line_it;

                if (line.size() < 2)
                    return;
                line_it = line.begin();
                for (int index = 0; index <= line.size() - 1; index++, line_it++) {
                    if (!line[index]->isStackable()) {
                        line[index]->setValue(std::to_string(line[index]->getValue() * 2));
                        line[index]->setStackable(true);
                        line.erase(line_it - 1);
                        _score += line[index]->getValue() * 2;
                    }
                }
            }
            void slideLeft_stackTiles()
            {
                slideLeft_stackLine(_line1);
                slideLeft_stackLine(_line2);
                slideLeft_stackLine(_line3);
                slideLeft_stackLine(_line4);
                setColumnsFromLines();
            }
            void slideLeft()
            {
                if (!_slideLeft) {
                    _sliding = true;
                    _slideLeft = true;

                    for (auto tile : _line1)
                        slideLeft_setSpeedAndNextPos(_line1, tile);
                    for (auto tile : _line2)
                        slideLeft_setSpeedAndNextPos(_line2, tile);
                    for (auto tile : _line3)
                        slideLeft_setSpeedAndNextPos(_line3, tile);
                    for (auto tile : _line4)
                        slideLeft_setSpeedAndNextPos(_line4, tile);
                } else {
                    bool end = true;

                    for (auto tile : _line1)
                        if (!slideLeft_setPos(tile))
                            end = false;
                    for (auto tile : _line2)
                        if (!slideLeft_setPos(tile))
                            end = false;
                    for (auto tile : _line3)
                        if (!slideLeft_setPos(tile))
                            end = false;
                    for (auto tile : _line4)
                        if (!slideLeft_setPos(tile))
                            end = false;
                    if (end) {
                        _sliding = false;
                        _slideLeft = false;
                        setColumnsFromLines();
                        setLinesFromColumns();
                        slideLeft_stackTiles();
                        generateTile();
                    }
                }
            }
            void slideRight_setSpeedAndNextPos(std::vector<Tile*> tmp, Tile *tile)
            {
                float move_number =
                    (tile->getPos().x == _max_x) ? 0 :
                    (tile->getPos().x == _max_x - _between_tile) ? 1 :
                    (tile->getPos().x == _max_x - (_between_tile * 2)) ? 2 : 3;
                int index;

                for (auto tmp_tile : tmp)
                    if (tmp_tile->getPos().x > tile->getPos().x)
                        move_number--;
                for (index = 0; tmp[index]; index++)
                    if (tmp[index] == tile)
                        break;
                if (index != tmp.size() - 1 && tmp[index + 1]->isStackable() &&
                    tmp[index + 1]->getValue() == tile->getValue()) {
                    move_number++;
                    if (tile->getPos().x + (_between_tile * move_number) < tmp[index + 1]->getNext())
                        move_number++;
                    tile->setStackable(false);
                }
                if (index != tmp.size() - 1 && !tmp[index + 1]->isStackable())
                    move_number++;
                tile->setSpeed(move_number);
                tile->setNext(tile->getPos().x + (_between_tile * move_number));
            }
            bool slideRight_setPos(Tile *tile)
            {
                bool end = true;

                if (tile->getPos().x < tile->getNext()) {
                    end = false;
                    tile->setPos(Vector2{tile->getPos().x + tile->getSpeed() * 20, tile->getPos().y});
                } else
                    tile->setPos(Vector2{tile->getNext(), tile->getPos().y});
                return (end);
            }
            void slideRight_stackLine(std::vector<Tile*> &line)
            {
                std::vector<Tile*>::reverse_iterator line_it;

                if (line.size() < 2)
                    return;
                line_it = line.rbegin();
                for (int index = line.size() - 1; index >= 0; index--, line_it++) {
                    if (!line[index]->isStackable()) {
                        line[index]->setValue(std::to_string(line[index]->getValue() * 2));
                        line[index]->setStackable(true);
                        line.erase((line_it).base());
                        _score += line[index]->getValue() * 2;
                    }
                }
            }
            void slideRight_stackTiles()
            {
                slideRight_stackLine(_line1);
                slideRight_stackLine(_line2);
                slideRight_stackLine(_line3);
                slideRight_stackLine(_line4);
                setColumnsFromLines();
            }
            void slideRight()
            {
                if (!_slideRight) {
                    _sliding = true;
                    _slideRight = true;

                    for (int index = _line1.size() - 1; index >= 0; index--)
                        slideRight_setSpeedAndNextPos(_line1, _line1[index]);
                    for (int index = _line2.size() - 1; index >= 0; index--)
                        slideRight_setSpeedAndNextPos(_line2, _line2[index]);
                    for (int index = _line3.size() - 1; index >= 0; index--)
                        slideRight_setSpeedAndNextPos(_line3, _line3[index]);
                    for (int index = _line4.size() - 1; index >= 0; index--)
                        slideRight_setSpeedAndNextPos(_line4, _line4[index]);
                } else {
                    bool end = true;

                    for (auto tile : _line1)
                        if (!slideRight_setPos(tile))
                            end = false;
                    for (auto tile : _line2)
                        if (!slideRight_setPos(tile))
                            end = false;
                    for (auto tile : _line3)
                        if (!slideRight_setPos(tile))
                            end = false;
                    for (auto tile : _line4)
                        if (!slideRight_setPos(tile))
                            end = false;
                    if (end) {
                        _sliding = false;
                        _slideRight = false;
                        setColumnsFromLines();
                        setLinesFromColumns();
                        slideRight_stackTiles();
                        generateTile();
                    }
                }
            }
            void slideUp_setSpeedAndNextPos(std::vector<Tile*> tmp, Tile *tile)
            {
                float move_number =
                    (tile->getPos().y == _min_y) ? 0 :
                    (tile->getPos().y == _min_y + _between_tile) ? 1 :
                    (tile->getPos().y == _min_y + (_between_tile * 2)) ? 2 : 3;
                int index;
                
                for (auto tmp_tile : tmp)
                    if (tmp_tile->getPos().y < tile->getPos().y)
                        move_number--;
                for (index = 0; tmp[index]; index++)
                    if (tmp[index] == tile)
                        break;
                if (index != 0 && tmp[index - 1]->isStackable() &&
                    tmp[index - 1]->getValue() == tile->getValue()) {
                    move_number++;
                    if (tile->getPos().y - (_between_tile * move_number) > tmp[index - 1]->getNext())
                        move_number++;
                    tile->setStackable(false);
                }
                if (index != 0 && !tmp[index - 1]->isStackable())
                    move_number++;
                tile->setSpeed(move_number);
                tile->setNext(tile->getPos().y - (_between_tile * move_number));
            }
            bool slideUp_setPos(Tile *tile)
            {
                bool end = true;

                if (tile->getPos().y > tile->getNext()) {
                    end = false;
                    tile->setPos(Vector2{tile->getPos().x, tile->getPos().y - tile->getSpeed() * 20});
                } else
                    tile->setPos(Vector2{tile->getPos().x, tile->getNext()});
                return (end);
            }
            void slideUp_stackColumn(std::vector<Tile*> &col)
            {
                std::vector<Tile*>::iterator col_it;

                if (col.size() < 2)
                    return;
                col_it = col.begin();
                for (int index = 0; index <= col.size() - 1; index++, col_it++) {
                    if (!col[index]->isStackable()) {
                        col[index]->setValue(std::to_string(col[index]->getValue() * 2));
                        col[index]->setStackable(true);
                        col.erase(col_it - 1);
                        _score += col[index]->getValue() * 2;
                    }
                }
            }
            void slideUp_stackTiles()
            {
                slideUp_stackColumn(_column1);
                slideUp_stackColumn(_column2);
                slideUp_stackColumn(_column3);
                slideUp_stackColumn(_column4);
                setLinesFromColumns();
            }
            void slideUp()
            {
                if (!_slideUp) {
                    _sliding = true;
                    _slideUp = true;

                    for (auto tile : _column1)
                        slideUp_setSpeedAndNextPos(_column1, tile);
                    for (auto tile : _column2)
                        slideUp_setSpeedAndNextPos(_column2, tile);
                    for (auto tile : _column3)
                        slideUp_setSpeedAndNextPos(_column3, tile);
                    for (auto tile : _column4)
                        slideUp_setSpeedAndNextPos(_column4, tile);
                } else {
                    bool end = true;

                    for (auto tile : _column1)
                        if (!slideUp_setPos(tile))
                            end = false;
                    for (auto tile : _column2)
                        if (!slideUp_setPos(tile))
                            end = false;
                    for (auto tile : _column3)
                        if (!slideUp_setPos(tile))
                            end = false;
                    for (auto tile : _column4)
                        if (!slideUp_setPos(tile))
                            end = false;
                    if (end) {
                        _sliding = false;
                        _slideUp = false;
                        setLinesFromColumns();
                        setColumnsFromLines();
                        slideUp_stackTiles();
                        generateTile();
                    }
                }
            }
            void slideDown_setSpeedAndNextPos(std::vector<Tile*> tmp, Tile *tile)
            {
                float move_number =
                    (tile->getPos().y == _max_y) ? 0 :
                    (tile->getPos().y == _max_y - _between_tile) ? 1 :
                    (tile->getPos().y == _max_y - (_between_tile * 2)) ? 2 : 3;
                int index;

                for (auto tmp_tile : tmp)
                    if (tmp_tile->getPos().y > tile->getPos().y)
                        move_number--;
                for (index = 0; tmp[index]; index++)
                    if (tmp[index] == tile)
                        break;
                if (index != tmp.size() - 1 && tmp[index + 1]->isStackable() &&
                    tmp[index + 1]->getValue() == tile->getValue()) {
                    move_number++;
                    if (tile->getPos().y + (_between_tile * move_number) < tmp[index + 1]->getNext())
                        move_number++;
                    tile->setStackable(false);
                }
                if (index != tmp.size() - 1 && !tmp[index + 1]->isStackable())
                    move_number++;
                tile->setSpeed(move_number);
                tile->setNext(tile->getPos().y + (_between_tile * move_number));
            }
            bool slideDown_setPos(Tile *tile)
            {
                bool end = true;

                if (tile->getPos().y < tile->getNext()) {
                    end = false;
                    tile->setPos(Vector2{tile->getPos().x, tile->getPos().y + tile->getSpeed() * 20});
                } else
                    tile->setPos(Vector2{tile->getPos().x, tile->getNext()});
                return (end);
            }
            void slideDown_stackColumn(std::vector<Tile*> &col)
            {
                std::vector<Tile*>::reverse_iterator col_it;

                if (col.size() < 2)
                    return;
                col_it = col.rbegin();
                for (int index = col.size() - 1; index >= 0; index--, col_it++) {
                    if (!col[index]->isStackable()) {
                        col[index]->setValue(std::to_string(col[index]->getValue() * 2));
                        col[index]->setStackable(true);
                        col.erase((col_it).base());
                        _score += col[index]->getValue() * 2;
                    }
                }
            }
            void slideDown_stackTiles()
            {
                slideDown_stackColumn(_column1);
                slideDown_stackColumn(_column2);
                slideDown_stackColumn(_column3);
                slideDown_stackColumn(_column4);
                setLinesFromColumns();
            }
            void slideDown()
            {
                if (!_slideDown) {
                    _sliding = true;
                    _slideDown = true;

                    for (int index = _column1.size() - 1; index >= 0; index--)
                        slideDown_setSpeedAndNextPos(_column1, _column1[index]);
                    for (int index = _column2.size() - 1; index >= 0; index--)
                        slideDown_setSpeedAndNextPos(_column2, _column2[index]);
                    for (int index = _column3.size() - 1; index >= 0; index--)
                        slideDown_setSpeedAndNextPos(_column3, _column3[index]);
                    for (int index = _column4.size() - 1; index >= 0; index--)
                        slideDown_setSpeedAndNextPos(_column4, _column4[index]);
                } else {
                    bool end = true;

                    for (auto tile : _column1)
                        if (!slideDown_setPos(tile))
                            end = false;
                    for (auto tile : _column2)
                        if (!slideDown_setPos(tile))
                            end = false;
                    for (auto tile : _column3)
                        if (!slideDown_setPos(tile))
                            end = false;
                    for (auto tile : _column4)
                        if (!slideDown_setPos(tile))
                            end = false;
                    if (end) {
                        _sliding = false;
                        _slideDown = false;
                        setLinesFromColumns();
                        setColumnsFromLines();
                        slideDown_stackTiles();
                        generateTile();
                    }
                }
            }
            int checkLeftSlide_checkTile(std::vector<Tile*> tmp, Tile *tile)
            {
                float move_number =
                    (tile->getPos().x == _min_x) ? 0 :
                    (tile->getPos().x == _min_x + _between_tile) ? 1 :
                    (tile->getPos().x == _min_x + (_between_tile * 2)) ? 2 : 3;
                int index;

                for (auto tmp_tile : tmp)
                    if (tmp_tile->getPos().x < tile->getPos().x)
                        move_number--;
                for (index = 0; tmp[index]; index++)
                    if (tmp[index] == tile)
                        break;
                if (index != 0 && tmp[index - 1]->isStackable() &&
                    tmp[index - 1]->getValue() == tile->getValue()) {
                    move_number++;
                    if (tile->getPos().x - (_between_tile * move_number) > tmp[index - 1]->getNext())
                        move_number++;
                }
                if (index != 0 && !tmp[index - 1]->isStackable())
                    move_number++;
                return (move_number);
            }
            bool checkLeftSlide()
            {
                bool canMove = false;

                for (auto tile : _line1)
                    if (checkLeftSlide_checkTile(_line1, tile) > 0)
                        canMove = true;
                for (auto tile : _line2)
                    if (checkLeftSlide_checkTile(_line2, tile) > 0)
                        canMove = true;
                for (auto tile : _line3)
                    if (checkLeftSlide_checkTile(_line3, tile) > 0)
                        canMove = true;
                for (auto tile : _line4)
                    if (checkLeftSlide_checkTile(_line4, tile) > 0)
                        canMove = true;
                return (canMove);
            }
            int checkRightSlide_checkTile(std::vector<Tile*> tmp, Tile *tile)
            {
                float move_number =
                    (tile->getPos().x == _max_x) ? 0 :
                    (tile->getPos().x == _max_x - _between_tile) ? 1 :
                    (tile->getPos().x == _max_x - (_between_tile * 2)) ? 2 : 3;
                int index;

                for (auto tmp_tile : tmp)
                    if (tmp_tile->getPos().x > tile->getPos().x)
                        move_number--;
                for (index = 0; tmp[index]; index++)
                    if (tmp[index] == tile)
                        break;
                if (index != tmp.size() - 1 && tmp[index + 1]->isStackable() &&
                    tmp[index + 1]->getValue() == tile->getValue()) {
                    move_number++;
                    if (tile->getPos().x + (_between_tile * move_number) < tmp[index + 1]->getNext())
                        move_number++;
                }
                if (index != tmp.size() - 1 && !tmp[index + 1]->isStackable())
                    move_number++;
                return (move_number);
            }
            bool checkRightSlide()
            {
                bool canMove = false;

                for (int index = _line1.size() - 1; index >= 0; index--)
                    if (checkRightSlide_checkTile(_line1, _line1[index]) > 0)
                        canMove = true;
                for (int index = _line2.size() - 1; index >= 0; index--)
                    if (checkRightSlide_checkTile(_line2, _line2[index]) > 0)
                        canMove = true;
                for (int index = _line3.size() - 1; index >= 0; index--)
                    if (checkRightSlide_checkTile(_line3, _line3[index]) > 0)
                        canMove = true;
                for (int index = _line4.size() - 1; index >= 0; index--)
                    if (checkRightSlide_checkTile(_line4, _line4[index]) > 0)
                        canMove = true;
                return (canMove);
            }
            int checkUpSlide_checkTile(std::vector<Tile*> tmp, Tile *tile)
            {
                float move_number =
                    (tile->getPos().y == _min_y) ? 0 :
                    (tile->getPos().y == _min_y + _between_tile) ? 1 :
                    (tile->getPos().y == _min_y + (_between_tile * 2)) ? 2 : 3;
                int index;
                
                for (auto tmp_tile : tmp)
                    if (tmp_tile->getPos().y < tile->getPos().y)
                        move_number--;
                for (index = 0; tmp[index]; index++)
                    if (tmp[index] == tile)
                        break;
                if (index != 0 && tmp[index - 1]->isStackable() &&
                    tmp[index - 1]->getValue() == tile->getValue()) {
                    move_number++;
                    if (tile->getPos().y - (_between_tile * move_number) > tmp[index - 1]->getNext())
                        move_number++;
                }
                if (index != 0 && !tmp[index - 1]->isStackable())
                    move_number++;
                return (move_number);
            }
            bool checkUpSlide()
            {
                bool canMove = false;

                for (auto tile : _column1)
                    if (checkUpSlide_checkTile(_column1, tile) > 0)
                        canMove = true;
                for (auto tile : _column2)
                    if (checkUpSlide_checkTile(_column2, tile) > 0)
                        canMove = true;
                for (auto tile : _column3)
                    if (checkUpSlide_checkTile(_column3, tile) > 0)
                        canMove = true;
                for (auto tile : _column4)
                    if (checkUpSlide_checkTile(_column4, tile) > 0)
                        canMove = true;
                return (canMove);
            }
            int checkDownSlide_checkTile(std::vector<Tile*> tmp, Tile *tile)
            {
                float move_number =
                    (tile->getPos().y == _max_y) ? 0 :
                    (tile->getPos().y == _max_y - _between_tile) ? 1 :
                    (tile->getPos().y == _max_y - (_between_tile * 2)) ? 2 : 3;
                int index;

                for (auto tmp_tile : tmp)
                    if (tmp_tile->getPos().y > tile->getPos().y)
                        move_number--;
                for (index = 0; tmp[index]; index++)
                    if (tmp[index] == tile)
                        break;
                if (index != tmp.size() - 1 && tmp[index + 1]->isStackable() &&
                    tmp[index + 1]->getValue() == tile->getValue()) {
                    move_number++;
                    if (tile->getPos().y + (_between_tile * move_number) < tmp[index + 1]->getNext())
                        move_number++;
                }
                if (index != tmp.size() - 1 && !tmp[index + 1]->isStackable())
                    move_number++;
                return (move_number);
            }
            bool checkDownSlide()
            {
                bool canMove = false;

                for (int index = _column1.size() - 1; index >= 0; index--)
                    if (checkDownSlide_checkTile(_column1, _column1[index]) > 0)
                        canMove = true;
                for (int index = _column2.size() - 1; index >= 0; index--)
                    if (checkDownSlide_checkTile(_column2, _column2[index]) > 0)
                        canMove = true;
                for (int index = _column3.size() - 1; index >= 0; index--)
                    if (checkDownSlide_checkTile(_column3, _column3[index]) > 0)
                        canMove = true;
                for (int index = _column4.size() - 1; index >= 0; index--)
                    if (checkDownSlide_checkTile(_column4, _column4[index]) > 0)
                        canMove = true;
                return (canMove);
            }
            bool isGameOver()
            {
                if (!checkLeftSlide() && !checkRightSlide() &&
                    !checkUpSlide() && !checkDownSlide())
                    return (true);
                return (false);
            }
            bool isGameWon()
            {
                for (auto tile : _line1)
                    if (tile->getValue() == 2048)
                        return (true);
                for (auto tile : _line2)
                    if (tile->getValue() == 2048)
                        return (true);
                for (auto tile : _line3)
                    if (tile->getValue() == 2048)
                        return (true);
                for (auto tile : _line4)
                    if (tile->getValue() == 2048)
                        return (true);
                return (false);
            }
            int getScore()
            {
                return (_score);
            }
            void update()
            {
                if (!_sliding && MyRayLib::myGetGamepadAxisMovement(0, 0) < 0 &&
                    checkLeftSlide())
                    slideLeft();
                if (!_sliding && MyRayLib::myIsKeyPressed(_left) &&
                    checkLeftSlide())
                    slideLeft();
                if (!_sliding && MyRayLib::myGetGamepadAxisMovement(0, 0) > 0 &&
                    checkRightSlide())
                    slideRight();
                if (!_sliding && MyRayLib::myIsKeyPressed(_right) &&
                    checkRightSlide())
                    slideRight();
                if (!_sliding && MyRayLib::myIsKeyPressed(_up) &&
                    checkUpSlide())
                    slideUp();
                if (!_sliding && MyRayLib::myIsKeyPressed(_down) &&
                    checkDownSlide())
                    slideDown();
                if (_slideLeft)
                    slideLeft();
                if (_slideRight)
                    slideRight();
                if (_slideUp)
                    slideUp();
                if (_slideDown)
                    slideDown();
            }
            void draw()
            {
                if (_slideLeft || _slideRight) {
                    for (auto tile : _line1)
                        tile->draw();
                    for (auto tile : _line2)
                        tile->draw();
                    for (auto tile : _line3)
                        tile->draw();
                    for (auto tile : _line4)
                        tile->draw();
                } else {
                    for (auto tile : _column1)
                        tile->draw();
                    for (auto tile : _column2)
                        tile->draw();
                    for (auto tile : _column3)
                        tile->draw();
                    for (auto tile : _column4)
                        tile->draw();
                }
            }
            void generateTile()
            {
                float chose_x;
                std::vector<float> possibles_x;
                float chose_y;
                std::vector<float> possibles_y;
                bool tiles1;
                bool tiles2;
                bool tiles3;
                bool tiles4;

                for (float x_index = _min_x; x_index <= _max_x; x_index += _between_tile) {
                    tiles1 = true;
                    tiles2 = true;
                    tiles3 = true;
                    tiles4 = true;
                    for (auto tile : _line1)
                        if (tile->getPos().x == x_index)
                            tiles1 = false;
                    for (auto tile : _line2)
                        if (tile->getPos().x == x_index)
                            tiles2 = false;
                    for (auto tile : _line3)
                        if (tile->getPos().x == x_index)
                            tiles3 = false;
                    for (auto tile : _line4)
                        if (tile->getPos().x == x_index)
                            tiles4 = false;
                    if (tiles1 || tiles2 || tiles3 || tiles4)
                        possibles_x.push_back(x_index);
                }
                chose_x = possibles_x[rand() % (possibles_x.size())];
                tiles1 = true;
                tiles2 = true;
                tiles3 = true;
                tiles4 = true;
                for (auto tile : _line1)
                    if (tile->getPos().x == chose_x && tile->getPos().y == _min_y)
                        tiles1 = false;
                for (auto tile : _line2)
                    if (tile->getPos().x == chose_x && tile->getPos().y == _min_y + _between_tile)
                        tiles2 = false;
                for (auto tile : _line3)
                    if (tile->getPos().x == chose_x && tile->getPos().y == _min_y + (_between_tile * 2))
                        tiles3 = false;
                for (auto tile : _line4)
                    if (tile->getPos().x == chose_x && tile->getPos().y == _max_y)
                        tiles4 = false;
                if (tiles1)
                    possibles_y.push_back(_min_y);
                if (tiles2)
                    possibles_y.push_back(_min_y + _between_tile);
                if (tiles3)
                    possibles_y.push_back(_min_y + (_between_tile * 2));
                if (tiles4)
                    possibles_y.push_back(_max_y);
                chose_y = possibles_y[rand() % (possibles_y.size())];
                std::string new_value = "2";
                if (chose_y == _min_y)
                    _line1.push_back(new Tile(new_value, Vector2{chose_x, chose_y}, Vector2{_width, _height}));
                else if (chose_y == _min_y + _between_tile)
                    _line2.push_back(new Tile(new_value, Vector2{chose_x, chose_y}, Vector2{_width, _height}));
                else if (chose_y == _min_y + (_between_tile * 2))
                    _line3.push_back(new Tile(new_value, Vector2{chose_x, chose_y}, Vector2{_width, _height}));
                else if (chose_y == _max_y)
                    _line4.push_back(new Tile(new_value, Vector2{chose_x, chose_y}, Vector2{_width, _height}));
                setColumnsFromLines();
                setLinesFromColumns();
            }
            void setKeys(std::vector<KeyboardKey> keys)
            {
                _up = keys[0];
                _down = keys[1];
                _left = keys[2];
                _right = keys[3];
            }
            void setDimensions(float min_x, float max_x, float min_y, float max_y, float between_tile)
            {
                _min_x = min_x;
                _max_x = max_x;
                _min_y = min_y;
                _max_y = max_y;
                _between_tile = between_tile;
            }
        private:
            float _width;
            float _height;
            Color _color;
            float _min_x;
            float _max_x;
            float _min_y;
            float _max_y;
            float _between_tile;
            std::vector<Tile*> _line1;
            std::vector<Tile*> _line2;
            std::vector<Tile*> _line3;
            std::vector<Tile*> _line4;
            std::vector<Tile*> _column1;
            std::vector<Tile*> _column2;
            std::vector<Tile*> _column3;
            std::vector<Tile*> _column4;
            bool _sliding = false;
            bool _slideUp = false;
            bool _slideDown = false;
            bool _slideLeft = false;
            bool _slideRight = false;
            KeyboardKey _up;
            KeyboardKey _down;
            KeyboardKey _left;
            KeyboardKey _right;
            int _score;
    };
}

#endif /* !RECTANGLERENDERER_HPP_ */
