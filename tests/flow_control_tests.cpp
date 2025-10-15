#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include "../src/funds_calculator.h"
#include "../src/gpu_model.h"

const double EPSILON = 0.001;


// 1. calculateTotalCost Flow Control Tests
TEST(CalculateTotalCost, BranchCoverage) {
    // TC1: Invalid input <- runningHours < 0 
    EXPECT_THROW({
        calculateTotalCost(1.0, 5, -1, 0.5);
    }, std::invalid_argument);

    // TC2: Invalid input <- dailyStorageCost < 0 
    EXPECT_THROW({
        calculateTotalCost(1.0, 5, 50, -0.5);
    }, std::invalid_argument);

    // TC3: Invalid input <- instanceCount <= 0 
    EXPECT_THROW({
        calculateTotalCost(1.0, 0, 50, 0.5);
    }, std::invalid_argument);

    // TC4: Invalid input <- hourlyRate < 0 (true)
    EXPECT_THROW({
        calculateTotalCost(-1.0, 5, 50, 0.5);
    }, std::invalid_argument);

    // TC5: Valid inputs
    EXPECT_NEAR(257.5, calculateTotalCost(1.0, 5, 50, 0.5), EPSILON);
}

// 2. calculateRemainingFunds Flow Control Tests
TEST(CalculateRemainingFunds, BranchCoverage) {
    // TC1: Invalid input <- runningHours < 0 
    EXPECT_THROW({
        calculateRemainingFunds(1000.0, 1.0, 5, -1, 0.5);
    }, std::invalid_argument);

    // TC2: Invalid input <- dailyStorageCost < 0 
    EXPECT_THROW({
        calculateRemainingFunds(1000.0, 1.0, 5, 50, -0.5);
    }, std::invalid_argument);

    // TC3: Invalid input <- instanceCount <= 0 
    EXPECT_THROW({
        calculateRemainingFunds(1000.0, 1.0, 0, 50, 0.5);
    }, std::invalid_argument);

    // TC4: Invalid input <- hourlyRate < 0 
    EXPECT_THROW({
        calculateRemainingFunds(1000.0, -1.0, 5, 50, 0.5);
    }, std::invalid_argument);

    // TC5: Valid inputs <- initialFunds < totalCost 
    EXPECT_NEAR(10.0, calculateRemainingFunds(10.0, 1.0, 5, 50, 0.5), EPSILON);

    // TC6: Valid inputs <- initialFunds >= totalCost 
    EXPECT_NEAR(742.5, calculateRemainingFunds(1000.0, 1.0, 5, 50, 0.5), EPSILON);
}

// 3. calculateFundsDuration Flow Control Tests
TEST(CalculateFundsDuration, BranchCoverage) {
    // TC1: Invalid input <- initialFunds < 0 (true)
    EXPECT_THROW({
        calculateFundsDuration(-1.0, 1.0, 5, 0.5);
    }, std::invalid_argument);

    // TC2: Invalid input <- hourlyRate < 0 (true)
    EXPECT_THROW({
        calculateFundsDuration(1000.0, -1.0, 5, 0.5);
    }, std::invalid_argument);

    // TC3: Invalid input <- instanceCount <= 0
    EXPECT_THROW({
        calculateFundsDuration(1000.0, 1.0, 0, 0.5);
    }, std::invalid_argument);

    // TC4: Invalid input <- dailyStorageCost < 0 
    EXPECT_THROW({
        calculateFundsDuration(1000.0, 1.0, 5, -0.5);
    }, std::invalid_argument);

    // TC5: Valid inputs <- initialFunds == 0 
    EXPECT_NEAR(0.0, calculateFundsDuration(0.0, 1.0, 5, 0.5), EPSILON);

    // TC6: Valid inputs <- initialFunds > 0, hourlyRate <= 0 && dailyStorageCost <= 0 
    EXPECT_NEAR(-1.0, calculateFundsDuration(1000.0, 0.0, 5, 0.0), EPSILON);

    // TC7: Valid inputs <- initialFunds > 0, hourlyRate <= 0 && dailyStorageCost > 0 
    EXPECT_NEAR(9600.0, calculateFundsDuration(1000.0, 0.0, 5, 0.5), EPSILON);

    // Valid inputs <- initialFunds > 0, hourlyRate > 0 && dailyStorageCost > 0 - enter while loop
    // TC8: remainingFunds <= 0 after storage deduction, loop ends 
    EXPECT_NEAR(0.0, calculateFundsDuration(2.5, 1.0, 5, 0.5), EPSILON); 

    // TC9: hoursToday > 24.0 (full day) for the first day, loops once then hoursToday <= 24.0 (partial day) for the second day, loop ends
    EXPECT_NEAR(25.0, calculateFundsDuration(2600.0, 1.0, 100, 0.5), EPSILON);  

    // TC10: hoursToday == 24.0 (partial day) for the first day, loop ends
    EXPECT_NEAR(24.0, calculateFundsDuration(2450.0, 1.0, 100, 0.5), EPSILON);
}

// 4. calculateTotalCostMultipleGpus Flow Control Tests
TEST(CalculateTotalCostMultipleGpus, BranchCoverage) {
    std::vector<GpuModel> gpuModels;
    GpuModel gpu1("Test1", 2.0, 1.0, 2);
    GpuModel gpu2("Test2", 3.0, 1.5, 3);
    GpuModel invalidGpu("Invalid", -1.0, -0.5, 0);

    // TC1: Invalid input <- gpuModels.empty() 
    EXPECT_THROW({
        calculateTotalCostMultipleGpus(gpuModels, 50);
    }, std::invalid_argument);

    // TC2: Invalid input <- runningHours < 0
    gpuModels = {gpu1, gpu2};
    EXPECT_THROW({
        calculateTotalCostMultipleGpus(gpuModels, -1);
    }, std::invalid_argument);

    // GPU validation loop branches
    // TC3: Invalid input gpu.getHourlyRate() < 0 
    gpuModels = {invalidGpu};
    EXPECT_THROW({
        calculateTotalCostMultipleGpus(gpuModels, 50);
    }, std::invalid_argument);

    // TC4: Invalid input <- gpu.getDailyStorageCost() < 0 
    GpuModel invalidStorageGpu("InvalidStorage", 1.0, -0.5, 2);
    gpuModels = {invalidStorageGpu};
    EXPECT_THROW({
        calculateTotalCostMultipleGpus(gpuModels, 50);
    }, std::invalid_argument);

    // TC5: Invalid input <- gpu.getNumInstances() <= 0 
    GpuModel invalidInstancesGpu("InvalidInstances", 1.0, 0.5, 0);
    gpuModels = {invalidInstancesGpu};
    EXPECT_THROW({
        calculateTotalCostMultipleGpus(gpuModels, 50);
    }, std::invalid_argument);

    // TC6: Valid inputs - loops once 
    gpuModels = {gpu1, gpu2};
    EXPECT_NEAR(669.5, calculateTotalCostMultipleGpus(gpuModels, 50), EPSILON);
}

// 5. calculateFundsDurationMultipleGpus Flow Control Tests
TEST(CalculateFundsDurationMultipleGpus, BranchCoverage) {
    std::vector<GpuModel> gpuModels;
    GpuModel gpu1("Test1", 2.0, 1.0, 2);
    GpuModel gpu2("Test2", 3.0, 1.5, 3);
    GpuModel invalidGpu("Invalid", -1.0, -0.5, 0);

    // TC1: Invalid input <- initialFunds < 0
    gpuModels = {gpu1, gpu2};
    EXPECT_THROW({
        calculateFundsDurationMultipleGpus(-1.0, gpuModels);
    }, std::invalid_argument);

    // TC2: Invalid input <- gpuModels.empty()
    gpuModels.clear();
    EXPECT_THROW({
        calculateFundsDurationMultipleGpus(1000.0, gpuModels);
    }, std::invalid_argument);

    // GPU validation loop branches
    // TC3: Invalid input <- gpu.getHourlyRate() < 0 
    gpuModels = {invalidGpu};
    EXPECT_THROW({
        calculateFundsDurationMultipleGpus(1000.0, gpuModels);
    }, std::invalid_argument);

    // TC4: Invalid input <- gpu.getDailyStorageCost() < 0 
    GpuModel invalidStorageGpu("InvalidStorage", 1.0, -0.5, 2);
    gpuModels = {invalidStorageGpu};
    EXPECT_THROW({
        calculateFundsDurationMultipleGpus(1000.0, gpuModels);
    }, std::invalid_argument);

    // TC5: Invalid input <- gpu.getNumInstances() <= 0 (true)
    GpuModel invalidInstancesGpu("InvalidInstances", 1.0, 0.5, 0);
    gpuModels = {invalidInstancesGpu};
    EXPECT_THROW({
        calculateFundsDurationMultipleGpus(1000.0, gpuModels);
    }, std::invalid_argument);

    // Escape validation loop
    // TC6: Valid GPUModels, initialFunds == 0
    gpuModels = {gpu1, gpu2};
    EXPECT_NEAR(0.0, calculateFundsDurationMultipleGpus(0.0, gpuModels), EPSILON);

    // Enter logic loop to calculate funds duration and escapes safely

    // TC7: Valid inpust, totalHourlyRate <= 0 && totalDailyStorageCost <= 0
    GpuModel zeroCostGpu("ZeroCost", 0.0, 0.0, 2);
    gpuModels = {zeroCostGpu};
    EXPECT_NEAR(-1.0, calculateFundsDurationMultipleGpus(1000.0, gpuModels), EPSILON);

    // TC8: Valid inputs, totalHourlyRate > 0 && totalDailyStorageCost > 0
    gpuModels = {gpu1, gpu2};
    EXPECT_NEAR(74.923, calculateFundsDurationMultipleGpus(1000.0, gpuModels), EPSILON);
}