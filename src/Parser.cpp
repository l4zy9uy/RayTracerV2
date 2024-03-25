//
// Created by l4zy9uy on 3/24/24.
//

#include "Parser.h"
#include <fstream>
#include <sstream>
#include "Shape/Triangle.h"

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
