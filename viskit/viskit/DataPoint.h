///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.02.2020
///
///

#pragma once

#include <cmath>
#include <algorithm>
#include <cassert>
#include <vector>
#include <memory>

namespace viskit
{
    using DataPointId = size_t;

    class DataPoint
    {
        // sub-types
    public:
        using iterator = float*;
        using const_iterator = const float*;

        // construction and destruction methods
    public:
        DataPoint(size_t size)
                : N(size)
                , m_id(m_currentId++)
        {
            coords = std::make_shared<std::vector<float>>(size);
        };

        DataPoint(std::vector<float> vec)
                : N(vec.size())
                , m_id(m_currentId++)
        {
            coords = std::make_shared<std::vector<float>>(vec);
        }

        DataPoint(std::vector<float> vec, size_t id)
                : N(vec.size())
        {
            coords = std::make_shared<std::vector<float>>(vec);
            m_id = id;
        }

        // public methods
    public:
        inline std::size_t size() const
        {
            return N;
        }

        inline float& operator[] (std::size_t index)
        {
            return coords->at(index);
        }

        inline float operator[] (std::size_t index) const
        {
            return coords->at(index);
        }

        inline typename DataPoint::iterator begin()
        {
            return coords->data();
        }

        inline typename DataPoint::const_iterator begin() const
        {
            return coords->data();
        }

        inline typename DataPoint::iterator end()
        {
            return begin() + coords->size();
        }

        inline typename DataPoint::const_iterator end() const
        {
            return begin() + coords->size();
        }

        DataPointId getId() { return m_id; }
        DataPointId getId() const { return m_id; }

        static size_t m_currentId;
        // private members
    private:
        DataPointId m_id;
        size_t N;
        std::shared_ptr<std::vector<float>> coords;

    };

    inline float Distance(const DataPoint& one, const DataPoint& two)
    {
        assert(one.size() == two.size());
        float result = 0.0;
        for (std::size_t i = 0; i < one.size(); ++i)
            result += (one[i] - two[i]) * (one[i] - two[i]);
        return result;
    }

    inline bool operator==(const DataPoint& one, const DataPoint& two)
    {
        assert(one.size() == two.size());
        return std::equal(one.begin(), one.end(), two.begin());
    }

    inline bool operator!=(const DataPoint& one, const DataPoint& two)
    {
        assert(one.size() == two.size());
        return !(one == two);
    }
}