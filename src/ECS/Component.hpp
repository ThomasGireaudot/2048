#ifndef COMPONENT_HPP
#define COMPONENT_HPP

namespace ECS {
    class Entity;
    class Component {
        public:
            Component() = default;
            virtual ~Component() = default;
            virtual bool init() {return (true);}
            virtual void draw() {}
            virtual void update() {}
            Entity *entity;
    };
}

#endif