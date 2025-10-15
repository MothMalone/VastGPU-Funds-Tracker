#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "funds_calculator.h"
#include "gpu_model.h"

int main() {
    std::cout << "VastGPU Funds Tracker\n\n";
    
    double initialFunds;
    std::cout << "Enter initial funds: $";
    std::cin >> initialFunds;
    while (!(initialFunds > 0.0) || std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Invalid input. Please enter a positive value: $";
        std::cin >> initialFunds;
    }
    
    int numModels;
    std::cout << "Enter number of different GPU models: ";
    std::cin >> numModels;
    while (numModels < 1 || std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Invalid input. Please enter at least 1 model: ";
        std::cin >> numModels;
    }
    
    std::vector<GpuModel> gpuModels;
    
    for (int i = 0; i < numModels; i++) {
        std::cout << "\n--- GPU Model " << (i+1) << " ---" << std::endl;
        
        std::string name;
        std::cout << "Enter GPU model name (e.g., A80, RTX3090): ";
        std::cin >> name;
        
        double hourlyRate;
        std::cout << "Enter hourly cost for " + name + ": $";
        std::cin >> hourlyRate;
        while (hourlyRate < 0.0 || std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please enter a non-negative value: $";
            std::cin >> hourlyRate;
        }
        
        double dailyStorageCost;
        std::cout << "Enter daily storage cost for " + name + ": $";
        std::cin >> dailyStorageCost;
        while (dailyStorageCost < 0.0 || std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please enter a non-negative value: $";
            std::cin >> dailyStorageCost;
        }
        
        int instances;
        std::cout << "Enter number of " + name + " instances: ";
        std::cin >> instances;
        while (instances < 1 || std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please enter at least 1 instance: ";
            std::cin >> instances;
        }
        
        GpuModel model(name, hourlyRate, dailyStorageCost, instances);
        gpuModels.push_back(model);
    }
    
    int runningTimeHours;
    std::cout << "\nEnter approximate running time (in hours): ";
    std::cin >> runningTimeHours;
    while (runningTimeHours < 0 || std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Invalid input. Please enter a non-negative value: ";
        std::cin >> runningTimeHours;
    }
    
    double totalCost = calculateTotalCostMultipleGpus(gpuModels, runningTimeHours);
    double remainingFunds = calculateRemainingFunds(initialFunds, totalCost);
    double fundsDuration = calculateFundsDurationMultipleGpus(initialFunds, gpuModels);
    
    std::cout << "\n================ RESULTS =================" << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    

    std::cout << "\nCosts by GPU model:" << std::endl;
    std::cout << std::setw(15) << "GPU Model" << std::setw(10) << "Instances" 
              << std::setw(15) << "Hourly Rate" << std::setw(15) << "Storage Cost" 
              << std::setw(15) << "Total Cost" << std::endl;
    std::cout << std::string(70, '-') << std::endl;
    
    for (const auto& gpu : gpuModels) {
        double modelCost = calculateTotalCost(gpu.getHourlyRate(), gpu.getNumInstances(), 
                                            runningTimeHours, gpu.getDailyStorageCost());
        std::cout << std::setw(15) << gpu.getName() 
                  << std::setw(10) << gpu.getNumInstances()
                  << std::setw(15) << "$" << gpu.getHourlyRate()
                  << std::setw(15) << "$" << gpu.getDailyStorageCost()
                  << std::setw(15) << "$" << modelCost << std::endl;
    }
    
    std::cout << "\nSummary:" << std::endl;
    
    int totalInstances = 0;
    for (const auto& gpu : gpuModels) {
        totalInstances += gpu.getNumInstances();
    }
    
    std::cout << "Total instances: " << totalInstances << std::endl;
    std::cout << "Total cost for " << runningTimeHours << " hours: $" << totalCost << std::endl;
    std::cout << "Initial funds: $" << initialFunds << std::endl;
    
    
    if (fundsDuration > 0) {
        std::cout << "Funds will last approximately " << fundsDuration << " hours with all GPU models" << std::endl;
        int days = (int)(fundsDuration) / 24;
        int hours = (int)(fundsDuration) % 24;
        std::cout << "(" << days << " days and " << hours << " hours)" << std::endl;
        std::cout << "Remaining funds: $" << remainingFunds << std::endl;
    } else if (fundsDuration == -1) {
        std::cout << "Funds will last indefinitely (no ongoing costs)" << std::endl;
        std::cout << "Remaining funds: $" << remainingFunds << std::endl;
    } else {
        std::cout << "Funds insufficient for any duration" << std::endl;
    }
    
    std::cout << "=========================================" << std::endl;

    return 0;
}