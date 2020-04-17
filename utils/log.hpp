#pragma once

// #include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>

#ifndef LOG_LVL_MATRIX_
std::fstream log_matrix;
#endif

#ifndef TIMESTAMP
std::time_t result = std::time(nullptr);
#endif

#define LOG_LVL_MATRIX_INIT()                                                                      \
  log_matrix.open("log/matrix.log", std::ios::trunc | std::ios::out);                              \
  log_matrix << "[Matrix] matrix with parameters {" << size_ << "} initialized" << std::endl;      \
  log_matrix.close()

#define LOG_LVL_MATRIX_ROUTINE(msg)                                                                \
  log_matrix.open("log/matrix.log", std::ios::app | std::ios::in);                                 \
  /* result = std::time(nullptr); */                                                               \
  log_matrix /* << std::asctime(std::localtime(&result))*/ << "[Matrix] " << msg << std::endl;     \
  log_matrix.close()

#define LOG_LVL_MATRIX_FAILURE(msg)                                                                \
  log_matrix.open("log/matrix.log", std::ios::app | std::ios::in);                                 \
  /* result = std::time(nullptr); */                                                               \
  log_matrix /* << std::asctime(std::localtime(&result))*/                                         \
      << "[Matrix] {FAILURE} " << msg << std::endl;                                                \
  log_matrix.close()
