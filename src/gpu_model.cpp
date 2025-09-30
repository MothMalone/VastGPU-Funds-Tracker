#include "gpu_model.h"

GpuModel::GpuModel(const std::string& name, double hourlyRate, double dailyStorageCost, int numInstances)
    : name(name), hourlyRate(hourlyRate), dailyStorageCost(dailyStorageCost), numInstances(numInstances) {
}


GpuModel::GpuModel()
    : name("Default"), hourlyRate(0.0), dailyStorageCost(0.0), numInstances(1) {
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

int GpuModel::getNumInstances() const {
    return numInstances;
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

void GpuModel::setNumInstances(int numInstances) {
    this->numInstances = numInstances;
}