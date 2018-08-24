#ifndef MESHRENDERER_H
#define MESHRENDERER_H
#include "unlitshader.h"
#include "mesh.h"
#include "texture.h"
#include "camera.h"
#include "transform.h"

/*

MeshRenderer

Links an instance of Transform and Mesh together, allowing the Mesh to be projected into a position

*/
class MeshRenderer
{
public:

    MeshRenderer() {}
    MeshRenderer(Mesh* m, Transform* tr) : m_mesh(m), m_transform(tr) {}
    ~MeshRenderer() {}

    inline Mesh* getMesh() { return m_mesh; }
    inline Transform* getTransform() { return m_transform; }

    void draw() { m_mesh->draw(); }

protected:
private:

    Mesh* m_mesh;
    Transform* m_transform;
};

#endif // MESHRENDERER_H
