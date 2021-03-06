//
// Created by awbrenn on 10/16/16.
//

#ifndef SQUISHYMESH_MESH_H
#define SQUISHYMESH_MESH_H
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include "Vector.h"
#include "Face.h"

typedef struct FaceVertexIndex {
  unsigned int position_index;
  unsigned int uv_index;
  unsigned int normal_index;
} FaceVertexIndex;

class Mesh {
  private:
    std::vector<FaceVertexIndex> face_vertex_indices;

  public:
    std::vector<Vector3d> vertex_positions;
    std::vector<Vector2d> vertex_uvs;
    std::vector<Vector3d> vertex_normals;
    std::vector<Vertex> vertices;
    std::vector<Face> faces;

    bool loadObj(std::string obj_filename);
    Mesh copy(); // return a copy of the mesh
};


#endif //SQUISHYMESH_MESH_H
