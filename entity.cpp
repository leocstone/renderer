#include "entity.h"

void Entity::update()
{
    for(unsigned i = 0; i < m_components.size(); i++)
    {
        m_components[i]->Update();
    }
}

void Entity::addComponent(Component* c)
{
    m_components.push_back(c);
    c->parent = this;
}
