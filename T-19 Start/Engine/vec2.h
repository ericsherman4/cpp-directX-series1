#pragma once

class Vec2 {
public:
    Vec2() = default;
    Vec2(float x_in, float y_in);
    Vec2 operator+(const Vec2 & rhs) const;
    Vec2& operator+=(const Vec2& rhs);
    Vec2 operator*(float rhs) const;
    Vec2& operator*=(float rhs);

    //float get_x(void);
    //float get_y(void);
    //float set_x(float x_in);
    //float set_y(float y_in);


private:
    float x;
    float y;
};
