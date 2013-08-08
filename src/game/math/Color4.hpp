#ifndef COLOR4_HPP
#define COLOR4_HPP

template<typename VARTYPE>
struct Color4
{
    VARTYPE r;
    VARTYPE g;
    VARTYPE b;
    VARTYPE a;

    Color4(): r(1), g(1), b(1), a(1) {}
    Color4(VARTYPE val): r(val), g(val), b(val), a(val) {}
    Color4(VARTYPE r, VARTYPE g, VARTYPE b, VARTYPE a): r(r), g(g), b(b), a(a) {}
};

#endif
