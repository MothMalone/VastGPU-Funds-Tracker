#ifndef GPU_MODEL_H
#define GPU_MODEL_H

#include <string>

class GpuModel {
public:
    /**
     * Constructor with all parameters
     * 
     * @param name The name of the GPU model (e.g., "A100", "V100", etc.)
     * @param hourlyRate The hourly cost rate for this GPU model
     * @param dailyStorageCost The daily storage cost for this GPU model
     */
    GpuModel(const std::string& name, double hourlyRate, double dailyStorageCost);

    GpuModel();
    
    std::string getName() const;
    double getHourlyRate() const;
    double getDailyStorageCost() const;
    
    void setName(const std::string& name);
    void setHourlyRate(double hourlyRate);
    void setDailyStorageCost(double dailyStorageCost);

private:
    std::string name;
    double hourlyRate;
    double dailyStorageCost;
};

#endif 