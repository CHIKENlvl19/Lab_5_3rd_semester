#pragma once

#include "../services/GradeService.h"
#include <vector>
#include <memory>

class Grade;

// Concrete Strategy 1: Weighted Average
class WeightedAverageStrategy : public IGradeCalculationStrategy {
private:
    double presentationWeight = 0.3;
    double labWeight = 0.3;
    double examWeight = 0.4;

public:
    WeightedAverageStrategy(double pWeight = 0.3, double lWeight = 0.3, double eWeight = 0.4);
    int calculateFinalGrade(const std::vector<std::shared_ptr<Grade>>& grades) override;
};

// Concrete Strategy 2: Simple Average
class SimpleAverageStrategy : public IGradeCalculationStrategy {
public:
    int calculateFinalGrade(const std::vector<std::shared_ptr<Grade>>& grades) override;
};

// Concrete Strategy 3: Maximum Grade
class MaximumGradeStrategy : public IGradeCalculationStrategy {
public:
    int calculateFinalGrade(const std::vector<std::shared_ptr<Grade>>& grades) override;
};