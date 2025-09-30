#include "funds_calculator.h"
#include <cmath>

int calculateRunningDays(int runningHours) {
    return (runningHours + 23) / 24;
}

double calculateTotalCost(double hourlyRate, int instanceCount, int runningHours, double dailyStorageCost) {
    double runtimeCost = hourlyRate * (double)(instanceCount) * (double)(runningHours);
    
    int days = calculateRunningDays(runningHours);
    double storageCost = dailyStorageCost * (double)(instanceCount) * (double)(days);
    
    double totalCost = runtimeCost + storageCost;

    return std::round(totalCost * 100.0) / 100.0; 
}

double calculateRemainingFunds(double initialFunds, double totalCost) {
    return initialFunds - totalCost;
}

double calculateRemainingFunds(double initialFunds, double hourlyRate, int instanceCount, 
                                int runningHours, double dailyStorageCost) {
    double totalCost = calculateTotalCost(hourlyRate, instanceCount, runningHours, dailyStorageCost);

    return initialFunds - totalCost;
}

double calculateFundsDuration(double initialFunds, double hourlyRate, int instanceCount, double dailyStorageCost) {
    if (initialFunds <= 0 || instanceCount <= 0) {
        return 0.0;
    }
    
    if (hourlyRate <= 0 && dailyStorageCost <= 0) {
        return -1; 
    }

    if (hourlyRate <= 0) {
        return (initialFunds / (dailyStorageCost * instanceCount)) * 24.0; 
    }

    double hourlyRuntimeCost = hourlyRate * instanceCount;

    double totalDailyStorageCost = dailyStorageCost * instanceCount;

    double remainingFunds = initialFunds;
    double totalHours = 0.0;

    while (remainingFunds > 0) {
        remainingFunds -= totalDailyStorageCost;

        if (remainingFunds <= 0) {
            break;
        }
        double hoursToday = remainingFunds / hourlyRuntimeCost;

        if (hoursToday > 24.0) {
            totalHours += 24.0;
            remainingFunds -= hourlyRuntimeCost * 24.0;
        } else {
            totalHours += hoursToday;
            break;
        }
    }

    return totalHours;
}

double calculateTotalCostMultipleGpus(const std::vector<GpuModel>& gpuModels, int runningHours) {
    double totalCost = 0.0;
    for (const auto& gpu : gpuModels) {
        totalCost += calculateTotalCost(gpu.getHourlyRate(), gpu.getNumInstances(), 
                                        runningHours, gpu.getDailyStorageCost());
    }
    return totalCost;
}


double calculateFundsDurationMultipleGpus(double initialFunds, const std::vector<GpuModel>& gpuModels) {
    if (initialFunds <= 0 || gpuModels.empty()) {
        return 0.0;
    }

    double totalHourlyRate = 0.0;
    double totalDailyStorageCost = 0.0;
    int totalInstances = 0;

    for (const auto& gpu: gpuModels) {
        totalHourlyRate += gpu.getHourlyRate() * gpu.getNumInstances();
        totalDailyStorageCost += gpu.getDailyStorageCost() * gpu.getNumInstances();
        totalInstances += gpu.getNumInstances();
    }

    if (totalInstances == 0) {
        return 0.0;
    }

    if (totalHourlyRate <= 0 && totalDailyStorageCost <= 0) {
        return -1;
    }

    return calculateFundsDuration(initialFunds, totalHourlyRate, 1, totalDailyStorageCost);
}

