/*
** EPITECH PROJECT, 2022
** arcade_2048
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include "../ECS/EntityManager.hpp"
#include "../Renderer/Renderer.hpp"
#include "../Error/Error.hpp"
#include "Enum.hpp"
#include <map>

namespace Game {
    enum Mode {
        SOLO,
        DUO
    };
    static std::map<const char*, Mode> map_mode {
        {"solo", SOLO},
        {"duo", DUO}
    };
    class Core {
        public:
            Core()
            {
                WindowLoading();
                BaseGameLoading();
                Run();
                MyRayLib::myCloseWindow();
            }
            ~Core()
            {
                delete(_manager);
            }
            void WindowLoading()
            {
                MyRayLib::myInitWindow(1680, 1050, "2048");
                MyRayLib::mySetTargetFPS(60);
            }
            void BaseGameLoading()
            {
                ECS::Entity *title = new ECS::Entity("title");
                int title_size = MyRayLib::myMeasureText("2048", 150);

                _manager = new ECS::EntityManager();
                _manager->addEntity(title);
                title->addComponent<Renderer::TextRenderer>("2048", (1680/2) - (title_size/2), 100, 150, ORANGE);
                SoloGameLoading();
            }
            void SoloGameLoading()
            {
                ECS::Entity *board = new ECS::Entity("board");
                int tile_size = 150;
                int tile_between = 15;
                int tile_size_plus_between = tile_size + tile_between;
                int small_board_size = tile_size*4 + tile_between*3;
                int full_board_size = tile_size*4 + tile_between*5;
                Vector2 small_board_pos = {
                    (1680/2) - (small_board_size/2),
                    (1680/2) - (small_board_size/2 + 200)
                };
                Vector2 full_board_pos = {
                    small_board_pos.x - tile_between,
                    small_board_pos.y - tile_between
                };
                ECS::Entity *gametiles = new ECS::Entity("gametiles");

                _manager->addEntity(board);
                _manager->addEntity(gametiles);
                board->addComponent<Renderer::RectangleRenderer>(
                    full_board_pos.x,
                    full_board_pos.y,
                    full_board_size, full_board_size, Color{187, 173, 160, 255});
                board->addComponent<Renderer::MapRectangleRenderer>(tile_size, tile_size, Color{205, 193, 180, 255});
                board->getComponent<Renderer::MapRectangleRenderer>().setLines(true, Color{187, 173, 160, 255});
                for (float y = small_board_pos.y, i = 0;
                    y <= small_board_pos.y + tile_size_plus_between*3;
                    y += tile_size_plus_between, i++) {
                    for (float x = small_board_pos.x, u = 0;
                        x <= small_board_pos.x + tile_size_plus_between*3;
                        x += tile_size_plus_between, u++) {
                        board->getComponent<Renderer::MapRectangleRenderer>().addPosition(Vector2{x, y});
                    }
                }
                gametiles->addComponent<Renderer::GameTiles>(tile_size, tile_size, Color{238, 228, 218, 255});
                gametiles->getComponent<Renderer::GameTiles>().setKeys(std::vector<KeyboardKey>{KEY_Z, KEY_S, KEY_Q, KEY_D});
                gametiles->getComponent<Renderer::GameTiles>().setDimensions(
                    small_board_pos.x, small_board_pos.x + (tile_size_plus_between * 3),
                    small_board_pos.y, small_board_pos.y + (tile_size_plus_between * 3),
                    tile_size_plus_between);
                gametiles->getComponent<Renderer::GameTiles>().generateTile();
            }
            void Exit()
            {
                exit(0);
            }
            void Run()
            {
                while (!MyRayLib::myWindowShouldClose()) {
                    _manager->update();
                    MyRayLib::myBeginDrawing();
                    MyRayLib::myClearBackground(WHITE);
                    _manager->draw();
                    MyRayLib::myEndDrawing();
                    for (auto &entity : _manager->entities) {
                        if (entity.get()->name == "gametiles") {
                            if (entity.get()->getComponent<Renderer::GameTiles>().isGameOver() ||
                                entity.get()->getComponent<Renderer::GameTiles>().isGameWon()) {
                                MyRayLib::myCloseWindow();
                                std::cout << "Score: " << entity.get()->getComponent<Renderer::GameTiles>().getScore() << std::endl;
                                Exit();
                            }
                        }
                    }
                }
            }
        private:
            ECS::EntityManager *_manager;
    };
}

#endif /* !CORE_HPP_ */
