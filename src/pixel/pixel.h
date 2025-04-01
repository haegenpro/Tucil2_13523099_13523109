#ifndef _PIXEL_H_
#define _PIXEL_H_

class Pixel {
private:
    unsigned char r, g, b, a;

public:
    Pixel();
    Pixel(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
    ~Pixel();
    bool operator==(const Pixel&) const;
    Pixel& operator=(const Pixel&);
    unsigned char getRed() const;
    unsigned char getGreen() const;
    unsigned char getBlue() const;
    unsigned char getAlpha() const;
    void setRed(unsigned char val);
    void setGreen(unsigned char val);
    void setBlue(unsigned char val);
    void setAlpha(unsigned char val);
};
#endif