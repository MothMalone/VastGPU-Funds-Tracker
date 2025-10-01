#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include "../src/funds_calculator.h"
#include "../src/gpu_model.h"

const double EPSILON = 0.001; 

// 3.1. calculateTotalCost
TEST(CalculateTotalCostTest, BoundaryValueTests) {
    // TC1: nom values
    EXPECT_NEAR(257.5, calculateTotalCost(1.0, 5, 50, 0.5), EPSILON);
    
    // TC2-TC5: hourlyRate boundaries
    EXPECT_NEAR(7.5, calculateTotalCost(0.0, 5, 50, 0.5), EPSILON);  // TC2: min
    EXPECT_NEAR(10.0, calculateTotalCost(0.01, 5, 50, 0.5), EPSILON);  // TC3: min+
    EXPECT_NEAR(2505.0, calculateTotalCost(9.99, 5, 50, 0.5), EPSILON);  // TC4: max-
    EXPECT_NEAR(2507.5, calculateTotalCost(10.0, 5, 50, 0.5), EPSILON);  // TC5: max
    
    // TC6-TC9: instanceCount boundaries
    EXPECT_NEAR(51.5, calculateTotalCost(1.0, 1, 50, 0.5), EPSILON);  // TC6: min
    EXPECT_NEAR(103.0, calculateTotalCost(1.0, 2, 50, 0.5), EPSILON);  // TC7: min+
    EXPECT_NEAR(5098.5, calculateTotalCost(1.0, 99, 50, 0.5), EPSILON);  // TC8: max-
    EXPECT_NEAR(5150.0, calculateTotalCost(1.0, 100, 50, 0.5), EPSILON);  // TC9: max
    
    // TC10-TC13: runningHours boundaries
    EXPECT_NEAR(7.5, calculateTotalCost(1.0, 5, 1, 0.5), EPSILON);  // TC10: min
    EXPECT_NEAR(12.5, calculateTotalCost(1.0, 5, 2, 0.5), EPSILON);  // TC11: min+
    EXPECT_NEAR(5100.0, calculateTotalCost(1.0, 5, 999, 0.5), EPSILON);  // TC12: max-
    EXPECT_NEAR(5105.0, calculateTotalCost(1.0, 5, 1000, 0.5), EPSILON);  // TC13: max
    
    // TC14-TC17: dailyStorageCost boundaries
    EXPECT_NEAR(250.0, calculateTotalCost(1.0, 5, 50, 0.0), EPSILON);  // TC14: min
    EXPECT_NEAR(250.15, calculateTotalCost(1.0, 5, 50, 0.01), EPSILON);  // TC15: min+
    EXPECT_NEAR(324.85, calculateTotalCost(1.0, 5, 50, 4.99), EPSILON);  // TC16: max-
    EXPECT_NEAR(325.0, calculateTotalCost(1.0, 5, 50, 5.0), EPSILON);  // TC17: max
}


