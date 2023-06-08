#pragma once
#include <iostream>
#include <vector>
#include <thread>
#include <atomic>

/* Interface for making new engine classes */
class Engines {
public:
	double I; //Inertion
	double Tover; // Overheating temperature
	double T; // Temperature engine
	double Tenvironment; // Environment temperature
	double N = 0.0; // Power 

	virtual void resetEngine() = 0;
	virtual void engineIteration(double& time, double delta_time) = 0;
	Engines(double I, double Tover, double Tenvironment);
};

/* An example of engine class */
class EngineInternalCombustion : public Engines{

public:
	/* I have made these variables public in case we need them for the tests */

	std::vector<double> M_values; // Torque values
	std::vector<double> V_values; // Velocity values
	double Hm; // Heating torque coefficient
	double Hv; // Heating velocity coefficient
	double C; // Cooling coefficient

	double V = 0.0; // Velocity
	double M = 0.0; // Torque
	double a = 0.0; // Acceleration

	EngineInternalCombustion(double I, std::vector<double> M_values, std::vector<double> V_values, double Tover,
		double Hm, double Hv, double C, double Tenvironment);

	void resetEngine() override;

	void engineIteration(double& time, double delta_time) override;

};