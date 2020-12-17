#include "TVec3D.h"
#include "TestCode.h"

bool TestDefaultConstruction()
{
    START();
    auto passed = true;
    const TVec3D<double> vec;
    passed &= EXPECT_EQUAL(0.0, vec.X());
    passed &= EXPECT_EQUAL(0.0, vec.Y());
    passed &= EXPECT_EQUAL(0.0, vec.Z());
    return END(passed);
}

bool TestConstruction()
{
    START();
    auto passed = true;
    const TVec3D<double> vec(4.2, 36.4, 5.0);
    passed &= EXPECT_EQUAL(4.2, vec.X());
    passed &= EXPECT_EQUAL(36.4, vec.Y());
    passed &= EXPECT_EQUAL(5.0, vec.Z());
    return END(passed);
}

bool TestCopyConstructor()
{
	START();
	auto passed = true;
	const TVec3D<double> vec(3.2, 6.9, 9.8);
	const auto vecCopy = vec;
	passed &= EXPECT_EQUAL(vec.X(), vecCopy.X());
	passed &= EXPECT_EQUAL(vec.Y(), vecCopy.Y());
	passed &= EXPECT_EQUAL(vec.Z(), vecCopy.Z());
	return END(passed);
}

bool TestAssignmentOperator()
{
	START();
	auto passed = true;
	const TVec3D<double> vec(3.2, 6.9, 9.8);
	TVec3D<double> vecCopy;
	vecCopy = vec;
	passed &= EXPECT_EQUAL(vec.X(), vecCopy.X());
	passed &= EXPECT_EQUAL(vec.Y(), vecCopy.Y());
	passed &= EXPECT_EQUAL(vec.Z(), vecCopy.Z());
	return END(passed);
}

bool TestAddVector()
{
    START();
    auto passed = true;
    const TVec3D<double> vec1(4.0, 12.0, 25.0);
    const TVec3D<double> vec2(5.0, 8.0, 6.3);
    const auto vecResult = vec1 + vec2;

    passed &= EXPECT_EQUAL(4.0, vec1.X());
    passed &= EXPECT_EQUAL(12.0, vec1.Y());
    passed &= EXPECT_EQUAL(25.0, vec1.Z());

    passed &= EXPECT_EQUAL(5.0, vec2.X());
    passed &= EXPECT_EQUAL(8.0, vec2.Y());
    passed &= EXPECT_EQUAL(6.3, vec2.Z());

    passed &= EXPECT_EQUAL(9.0, vecResult.X());
    passed &= EXPECT_EQUAL(20.0, vecResult.Y());
    passed &= EXPECT_EQUAL(31.3, vecResult.Z());
    return END(passed);
}

bool TestAddCommutative()
{
    START();
    auto passed = true;
    const TVec3D<double> vec1(4.0, 12.0, 25.0);
    const TVec3D<double> vec2(5.0, 8.0, 6.3);
    const auto vecResult1 = vec1 + vec2;
    const auto vecResult2 = vec2 + vec1;

    passed &= EXPECT_EQUAL(vecResult1.X(), vecResult2.X());
    passed &= EXPECT_EQUAL(vecResult1.Y(), vecResult2.Y());
    passed &= EXPECT_EQUAL(vecResult1.Z(), vecResult2.Z());
    return END(passed);
}

bool TestSubtract()
{
    START();
    auto passed = true;
    const TVec3D<double> vec1(4.0, 12.0, 25.0);
    const TVec3D<double> vec2(5.0, 8.0, 6.3);
    const auto vecResult = vec1 - vec2;

    passed &= EXPECT_EQUAL(4.0, vec1.X());
    passed &= EXPECT_EQUAL(12.0, vec1.Y());
    passed &= EXPECT_EQUAL(25.0, vec1.Z());

    passed &= EXPECT_EQUAL(5.0, vec2.X());
    passed &= EXPECT_EQUAL(8.0, vec2.Y());
    passed &= EXPECT_EQUAL(6.3, vec2.Z());

    passed &= EXPECT_EQUAL(-1.0, vecResult.X());
    passed &= EXPECT_EQUAL(4.0, vecResult.Y());
    passed &= EXPECT_EQUAL(18.7, vecResult.Z());
    return END(passed);
}

bool TestSubtractOrder()
{
    START();
    auto passed = true;
    const TVec3D<double> vec1(4.0, 12.0, 25.0);
    const TVec3D<double> vec2(5.0, 8.0, 6.3);
    const auto vecResult1 = vec1 - vec2;
    const auto vecResult2 = vec2 - vec1;

    passed &= EXPECT_EQUAL(vecResult2.X(), -vecResult1.X());
    passed &= EXPECT_EQUAL(vecResult2.Y(), -vecResult1.Y());
    passed &= EXPECT_EQUAL(vecResult2.Z(), -vecResult1.Z());
    return END(passed);
}

bool TestDotProduct()
{
	START();
	auto passed = true;
	const TVec3D<double> vec1(4.0, 11.0, 20.0);
	const TVec3D<double> vec2(5.0, 8.0, 6.0);
	const auto x = 20.0;
	const auto y = 88.0;
	const auto z = 120.0;
	
	passed &= EXPECT_EQUAL(x + y + z, vec1.DotProduct(vec2));
	passed &= EXPECT_EQUAL(4.0, vec1.X());
	passed &= EXPECT_EQUAL(11.0, vec1.Y());
	passed &= EXPECT_EQUAL(20.0, vec1.Z());
	passed &= EXPECT_EQUAL(5.0, vec2.X());
	passed &= EXPECT_EQUAL(8.0, vec2.Y());
	passed &= EXPECT_EQUAL(6.0, vec2.Z());	
	return END(passed);
}

bool TestDotProductCommutative()
{
	START();
	auto passed = true;
	const TVec3D<double> vec1(4.0, 11.0, 20.0);
	const TVec3D<double> vec2(5.0, 8.0, 6.0);
	const auto x = 20.0;
	const auto y = 88.0;
	const auto z = 120.0;
	const auto ref = x + y + z;
	
	passed &= EXPECT_EQUAL(ref, vec1.DotProduct(vec2));
	passed &= EXPECT_EQUAL(ref, vec2.DotProduct(vec1));
	return END(passed);
}

bool TestCrossProduct()
{
	START();
	auto passed = true;
	static const auto x1 = 4.0;
	static const auto y1 = 11.0;
	static const auto z1 = 20.0;
	
	static const auto x2 = 5.0;
	static const auto y2 = 8.0;
	static const auto z2 = 6.0;
	
	const TVec3D<double> vec1(x1, y1, z1);
	const TVec3D<double> vec2(x2, y2, z2);
	const auto x = y1 * z2 - z1 * y2;
	const auto y = z1 * x2 - x1 * z2;
	const auto z = x1 * y2 - y1 * x2;
	const auto vecResult = vec1 * vec2;
	
	passed &= EXPECT_EQUAL(x, vecResult.X());
	passed &= EXPECT_EQUAL(y, vecResult.Y());
	passed &= EXPECT_EQUAL(z, vecResult.Z());

	passed &= EXPECT_EQUAL(x1, vec1.X());
	passed &= EXPECT_EQUAL(y1, vec1.Y());
	passed &= EXPECT_EQUAL(z1, vec1.Z());
	passed &= EXPECT_EQUAL(x2, vec2.X());
	passed &= EXPECT_EQUAL(y2, vec2.Y());
	passed &= EXPECT_EQUAL(z2, vec2.Z());
	return END(passed);
}

bool TestCrossProductOrder()
{
	START();
	auto passed = true;
	static const auto x1 = 4.0;
	static const auto y1 = 11.0;
	static const auto z1 = 20.0;

	static const auto x2 = 5.0;
	static const auto y2 = 8.0;
	static const auto z2 = 6.0;

	const TVec3D<double> vec1(x1, y1, z1);
	const TVec3D<double> vec2(x2, y2, z2);
	const auto x = y1 * z2 - z1 * y2;
	const auto y = z1 * x2 - x1 * z2;
	const auto z = x1 * y2 - y1 * x2;

	const auto vecResult1 = vec1 * vec2;
	const auto vecResult2 = vec2 * vec1;

	passed &= EXPECT_EQUAL(vecResult1.X(), -vecResult2.X());
	passed &= EXPECT_EQUAL(vecResult1.Y(), -vecResult2.Y());
	passed &= EXPECT_EQUAL(vecResult1.Z(), -vecResult2.Z());

	return END(passed);
}

bool TestMagnitude()
{
	START();
	auto passed = true;

	const TVec3D<double> vec(3.0, 4.0, 9.0);
	static const auto ref = std::sqrt(std::pow(3.0, 2) + std::pow(4.0, 2) +std::pow(9.0, 2));
	passed &= EXPECT_EQUAL(ref, vec.Magnitude());

	passed &= EXPECT_EQUAL(3.0, vec.X());
	passed &= EXPECT_EQUAL(4.0, vec.Y());
	passed &= EXPECT_EQUAL(9.0, vec.Z());
	return END(passed);
}

bool TestOpposite()
{
    START();
    auto passed = true;
    const TVec3D<double> vec(3.0, 4.0, 9.0);
    const auto vecOpposite = vec.Opposite();

    passed &= EXPECT_EQUAL(3.0, vec.X());
    passed &= EXPECT_EQUAL(4.0, vec.Y());
    passed &= EXPECT_EQUAL(9.0, vec.Z());

    passed &= EXPECT_EQUAL(-3.0, vecOpposite.X());
    passed &= EXPECT_EQUAL(-4.0, vecOpposite.Y());
    passed &= EXPECT_EQUAL(-9.0, vecOpposite.Z());

    return END(passed);
}

bool TestNormalized()
{
    START();
    auto passed = true;
    static const auto x = 3.0;
    static const auto y = 4.0;
    static const auto z = 9.0;

    TVec3D<double> vec(x, y, z);
    const auto magnitude = vec.Magnitude();
    const auto xNormalized = x / magnitude;
    const auto yNormalized = y / magnitude;
    const auto zNormalized = z / magnitude;

    const auto vecNormalized = vec.Normalized();

    passed &= EXPECT_EQUAL(x, vec.X());
    passed &= EXPECT_EQUAL(y, vec.Y());
    passed &= EXPECT_EQUAL(z, vec.Z());

    passed &= EXPECT_EQUAL(1.0, vecNormalized.Magnitude());
    passed &= EXPECT_EQUAL(xNormalized, vecNormalized.X());
    passed &= EXPECT_EQUAL(yNormalized, vecNormalized.Y());
    passed &= EXPECT_EQUAL(zNormalized, vecNormalized.Z());
    return END(passed);
}

bool TestScalar()
{
    START();
    auto passed = true;
    const TVec3D<double> vec(3.0, 4.0, 9.0);
    const auto scalar = 5.0;
    const auto vecScaled1 = scalar * vec;
    const auto vecScaled2 = vec * scalar;

    passed &= EXPECT_EQUAL(vecScaled1.X(), vecScaled2.X());
    passed &= EXPECT_EQUAL(vecScaled1.Y(), vecScaled2.Y());
    passed &= EXPECT_EQUAL(vecScaled1.Z(), vecScaled2.Z());

    passed &= EXPECT_EQUAL(15.0, vecScaled1.X());
    passed &= EXPECT_EQUAL(20.0, vecScaled1.Y());
    passed &= EXPECT_EQUAL(45.0, vecScaled2.Z());

    passed &= EXPECT_EQUAL(3.0, vec.X());
    passed &= EXPECT_EQUAL(4.0, vec.Y());
    passed &= EXPECT_EQUAL(9.0, vec.Z());
    return END(passed);
}

bool TestDivide()
{
    START();
    auto passed = true;
    const TVec3D<double> vec(2.0, 4.0, -10.0);
    const auto divide = 4.0;
    const auto vecDivided = vec / divide;

    passed &= EXPECT_EQUAL(0.5, vecDivided.X());
    passed &= EXPECT_EQUAL(1.0, vecDivided.Y());
    passed &= EXPECT_EQUAL(-2.5, vecDivided.Z());

    passed &= EXPECT_EQUAL(2.0, vec.X());
    passed &= EXPECT_EQUAL(4.0, vec.Y());
    passed &= EXPECT_EQUAL(-10.0, vec.Z());
    return END(passed);
}

bool TestTranslatePoint()
{
    START();
    auto passed = true;
    const TVec3D<double> vec(2.0, 4.0, -10.0);
    const TPoint3D<double> point(3.0, -9.0, 8.0);
    const auto pointMoved1 = point + vec;

    passed &= EXPECT_EQUAL(typeid(TPoint3D<double>).name(), typeid(pointMoved1).name());

    passed &= EXPECT_EQUAL(2.0, vec.X());
    passed &= EXPECT_EQUAL(4.0, vec.Y());
    passed &= EXPECT_EQUAL(-10.0, vec.Z());

    passed &= EXPECT_EQUAL(3.0, point.X());
    passed &= EXPECT_EQUAL(-9.0, point.Y());
    passed &= EXPECT_EQUAL(8.0, point.Z());

    passed &= EXPECT_EQUAL(5.0, pointMoved1.X());
    passed &= EXPECT_EQUAL(-5.0, pointMoved1.Y());
    passed &= EXPECT_EQUAL(-2.0, pointMoved1.Z());

    return END(passed);
}

int main()
{
    auto result = true;

    result &= TestDefaultConstruction();
    result &= TestConstruction();
	result &= TestCopyConstructor();
	result &= TestAssignmentOperator();
    result &= TestAddVector();
    result &= TestAddCommutative();
    result &= TestSubtract();
    result &= TestSubtractOrder();
	result &= TestDotProduct();
	result &= TestDotProductCommutative();
	result &= TestCrossProduct();
	result &= TestCrossProductOrder();
	result &= TestMagnitude();
    result &= TestOpposite();
    result &= TestNormalized();
    result &= TestScalar();
    result &= TestDivide();
    result &= TestTranslatePoint();

    if (!result)
        std::cout << "Test failed" << std::endl;
    else
        std::cout << "All tests passed" << std::endl;

    return 0;
}