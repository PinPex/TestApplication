#include "Engines.h"

Engines::Engines(double I, double Tover, double Tenvironment) : I(I), Tover(Tover), T(Tenvironment), Tenvironment(Tenvironment) {

}

EngineInternalCombustion::EngineInternalCombustion(double I, std::vector<double> M_values, std::vector<double> V_values, double Tover,
	double Hm, double Hv, double C, double Tenvironment) :
	M_values(M_values), V_values(V_values), Hm(Hm), Hv(Hv), C(C), Engines{ I, Tover, Tenvironment }{

}

void EngineInternalCombustion::resetEngine()
{
	V = 0.0;
	M = 0.0;
	a = 0.0;
	N = 0.0;
	T = Tenvironment;
}

void EngineInternalCombustion::engineIteration(double& time, double delta_time)
{
    {

        double torque = 0.0;
        double velocity = V;
        /* Calculating current torque using interpolation */
        for (size_t i = 0; i < M_values.size(); ++i) {
            if (i == 0 && velocity <= V_values[i]) {
                torque = M_values[i];
                break;
            }
            else if (i == M_values.size() - 1 && velocity > V_values[i]) {
                torque = M_values[i];
                break;
            }
            else if (velocity > V_values[i] && velocity <= V_values[i + 1]) {
                double torque1 = M_values[i];
                double torque2 = M_values[i + 1];
                double velocity1 = V_values[i];
                double velocity2 = V_values[i + 1];
                torque = torque1 + (torque2 - torque1) / (velocity2 - velocity1) * (velocity - velocity1);
                break;
            }
        }

        /* Calculate Acceleration and velocity */
        M = torque;
        a = M / I;
        V += a * delta_time;

        /* Calculating heating rate and cooling rate */
        double heating_rate = M * Hm + pow(V, 2) * Hv;
        double cooling_rate = C * (Tenvironment - T);
        /* Calculate temperature of engine */
        T += (heating_rate - cooling_rate) * delta_time;
        /* Calculate power of engine */
        N = M * V / 1000.0;

        time += delta_time;
    }
}
