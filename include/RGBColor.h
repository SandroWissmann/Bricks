#ifndef RGBCOLOR_H
#define RGBCOLOR_H

namespace bricks {
class RGBColor {
public:
    RGBColor(int r, int g, int b, int a = 0xFF);

    int r() const;
    int g() const;
    int b() const;
    int a() const;

    RGBColor lighter(double factor = 0.3) const;
    RGBColor darker(double factor = 0.3) const;

    RGBColor grayscale() const;

private:
    int calcLighterPart(int part, double factor) const;
    int calcDarkerPart(int part, double factor) const;

    int mR;
    int mG;
    int mB;
    int mA;
};
} // namespace bricks
#endif