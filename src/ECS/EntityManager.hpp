//
// Created by Demon on 09/05/2022.
//

#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include <vector>
#include <memory>
#include <string>
#include "../MyRayLib/MyRayLib.hpp"
#include "Component.hpp"
#include "ECS.hpp"

namespace ECS {
    class Entity {
        public:
            Entity(std::string nameEntity) : name(nameEntity) {}
            virtual ~Entity() = default;

            template<typename T, typename... TArgs>
            inline T& addComponent(TArgs&&... args) {
                T* comp(new T(std::forward<TArgs>(args)...));
                std::unique_ptr<Component> uptr { comp };
                components.emplace_back(std::move(uptr));
                comp->entity = this;
                if (comp->init()) {
                    compArray[getComponentTypeID<T>()] = comp;
                    return *comp;
                }
                return *static_cast<T*>(nullptr);
            }

            template<typename T>
            inline T& getComponent() const {
                auto ptr(compArray[getComponentTypeID<T>()]);
                return *static_cast<T*>(ptr);
            }

            template<typename T>
            inline bool hasComponent() const {
                return compBitset[getComponentTypeID<T>()];
            }

            inline bool isActive() const {
                return active;
            }

            inline void destroy() {
                active = false;
            }

            inline void draw() {
                for (auto& comp : components) {
                    comp->draw();
                }
            }

            inline void update() {
                for (auto& comp : components)
                    comp->update();
            }

            std::string name;

        private:
            bool active;
            ComponentArray compArray;
            ComponentBitset compBitset;
            std::vector<std::unique_ptr<Component>> components;
    };
    class EntityManager {
        public:
            EntityManager() = default;
            ~EntityManager() = default;
            void draw()
            {
                for (auto& entity : entities)
                    entity->draw();
            }
            void update()
            {
                for (auto& entity : entities)
                    entity->update();
            }
            void addEntity(Entity *entity)
            {
                std::unique_ptr<Entity> uniquePtr {entity};

                entities.emplace_back(std::move(uniquePtr));
            }
            std::vector<std::unique_ptr<Entity>> entities;
    };
}

#endif //B_YEP_400_LIL_4_1_INDIESTUDIO_THIBAULT_CAMPAGNE_ENTITYMANAGER_HPP
