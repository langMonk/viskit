///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 13.05.2019
///

#pragma once

namespace viskit
{
    struct vec2
    {
    public:
        explicit vec2(float x = 0.0f, float y = 0.0f)
            : x{ x }
            , y{ y }
        {
        }

    public:
        float x;
        float y;
    };

    struct vec3
    {
    public:
        explicit vec3(float x = 0.0f, float y = 0.0f, float z = 0.0f)
            : x{ x }
            , y{ y }
            , z{ z }
        {
        }

    public:
        float x;
        float y;
        float z;
    };

    struct vec4
    {
    public:
        explicit vec4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f)
            : x{ x }
            , y{ y }
            , z{ z }
            , w{ w }
        {
        }

    public:
        float x;
        float y;
        float z;
        float w;
    };
}