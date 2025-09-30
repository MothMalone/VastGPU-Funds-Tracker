#pragma once

#include "gpu_model.h"
#include <vector>

// Calculate total cost for a single GPU config
double calculateTotalCost(double hourlyRate, int numInstances, int runningTimeHours, double dailyStorageCost);

double calculateRemainingFunds(double initialFunds, double totalCost);

double calculateRemainingFunds(double initialFunds, double hourlyRate, int numInstances, 
                               int runningTimeHours, double dailyStorageCost);


double calculateFundsDuration(double initialFunds, double hourlyRate, int numInstances, double dailyStorageCost);


// Helper function to convert hours to days (for storage cost)
int calculateRunningDays(int runningTimeHours);

// Calculate total cost for all GPU configs
double calculateTotalCostMultipleGpus(const std::vector<GpuModel>& gpuModels, int runningHours);

double calculateFundsDurationMultipleGpus(double initialFunds, const std::vector<GpuModel>& gpuModels);


