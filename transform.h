#ifndef TRANSFORM_H
#define TRANSFORM_H

// Enable use of gtx quaternions
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "engine_constants.h"
#include "extra_operators.h"
#include <vector>

using glm::vec3;

/*

Transform

Represents an affine transformation in 3D space
Can have a single parent and multiple children

*/
class Transform
{
public:
    Transform(const glm::vec3& pos = glm::vec3(0, 0, 0),
              const glm::vec3& rot = glm::vec3(0, 0, 0),
              const glm::vec3& scale = glm::vec3(1.0, 1.0, 1.0))
    {
        m_pos = pos;
        m_rot = rot;
        m_scale = scale;
        m_parent = NULL;
        m_recalcNeeded = true;
        recalcModel();
    }
    Transform(const Transform& other) : m_children(other.getChildren())
    {
        m_pos = other.getPos();
        m_rot = other.getRot();
        m_scale = other.getScale();
        m_parent = other.getParent();
        m_recalcNeeded = true;
        recalcModel();
    }

    void recalcModel()
    {
        if(m_recalcNeeded)
        {
            glm::mat4 posMatrix = glm::translate(m_pos);
            glm::mat4 scaleMatrix = glm::scale(m_scale);
            glm::mat4 rotXMatrix = glm::rotate(m_rot.x, glm::vec3(1.0, 0.0, 0.0));
            glm::mat4 rotYMatrix = glm::rotate(m_rot.y, glm::vec3(0.0, 1.0, 0.0));
            glm::mat4 rotZMatrix = glm::rotate(m_rot.z, glm::vec3(0.0, 0.0, 1.0));
            glm::mat4 rotMatrix = rotXMatrix * rotYMatrix * rotZMatrix;
            m_model = posMatrix * rotMatrix * scaleMatrix;
            m_recalcNeeded = false;
        }
    }

    // Get the Model for this transform - A mat4 that contains the position, rotation, and scale
    glm::mat4 getModel()
    {
        recalcModel();
        if(m_parent == NULL)
        {
            return m_model;
        }
        return m_parent->getModel() * m_model;
    }

    const glm::vec3& getPos() const { return m_pos; }
    const glm::vec3& getRot() const { return m_rot; }
    const glm::vec3& getScale() const { return m_scale; }

    void setPos(const vec3& pos)
    {
        m_pos = pos;
        m_recalcNeeded = true;
    }

    void setRot(const vec3& rot)
    {
        m_rot = rot;
        m_recalcNeeded = true;
    }

    void setScale(const vec3& scale)
    {
        m_scale = scale;
        m_recalcNeeded = true;
    }

    void move(const glm::vec3& delta)
    {
        m_recalcNeeded = true;
        m_pos += delta;
    }

    void rotate(const glm::vec3& delta)
    {
        m_recalcNeeded = true;
        m_rot += delta;
    }

    void addChild(Transform* t)
    {
        t->setParent(this);
        m_children.push_back(t);
    }

    void setParent(Transform* t)
    {
        m_parent = t;
    }

    Transform* getParent() const { return m_parent; }
    const vector<Transform*>& getChildren() const { return m_children; }

    virtual ~Transform() {}
protected:
    Transform* m_parent;
    glm::vec3 m_pos;
    glm::vec3 m_rot;
    glm::vec3 m_scale;
    glm::mat4 m_model;
    bool m_recalcNeeded;

    vector<Transform*> m_children;
};

#endif // TRANSFORM_H
