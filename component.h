#ifndef COMPONENT_H
#define COMPONENT_H

class Entity;

class Component
{
public:

    Component() {}
    virtual ~Component() {}

    virtual void Update() {}

    Entity* parent;

protected:

};

#endif // COMPONENT_H
