#include "gpu_model.h"

GpuModel::GpuModel(const std::string& name, double hourlyRate, double dailyStorageCost)
    : name(name), hourlyRate(hourlyRate), dailyStorageCost(dailyStorageCost) {
}

GpuModel::GpuModel()
    : name("Default"), hourlyRate(0.0), dailyStorageCost(0.0) {
}

std::string GpuModel::getName() const {
    
    return name;
}

double GpuModel::getHourlyRate() const {
    return hourlyRate;
}

double GpuModel::getDailyStorageCost() const {
    return dailyStorageCost;
}

void GpuModel::setName(const std::string& name) {
    this->name = name;
}

void GpuModel::setHourlyRate(double hourlyRate) {
    this->hourlyRate = hourlyRate;
}

void GpuModel::setDailyStorageCost(double dailyStorageCost) {
    this->dailyStorageCost = dailyStorageCost;
}