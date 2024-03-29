//
// Created by l4zy9uy on 3/24/24.
//

#include "Parser.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "Shape/Triangle.h"
#include <glm/gtx/string_cast.hpp>

Parser parse_file_obj(const std::string &fileName) {
  std::ifstream f(fileName);
  std::vector<glm::dvec4> vertices(1, {0, 0, 0, 1});
  Group g;
  unsigned int cnt = 0;
  std::string s;
  while(getline(f, s)) {
    std::vector<std::string> temp_vector;
    split(temp_vector, s, ' ');
    if(temp_vector.size() < 4 || !is_numeric(temp_vector[1]) || !is_numeric(temp_vector[2]) || !is_numeric(temp_vector[3])) {
      cnt++;
      continue;
    }
    if(temp_vector[0] == "v") {
      if(temp_vector.size() != 4) {
        cnt++;
        continue;
      }
      else {
        vertices.emplace_back(std::stod(temp_vector[1]),
                              std::stod(temp_vector[2]),
                              std::stod(temp_vector[3]),
                              1);
      }
    }
    else if(temp_vector[0] == "f") {
      /*auto t = std::make_unique<Triangle>(vertices.at(std::stoul(temp_vector[1])),
                                          vertices.at(std::stoul(temp_vector[2])),
                                          vertices.at(std::stoul(temp_vector[3])));*/

      auto ts = fan_triangulation(vertices, temp_vector);
      for(const auto &t : ts) {
        g.addChild(std::make_unique<Triangle>(t));
      }
    }
    else {
      cnt++;
      continue;
    }
  }
  return {cnt, vertices, std::move(g)};
}
void split(std::vector<std::string> &v, const std::string &s, const char &delimiter) {
  std::stringstream ss(s);
  std::string token;
  while(getline(ss, token, delimiter)) {
    v.push_back(token);
  }
}
bool is_numeric(const std::string &s) {
  auto result = double();
  auto i = std::istringstream(s);
  i >> result;
  return !i.fail() && i.eof();
}
std::vector<Triangle> fan_triangulation(std::vector<glm::dvec4> &vertices,
                                        const std::vector<std::string> &string_vector) {
  std::vector<Triangle> ts;
  for(auto i = 2; i < string_vector.size() - 1; i++) {
    ts.emplace_back(vertices.at(std::stoul(string_vector.at(1))),
                    vertices.at(std::stoul(string_vector.at(i))),
                    vertices.at(std::stoul(string_vector.at(i+1))));
  }
  return ts;
}
void Parser::test(const std::string &path) {
  Assimp::Importer importer;
  auto scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
  if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
  {
    std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << "\n";
    return;
  }
  processNode(scene->mRootNode, scene);
}
void Parser::processNode(aiNode *node, const aiScene *scene) {
  for(unsigned int i = 0; i < node->mNumMeshes; i++)
  {
    aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
    groups_.push_back(processMesh(mesh));
  }
  // then do the same for each of its children
  for(unsigned int i = 0; i < node->mNumChildren; i++)
  {
    processNode(node->mChildren[i], scene);
  }
}
std::unique_ptr<Group> Parser::processMesh(aiMesh *mesh) {
  auto g = std::make_unique<Group>();
  for(auto i = 0; i < mesh->mNumFaces; i++) {
    auto f = mesh->mFaces[i];
    //std::cout << f.mNumIndices << "\n";
    auto p1 = convertAiVertex(mesh->mVertices[f.mIndices[0]]);
    auto p2 = convertAiVertex(mesh->mVertices[f.mIndices[1]]);
    auto p3 = convertAiVertex(mesh->mVertices[f.mIndices[2]]);
    /*std::cout << f.mIndices[0] << " " << glm::to_string(p1) << "\n";
    std::cout << f.mIndices[1] << " " << glm::to_string(p2) << "\n";
    std::cout << f.mIndices[2] << " " << glm::to_string(p3) << "\n";*/
    if(mesh->HasNormals()) {
      auto n1 = convertAiVector(mesh->mNormals[f.mIndices[0]]);
      auto n2 = convertAiVector(mesh->mNormals[f.mIndices[1]]);
      auto n3 = convertAiVector(mesh->mNormals[f.mIndices[2]]);
      g->addChild(std::make_unique<SmoothTriangle>(p1, p2, p3, n1, n2, n3));
    }
    else {
      g->addChild(std::make_unique<Triangle>(p1, p2, p3));
    }
  }
  return g;
}
glm::dvec4 Parser::convertAiVertex(const aiVector3D &vtx) {
  return {vtx.x, vtx.y, vtx.z, 1};
}
glm::dvec4 Parser::convertAiVector(const aiVector3D &vec) {
  return {vec.x, vec.y, vec.y, 0};
}
