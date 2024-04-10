#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <stdexcept>

class PumpCalculator {
public:
    PumpCalculator(double efficiency, double dailyConsumption, double operationTime, double geodeticHeight,
        double staticHead, double darcyCoefficient, double pipeLength, double pipeDiameter)
        : k(efficiency), V(dailyConsumption), t(operationTime), H_g(geodeticHeight),
        H_s(staticHead), D(darcyCoefficient), L(pipeLength), d(pipeDiameter) {
        if (k <= 0 || t <= 0 || d <= 0) {
            throw std::invalid_argument("Efficiency, operation time, and pipe diameter must be greater than 0.");
        }
    }

    double calculatePumpPower() {
        auto Q = calculateFlowRate();
        auto velocity = calculateVelocity(Q);
        auto h_l = calculateFrictionHeadLoss(velocity);
        auto h_m = calculateLocalHeadLoss(h_l);
        auto H = calculateTotalHead(h_l, h_m);

        return (9.81 * Q * H) / k;
    }

private:
    double k, V, t, H_g, H_s, D, L, d;

    double calculateFlowRate() const {
        return V / (3600 * t);
    }

    double calculateVelocity(double Q) const {
        return (4 * Q) / (M_PI * std::pow(d, 2));
    }

    double calculateFrictionHeadLoss(double velocity) const {
        return D * (L / d) * std::pow(velocity, 2) / 19.6;
    }

    double calculateLocalHeadLoss(double h_l) const {
        return 0.1 * h_l;
    }

    double calculateTotalHead(double h_l, double h_m) const {
        return H_g + h_l + h_m + H_s;
    }
};

int main() {
    try {
        double k, V, t, H_g, H_s, D, L, d;
        std::cout << "Enter the pump's efficiency (k): ";
        std::cin >> k;
        std::cout << "Enter the daily water consumption (V, in cubic meters): ";
        std::cin >> V;
        std::cout << "Enter the pump's operation time per day (t, in seconds): ";
        std::cin >> t;
        std::cout << "Enter the geodetic height (H_g, in meters): ";
        std::cin >> H_g;
        std::cout << "Enter the static head (H_s, in meters): ";
        std::cin >> H_s;
        std::cout << "Enter the Darcy coefficient (D): ";
        std::cin >> D;
        std::cout << "Enter the length of the pipe (L, in meters): ";
        std::cin >> L;
        std::cout << "Enter the diameter of the pipe (d, in meters): ";
        std::cin >> d;

        PumpCalculator calculator(k, V, t, H_g, H_s, D, L, d);
        std::cout << "The required pump power (N) is: " << calculator.calculatePumpPower() << " Watts" << std::endl;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}