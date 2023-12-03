#ifndef Q4_H
#define Q4_H

namespace q4
{
    struct Vector2D
    {
        double x{};
        double y{};
    };

    struct Sensor
    {
        Vector2D pos;
        double accuracy;
    };

    inline Vector2D kalman_filter(std::vector<Sensor> sensor) {
        double x = 0, y = 0, accuracy = 0;
        auto func = [&x, &y, &accuracy](Sensor& sensor) {
            x += sensor.pos.x * sensor.accuracy;
            y += sensor.pos.y * sensor.accuracy;
            accuracy += sensor.accuracy;
        };
        std::for_each(sensor.begin(), sensor.end(), func);
        x /= accuracy, y /= accuracy;
        return Vector2D{x, y};
    }
};

#endif //Q4_H