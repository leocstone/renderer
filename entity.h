#ifndef ENTITY_H
#define ENTITY_H
#include "component.h"
#include "transform.h"
#include <vector>

/*

Entity

Base class for anything that needs to be updated once per frame

*/
class Entity
{
public:

    Entity() {}
    virtual ~Entity() {}

    virtual void update();
    void addComponent(Component* c);

    Transform transform;

protected:

    std::vector<Component*> m_components;
};

#endif // ENTITY_H
