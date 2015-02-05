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
  const double width = 612;
  const double height = 792;
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
  
  auto letter = letters.begin();
  const int rows = 3;
  const int columns = 2;
  for (int p = 1; letter != letters.end(); ++p) {
    std::string filename = "image" + std::to_string(p) + ".pdf";
    Cairo::RefPtr<Cairo::PdfSurface> surface =
      Cairo::PdfSurface::create(filename, width, height);
    for (int i = 0; i < rows && letter != letters.end(); ++i) {
      for (int j = 0; j < columns && letter != letters.end(); ++j, ++letter) {
        (*letter)->Draw(surface, scale,
          width * (j + 0.5) / columns, height * (i + 0.5) / rows);
      }
    }
    surface.clear();
    system(("open " + filename).c_str());
  }

  return 0;
}