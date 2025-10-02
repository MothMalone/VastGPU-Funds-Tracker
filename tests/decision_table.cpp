#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include "../src/funds_calculator.h"
#include "../src/gpu_model.h"

const double EPSILON = 0.001;

// 4.1. calculateTotalCost Decision Table Tests
TEST(CalculateTotalCostTest, DecisionTableTests) {

    // TC1: Invalid input <- hourlyRate > 0, instanceCount > 0, runningHours < 0, any dailyStorageCost (not handled in function on unit level)
    // EXPECT("Invalid", calculateTotalCost(1.0, 5, -50, 0.5);

    // TC2: Invalid input <- hourlyRate > 0, instanceCount > 0, runningHours = 0, dailyStorageCost < 0 (not handled in function on unit level)
    // EXPECT("Invalid", calculateTotalCost(1.0, 5, 0, -0.5);

    // TC3: Result = 0 <- hourlyRate > 0, instanceCount > 0, runningHours = 0, dailyStorageCost = 0
    EXPECT_NEAR(0.0, calculateTotalCost(1.0, 5, 0, 0.0), EPSILON);

    // TC4: Result = 0 <- hourlyRate > 0, instanceCount > 0, runningHours = 0, dailyStorageCost > 0
    EXPECT_NEAR(0.0, calculateTotalCost(1.0, 5, 0, 0.5), EPSILON);

    // TC5: Normal with running hours <- hourlyRate > 0, instanceCount > 0, runningHours > 0, dailyStorageCost > 0
    EXPECT_NEAR(257.5, calculateTotalCost(1.0, 5, 50, 0.5), EPSILON);


    // TC6: Only runtime <- hourlyRate > 0, instanceCount > 0, runningHours > 0, dailyStorageCost = 0
    EXPECT_NEAR(250.0, calculateTotalCost(1.0, 5, 50, 0.0), EPSILON);


    // TC7: Invalid input <- hourlyRate > 0, instanceCount > 0, runningHours > 0, dailyStorageCost < 0 (not handled in function on unit level)
    // EXPECT("Invalid", calculateTotalCost(1.0, 5, 50, -0.5);
    
    // TC8: Invalid input <- hourlyRate > 0, instanceCount <= 0, any runningHours , any dailyStorageCost (not handled in function on unit level)
    // EXPECT("Invalid", calculateTotalCost(1.0, 0, 50, 0.5);
    
    // TC9: Invalid input <- hourlyRate < 0, any instanceCount, any runningHours, any dailyStorageCost (not handled in function on unit level)
    // EXPECT("Invalid", calculateTotalCost(-1.0, 0, 50, 0.5);
    
    // TC10: Invalid input <- hourlyRate = 0, instanceCount <= 0, any runningHours, any dailyStorageCost (not handled in function on unit level)
    // EXPECT("Invalid", calculateTotalCost(0.0, -5, 50, 0.5);


    // TC11: Only Storage <- hourlyRate = 0, instanceCount > 0, runningHours > 0, dailyStorageCost > 0
    EXPECT_NEAR(7.5, calculateTotalCost(0.0, 5, 50, 0.5), EPSILON);
    
    // TC12: Result = 0 <- hourlyRate = 0, instanceCount > 0, runningHours > 0, dailyStorageCost = 0
    EXPECT_NEAR(0.0, calculateTotalCost(0.0, 5, 50, 0.0), EPSILON);


    // TC13: Invalid input <- hourlyRate = 0, instanceCount > 0, runningHours > 0, dailyStorageCost < 0 (not handled in function on unit level)
    // EXPECT("Invalid", calculateTotalCost(0.0, 5, 50, -0.5);


    // TC14: Result = 0 <- hourlyRate = 0, instanceCount > 0, runningHours = 0, dailyStorageCost > 0
    EXPECT_NEAR(0.0, calculateTotalCost(0.0, 5, 0, 0.5), EPSILON);
    
    // TC15: Result = 0 <- hourlyRate = 0, instanceCount > 0, runningHours = 0, dailyStorageCost = 0
    EXPECT_NEAR(0.0, calculateTotalCost(0.0, 5, 0, 0.0), EPSILON);


    // TC16: Invalid input <- hourlyRate = 0, instanceCount > 0, runningHours = 0, dailyStorageCost < 0 (not handled in function on unit level)
    // EXPECT("Invalid", calculateTotalCost(0.0, 5, 0, -0.5);

    // TC17: Invalid input <- hourlyRate = 0, instanceCount > 0, runningHours < 0, any dailyStorageCost (not handled in function on unit level)
    // EXPECT("Invalid", calculateTotalCost(0.0, 5, -50, 0.5);
}


// 4.2. calculateFundsDuration Decision Table Tests 
TEST(CalculateFundsDurationTest, DecisionTableTests) {
    // TC1: Normal calculation <- initialFunds > 0, hourlyRate > 0, instanceCount > 0, dailyStorageCost > 0 
    EXPECT_NEAR(195.5, calculateFundsDuration(1000.0, 1.0, 5, 0.5), EPSILON);

    // TC2: Only runtime cost <- initialFunds > 0, hourlyRate > 0, instanceCount > 0, dailyStorageCost = 0
    EXPECT_NEAR(200.0, calculateFundsDuration(1000.0, 1.0, 5, 0.0), EPSILON);

    
    // TC3: Invalid input <- initialFunds > 0, hourlyRate > 0, instanceCount > 0, dailyStorageCost < 0   (not handled in function on unit level)
    //EXPECT("Invalid", calculateFundsDuration(1000.0, 1.0, 5, -0.5);   
    
    // TC4: Invalid input <- initialFunds > 0, hourlyRate < 0, any instanceCount, any dailyStorageCost  (not handled in function on unit level)
    // EXPECT("Invalid", calculateFundsDuration(1000.0, 1.0, 5, 0.0));
    
    
    // TC5: Only storage cost <- initialFunds > 0, hourlyRate = 0, instanceCount > 0, dailyStorageCost > 0
    EXPECT_NEAR(9600.0, calculateFundsDuration(1000.0, 0.0, 5, 0.5), EPSILON);
    
    // TC6: Funds last forever <- initialFunds > 0, hourlyRate = 0, instanceCount > 0, dailyStorageCost = 0
    EXPECT_NEAR(-1.0, calculateFundsDuration(1000.0, 0.0, 5, 0.0), EPSILON);

    // TC7: Invalid input <- initialFunds > 0, hourlyRate = 0, instanceCount > 0, dailyStorageCost < 0  (not handled in function on unit level)
    // EXPECT("Invalid", calculateFundsDuration(1000.0, 0.0, 5, -0.5);

    // TC8: Invalid input <- initialFunds > 0, hourlyRate = 0, instanceCount <= 0, any dailyStorageCost  (not handled in function on unit level)
    // EXPECT("Invalid", calculateFundsDuration(1000.0, 0.0, -5, 0.0);

    // TC9: Invalid input <- initialFunds > 0, hourlyRate < 0, instanceCount <= 0  (not handled in function on unit level)
    // EXPECT("Invalid", calculateFundsDuration(1000.0, 0.0, 0, 0.5);
    
    // TC10: Invalid input <- initialFunds <= 0, any costs & instanceCount   (not handled in function on unit level)
    // EEXPECT("Invalid", calculateFundsDuration(1000.0, 0.0, 0, 0.0);
    
}


// 4.3. calculateRemainingFunds Decision Table Tests 
TEST(CalculateRemainingFundsTest, DecisionTableTests) {
    // TC1: Invalid input <- initialFunds >= totalCost, hourlyRate > 0, instanceCount > 0, runningHours < 0, any dailyStorageCost (not handled in function on unit level)
    // EXPECT("Invalid", calculateRemainingFunds(1000.0 ,1.0, 5, -50, 0.5);

    // TC2: Invalid input <- initialFunds >= totalCost, hourlyRate > 0, instanceCount > 0, runningHours = 0, dailyStorageCost < 0 (not handled in function on unit level)
    // EXPECT("Invalid", calculateRemainingFunds(1000.0, 1.0, 5, 0, -0.5);

    // TC3: Result = 0 <- initialFunds >= totalCost, hourlyRate > 0, instanceCount > 0, runningHours = 0, dailyStorageCost = 0
    EXPECT_NEAR(1000.0, calculateRemainingFunds(1000.0, 1.0, 5, 0, 0.0), EPSILON);

    // TC4: Result = 0 <- initialFunds >= totalCost, hourlyRate > 0, instanceCount > 0, runningHours = 0, dailyStorageCost > 0
    EXPECT_NEAR(1000.0, calculateRemainingFunds(1000.0, 1.0, 5, 0, 0.5), EPSILON);

    // TC5: Normal with running hours <- initialFunds >= totalCost, hourlyRate > 0, instanceCount > 0, runningHours > 0, dailyStorageCost > 0
    EXPECT_NEAR(742.5, calculateRemainingFunds(1000.0, 1.0, 5, 50, 0.5), EPSILON);


    // TC6: Only runtime <- initialFunds >= totalCost, hourlyRate > 0, instanceCount > 0, runningHours > 0, dailyStorageCost = 0
    EXPECT_NEAR(750.0, calculateRemainingFunds(1000.0, 1.0, 5, 50, 0.0), EPSILON);


    // TC7: Invalid input <- initialFunds >= totalCost, hourlyRate > 0, instanceCount > 0, runningHours > 0, dailyStorageCost < 0 (not handled in function on unit level)
    // EXPECT("Invalid", calculateRemainingFunds(1000.0, 1.0, 5, 50, -0.5);

    // TC8: Invalid input <- initialFunds >= totalCost, hourlyRate > 0, instanceCount <= 0, any runningHours , any dailyStorageCost (not handled in function on unit level)
    // EXPECT("Invalid", calculateRemainingFunds(1000.0,1.0, 0, 50, 0.5);
    
    // TC9: Invalid input <- initialFunds >= totalCost, hourlyRate < 0, any instanceCount, any runningHours, any dailyStorageCost (not handled in function on unit level)
    // EXPECT("Invalid", calculateRemainingFunds(1000.0, -1.0, 0, 50, 0.5);
    
    // TC10: Invalid input <- initialFunds >= totalCost, hourlyRate = 0, instanceCount <= 0, any runningHours, any dailyStorageCost (not handled in function on unit level)
    // EXPECT("Invalid", calculateRemainingFunds(1000.0, 0.0, -5, 50, 0.5);


    // TC11: Only Storage <- initialFunds >= totalCost, hourlyRate = 0, instanceCount > 0, runningHours > 0, dailyStorageCost > 0
    EXPECT_NEAR(992.5, calculateRemainingFunds(1000.0, 0.0, 5, 50, 0.5), EPSILON);
    
    // TC12: Result = 0 <- initialFunds >= totalCost, hourlyRate = 0, instanceCount > 0, runningHours > 0, dailyStorageCost = 0
    EXPECT_NEAR(1000.0, calculateRemainingFunds(1000.0,0.0, 5, 50, 0.0), EPSILON);


    // TC13: Invalid input <- initialFunds >= totalCost, hourlyRate = 0, instanceCount > 0, runningHours > 0, dailyStorageCost < 0 (not handled in function on unit level)
    // EXPECT("Invalid", calculateRemainingFunds(1000.0, 0.0, 5, 50, -0.5);


    // TC14: Result = 0 <- initialFunds >= totalCost, hourlyRate = 0, instanceCount > 0, runningHours = 0, dailyStorageCost > 0
    EXPECT_NEAR(1000.0, calculateRemainingFunds(1000.0, 0.0, 5, 0, 0.5), EPSILON);
    
    // TC15: Result = 0 <- initialFunds >= totalCost, hourlyRate = 0, instanceCount > 0, runningHours = 0, dailyStorageCost = 0
    EXPECT_NEAR(1000.0, calculateRemainingFunds(1000.0, 0.0, 5, 0, 0.0), EPSILON);


    // TC16: Invalid input <- initialFunds >= totalCost, hourlyRate = 0, instanceCount > 0, runningHours = 0, dailyStorageCost < 0 (not handled in function on unit level)
    // EXPECT("Invalid", calculateRemainingFunds(1000.0, 0.0, 5, 0, -0.5);

    // TC17: Invalid input <- initialFunds >= totalCost, hourlyRate = 0, instanceCount > 0, runningHours < 0, any dailyStorageCost (not handled in function on unit level)
    // EXPECT("Invalid", calculateRemainingFunds(1000.0, 0.0, 5, -50, 0.5);
    
    // TC18: Insufficient funds <- initialFunds < totalCost, any other values
    EXPECT_NEAR(10.0, calculateRemainingFunds(10.0, 1.0, 5, 50, 0.5), EPSILON);
}