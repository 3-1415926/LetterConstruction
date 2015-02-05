#include "figures.h"

void Figure::DrawFigure(Cairo::RefPtr<Cairo::Surface> surface,
                        double scale, double x, double y, double angle) const {
  auto cr = Cairo::Context::create(surface);
  cr->translate(x, y);
  cr->rotate(angle);
  cr->scale(scale, scale);
  SetColor(cr, color);
  cr->set_line_width(LINE_WIDTH);
  Draw(cr);
}

void Figure::DrawDefault(Cairo::RefPtr<Cairo::Surface> surface,
                         const Figure* next_figure,
                         double scale, double* x, double* y) const {
  if (surface) {
    DrawFigure(surface, scale, *x, *y, default_angle);
  }
  *x += scale * (FIGURE_WIDTH + DEFAULT_STEP);
}

void Stick::Draw(Cairo::RefPtr<Cairo::Context> cr) const {
  cr->arc(-half_length, 0, END_RADIUS, M_PI_2, M_PI_2 * 3);
  cr->line_to(half_length, -END_RADIUS);
  cr->arc(half_length, 0, END_RADIUS, -M_PI_2, M_PI_2);
  cr->line_to(-half_length, END_RADIUS);
  cr->fill();

  SetColor(cr, Color::EDGE);
  cr->set_line_width(LINE_WIDTH);
  for (const double dot : dots) {
    cr->arc(dot, 0, DOT_RADIUS, 0, M_PI * 2);
    cr->stroke();
  }
}

void HasRadius::DrawDefault(Cairo::RefPtr<Cairo::Surface> surface,
                            const Figure* next_figure,
                            double scale, double* x, double* y) const {
  *x += scale * radius;
  Figure::DrawDefault(surface, next_figure, scale, x, y);
  const HasRadius* next_has_radius =
      dynamic_cast<const HasRadius*>(next_figure);
  if (next_has_radius) {
    double hypo = next_has_radius->radius + FIGURE_WIDTH + DEFAULT_STEP;
    double oppo = GapSize() / 2;
    double adja = sqrt(hypo * hypo - oppo * oppo);
    *x -= scale * (hypo - adja);
  }
}

void PurpleDot::Draw(Cairo::RefPtr<Cairo::Context> cr) const {
  cr->arc(0, 0, END_RADIUS, 0, M_PI * 2);
  cr->fill();
}

void Arc::Draw(Cairo::RefPtr<Cairo::Context> cr) const {
  double top_angle = M_PI + sweep_angle / 2;
  double bottom_angle = M_PI - sweep_angle / 2;
  cr->arc(radius * cos(top_angle), radius * sin(top_angle),
          END_RADIUS, top_angle, top_angle + M_PI);
  cr->arc_negative(0, 0, radius - END_RADIUS, top_angle, bottom_angle);
  cr->arc(radius * cos(bottom_angle), radius * sin(bottom_angle),
          END_RADIUS, bottom_angle - M_PI, bottom_angle);
  cr->arc(0, 0, radius + END_RADIUS, bottom_angle, top_angle);
  cr->fill();
  
  SetColor(cr, Color::EDGE);
  for (const double dot_angle : dot_angles) {
    cr->arc(radius * cos(M_PI + dot_angle), radius * sin(M_PI + dot_angle),
            DOT_RADIUS, 0, M_PI * 2);
    cr->stroke();
  }
}

void GreenArc::DrawDefault(Cairo::RefPtr<Cairo::Surface> surface,
                           const Figure* next_figure,
                           double scale, double* x, double* y) const {
  HasRadius::DrawDefault(surface, next_figure, scale, x, y);
  *x += scale * GREEN_ARC_RADIUS * cos(GREEN_ARC_OPEN_HALF_ANGLE);
}

void PurpleArc::Draw(Cairo::RefPtr<Cairo::Context> cr) const {
  cr->arc(PURPLE_ARC_OFFSET, -PURPLE_ARC_RADIUS, END_RADIUS,
          M_PI_2 * 3, M_PI_2);
  cr->line_to(0, -PURPLE_ARC_RADIUS + END_RADIUS);
  cr->arc_negative(0, 0, PURPLE_ARC_RADIUS - END_RADIUS, M_PI_2 * 3, M_PI_2);
  cr->line_to(PURPLE_ARC_OFFSET, PURPLE_ARC_RADIUS - END_RADIUS);
  cr->arc(PURPLE_ARC_OFFSET, PURPLE_ARC_RADIUS, END_RADIUS, M_PI_2 * 3, M_PI_2);
  cr->line_to(0, PURPLE_ARC_RADIUS + END_RADIUS);
  cr->arc(0, 0, PURPLE_ARC_RADIUS + END_RADIUS, M_PI_2, M_PI_2 * 3);
  cr->line_to(PURPLE_ARC_OFFSET, -PURPLE_ARC_RADIUS - END_RADIUS);
  cr->fill();

  SetColor(cr, Color::EDGE);
  std::pair<double, double> points[] {
    std::pair<double, double>(-PURPLE_ARC_RADIUS, 0),
    std::make_pair(PURPLE_ARC_OFFSET, -PURPLE_ARC_RADIUS),
    std::make_pair(PURPLE_ARC_OFFSET, PURPLE_ARC_RADIUS),
  };
  for (const auto& pair : points) {
    cr->arc(pair.first, pair.second, DOT_RADIUS, 0, M_PI * 2);
    cr->stroke();
  }
}

void PurpleArc::DrawDefault(Cairo::RefPtr<Cairo::Surface> surface,
                            const Figure* next_figure,
                            double scale, double* x, double* y) const {
  HasRadius::DrawDefault(surface, next_figure, scale, x, y);
  *x += scale * PURPLE_ARC_OFFSET;
}
