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
  const double scale = 0.6;
  
  std::vector<Letter*> letters = {
    new А(), new Б(), new В(), new Г(), new Д(),
    new Е(), new Ё(), new Ж(), new З(), new И(),
    new Й(), new К(), new Л(), new М(), new Н(),
    new О(), new П(), new Р(), new С(), new Т(),
    new У(), new Ф(), new Х(), new Ц(), new Ч(),
    new Ш(), new Щ(), new Ъ(), new Ы(), new Ь(),
    new Э(), new Ю(), new Я(),
  };
  
  std::string filename = "image.pdf";
  Cairo::RefPtr<Cairo::PdfSurface> surface =
    Cairo::PdfSurface::create(filename, width, height);

  auto letter = letters.begin();
  const int rows = 3;
  const int columns = 2;
  while (letter != letters.end()) {
    for (int i = 0; i < rows && letter != letters.end(); ++i) {
      for (int j = 0; j < columns && letter != letters.end(); ++j, ++letter) {
        (*letter)->Draw(surface, scale,
          width * (j + 0.5) / columns, height * (i + 0.5) / rows);
      }
    }
    surface->show_page();
  }

  surface.clear();
  system(("open " + filename).c_str());

  return 0;
}