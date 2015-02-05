#include "letters.h"

namespace {
  void DrawPartsImpl(std::vector<OffsetFigure*> figures,
                     Cairo::RefPtr<Cairo::Surface> surface,
                     double scale, double* x, double* y) {
    for (int i = 0; i < figures.size(); ++i) {
      figures[i]->figure->DrawDefault(surface,
          i == figures.size() - 1 ? nullptr : figures[i + 1]->figure.get(),
          scale, x, y);
    }
  }
}

void Letter::Draw(Cairo::RefPtr<Cairo::Surface> surface,
                  double scale, double x, double y) const {
  for (const OffsetFigure* figure : figures) {
    figure->Draw(surface, scale, x, y, 0);
  }
}

void Letter::DrawParts(Cairo::RefPtr<Cairo::Surface> surface,
                       double scale, double x, double y) const {
  Cairo::RefPtr<Cairo::Surface> dummy_surface;
  double temp_x = 0, temp_y = 0;
  DrawPartsImpl(figures, dummy_surface, scale, &temp_x, &temp_y);
  x -= temp_x / 2;
  y -= temp_y / 2;
  DrawPartsImpl(figures, surface, scale, &x, &y);
}
