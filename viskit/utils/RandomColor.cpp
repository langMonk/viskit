///
/// \author Bartosz Minch <minch@agh.edu.pl>
/// \date 18.05.2010
///

#include <viskit/utils/RandomColor.h>

namespace viskit::utils {
using ColorList = RandomColor::ColorList;
const ColorList RandomColor::AnyRed = { PinkRed, Red, RedOrange };
const ColorList RandomColor::AnyOrange = { RedOrange, Orange, OrangeYellow };
const ColorList RandomColor::AnyYellow = { OrangeYellow, Yellow, YellowGreen };
const ColorList RandomColor::AnyGreen = { YellowGreen, Green, GreenCyan };
const ColorList RandomColor::AnyBlue = { Cyan, CyanBlue, Blue, BlueMagenta };
const ColorList RandomColor::AnyMagenta = { BlueMagenta, Magenta, MagentaPink };
const ColorList RandomColor::AnyPink = { MagentaPink, Pink, PinkRed };

glm::vec4 RandomColor::generate(Color color, Luminosity luminosity)
{
    const ColorInfo& info = colorMap[color];
    const int h = randomWithin(info.hRange);
    if (color != RandomHue) {
        return generate(h, info, luminosity);
    } else {
        return generate(h, getColorInfo(h), luminosity);
    }
}

glm::vec4 RandomColor::generate(ColorList colors, Luminosity luminosity)
{
    // Each color will have probability = color.hRange.size() / totalRangeSize,
    // so calculate totalRangeSize
    double totalRangeSize = 0;
    for (auto color : colors) {
        totalRangeSize += colorMap[color].hRange.size();
    }

    // Generate a number within [0; 1) and select a color according with the
    // cumulative distribution function f(i) = f(i - 1) + colorProbability(i)
    std::uniform_real_distribution<double> probability(0, 1);
    const auto p = probability(randomEngine);
    double f = 0;
    for (auto color : colors) {
        const auto colorProbability = colorMap[color].hRange.size() / totalRangeSize;
        f += colorProbability;
        if (f >= p) {
            return generate(color, luminosity);
        }
    }

    // This place can be reached due to rounding (if p ~ 1 and f < p even
    // for the last color). Then return the last color.
    const Color lastColor = *(colors.end() - 1);
    return generate(lastColor, luminosity);
}

glm::vec4 RandomColor::generate(const Range& hueRange, Luminosity luminosity)
{
    const int h = randomWithin(hueRange);
    const ColorInfo& info = getColorInfo(h);
    return generate(h, info, luminosity);
}

glm::vec4 RandomColor::generate(int h, const ColorInfo& info, Luminosity luminosity)
{
    const int s = pickSaturation(info, luminosity);
    const int b = pickBrightness(s, info, luminosity);
    return HSBtoRGB(h, s, b);
}

int RandomColor::pickSaturation(const ColorInfo& info, Luminosity luminosity)
{
    Range sRange = Range(info.sbRanges[0].s, info.sbRanges.back().s);
    int sRangeSize = sRange.size();

    switch (luminosity) {
    case Dark:
        sRange[0] = static_cast<int>(sRange[1] - sRangeSize * 0.3);
        break;

    case Light:
        sRange[1] = static_cast<int>(sRange[0] + sRangeSize * 0.25);
        break;

    case Bright:
        sRange[0] = static_cast<int>(sRange[1] - sRangeSize * 0.3);
        break;

    case Normal:
        sRange[0] = std::max(sRange[0], std::min(50, sRange[1]));
        break;

    case RandomLuminosity:
        // Just use the whole range
        break;
    }
    return randomWithin(sRange);
}

int RandomColor::pickBrightness(int s, const ColorInfo& info, Luminosity luminosity)
{
    Range bRange = getBrightnessRange(s, info);
    const int bRangeSize = bRange.size();

    switch (luminosity) {
    case Dark:
        bRange[1] = static_cast<int>(bRange[0] + std::min(bRangeSize * 0.3, 30.0));
        break;

    case Light:
        bRange[0] = static_cast<int>(bRange[1] - std::min(bRangeSize * 0.3, 15.0));
        break;

    case Bright:
        bRange[0] = static_cast<int>(bRange[1] - std::min(bRangeSize * 0.3, 10.0));
        break;

    case Normal:
        bRange[0] += static_cast<int>(bRangeSize * 0.5);
        bRange[1] -= static_cast<int>(bRangeSize * 0.125);
        break;

    case RandomLuminosity:
        // Just use the whole range
        break;
    }
    return randomWithin(bRange);
}

RandomColor::Range RandomColor::getBrightnessRange(int s, const ColorInfo& info)
{
    const std::vector<SBRange>& sbRanges = info.sbRanges;

    // Find a slice of sbRanges to which s belongs, and calculate the
    // brightness range proportionally to s
    for (int i = static_cast<int>(sbRanges.size() - 2); i >= 0; --i) {
        if (s >= sbRanges[i].s) {
            const auto& r1 = sbRanges[i];
            const auto& r2 = sbRanges[1 + i];
            const auto sRangeSize = static_cast<double>(r2.s - r1.s);
            const auto sFraction = static_cast<bool>(sRangeSize ? (s - r1.s) / sRangeSize : false);
            const auto bMin = static_cast<int>(r1.bMin + sFraction * (r2.bMin - r1.bMin));
            const auto bMax = static_cast<int>(r1.bMax + sFraction * (r2.bMax - r1.bMax));
            return { bMin, bMax };
        }
    }
    if (sbRanges.size() == 1) {
        return { sbRanges[0].bMin, sbRanges[0].bMax };
    }
    return { 0, 100 };
}

const RandomColor::ColorInfo& RandomColor::getColorInfo(int h)
{
    if (h < 0)
        h += 360;

    // Find the narrowest range containing h
    auto found = &colorMap[RandomHue];
    for (const auto& info : colorMap) {
        if ((info.hRange[0] <= h && h <= info.hRange[1]) || (info.hRange[0] <= 0 && h >= 360 + info.hRange[0])) {
            if (info.hRange.size() < found->hRange.size() && info.color <= RandomHue) {
                found = &info;
            }
        }
    }
    return *found;
}

int RandomColor::randomWithin(const Range& range)
{
    std::uniform_int_distribution<int> d(range[0], range[1]);
    return d(randomEngine);
}

void RandomColor::setSeed(const int seed)
{
    randomEngine.seed(seed);
}

// Parameter "b" is renamed as "v" (value) for convenience
glm::vec4 RandomColor::HSBtoRGB(double h, double s, double v) const
{
    assert(-360 <= h && h <= 360 && "h must be within [-360; 360]");
    assert(0 <= s && s <= 100 && "s must be within [0; 100]");
    assert(0 <= v && v <= 100 && "v must be within [0; 100]");

    // Keep h within [0; 359], s and v within [0; 1]
    if (h >= 360)
        h -= 360;
    if (h < 0)
        h += 360;
    s = s / 100.0;
    v = v / 100.0;

    // Convert hsv to rgb. This algorithm is described at
    // https://en.wikipedia.org/wiki/HSL_and_HSV#From_HSV
    const double C = v * s;
    const double hd = h / 60;
    const int hi = int(hd);
    const double hd_mod2 = hd - hi + hi % 2;
    const double X = C * (1 - fabs(hd_mod2 - 1));
    double r, g, b;

    switch (hi) {
    case 0:
        r = C;
        g = X;
        b = 0;
        break;
    case 1:
        r = X;
        g = C;
        b = 0;
        break;
    case 2:
        r = 0;
        g = C;
        b = X;
        break;
    case 3:
        r = 0;
        g = X;
        b = C;
        break;
    case 4:
        r = X;
        g = 0;
        b = C;
        break;
    case 5:
        r = C;
        g = 0;
        b = X;
        break;
    // This should never happen
    default:
        return glm::vec4 { 0.0f };
    }

    const double m = v - C;
    r += m;
    g += m;
    b += m;

    // Scale r, g, b to [0; 255]
    return glm::vec4 { r, g, b, 1.0f };
}
}