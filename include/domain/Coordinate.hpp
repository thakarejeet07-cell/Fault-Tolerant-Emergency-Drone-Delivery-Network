#ifndef DRONE_MESH_COORDINATE_HPP
#define DRONE_MESH_COORDINATE_HPP

#include <iostream>

namespace simulator {
namespace mesh {
namespace domain {

class Coordinate {
private:
    double latitude;
    double longitude;

public:
    Coordinate();
    Coordinate(double latitude, double longitude);

    double getLatitude() const;
    double getLongitude() const;

    void setLatitude(double latitude);
    void setLongitude(double longitude);

    double distanceTo(const Coordinate& other) const;
    double distanceTo(double targetLat, double targetLon) const;

    Coordinate operator+(const Coordinate& other) const;
    bool operator==(const Coordinate& other) const;
    friend Coordinate midpoint(
        const Coordinate& a,
        const Coordinate& b
    );

    // STREAM OPERATOR OVERLOADING (friend functions):
    // These must be friends (not members) because the left-hand operand
    // is a std::ostream/std::istream, not a Coordinate. Declaring them as
    // friends grants them access to the private latitude/longitude members
    // without needing public getters/setters for the raw fields.
    friend std::ostream& operator<<(std::ostream& os, const Coordinate& coord);
    friend std::istream& operator>>(std::istream& is, Coordinate& coord);

};

} // namespace domain
} // namespace mesh
} // namespace simulator

#endif
