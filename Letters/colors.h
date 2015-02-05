#ifndef Letters_colors_h
#define Letters_colors_h

struct Color {
public:
  Color(double r, double g, double b)
  : r(WithOpacity(r)), g(WithOpacity(g)), b(WithOpacity(b)), a(opacity) { }
  
  static const Color BLUE;
  static const Color GREEN;
  static const Color ORANGE;
  static const Color PURPLE;
  static const Color EDGE;
  
  const double r, g, b, a;
  
private:
  constexpr static const double opacity = 0.5;
  
  static inline double WithOpacity(double initial) {
    return (initial + opacity - 1) / opacity;
  }
};

#endif
