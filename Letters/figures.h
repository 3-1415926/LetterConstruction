#ifndef Letters_figures_h
#define Letters_figures_h

#include <cmath>
#include <set>
#include <vector>

#include "cairommconfig.h"
#include "cairomm/context.h"
#include "cairomm/surface.h"
#include "colors.h"

constexpr double LINE_WIDTH = 0.7;

constexpr double DOT_DIAMETER = 7;
constexpr double DOT_RADIUS = DOT_DIAMETER / 2;

constexpr double FIGURE_WIDTH = 39;
constexpr double END_RADIUS = FIGURE_WIDTH / 2;

constexpr double BLUE_SMALL_STEP = 33.5;
constexpr double BLUE_LARGE_STEP = 76.5;
constexpr double BLUE_HALF_LENGTH = BLUE_SMALL_STEP + BLUE_LARGE_STEP;

constexpr double GREEN_STEP = 71.5;
constexpr double ORANGE_STEP = 55;

constexpr double ORANGE_ARC_RADIUS = 32;
constexpr double GREEN_ARC_RADIUS = ORANGE_STEP;
constexpr double PURPLE_ARC_RADIUS = ORANGE_STEP;
constexpr double PURPLE_ARC_OFFSET = FIGURE_WIDTH;

const double GREEN_ARC_OPEN_HALF_ANGLE(
    asin(BLUE_LARGE_STEP / 2 / GREEN_ARC_RADIUS));

static_assert(BLUE_HALF_LENGTH == ORANGE_STEP * 2,
              "Half of blue stick should align with orange stick");

class Figure {
public:
  Figure(Color color) : color(color) { }
  virtual ~Figure() { }

  void DrawFigure(Cairo::RefPtr<Cairo::Surface> surface,
                  double scale, double x, double y, double angle) const;
  
protected:
  virtual void Draw(Cairo::RefPtr<Cairo::Context> cr) const = 0;
  
  inline void SetColor(Cairo::RefPtr<Cairo::Context> cr, Color color) const {
    cr->set_source_rgba(color.r, color.g, color.b, color.a);
  }
  
  const Color color;
};

class OffsetFigure {
public:
  OffsetFigure(Figure* figure, double x, double y, double angle)
  : figure(figure), _x(x), _y(y), _angle(angle) { }
  std::unique_ptr<Figure> figure;
  const double _x, _y;
  const double _angle;

  void Draw(Cairo::RefPtr<Cairo::Surface> surface,
            double scale, double x, double y, double angle) const {
    figure->DrawFigure(surface, scale, scale * _x + x, scale * _y + y,
                       _angle + angle);
  }
};

class Stick : public Figure {
public:
  Stick(Color color, double half_length,
        std::initializer_list<double> extra_dots)
  : Figure(color), half_length(half_length) {
    dots.insert(0);
    dots.insert(-half_length);
    dots.insert(half_length);
    for (const double p : extra_dots) {
      dots.insert(-p);
      dots.insert(p);
    }
  }
  ~Stick() override { }
protected:
  void Draw(Cairo::RefPtr<Cairo::Context> cr) const override;
private:
  std::set<double> dots;
  const double half_length;
};

struct BlueStick : public Stick {
  BlueStick() : Stick(Color::BLUE, BLUE_HALF_LENGTH, { BLUE_SMALL_STEP }) { }
};

struct GreenStick : public Stick {
  GreenStick() : Stick(Color::GREEN, GREEN_STEP, { }) { }
};

struct OrangeStick : public Stick {
  OrangeStick() : Stick(Color::ORANGE, ORANGE_STEP, { }) { }
};

struct PurpleDot : public Figure {
  PurpleDot() : Figure(Color::PURPLE) { }
protected:
  void Draw(Cairo::RefPtr<Cairo::Context> cr) const override;
};

class Arc : public Figure {
public:
  Arc(Color color, double radius, double sweep_angle,
      std::initializer_list<double> dot_angles_asymm)
  : Figure(color), radius(radius), sweep_angle(sweep_angle) {
    for (const double dot_angle : dot_angles_asymm) {
      dot_angles.insert(-dot_angle);
      dot_angles.insert(dot_angle);
    }
  }
  ~Arc() override { }
protected:
  void Draw(Cairo::RefPtr<Cairo::Context> cr) const override;
private:
  std::set<double> dot_angles;
  double radius;
  double sweep_angle;
};

struct BlueArc : public Arc {
  BlueArc()
  : Arc(Color::BLUE, BLUE_HALF_LENGTH, M_PI, { 0, M_PI_4, M_PI_2 }) { }
};

struct GreenArc : public Arc {
  GreenArc()
  : Arc(Color::GREEN,
        GREEN_ARC_RADIUS, (M_PI - GREEN_ARC_OPEN_HALF_ANGLE) * 2,
        { 0,
          GREEN_ARC_OPEN_HALF_ANGLE,
          M_PI_2,
          M_PI - GREEN_ARC_OPEN_HALF_ANGLE }) { }
};

struct OrangeArc : public Arc {
  OrangeArc() : Arc(Color::ORANGE, ORANGE_ARC_RADIUS, M_PI, { M_PI_2 }) { }
};

struct PurpleArc : public Figure {
  PurpleArc() : Figure(Color::PURPLE) { }
protected:
  void Draw(Cairo::RefPtr<Cairo::Context> cr) const override;
};

#endif