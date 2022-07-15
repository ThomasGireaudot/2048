/*
** EPITECH PROJECT, 2022
** arcade_2048
** File description:
** ECS
*/

#ifndef ECS_HPP_
#define ECS_HPP_

#include <array>
#include <bitset>
#include <iostream>

namespace ECS {
    class Entity;
    class Component;
}

using ComponentTypeID = std::size_t;

inline ComponentTypeID getUniqueComponentID() {
    static ComponentTypeID lastID = 0u;
    return lastID++;
}

template<typename T>
inline ComponentTypeID getComponentTypeID() noexcept {
    static_assert(std::is_base_of<ECS::Component, T>::value, "Type not base on component!");
    static const ComponentTypeID  typeID = getUniqueComponentID();
    return typeID;
}

constexpr std::size_t MAX_ENTITIES = 5000;
constexpr std::size_t MAX_COMPONENTS = 32;

using ComponentBitset = std::bitset<MAX_COMPONENTS>;
using ComponentArray = std::array<ECS::Component*, MAX_COMPONENTS>;

#endif /* !ECS_HPP_ */
