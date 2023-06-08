#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include "Engines.h"

/* You can add new tests for a new engine by creating a new class that inherits from the Test class */

class Test {
public:

    /* Container of parameters */
	std::vector<double> parameters;
    Test() {};
    /* This function retrieves all numbers from a file and pushes them back into a vector */
    void ParsingParameters(std::string filename);
    
    /* This function returns array parameter */
    std::vector<double> getArrayParameter(int first_position, int second_position);
	virtual void Start() = 0;
};

/* An example of a test class for an internal combustion engine */

class TestInternalCombustion : public Test {
public:
    EngineInternalCombustion* engine;
    void printParameters();
    TestInternalCombustion(){}

    /* You can add new tests for any parameter of engine */

    /* First test stand */
    void firstTestStand(EngineInternalCombustion* engine);

    /* Second test stand */
    void secondTestStand(EngineInternalCombustion* engine);

    /* Start of testing */
    void Start() override;
};