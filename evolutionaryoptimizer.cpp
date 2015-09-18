#include "evolutionaryoptimizer.hpp"

EvolutionaryOptimizer::EvolutionaryOptimizer() {}

void EvolutionaryOptimizer::startTimer()
{
    this->startTime = std::chrono::steady_clock::now();
}

void EvolutionaryOptimizer::stopTimer()
{
    this->stopTime = std::chrono::steady_clock::now();

    this->executionTime = this->stopTime - this->startTime;
}
