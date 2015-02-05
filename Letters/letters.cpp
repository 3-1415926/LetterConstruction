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

double Letter::MeasurePartsWidth(double scale) const {
  Cairo::RefPtr<Cairo::Surface> dummy_surface;
  double width = 0, _ = 0;
  DrawPartsImpl(figures, dummy_surface, scale, &width, &_);
  return width;
}

void Letter::DrawParts(Cairo::RefPtr<Cairo::Surface> surface,
                       double scale, double x, double y) const {
  DrawPartsImpl(figures, surface, scale, &x, &y);
}
