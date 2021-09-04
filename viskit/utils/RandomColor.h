///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.05.2010
///

#pragma once

#include <utility>
#include <vector>
#include <random>
#include <cassert>
#include <initializer_list>

#include <viskit/math/glm_adapter.h>

namespace viskit::utils
{
	class RandomColor
	{
	public:
		enum Color
		{
			Red,
			RedOrange,
			Orange,
			OrangeYellow,
			Yellow,
			YellowGreen,
			Green,
			GreenCyan,
			Cyan,
			CyanBlue,
			Blue,
			BlueMagenta,
			Magenta,
			MagentaPink,
			Pink,
			PinkRed,
			RandomHue,
			BlackAndWhite,
			Brown
		};

		enum Luminosity
		{
			Dark,
			Normal,
			Light,
			Bright,
			RandomLuminosity
		};

        using ColorList = std::initializer_list<Color>;

		// Additional colors
		static const ColorList AnyRed;
		static const ColorList AnyOrange;
		static const ColorList AnyYellow;
		static const ColorList AnyGreen;
		static const ColorList AnyBlue;
		static const ColorList AnyMagenta;
		static const ColorList AnyPink;

		struct Range
		{
			explicit Range(int value = 0);
			Range(int left, int right);
			int& operator [](int i);
			int operator [](int i) const;
			[[nodiscard]] int size() const;

			int values[2];
		};

		/**
		 * Returns a random color with specified luminosity, in RGB format
		 */
		glm::vec4 generate(Color color = RandomHue, Luminosity luminosity = Normal);

		/**
		 * The same as generate(color, luminosity), but for one of the colors.
		 * The color is selected randomly - the wider a color's hue range, the
		 * higher chance it will be selected. The colors can be passed as
		 * {color1, color2, ..., colorN}.
		 */
		glm::vec4 generate(ColorList colors, Luminosity luminosity = Normal);

		/**
		 * Returns a random color within hueRange, with specified luminosity,
		 * in RGB format. The range can be a pair {left, right} or
		 * a single value (then it becomes {value, value}).
		 */
		glm::vec4 generate(const Range& hueRange, Luminosity luminosity = Normal);

		/**
		 * Sets the seed of the random generator.
		 */
		void setSeed(int seed);

	private:
        struct SBRange
        {
            explicit SBRange(int s_ = 0, int bMin_ = 0, int bMax_ = 100)
            {
                s = s_;
                bMin = bMin_;
                bMax = bMax_;
            };

            int s;
            int bMin;
            int bMax;
        };

        struct ColorInfo
		{
            explicit ColorInfo(Color m_color = Red, Range m_range = {0,0}, std::vector<SBRange> m_ranges = {})
            {
                color = m_color;
                hRange = m_range;
                sbRanges = std::move(m_ranges);
            }

            Color color;
			Range hRange;
			std::vector<SBRange> sbRanges;
		};

		glm::vec4 generate(int h, const ColorInfo&, Luminosity);
		int pickSaturation(const ColorInfo&, Luminosity);
		int pickBrightness(int s, const ColorInfo&, Luminosity);

		Range getBrightnessRange(int s, const ColorInfo&);
		const ColorInfo& getColorInfo(int h);
		int randomWithin(const Range&);
		[[nodiscard]] glm::vec4 HSBtoRGB(double h, double s, double b) const;

		const std::vector<ColorInfo> colorMap =
        {
                RandomColor::ColorInfo{Red, {-5, 10}, {SBRange{20, 100}, SBRange{30, 95}, SBRange{40, 90}, SBRange{50, 88}, SBRange{60, 80}, SBRange{70, 70}, SBRange{80, 60}, SBRange{90, 58}, SBRange{100, 55}}},
                RandomColor::ColorInfo{RedOrange, {11, 19}, {SBRange{20, 100}, SBRange{30, 95}, SBRange{40, 90}, SBRange{50, 85}, SBRange{60, 80}, SBRange{70, 70}, SBRange{80, 60}, SBRange{90, 60}, SBRange{100, 55}}},
                RandomColor::ColorInfo{OrangeYellow,  {42, 50}, {SBRange{25, 100}, SBRange{30, 93}, SBRange{40, 88}, SBRange{50, 86}, SBRange{60, 85}, SBRange{70, 70}, SBRange{100, 70}}},
                RandomColor::ColorInfo{ Yellow,         {51, 61},    {SBRange{28, 100}, SBRange{40, 98}, SBRange{50, 95}, SBRange{60, 93}, SBRange{70, 85}, SBRange{80, 82}, SBRange{90, 78}, SBRange{100, 75}} },
                RandomColor::ColorInfo{ YellowGreen,    {62, 75},    {SBRange{30, 100}, SBRange{40, 94}, SBRange{50, 90}, SBRange{60, 86}, SBRange{70, 84}, SBRange{80, 82}, SBRange{90, 78}, SBRange{100, 75}} },
                RandomColor::ColorInfo{ Green,          {76, 140},   {SBRange{30, 100}, SBRange{40, 95}, SBRange{50, 85}, SBRange{60, 75}, SBRange{70, 60}, SBRange{80, 54}, SBRange{90, 48}, SBRange{100, 45}} },
                RandomColor::ColorInfo{ GreenCyan,      {141, 171},  {SBRange{20, 100}, SBRange{30, 95}, SBRange{40, 90}, SBRange{50, 85}, SBRange{60, 80}, SBRange{70, 60}, SBRange{80, 55}, SBRange{90, 52}, SBRange{100, 45}} },
                RandomColor::ColorInfo{ Cyan,           {172, 200},  {SBRange{20, 100}, SBRange{30, 90}, SBRange{40, 80}, SBRange{50, 74}, SBRange{60, 58}, SBRange{70, 52}, SBRange{90, 52}, SBRange{100, 50}} },
                RandomColor::ColorInfo{ CyanBlue,       {201, 215},  {SBRange{20, 100}, SBRange{30, 90}, SBRange{40, 80}, SBRange{50, 74}, SBRange{60, 58}, SBRange{70, 52}, SBRange{90, 52}, SBRange{100, 50}} },
                RandomColor::ColorInfo{ Blue,           {216, 240},  {SBRange{20, 100}, SBRange{30, 90}, SBRange{40, 85}, SBRange{50, 76}, SBRange{60, 65}, SBRange{70, 64}, SBRange{80, 60}, SBRange{90, 55}, SBRange{100, 55}} },
                RandomColor::ColorInfo{ BlueMagenta,    {241, 280},  {SBRange{20, 100}, SBRange{30, 90}, SBRange{40, 85}, SBRange{50, 76}, SBRange{60, 65}, SBRange{70, 64}, SBRange{80, 60}, SBRange{90, 55}, SBRange{100, 55}} },
                RandomColor::ColorInfo{ Magenta,        {281, 315},  {SBRange{20, 100}, SBRange{30, 85}, SBRange{40, 80}, SBRange{50, 70}, SBRange{60, 60}, SBRange{70, 55}, SBRange{100, 55}} },
                RandomColor::ColorInfo{ MagentaPink,    {316, 330},  {SBRange{20, 100}, SBRange{30, 95}, SBRange{40, 92}, SBRange{50, 87}, SBRange{60, 84}, SBRange{80, 70}, SBRange{90, 65}, SBRange{100, 65}} },
                RandomColor::ColorInfo{ Pink,           {331, 340},  {SBRange{20, 100}, SBRange{30, 95}, SBRange{40, 92}, SBRange{50, 87}, SBRange{60, 84}, SBRange{80, 80}, SBRange{90, 75}, SBRange{100, 73}} },
                RandomColor::ColorInfo{ PinkRed,        {341, 354},  {SBRange{20, 100}, SBRange{30, 95}, SBRange{40, 90}, SBRange{50, 85}, SBRange{60, 80}, SBRange{70, 70}, SBRange{80, 60}, SBRange{90, 58}, SBRange{100, 55}} },

                RandomColor::ColorInfo{ RandomHue,      {0, 359},    {SBRange{20, 100}, SBRange{100, 50}} },
                RandomColor::ColorInfo{ BlackAndWhite,  {0, 359},    {SBRange{0, 0, 100}} },
                RandomColor::ColorInfo{ Brown,          {15, 30},    {SBRange{20, 90, 95}, SBRange{30, 80, 90}, SBRange{40, 60, 90}, SBRange{50, 50, 90}, SBRange{60, 50, 90}, SBRange{70, 50, 90}, SBRange{80, 45, 85}, SBRange{90, 45, 85}, SBRange{100, 40, 85}} }
        };

		std::default_random_engine randomEngine;	};

	inline RandomColor::Range::Range(int left, int right)
		: values{ left, right }
	{}

	inline RandomColor::Range::Range(int value)
		: values{ value, value }
	{}

	inline int& RandomColor::Range::operator [](int i)
	{
		return values[i];
	}

	inline int RandomColor::Range::operator [](int i) const
	{
		return values[i];
	}

	inline int RandomColor::Range::size() const
	{
		return values[1] - values[0];
	}

}
