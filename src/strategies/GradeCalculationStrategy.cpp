#include "../../include/strategies/GradeCalculationStrategy.h"
#include "../../include/domain/Grade.h"
#include <numeric>
#include <algorithm>

// WeightedAverageStrategy
WeightedAverageStrategy::WeightedAverageStrategy(double pWeight, double lWeight, double eWeight)
    : presentationWeight(pWeight), labWeight(lWeight), examWeight(eWeight) {}

int WeightedAverageStrategy:: calculateFinalGrade(const std::vector<std::shared_ptr<Grade>>& grades) {
    if (grades.empty()) return 0;

    double presentationSum = 0, presentationCount = 0;
    double labSum = 0, labCount = 0;
    double examSum = 0, examCount = 0;

    for (const auto& grade : grades) {
        switch (grade->getType()) {
            case GradeType:: PRESENTATION:
                presentationSum += grade->getScore();
                presentationCount++;
                break;
            case GradeType::LAB:
                labSum += grade->getScore();
                labCount++;
                break;
            case GradeType::EXAM: 
                examSum += grade->getScore();
                examCount++;
                break;
        }
    }

    double finalGrade = 0;
    if (presentationCount > 0)
        finalGrade += (presentationSum / presentationCount) * presentationWeight;
    if (labCount > 0)
        finalGrade += (labSum / labCount) * labWeight;
    if (examCount > 0)
        finalGrade += (examSum / examCount) * examWeight;

    return static_cast<int>(finalGrade + 0.5);
}

// SimpleAverageStrategy
int SimpleAverageStrategy::calculateFinalGrade(const std::vector<std::shared_ptr<Grade>>& grades) {
    if (grades.empty()) return 0;

    int sum = std::accumulate(grades.begin(), grades.end(), 0,
                              [](int acc, const std::shared_ptr<Grade>& g) {
                                  return acc + g->getScore();
                              });
    return sum / grades.size();
}

// MaximumGradeStrategy
int MaximumGradeStrategy::calculateFinalGrade(const std::vector<std::shared_ptr<Grade>>& grades) {
    if (grades.empty()) return 0;

    return (*std::max_element(grades. begin(), grades.end(),
                             [](const std::shared_ptr<Grade>& a, const std::shared_ptr<Grade>& b) {
                                 return a->getScore() < b->getScore();
                             }))->getScore();
}