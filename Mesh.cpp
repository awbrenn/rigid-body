//
// Created by awbrenn on 10/16/16.
//

#include "Mesh.h"

bool Mesh::loadObj(std::string obj_filename) {
  bool succeeded = true;
  std::string line;
  std::ifstream obj_file(obj_filename);

  if (obj_file.is_open()) {
    // read through the file
    while (getline(obj_file, line)) {
      std::stringstream line_stream(line);
      std::string type;
      line_stream >> type;

      if (type.compare("v") == 0) {
        Vector3d position;
        line_stream >> position.x >> position.y >> position.z;
        vertex_positions.push_back(position);
//        std::cout << vertex.x << " " << vertex.y << " " << vertex.z << std::endl;
      }
      else if (type.compare("vt") == 0) {
        Vector2d uv;
        line_stream >> uv.x >> uv.y;
        vertex_uvs.push_back(uv);
//        std::cout << uv.x << " " << uv.y << " " << std::endl;
      }
      else if (type.compare("vn") == 0) {
        Vector3d normal;
        line_stream >> normal.x >> normal.y >> normal.z;
        vertex_normals.push_back(normal);
//        std::cout << normal.x << " " << normal.y << " " << normal.z << std::endl;
      }
      else if (type.compare("f") == 0) {
        unsigned int position_index[3], uv_index[3], normal_index[3];
        char delimiter;
        line_stream >> position_index[0] >> delimiter >> uv_index[0] >> delimiter >> normal_index[0]
                    >> position_index[1] >> delimiter >> uv_index[1] >> delimiter >> normal_index[1]
                    >> position_index[2] >> delimiter >> uv_index[2] >> delimiter >> normal_index[2];


//        std::cout << position_index[0] << " " << uv_index[0] << " " << normal_index[0] << std::endl
//                  << position_index[1] << " " << uv_index[1] << " " << normal_index[1] << std::endl
//                  << position_index[2] << " " << uv_index[2] << " " << normal_index[2] << std::endl << std::endl;

        // push back these three vertices
        for (int i = 0; i < 3; ++i) {
          vertices.push_back(Vertex(&vertex_positions[position_index[i]-1],
                                    &vertex_uvs[position_index[i]-1],
                                    &vertex_positions[position_index[i]-1]));
        }
      }
    }
  }
  else {
    succeeded = false;
  }

  // add the faces
  for (size_t i = 0; i < vertices.size(); i+=3) {
    faces.push_back(Face(&vertices[i], &vertices[i+1], &vertices[i+2]));
  }

  return succeeded;
}
