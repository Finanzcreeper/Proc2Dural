#pragma once

#include <random>
#include <chrono>
#include <iostream>



std::mt19937 create_rng();
double flat_real_random(std::mt19937& rng, double min, double max);
int flat_int_random(std::mt19937& rng, int min, int max);

extern std::mt19937 global_rng;