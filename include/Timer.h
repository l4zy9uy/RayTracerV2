//
// Created by l4zy9uy on 3/19/24.
//

#ifndef RAYTRACERV2_INCLUDE_TIMER_H
#define RAYTRACERV2_INCLUDE_TIMER_H
#include <chrono>

class Timer {
public:
  Timer();
  ~Timer();
private:
  std::chrono::time_point<std::chrono::system_clock> start;
  std::chrono::time_point<std::chrono::system_clock> end;
};

#endif //RAYTRACERV2_INCLUDE_TIMER_H
