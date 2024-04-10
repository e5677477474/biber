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