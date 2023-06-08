#include "Test.h"

void Test::ParsingParameters(std::string filename) {
    /* Pattern of numbers in the file */
    std::regex pattern(R"(\d+\.\d+|\d+)");
    /* Opening the file */
    std::ifstream file(filename);
    /* If file is opened */
    if (file.is_open()) {
        std::string line;
        /* Get line from file */
        while (std::getline(file, line)) {
            /* Find numbers by pattern */
            std::sregex_iterator next(line.begin(), line.end(), pattern);
            std::sregex_iterator end;
            /* Retrieving parameters while they still exist in the line */
            while (next != end) {
                std::smatch match = *next;
                parameters.push_back(std::stod(match.str()));
                ++next;
            }
        }
        /* Closing file */
        file.close();
    }
}

std::vector<double> Test::getArrayParameter(int first_position, int second_position) {
    return std::vector<double>(parameters.begin() + first_position, parameters.begin() + second_position);
}

void TestInternalCombustion::firstTestStand(EngineInternalCombustion* engine) {
    double time = 0.0;
    double delta_time = 0.01;

    while (engine->T < parameters[parameters.size() - 4]) {
        engine->engineIteration(time, delta_time);
    }

    std::cout << "Overheating time: " << time << std::endl;
    engine->resetEngine();
}

void TestInternalCombustion::secondTestStand(EngineInternalCombustion* engine) {
    const double EPSILON = 1e-5; // Margin of error
    double time = 0.0;
    double delta_time = 0.01;
    double Nmax = 0.0;
    double Vmax = 0.0;
    engine->engineIteration(time, delta_time);
    while (std::abs(engine->M) > EPSILON) {
        engine->engineIteration(time, delta_time);
        if (engine->N > Nmax) {
            Nmax = engine->N;
            Vmax = engine->V;
        }
    }
    std::cout << "With velocity " << Vmax << " maximum power: " << Nmax << std::endl;
    engine->resetEngine();
}

void TestInternalCombustion::Start(){
    /* Parsing file for numbers */
    ParsingParameters("Input.txt");

    /* Calculating torque and velocity vectors */
    std::vector<double> M = getArrayParameter(1, (parameters.size() - 4) / 2 + 1);
    std::vector<double> V = getArrayParameter((parameters.size() - 4) / 2 + 1, (parameters.size() - 4));

    /* Retrieving environment temperature from user */
    double Tenvironment;
    std::cin >> Tenvironment;
    /* Make engine object */
    EngineInternalCombustion* engine = new EngineInternalCombustion(parameters[0], M, V, parameters[parameters.size() - 4],
        parameters[parameters.size() - 3], parameters[parameters.size() - 2], parameters[parameters.size() - 1], Tenvironment);

    /* Make tests */
    firstTestStand(engine);
    secondTestStand(engine);

}