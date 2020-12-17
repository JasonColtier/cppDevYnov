#include "Color.h"
#include "TestCode.h"

static const auto g_epsilon = std::numeric_limits<double>::epsilon();

bool TestDefaultColorConstructor()
{
    START();
    auto passed = true;
    const Color color;
    
    passed &= EXPECT_EQUAL(0.5, color.Red());
    passed &= EXPECT_EQUAL(0.5, color.Green());
    passed &= EXPECT_EQUAL(0.5, color.Blue());
    passed &= EXPECT_EQUAL(0.0, color.Alpha());
    return END(passed);
}

bool TestColorConstructor()
{
    START();
    auto passed = true;
    const Color color(0.3, 0.2, 0.9, 0.6);

    passed &= EXPECT_EQUAL(0.3, color.Red());
    passed &= EXPECT_EQUAL(0.2, color.Green());
    passed &= EXPECT_EQUAL(0.9, color.Blue());
    passed &= EXPECT_EQUAL(0.6, color.Alpha());
    return END(passed);
}

bool TestSetters()
{
    START();
    auto passed = true;
    Color color(0.3, 0.2, 0.9, 0.6);
    color.SetRed(0.2);
    color.SetGreen(0.5);
    color.SetBlue(0.1);
    color.SetAlpha(0.3);

    passed &= EXPECT_EQUAL(0.2, color.Red());
    passed &= EXPECT_EQUAL(0.5, color.Green());
    passed &= EXPECT_EQUAL(0.1, color.Blue());
    passed &= EXPECT_EQUAL(0.3, color.Alpha());
    return END(passed);
}

bool TestBrightness()
{
    START();
    auto passed = true;
    const Color color(0.2, 0.4, 0.3, 0.1);
    const auto brightness = color.Brightness();

    passed &= EXPECT_DOUBLE_EQUAL(0.3, brightness, g_epsilon);
    passed &= EXPECT_EQUAL(0.2, color.Red());
    passed &= EXPECT_EQUAL(0.4, color.Green());
    passed &= EXPECT_EQUAL(0.3, color.Blue());
    passed &= EXPECT_EQUAL(0.1, color.Alpha());
    return END(passed);
}

bool TestAverage()
{
    START();
    auto passed = true;
    const Color color1(0.2, 0.4, 0.3, 0.1);
    const Color color2(0.3, 0.5, 0.1, 0.0);
    const auto average1 = color1.Average(color2);
    const auto average2 = color2.Average(color1);

    passed &= EXPECT_EQUAL(average1.Red(), average2.Red());
    passed &= EXPECT_EQUAL(average1.Green(), average2.Green());
    passed &= EXPECT_EQUAL(average1.Blue(), average2.Blue());
    passed &= EXPECT_EQUAL(0.1, average1.Alpha());
    passed &= EXPECT_EQUAL(0.0, average2.Alpha());

    passed &= EXPECT_EQUAL(0.2, color1.Red());
    passed &= EXPECT_EQUAL(0.4, color1.Green());
    passed &= EXPECT_EQUAL(0.3, color1.Blue());
    passed &= EXPECT_EQUAL(0.1, color1.Alpha());

    passed &= EXPECT_EQUAL(0.3, color2.Red());
    passed &= EXPECT_EQUAL(0.5, color2.Green());
    passed &= EXPECT_EQUAL(0.1, color2.Blue());
    passed &= EXPECT_EQUAL(0.0, color2.Alpha());
    return END(passed);
}

bool TestAddColor()
{
    START();
    auto passed = true;
    Color color1(0.2, 0.4, 0.3, 0.1);
    const Color color2(0.3, 0.5, 0.1, 0.0);
    const auto colorResult1 = color1 + color1;
    const auto colorResult2 = color2 + color1;

    passed &= EXPECT_EQUAL(0.2, color1.Red());
    passed &= EXPECT_EQUAL(0.4, color1.Green());
    passed &= EXPECT_EQUAL(0.3, color1.Blue());
    passed &= EXPECT_EQUAL(0.1, color1.Alpha());
    passed &= EXPECT_EQUAL(0.3, color2.Red());
    passed &= EXPECT_EQUAL(0.5, color2.Green());
    passed &= EXPECT_EQUAL(0.1, color2.Blue());
    passed &= EXPECT_EQUAL(0.0, color2.Alpha());

    passed &= EXPECT_DOUBLE_EQUAL(colorResult1.Red(), colorResult2.Red(), g_epsilon);
    passed &= EXPECT_DOUBLE_EQUAL(colorResult1.Green(), colorResult2.Green(), g_epsilon);
    passed &= EXPECT_DOUBLE_EQUAL(colorResult1.Blue(), colorResult2.Blue(), g_epsilon);

    passed &= EXPECT_DOUBLE_EQUAL(0.5, colorResult1.Red(), g_epsilon);
    passed &= EXPECT_DOUBLE_EQUAL(0.9, colorResult1.Green(), g_epsilon);
    passed &= EXPECT_DOUBLE_EQUAL(0.4, colorResult1.Blue(), g_epsilon);
    passed &= EXPECT_EQUAL(0.1, colorResult1.Alpha());
    passed &= EXPECT_EQUAL(0.0, colorResult2.Alpha());
    return END(passed);
}

bool TestSubtractColor()
{
    START();
    auto passed = true;
    static const Color color1(0.2, 0.4, 0.3, 0.1);
    static const Color color2(0.3, 0.5, 0.1, 0.0);
	static const Color colorRef1(0.06, 0.02, 0.03, 0.1);
	static const Color colorRef2(0.06, 0.02, 0.03, 0.0);
    const auto colorResult1 = color1 * color2;
    const auto colorResult2 = color2 * color1;

    passed &= EXPECT_EQUAL(0.2, color1.Red());
    passed &= EXPECT_EQUAL(0.4, color1.Green());
    passed &= EXPECT_EQUAL(0.3, color1.Blue());
    passed &= EXPECT_EQUAL(0.1, color1.Alpha());
    passed &= EXPECT_EQUAL(0.3, color2.Red());
    passed &= EXPECT_EQUAL(0.5, color2.Green());
    passed &= EXPECT_EQUAL(0.1, color2.Blue());
    passed &= EXPECT_EQUAL(0.0, color2.Alpha());

    passed &= EXPECT_DOUBLE_EQUAL(colorResult1.Red(), colorResult2.Red(), g_epsilon);
    passed &= EXPECT_DOUBLE_EQUAL(colorResult1.Green(), colorResult2.Green(), g_epsilon);
    passed &= EXPECT_DOUBLE_EQUAL(colorResult1.Blue(), colorResult2.Blue(), g_epsilon);

    passed &= EXPECT_DOUBLE_EQUAL(colorRef1.Red(), colorResult1.Red(), g_epsilon);
	passed &= EXPECT_DOUBLE_EQUAL(colorRef1.Green(), colorResult1.Green(), g_epsilon);
	passed &= EXPECT_DOUBLE_EQUAL(colorRef1.Blue(), colorResult1.Blue(), g_epsilon);
	
	passed &= EXPECT_DOUBLE_EQUAL(colorRef1.Alpha(), colorResult1.Alpha(), g_epsilon);
	passed &= EXPECT_DOUBLE_EQUAL(colorRef2.Alpha(), colorResult2.Alpha(), g_epsilon);
    return END(passed);
}

bool TestMultiplyColor()
{
	START();
	auto passed = true;
	static const Color color1(0.2, 0.4, 0.3, 0.1);
	static const Color color2(0.3, 0.5, 0.1, 0.0);
	static const auto colorResult1 = color1 - color2;
	static const auto colorResult2 = color2 - color1;

	passed &= EXPECT_EQUAL(0.2, color1.Red());
	passed &= EXPECT_EQUAL(0.4, color1.Green());
	passed &= EXPECT_EQUAL(0.3, color1.Blue());
	passed &= EXPECT_EQUAL(0.1, color1.Alpha());
	passed &= EXPECT_EQUAL(0.3, color2.Red());
	passed &= EXPECT_EQUAL(0.5, color2.Green());
	passed &= EXPECT_EQUAL(0.1, color2.Blue());
	passed &= EXPECT_EQUAL(0.0, color2.Alpha());

	passed &= EXPECT_DOUBLE_EQUAL(colorResult1.Red(), -colorResult2.Red(), g_epsilon);
	passed &= EXPECT_DOUBLE_EQUAL(colorResult1.Green(), -colorResult2.Green(), g_epsilon);
	passed &= EXPECT_DOUBLE_EQUAL(colorResult1.Blue(), -colorResult2.Blue(), g_epsilon);

	passed &= EXPECT_DOUBLE_EQUAL(-0.1, colorResult1.Red(), g_epsilon);
	passed &= EXPECT_DOUBLE_EQUAL(-0.1, colorResult1.Green(), g_epsilon);
	passed &= EXPECT_DOUBLE_EQUAL(0.2, colorResult1.Blue(), g_epsilon);
	passed &= EXPECT_DOUBLE_EQUAL(0.1, colorResult2.Red(), g_epsilon);
	passed &= EXPECT_DOUBLE_EQUAL(0.1, colorResult2.Green(), g_epsilon);
	passed &= EXPECT_DOUBLE_EQUAL(-0.2, colorResult2.Blue(), g_epsilon);
	passed &= EXPECT_EQUAL(0.1, colorResult1.Alpha());
	passed &= EXPECT_EQUAL(0.0, colorResult2.Alpha());
	return END(passed);
}

bool TestMultiplyWithScalar()
{
	START();
	auto passed = true;
	static const Color color1(0.2, 0.4, 0.3, 0.1);
	static const auto value = 4.0;
	const auto result1 = value * color1;
	const auto result2 = color1 * value;
	static const Color ref(0.8, 1.6, 1.2, 0.1);

	passed &= EXPECT_DOUBLE_EQUAL(result2.Red(), result1.Red(), g_epsilon);
	passed &= EXPECT_DOUBLE_EQUAL(result2.Green(), result1.Green(), g_epsilon);
	passed &= EXPECT_DOUBLE_EQUAL(result2.Blue(), result1.Blue(), g_epsilon);
	passed &= EXPECT_DOUBLE_EQUAL(result2.Alpha(), result1.Alpha(), g_epsilon);
	
	passed &= EXPECT_DOUBLE_EQUAL(ref.Red(), result1.Red(), g_epsilon);
	passed &= EXPECT_DOUBLE_EQUAL(ref.Green(), result1.Green(), g_epsilon);
	passed &= EXPECT_DOUBLE_EQUAL(ref.Blue(), result1.Blue(), g_epsilon);
	passed &= EXPECT_DOUBLE_EQUAL(ref.Alpha(), result1.Alpha(), g_epsilon);
	
	return END(passed);
}

bool TestDivideByScalar()
{
	START();
	auto passed = true;
	static const Color color(0.2, 0.4, 0.3, 0.1);
	static const auto value = 2.0;
	const auto result = color / value;
	static const Color ref(0.1, 0.2, 0.15, 0.05);

	passed &= EXPECT_DOUBLE_EQUAL(ref.Red(), result.Red(), g_epsilon);
	passed &= EXPECT_DOUBLE_EQUAL(ref.Green(), result.Green(), g_epsilon);
	passed &= EXPECT_DOUBLE_EQUAL(ref.Blue(), result.Blue(), g_epsilon);
	passed &= EXPECT_DOUBLE_EQUAL(ref.Alpha(), result.Alpha(), g_epsilon);

	return END(passed);
}

int main()
{
    auto result = true;

    result &= TestDefaultColorConstructor();
    result &= TestColorConstructor();
    result &= TestSetters();
    result &= TestBrightness();
    result &= TestAverage();
    result &= TestAddColor();
    result &= TestSubtractColor();
	result &= TestMultiplyColor();
	result &= TestMultiplyWithScalar();
	result &= TestDivideByScalar();

    if (!result)
        std::cout << "Test failed" << std::endl;
    else
        std::cout << "All tests passed" << std::endl;

    return 0;
}