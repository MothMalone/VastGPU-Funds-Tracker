#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include "../src/funds_calculator.h"
#include "../src/gpu_model.h"

const double EPSILON = 0.001; 

// 3.1. calculateTotalCost Boundary Value Tests
TEST(CalculateTotalCostTest, BoundaryValueTests) {
    // TC1: Nomial values
    EXPECT_NEAR(257.5, calculateTotalCost(1.0, 5, 50, 0.5), EPSILON);
    
    // TC2-TC5: hourlyRate boundaries
    EXPECT_NEAR(7.5, calculateTotalCost(0.0, 5, 50, 0.5), EPSILON);  // TC2: min
    EXPECT_NEAR(10.0, calculateTotalCost(0.01, 5, 50, 0.5), EPSILON);  // TC3: min+
    EXPECT_NEAR(2505.0, calculateTotalCost(9.99, 5, 50, 0.5), EPSILON);  // TC4: max-
    EXPECT_NEAR(2507.5, calculateTotalCost(10.0, 5, 50, 0.5), EPSILON);  // TC5: max (simulate an imaginary maximum value)
    
    // TC6-TC9: instanceCount boundaries
    EXPECT_NEAR(51.5, calculateTotalCost(1.0, 1, 50, 0.5), EPSILON);  // TC6: min
    EXPECT_NEAR(103.0, calculateTotalCost(1.0, 2, 50, 0.5), EPSILON);  // TC7: min+
    EXPECT_NEAR(5098.5, calculateTotalCost(1.0, 99, 50, 0.5), EPSILON);  // TC8: max-
    EXPECT_NEAR(5150.0, calculateTotalCost(1.0, 100, 50, 0.5), EPSILON);  // TC9: max (simulate an imaginary maximum value)
    
    // TC10-TC13: runningHours boundaries
    EXPECT_NEAR(7.5, calculateTotalCost(1.0, 5, 1, 0.5), EPSILON);  // TC10: min
    EXPECT_NEAR(12.5, calculateTotalCost(1.0, 5, 2, 0.5), EPSILON);  // TC11: min+
    EXPECT_NEAR(5100.0, calculateTotalCost(1.0, 5, 999, 0.5), EPSILON);  // TC12: max-
    EXPECT_NEAR(5105.0, calculateTotalCost(1.0, 5, 1000, 0.5), EPSILON);  // TC13: max (simulate an imaginary maximum value)
    
    // TC14-TC17: dailyStorageCost boundaries
    EXPECT_NEAR(250.0, calculateTotalCost(1.0, 5, 50, 0.0), EPSILON);  // TC14: min
    EXPECT_NEAR(250.15, calculateTotalCost(1.0, 5, 50, 0.01), EPSILON);  // TC15: min+
    EXPECT_NEAR(324.85, calculateTotalCost(1.0, 5, 50, 4.99), EPSILON);  // TC16: max-
    EXPECT_NEAR(325.0, calculateTotalCost(1.0, 5, 50, 5.0), EPSILON);  // TC17: max (simulate an imaginary maximum value)
} 


// 3.2. calculateFundsDuration Boundary Value Tests
TEST(CalculateFundsDurationTest, BoundaryValueTests) {
    // TC1: nom values
    EXPECT_NEAR(195.5, calculateFundsDuration(1000.0, 1.0, 5, 0.5), EPSILON);
    
    // // TC2-TC5: initialFunds boundaries
    EXPECT_NEAR(0.0, calculateFundsDuration(0.0, 1.0, 5, 0.5), EPSILON); // TC2: min
    EXPECT_NEAR(0.0, calculateFundsDuration(0.01, 1.0, 5, 0.5), EPSILON); // TC3: min+
    EXPECT_NEAR(1958.998, calculateFundsDuration(9999.99, 1.0, 5, 0.5), EPSILON); // TC4: max-
    EXPECT_NEAR(1959.0, calculateFundsDuration(10000.0, 1.0, 5, 0.5), EPSILON);  // TC5: max (simulate an imaginary maximum value)
    
    // // TC6-TC9: hourlyRate boundaries
    EXPECT_NEAR(9600.0, calculateFundsDuration(1000.0, 0.0, 5, 0.5), EPSILON); // TC6: min
    EXPECT_NEAR(6480.0, calculateFundsDuration(1000.0, 0.01, 5, 0.5), EPSILON); // TC7: min+
    EXPECT_NEAR(19.969, calculateFundsDuration(1000.0, 9.99, 5, 0.5), EPSILON); // TC8: max-
    EXPECT_NEAR(19.95, calculateFundsDuration(1000.0, 10.0, 5, 0.5), EPSILON);  // TC9: max (simulate an imaginary maximum value)
    
    
    // // TC10-TC13: instanceCount boundaries
    EXPECT_NEAR(979.5, calculateFundsDuration(1000.0, 1.0, 1, 0.5), EPSILON); // TC10: min
    EXPECT_NEAR(489.5, calculateFundsDuration(1000.0, 1.0, 2, 0.5), EPSILON); // TC11: min+
    EXPECT_NEAR(9.601, calculateFundsDuration(1000.0, 1.0, 99, 0.5), EPSILON); // TC12: max-
    EXPECT_NEAR(9.5, calculateFundsDuration(1000.0, 1.0, 100, 0.5), EPSILON);  // TC13: max (simulate an imaginary maximum value)
    
    // // TC14-TC17: dailyStorageCost boundaries
    EXPECT_NEAR(200.0, calculateFundsDuration(1000.0, 1.0, 5, 0.0), EPSILON); // TC14: min
    EXPECT_NEAR(199.91, calculateFundsDuration(1000.0, 1.0, 5, 0.01), EPSILON); // TC15: min+
    EXPECT_NEAR(165.07, calculateFundsDuration(1000.0, 1.0, 5, 4.99), EPSILON); // TC16: max- 
    EXPECT_NEAR(165, calculateFundsDuration(1000.0, 1.0, 5, 5.0), EPSILON);  // TC17: max (simulate an imaginary maximum value)
    
}


// 3.3. calculateRemainingFunds Boundary Value Tests
TEST(CalculateRemainingFundsTest, BoundaryValueTests) {
    // TC1: Nominal values
    EXPECT_NEAR(742.5, calculateRemainingFunds(1000.0, 1.0, 5, 50, 0.5), EPSILON);  

    
    // TC2-TC5: initialFunds boundaries
    EXPECT_NEAR(0.0, calculateRemainingFunds(0.0, 1.0, 5, 50, 0.5), EPSILON); // TC2: min
    EXPECT_NEAR(0.01, calculateRemainingFunds(0.01, 1.0, 5, 50, 0.5), EPSILON); // TC3: min+
    EXPECT_NEAR(9742.49, calculateRemainingFunds(9999.99, 1.0, 5, 50, 0.5), EPSILON); // TC4: max-
    EXPECT_NEAR(9742.5, calculateRemainingFunds(10000.0, 1.0, 5, 50, 0.5), EPSILON);  // TC5: max (simulate an imaginary maximum value)

    
    // // TC6-TC9: hourlyRate boundaries
    EXPECT_NEAR(992.5, calculateRemainingFunds(1000.0, 0.0, 5, 50, 0.5), EPSILON); // TC6: min
    EXPECT_NEAR(990.0, calculateRemainingFunds(1000.0, 0.01, 5, 50, 0.5), EPSILON); // TC7: min+
    EXPECT_NEAR(1000.0, calculateRemainingFunds(1000.0, 9.99, 5, 50, 0.5), EPSILON); // TC8: max-
    EXPECT_NEAR(1000.0, calculateRemainingFunds(1000.0, 10.0, 5, 50, 0.5), EPSILON);  // TC9: max (simulate an imaginary maximum value)
    
    
    // // TC10-TC13: instanceCount boundaries
    EXPECT_NEAR(948.5, calculateRemainingFunds(1000.0, 1.0, 1, 50, 0.5), EPSILON); // TC10: min
    EXPECT_NEAR(897.0, calculateRemainingFunds(1000.0, 1.0, 2, 50, 0.5), EPSILON); // TC11: min+
    EXPECT_NEAR(1000.0, calculateRemainingFunds(1000.0, 1.0, 99, 50, 0.5), EPSILON); // TC12: max-
    EXPECT_NEAR(1000.0, calculateRemainingFunds(1000.0, 1.0, 100, 50, 0.5), EPSILON);  // TC13: max (simulate an imaginary maximum value)

    
    // // TC14-TC17: runningHours boundaries
    EXPECT_NEAR(992.5, calculateRemainingFunds(1000.0, 1.0, 5, 1, 0.5), EPSILON); // TC14: min
    EXPECT_NEAR(987.5, calculateRemainingFunds(1000.0, 1.0, 5, 2, 0.5), EPSILON); // TC15: min+
    EXPECT_NEAR(1000.0, calculateRemainingFunds(1000.0, 1.0, 5, 999, 0.5), EPSILON); // TC16: max-
    EXPECT_NEAR(1000.0, calculateRemainingFunds(1000.0, 1.0, 5, 1000, 0.5), EPSILON);  // TC17: max (simulate an imaginary maximum value)

    
    // // TC18-TC21: dailyStorageCost boundaries
    EXPECT_NEAR(750.0, calculateRemainingFunds(1000.0, 1.0, 5, 50, 0.0), EPSILON); // TC18: min
    EXPECT_NEAR(749.85, calculateRemainingFunds(1000.0, 1.0, 5, 50, 0.01), EPSILON); // TC19: min+
    EXPECT_NEAR(675.15, calculateRemainingFunds(1000.0, 1.0, 5, 50, 4.99), EPSILON); // TC20: max-
    EXPECT_NEAR(675, calculateRemainingFunds(1000.0, 1.0, 5, 50, 5.0), EPSILON);  // TC21: max (simulate an imaginary maximum value)
}



// 3.4. calculateTotalCostMultipleGpus Boundary Value Tests
TEST(CalculateTotalCostMultipleGpusTest, BoundaryValueTests) {
    std::vector<GpuModel> gpuModels;
    
    GpuModel gpu1("Test1", 2.0, 1.0, 2);
    GpuModel gpu2("Test2", 3.0, 1.5, 3);
    GpuModel gpu3("Test3", 1.0, 0.5, 1);
    
    // TC1: Nominal values (3 GPUs, 50 hours)
    gpuModels = {gpu1, gpu2, gpu3};
    EXPECT_NEAR(721.0, calculateTotalCostMultipleGpus(gpuModels, 50), EPSILON); 

    
    // TC2: 1 GPU
    gpuModels = {gpu1};
    EXPECT_NEAR(206.0, calculateTotalCostMultipleGpus(gpuModels, 50), EPSILON);  // TC2: min
    
    // TC3: 2 GPUs
    gpuModels = {gpu1, gpu2};
    EXPECT_NEAR(669.5, calculateTotalCostMultipleGpus(gpuModels, 50), EPSILON);  // TC3: min+
  
    
    // TC4: 9 GPUs
    gpuModels.clear();
    for (int i = 0; i < 9; i++) {
        gpuModels.push_back(GpuModel("GPU" + std::to_string(i), 1.0, 0.5, 1));
    }
    EXPECT_NEAR(463.5, calculateTotalCostMultipleGpus(gpuModels, 50), EPSILON);  // TC4: max-
    
    // TC5: 10 GPUs
    gpuModels.push_back(GpuModel("GPU9", 1.0, 0.5, 1));
    EXPECT_NEAR(515.0, calculateTotalCostMultipleGpus(gpuModels, 50), EPSILON);  // TC5: max (simulate an imaginary maximum value)

    
    gpuModels = {gpu1, gpu2};
    
    // TC6: 0 hours
    EXPECT_NEAR(0.0, calculateTotalCostMultipleGpus(gpuModels, 0), EPSILON);  // TC6: min
    
    // TC7: 1 hour
    EXPECT_NEAR(19.5, calculateTotalCostMultipleGpus(gpuModels, 1), EPSILON);  // TC7: min+
    
    // TC8: 999 hours
    EXPECT_NEAR(13260.0, calculateTotalCostMultipleGpus(gpuModels, 999), EPSILON);  // TC8: max-
    
    // TC9: 1000 hours
    EXPECT_NEAR(13273.0, calculateTotalCostMultipleGpus(gpuModels, 1000), EPSILON);  // TC9: max (simulate an imaginary maximum value)
}

// 3.5. calculateFundsDurationMultipleGpus Boundary Value Tests
TEST(CalculateFundsDurationMultipleGpusTest, BoundaryValueTests) {
    std::vector<GpuModel> gpuModels;
    

    GpuModel gpu1("Test1", 2.0, 1.0, 2);
    GpuModel gpu2("Test2", 3.0, 1.5, 3);
    GpuModel gpu3("Test3", 1.0, 0.5, 1);

    // TC1: Nominal values (3 GPUs, 1000 initialFunds)
    gpuModels = {gpu1, gpu2, gpu3};
    EXPECT_NEAR(69.929, calculateFundsDurationMultipleGpus(1000.0, gpuModels), EPSILON);  


    // TC2: Zero initialFunds
    EXPECT_NEAR(0.0, calculateFundsDurationMultipleGpus(0.0, gpuModels), EPSILON);  // TC2: min
    
    // TC3: Small initialFunds
    EXPECT_NEAR(0.0, calculateFundsDurationMultipleGpus(0.01, gpuModels), EPSILON);  // TC3: min+

    // TC4: Large initialFunds (near max)
    EXPECT_NEAR(699.285, calculateFundsDurationMultipleGpus(9999.99, gpuModels), EPSILON);  // TC4: max-
    
    // TC5: Max initialFunds
    EXPECT_NEAR(699.285, calculateFundsDurationMultipleGpus(10000.0, gpuModels), EPSILON);  // TC5: max (simulate an imaginary maximum value)
    
   
    
    // TC6: 1 GPU
    gpuModels = {gpu1};
    EXPECT_NEAR(244.5, calculateFundsDurationMultipleGpus(1000.0, gpuModels), EPSILON);   // TC6: min

     // TC7: 2 GPU
    gpuModels = {gpu1, gpu2};
    EXPECT_NEAR(74.923, calculateFundsDurationMultipleGpus(1000.0, gpuModels), EPSILON);  // TC6: min+
    
    
    // TC8: 9 GPUs
    gpuModels.clear();
    for (int i = 0; i < 9; i++) {
        gpuModels.push_back(GpuModel("GPU" + std::to_string(i), 1.0, 0.5, 1));
    }
    EXPECT_NEAR(108.611, calculateFundsDurationMultipleGpus(1000.0, gpuModels), EPSILON);  // TC8: max-
    
    // TC9: 10 GPUs
    gpuModels.push_back(GpuModel("GPU9", 1.0, 0.5, 1));
    EXPECT_NEAR(97.5, calculateFundsDurationMultipleGpus(1000.0, gpuModels), EPSILON);  // TC9: max (simulate an imaginary maximum value)
}