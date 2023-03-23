#include <iostream>
#include <optional>
#include <vector>
#include <xieite/geometry/Circle.hpp>
#include <xieite/geometry/Point.hpp>
#include <xieite/geometry/Line.hpp>
#include <xieite/geometry/getDistance.hpp>
#include <xieite/geometry/getIntersections.hpp>

using namespace xieite::geometry;

int main() {
	const Circle object(Point(0, 10), 5);
	const Point lightSource(0, 20);
	const Point camera(0, -10);

	std::vector<int> result;
	for (int i = -15; i <= 15; ++i) {
		result.push_back(0);
		const std::vector<Point> intersections1 = getIntersections(object, Line(camera, Point(i, 0)));
		if (intersections1.size()) {
			const Point intersection = intersections1[getDistance(camera, intersections1[0]) > getDistance(camera, intersections1[1])];
			const Line line(intersection, lightSource);
			const std::vector<Point> intersections2 = getIntersections(object, line);
			if (intersection != intersections2[0] || intersection != intersections2[1])
				result[i + 15] = getDistance(intersection, lightSource);
		}
	}

	for (const int value : result)
		std::cout << value << ' ';
	std::cout << '\n';
}
