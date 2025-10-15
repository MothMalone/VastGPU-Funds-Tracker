#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include "../src/funds_calculator.h"
#include "../src/gpu_model.h"

const double EPSILON = 0.001;

// 4.1. calculateTotalCost Decision Table Tests
TEST(CalculateTotalCostTest, DecisionTableTests) {

    // TC1: Invalid input <- hourlyRate > 0, instanceCount > 0, runningHours < 0, any dailyStorageCost
    EXPECT_THROW({
        calculateTotalCost(1.0, 5, -50, 0.5);
    }, std::invalid_argument);

    // TC2: Invalid input <- hourlyRate > 0, instanceCount > 0, runningHours = 0, dailyStorageCost < 0
     EXPECT_THROW({
        calculateTotalCost(1.0, 5, 0, -0.5);
    }, std::invalid_argument);

    // TC3: Result = 0 <- hourlyRate > 0, instanceCount > 0, runningHours = 0, dailyStorageCost = 0
    EXPECT_NEAR(0.0, calculateTotalCost(1.0, 5, 0, 0.0), EPSILON);

    // TC4: Result = 0 <- hourlyRate > 0, instanceCount > 0, runningHours = 0, dailyStorageCost > 0
    EXPECT_NEAR(0.0, calculateTotalCost(1.0, 5, 0, 0.5), EPSILON);

    // TC5: Normal with running hours <- hourlyRate > 0, instanceCount > 0, runningHours > 0, dailyStorageCost > 0
    EXPECT_NEAR(257.5, calculateTotalCost(1.0, 5, 50, 0.5), EPSILON);


    // TC6: Only runtime <- hourlyRate > 0, instanceCount > 0, runningHours > 0, dailyStorageCost = 0
    EXPECT_NEAR(250.0, calculateTotalCost(1.0, 5, 50, 0.0), EPSILON);


    // TC7: Invalid input <- hourlyRate > 0, instanceCount > 0, runningHours > 0, dailyStorageCost < 0
     EXPECT_THROW({
        calculateTotalCost(1.0, 5, 50, -0.5);
    }, std::invalid_argument);
    
    // TC8: Invalid input <- hourlyRate > 0, instanceCount <= 0, any runningHours , any dailyStorageCost
     EXPECT_THROW({
        calculateTotalCost(1.0, 0, 50, 0.5);
    }, std::invalid_argument);
    
    // TC9: Invalid input <- hourlyRate < 0, any instanceCount, any runningHours, any dailyStorageCost
    EXPECT_THROW({
        calculateTotalCost(-1.0, 5, 50, 0.5);
    }, std::invalid_argument);
    
    // TC10: Invalid input <- hourlyRate = 0, instanceCount <= 0, any runningHours, any dailyStorageCost
    EXPECT_THROW({
        calculateTotalCost(0.0, -5, 50, 0.5);
    }, std::invalid_argument);


    // TC11: Only Storage <- hourlyRate = 0, instanceCount > 0, runningHours > 0, dailyStorageCost > 0
    EXPECT_NEAR(7.5, calculateTotalCost(0.0, 5, 50, 0.5), EPSILON);
    
    // TC12: Result = 0 <- hourlyRate = 0, instanceCount > 0, runningHours > 0, dailyStorageCost = 0
    EXPECT_NEAR(0.0, calculateTotalCost(0.0, 5, 50, 0.0), EPSILON);


    // TC13: Invalid input <- hourlyRate = 0, instanceCount > 0, runningHours > 0, dailyStorageCost < 0
    EXPECT_THROW({
        calculateTotalCost(0.0, 5, 50, -0.5);
    }, std::invalid_argument);


    // TC14: Result = 0 <- hourlyRate = 0, instanceCount > 0, runningHours = 0, dailyStorageCost > 0
    EXPECT_NEAR(0.0, calculateTotalCost(0.0, 5, 0, 0.5), EPSILON);
    
    // TC15: Result = 0 <- hourlyRate = 0, instanceCount > 0, runningHours = 0, dailyStorageCost = 0
    EXPECT_NEAR(0.0, calculateTotalCost(0.0, 5, 0, 0.0), EPSILON);


    // TC16: Invalid input <- hourlyRate = 0, instanceCount > 0, runningHours = 0, dailyStorageCost < 0
    EXPECT_THROW({
        calculateTotalCost(0.0, 5, 0, -0.5);
    }, std::invalid_argument);

    // TC17: Invalid input <- hourlyRate = 0, instanceCount > 0, runningHours < 0, any dailyStorageCost
    EXPECT_THROW({
        calculateTotalCost(0.0, 5, -50, 0.5);
    }, std::invalid_argument);
}


// 4.2. calculateFundsDuration Decision Table Tests 
TEST(CalculateFundsDurationTest, DecisionTableTests) {
    // TC1: Normal calculation <- initialFunds > 0, hourlyRate > 0, instanceCount > 0, dailyStorageCost > 0 
    EXPECT_NEAR(195.5, calculateFundsDuration(1000.0, 1.0, 5, 0.5), EPSILON);

    // TC2: Only runtime cost <- initialFunds > 0, hourlyRate > 0, instanceCount > 0, dailyStorageCost = 0
    EXPECT_NEAR(200.0, calculateFundsDuration(1000.0, 1.0, 5, 0.0), EPSILON);

    
    // TC3: Invalid input <- initialFunds > 0, hourlyRate > 0, instanceCount > 0, dailyStorageCost < 0
    EXPECT_THROW({
        calculateFundsDuration(1000.0, 1.0, 5, -0.5);
    }, std::invalid_argument);   
    
    // TC4: Invalid input <- initialFunds > 0, hourlyRate < 0, any instanceCount, any dailyStorageCost
    EXPECT_THROW({
        calculateFundsDuration(1000.0, -1.0, 5, 0.0);
    }, std::invalid_argument);
    
    
    // TC5: Only storage cost <- initialFunds > 0, hourlyRate = 0, instanceCount > 0, dailyStorageCost > 0
    EXPECT_NEAR(9600.0, calculateFundsDuration(1000.0, 0.0, 5, 0.5), EPSILON);
    
    // TC6: Funds last forever <- initialFunds > 0, hourlyRate = 0, instanceCount > 0, dailyStorageCost = 0
    EXPECT_NEAR(-1.0, calculateFundsDuration(1000.0, 0.0, 5, 0.0), EPSILON);

    // TC7: Invalid input <- initialFunds > 0, hourlyRate = 0, instanceCount > 0, dailyStorageCost < 0
    EXPECT_THROW({
        calculateFundsDuration(1000.0, 0.0, 5, -0.5);
    }, std::invalid_argument);

    // TC8: Invalid input <- initialFunds > 0, hourlyRate = 0, instanceCount <= 0, any dailyStorageCost
    EXPECT_THROW({
        calculateFundsDuration(1000.0, 0.0, -5, 0.0);
    }, std::invalid_argument);

    // TC9: Invalid input <- initialFunds > 0, hourlyRate < 0, instanceCount <= 0 (two errors)
    EXPECT_THROW({
        calculateFundsDuration(1000.0, -1.0, 0, 0.5);
    }, std::invalid_argument);
    
    // TC10: Invalid input <- initialFunds < 0, any costs & instanceCount
    EXPECT_THROW({
        calculateFundsDuration(-1000.0, 0.0, 5, 0.0);
    }, std::invalid_argument);
    
}


// 4.3. calculateRemainingFunds Decision Table Tests 
TEST(CalculateRemainingFundsTest, DecisionTableTests) {
    // TC1: Invalid input <- initialFunds >= totalCost, hourlyRate > 0, instanceCount > 0, runningHours < 0, any dailyStorageCost
    EXPECT_THROW({
        calculateRemainingFunds(1000.0, 1.0, 5, -50, 0.5);
    }, std::invalid_argument);

    // TC2: Invalid input <- initialFunds >= totalCost, hourlyRate > 0, instanceCount > 0, runningHours = 0, dailyStorageCost < 0
    EXPECT_THROW({
        calculateRemainingFunds(1000.0, 1.0, 5, 0, -0.5);
    }, std::invalid_argument);

    // TC3: Result = 0 <- initialFunds >= totalCost, hourlyRate > 0, instanceCount > 0, runningHours = 0, dailyStorageCost = 0
    EXPECT_NEAR(1000.0, calculateRemainingFunds(1000.0, 1.0, 5, 0, 0.0), EPSILON);

    // TC4: Result = 0 <- initialFunds >= totalCost, hourlyRate > 0, instanceCount > 0, runningHours = 0, dailyStorageCost > 0
    EXPECT_NEAR(1000.0, calculateRemainingFunds(1000.0, 1.0, 5, 0, 0.5), EPSILON);

    // TC5: Normal with running hours <- initialFunds >= totalCost, hourlyRate > 0, instanceCount > 0, runningHours > 0, dailyStorageCost > 0
    EXPECT_NEAR(742.5, calculateRemainingFunds(1000.0, 1.0, 5, 50, 0.5), EPSILON);


    // TC6: Only runtime <- initialFunds >= totalCost, hourlyRate > 0, instanceCount > 0, runningHours > 0, dailyStorageCost = 0
    EXPECT_NEAR(750.0, calculateRemainingFunds(1000.0, 1.0, 5, 50, 0.0), EPSILON);


    // TC7: Invalid input <- initialFunds >= totalCost, hourlyRate > 0, instanceCount > 0, runningHours > 0, dailyStorageCost < 0
    EXPECT_THROW({
        calculateRemainingFunds(1000.0, 1.0, 5, 50, -0.5);
    }, std::invalid_argument);

    // TC8: Invalid input <- initialFunds >= totalCost, hourlyRate > 0, instanceCount <= 0, any runningHours , any dailyStorageCost
    EXPECT_THROW({
        calculateRemainingFunds(1000.0, 1.0, 0, 50, 0.5);
    }, std::invalid_argument);
    
    // TC9: Invalid input <- initialFunds >= totalCost, hourlyRate < 0, any instanceCount, any runningHours, any dailyStorageCost
    EXPECT_THROW({
        calculateRemainingFunds(1000.0, -1.0, 5, 50, 0.5);
    }, std::invalid_argument);
    
    // TC10: Invalid input <- initialFunds >= totalCost, hourlyRate = 0, instanceCount <= 0, any runningHours, any dailyStorageCost
    EXPECT_THROW({
        calculateRemainingFunds(1000.0, 0.0, -5, 50, 0.5);
    }, std::invalid_argument);


    // TC11: Only Storage <- initialFunds >= totalCost, hourlyRate = 0, instanceCount > 0, runningHours > 0, dailyStorageCost > 0
    EXPECT_NEAR(992.5, calculateRemainingFunds(1000.0, 0.0, 5, 50, 0.5), EPSILON);
    
    // TC12: Result = 0 <- initialFunds >= totalCost, hourlyRate = 0, instanceCount > 0, runningHours > 0, dailyStorageCost = 0
    EXPECT_NEAR(1000.0, calculateRemainingFunds(1000.0,0.0, 5, 50, 0.0), EPSILON);


    // TC13: Invalid input <- initialFunds >= totalCost, hourlyRate = 0, instanceCount > 0, runningHours > 0, dailyStorageCost < 0
    EXPECT_THROW({
        calculateRemainingFunds(1000.0, 0.0, 5, 50, -0.5);
    }, std::invalid_argument);


    // TC14: Result = 0 <- initialFunds >= totalCost, hourlyRate = 0, instanceCount > 0, runningHours = 0, dailyStorageCost > 0
    EXPECT_NEAR(1000.0, calculateRemainingFunds(1000.0, 0.0, 5, 0, 0.5), EPSILON);
    
    // TC15: Result = 0 <- initialFunds >= totalCost, hourlyRate = 0, instanceCount > 0, runningHours = 0, dailyStorageCost = 0
    EXPECT_NEAR(1000.0, calculateRemainingFunds(1000.0, 0.0, 5, 0, 0.0), EPSILON);


    // TC16: Invalid input <- initialFunds >= totalCost, hourlyRate = 0, instanceCount > 0, runningHours = 0, dailyStorageCost < 0
    EXPECT_THROW({
        calculateRemainingFunds(1000.0, 0.0, 5, 0, -0.5);
    }, std::invalid_argument);

    // TC17: Invalid input <- initialFunds >= totalCost, hourlyRate = 0, instanceCount > 0, runningHours < 0, any dailyStorageCost
    EXPECT_THROW({
        calculateRemainingFunds(1000.0, 0.0, 5, -50, 0.5);
    }, std::invalid_argument);
    
    // TC18: Insufficient funds <- initialFunds < totalCost, any other values
    EXPECT_NEAR(10.0, calculateRemainingFunds(10.0, 1.0, 5, 50, 0.5), EPSILON);
}


// 4.4. calculateTotalCostMultipleGpus Decision Table Tests 
TEST(CalculateTotalCostMultipleGpusTest, DecisionTableTests) {
    std::vector<GpuModel> gpuModels;
    GpuModel gpu1("Test1", 2.0, 1.0, 2);
    GpuModel gpu2("Test2", 3.0, 1.5, 3);
    GpuModel invalidGpu("Invalid", -1.0, -1.0, -1);
    
    // TC1: Normal calculation <- gpuModels not empty, runningHours > 0, GPU valid 
    gpuModels = {gpu1, gpu2};
    EXPECT_NEAR(669.5, calculateTotalCostMultipleGpus(gpuModels, 50), EPSILON);

    // TC2: Invalid input <- gpuModels not empty, runningHours > 0, GPU with invalid values
    gpuModels = {invalidGpu};
    EXPECT_THROW({
        calculateTotalCostMultipleGpus(gpuModels, 50);
    }, std::invalid_argument);   
   
    
    // TC3: Result = 0 <- gpuModels not empty, runningHours = 0, GPU valid
    gpuModels = {gpu1, gpu2};
    EXPECT_NEAR(0.0, calculateTotalCostMultipleGpus(gpuModels, 0), EPSILON);
    
    
    // TC4: Invalid input <- gpuModels not empty, runningHours = 0, GPU invalid
    gpuModels = {invalidGpu};
    EXPECT_THROW({
        calculateTotalCostMultipleGpus(gpuModels, 0);
    }, std::invalid_argument);
    
    // TC5: Invalid input <- gpuModels not empty, runningHours < 0
    gpuModels = {gpu1}; 
    EXPECT_THROW({
        calculateTotalCostMultipleGpus(gpuModels, -1);
    }, std::invalid_argument);
    
    // TC6: Invalid input <- gpuModels empty
    gpuModels.clear();
    EXPECT_THROW({
        calculateTotalCostMultipleGpus(gpuModels, 50);
    }, std::invalid_argument);
}



// 4.5. calculateFundsDurationMultipleGpus Decision Table Tests (5 test cases)

TEST(CalculateFundsDurationMultipleGpusTest, DecisionTableTests) {
    std::vector<GpuModel> gpuModels;
    GpuModel gpu1("Test1", 2.0, 1.0, 2);
    GpuModel gpu2("Test2", 3.0, 1.5, 3);
    
    // TC1: Normal calculation <- initialFunds > 0, gpuModels not empty, totalCost > 0
    gpuModels = {gpu1, gpu2};
    EXPECT_NEAR(74.923, calculateFundsDurationMultipleGpus(1000.0, gpuModels), EPSILON);
    
    // TC2: Funds last forever <- initialFunds > 0, gpuModels not empty, totalCost = 0
    GpuModel zeroGpu("Zero", 0.0, 0.0, 2);
    gpuModels = {zeroGpu};
    EXPECT_NEAR(-1.0, calculateFundsDurationMultipleGpus(1000.0, gpuModels), EPSILON);
    
    // TC3: Invalid input <- initialFunds > 0, gpuModels not empty with negative values
    GpuModel negGpu("Invalid", -1.0, -1.0, -1);
    gpuModels = {negGpu};
    EXPECT_THROW({
        calculateFundsDurationMultipleGpus(1000.0, gpuModels);
    }, std::invalid_argument);
      
    // TC4: Invalid input <- initialFunds > 0, gpuModels empty
    gpuModels.clear();
    EXPECT_THROW({
        calculateFundsDurationMultipleGpus(1000.0, gpuModels);
    }, std::invalid_argument);
    
    // TC5: Invalid input <- initialFunds < 0
    gpuModels = {gpu1, gpu2};
    EXPECT_THROW({
        calculateFundsDurationMultipleGpus(-1.0, gpuModels);
    }, std::invalid_argument);
}