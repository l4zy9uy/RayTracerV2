//
// Created by l4zy9uy on 3/19/24.
//

#include "Timer.h"
#include <iostream>

Timer::Timer() {
  start = std::chrono::high_resolution_clock::now();
}
Timer::~Timer() {
  end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << "Time taken: " << duration.count() << " milliseconds" << "\n";
}
