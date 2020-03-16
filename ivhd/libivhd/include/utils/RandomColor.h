#pragma once

#include <vector>
#include <random>
#include <initializer_list>
#include <cassert>

#include "math/glm_adapter.h"

namespace ivhd::utils
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

		typedef std::initializer_list<Color> ColorList;

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
			Range(int value = 0);
			Range(int left, int right);
			int& operator [](int i);
			int operator [](int i) const;
			int size() const;

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
			SBRange(int s = 0, int bMin = 0, int bMax = 100);

			int s;
			int bMin;
			int bMax;
		};

		struct ColorInfo
		{
			Color color;
			Range hRange;
			std::vector<SBRange> sbRanges;
		};

		glm::vec4 generate(int h, const ColorInfo&, Luminosity);
		int pickSaturation(const ColorInfo&, Luminosity);
		int pickBrightness(int s, const ColorInfo&, Luminosity);

		static Range getBrightnessRange(int s, const ColorInfo&);
		static const ColorInfo& getColorInfo(int h);
		int randomWithin(const Range&);
		glm::vec4 HSBtoRGB(double h, double s, double b) const;

		static const std::vector<ColorInfo> colorMap;
		std::default_random_engine randomEngine;
	};

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
