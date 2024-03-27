//
// Created by l4zy9uy on 3/24/24.
//

#ifndef RAYTRACERV2_INCLUDE_PARSER_H
#define RAYTRACERV2_INCLUDE_PARSER_H
#include <glm/vec4.hpp>
#include <string>
#include <vector>
#include "Shape/Group.h"
#include "Shape/Triangle.h"
#include "Shape/SmoothTriangle.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct Parser {
  unsigned int num_line_ignored;
  std::vector<glm::dvec4> vertices;
  Group defaultGroup;
  std::vector<std::unique_ptr<Group>> groups_;
  std::unique_ptr<Group> processMesh(aiMesh *mesh);
  void test(const std::string &path);
  void processNode(aiNode *node, const aiScene *scene);
  static glm::dvec4 convertAiVertex(const aiVector3D &vtx);
  static glm::dvec4 convertAiVector(const aiVector3D &vec);
};

Parser parse_file_obj(const std::string &fileName);
void split(std::vector<std::string> &v, const std::string &s, const char &delimiter);
bool is_numeric(std::string const & s);
std::vector<Triangle> fan_triangulation(std::vector<glm::dvec4> &vertices,
                                        const std::vector<std::string> &string_vector);

#endif //RAYTRACERV2_INCLUDE_PARSER_H
