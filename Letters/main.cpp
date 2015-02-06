#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "cairommconfig.h"
#include "cairomm/surface.h"
#include "digits.h"
#include "figures.h"
#include "letters.h"

int main() {
  const double points_in_inch = 72;
  const double width = 8.5 * points_in_inch;
  const double height = 11 * points_in_inch;
  const double margin = 0.25 * points_in_inch;
  const double scale = 0.6;
  
  std::vector<Letter*> letters = {
    new А(), new Б(), new В(), new Г(), new Д(), new Е(),
    new Ё(), new Ж(), new З(), new И(), new Й(), new К(),
    new Л(), new М(), new Н(), new О(), new П(), new Р(),
    new С(), new Т(), new У(), new Ф(), new Х(), new Ц(),
    new Ч(), new Ш(), new Щ(), new Ъ(), new Ы(), new Ь(),
    new Э(), new Ю(), new Я(),
    new One(), new Two(), new Three(), new Four(), new Five(),
    new Six(), new Seven(), new Eight(), new Nine(), new Zero(),
  };
  
  std::string filename = "letters-generated.pdf";
  Cairo::RefPtr<Cairo::PdfSurface> surface =
    Cairo::PdfSurface::create(filename, width, height);

  auto letter = letters.begin();
  const int rows = 3;
  const double max_parts_width = width / 2 - 2 * margin;
  while (letter != letters.end()) {
    for (int i = 0; i < rows && letter != letters.end(); ++i) {
      double parts_width = (*letter)->MeasurePartsWidth(scale);
      double extra_offset = parts_width > max_parts_width
          ? (parts_width - max_parts_width) / 2 : 0;
      (*letter)->Draw(surface, scale,
                      width / 4 - extra_offset,
                      height * (i + 0.5) / rows);
      (*letter)->DrawParts(surface, scale,
                           3 * width / 4 - parts_width / 2 - extra_offset,
                           height * (i + 0.5) / rows);
      if (i > 0) {
        auto cr = Cairo::Context::create(surface);
        cr->set_source_rgb(0.5, 0.5, 0.5);
        cr->set_line_width(LINE_WIDTH);
        cr->move_to(0, height * i / rows);
        cr->line_to(width, height * i / rows);
        cr->set_dash(std::vector<double>({ 1 }), 0);
        cr->stroke();
      }
      ++letter;
    }
    surface->show_page();
  }

  surface.clear();
  system(("open " + filename).c_str());

  return 0;
}