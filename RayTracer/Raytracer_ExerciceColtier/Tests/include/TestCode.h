#ifndef TEST_CODE_H
#define TEST_CODE_H

#include "conio.h"
#include "Windows.h"
#include <iostream>
#include <iomanip>

#define EXPECT_EQUAL(expected, tested) Test(expected, tested, #expected, #tested, __FILE__, __LINE__)
#define EXPECT_DOUBLE_EQUAL(expected, tested, epsilon) TestDouble(expected, tested, epsilon, #expected, #tested, __FILE__, __LINE__)
#define START() StartTest(__FUNCTION__)
#define END(result) EndTest(result, __FUNCTION__)

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);


template<typename E, typename T>
bool Test(const E& _expectedValue,
    const T& _testedValue,
    const char* _expectedName,
    const char* _testedName,
    const char* _fileName,
    const int& _lineNumber)
{
    if (_testedValue != _expectedValue)
    {
        std::cout << std::endl;
        std::cerr << _fileName << " : " << _lineNumber << " : " << std::endl;
        std::cerr << "\tExpected name : " << _expectedName << std::endl;
        std::cerr << "\tResult name : " << _testedName << std::endl;
        std::cerr << "\tExpected value : " << _expectedValue << std::endl;
        std::cerr << "\tResult value : " << _testedValue << std::endl;
        return false;
    }

    return true;
}

bool TestDouble(const double& _expectedValue,
    const double& _testedValue,
    const double& _epsilon,
    const char* _expectedName,
    const char* _testedName,
    const char* _fileName,
    const int& _lineNumber)
{
    if (_testedValue < _expectedValue - _epsilon && _testedValue > _expectedValue + _epsilon)
    {
        std::cout << std::endl;
        std::cerr << std::setprecision(10)<< _fileName << " : " << _lineNumber << " : " << std::endl;
        std::cerr << "\tExpected name : " << _expectedName << std::endl;
        std::cerr << "\tResult name : " << _testedName << std::endl;
        std::cerr << "\tExpected value between : [" << _expectedValue - _epsilon << " ; " << _expectedValue + _epsilon << "]" << std::endl;
        std::cerr << "\tResult value : " << _testedValue << std::endl;
        std::cerr << "\tEpsilon : " << _epsilon << std::endl;
        return false;
    }

    return true;
}

void StartTest(const std::string& _functionName)
{
	SetConsoleTextAttribute(console, 15);
    std::cout << std::setw(30) << _functionName.c_str() << std::setfill('.') << std::setw(30);
}

bool EndTest(const bool& isPassed, const std::string& _functionName)
{
    if (isPassed)
    {
        SetConsoleTextAttribute(console, FOREGROUND_GREEN);
        std::cout << "[ OK ]";
    }
    else
    {
        std::cout << _functionName.c_str() << "\t................... ";
        SetConsoleTextAttribute(console, FOREGROUND_RED);
        std::cout << "[ KO ]";
    }
    std::cout << std::endl;
	std::cout << std::setfill(' ');
    SetConsoleTextAttribute(console, 15);
    return isPassed;
}

#endif