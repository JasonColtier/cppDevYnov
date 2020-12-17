#ifndef TOOLS_H
#define TOOLS_H

#include <vector>
#include <algorithm>
#include <tuple>

namespace Tools
{
	inline int FindNearestIntersection(std::vector<double>&	_intersections)
	{
		if (_intersections.empty())
			return -1;
		
		// Find	the	lowest positive	value
		const auto it =	std::min_element(_intersections.begin(), _intersections.end(),[](const auto& _lhs, const auto& _rhs)
		{
			const auto isLhsNegative = std::signbit(_lhs);
			const auto isRhsNegative = std::signbit(_rhs);
			return std::tie(isLhsNegative, _lhs) < std::tie(isRhsNegative, _rhs);
		});
		
		if ((it	== _intersections.end()) ||	std::signbit(*it))
			return -1;
		
		return static_cast<int>(std::distance(_intersections.begin(), it));
	}
}

#endif // TOOLS_H
