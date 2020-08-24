#ifndef TYPES_RGBCOLOR_H
#define TYPES_RGBCOLOR_H

namespace bricks::types {
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
    static int checkArgs(int value);

    static int calcLighterPart(int part, double factor) ;
    static int calcDarkerPart(int part, double factor) ;

    int mR;
    int mG;
    int mB;
    int mA;
};
} // namespace bricks::types
#endif