#include <iostream>
#include "../src/funds_calculator.h"

int main() {
    double initialFunds = 9999.99;
    double hourlyRate = 1.0;
    int instanceCount = 5;
    double dailyStorageCost = 0.5;
    
    double duration = calculateFundsDuration(initialFunds, hourlyRate, instanceCount, dailyStorageCost);
    
    std::cout << "Calculated duration: " << duration << " hours" << std::endl;
    std::cout << "Expected duration: 1959.5 hours" << std::endl;
    std::cout << "Difference: " << (1959.5 - duration) << " hours" << std::endl;
    
    // Debug calculation
    double hourlyRuntimeCost = hourlyRate * instanceCount; // 5.0
    double totalDailyStorageCost = dailyStorageCost * instanceCount; // 2.5
    
    std::cout << "\nDebug calculations:" << std::endl;
    std::cout << "Hourly runtime cost: " << hourlyRuntimeCost << std::endl;
    std::cout << "Daily storage cost: " << totalDailyStorageCost << std::endl;
    
    double remainingFunds = initialFunds;
    double days = 0;
    
    // Calculate full days
    while (remainingFunds > totalDailyStorageCost + (hourlyRuntimeCost * 24)) {
        days++;
        remainingFunds -= totalDailyStorageCost + (hourlyRuntimeCost * 24);
    }
    
    // Calculate partial day
    remainingFunds -= totalDailyStorageCost; // Subtract storage cost for partial day
    double partialDay = 0;
    if (remainingFunds > 0) {
        partialDay = remainingFunds / hourlyRuntimeCost;
    }
    
    std::cout << "Manual calculation: " << (days * 24 + partialDay) << " hours" << std::endl;
    std::cout << "Full days: " << days << std::endl;
    std::cout << "Partial day hours: " << partialDay << std::endl;
    
    return 0;
}