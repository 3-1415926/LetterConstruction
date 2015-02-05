#ifndef Letters_letters_h
#define Letters_letters_h

#include <cmath>
#include <vector>

#include "cairommconfig.h"
#include "cairomm/context.h"
#include "cairomm/surface.h"
#include "figures.h"

class Letter {
public:
  Letter() { }
  virtual ~Letter() { }

  void Draw(Cairo::RefPtr<Cairo::Surface> surface,
            double scale, double x, double y) const;

  void DrawParts(Cairo::RefPtr<Cairo::Surface> surface,
                 double scale, double x, double y) const;
protected:
  void AddFigures(std::initializer_list<OffsetFigure*> figures) {
    this->figures.insert(this->figures.end(), figures.begin(), figures.end());
  }

private:
  std::vector<OffsetFigure*> figures;
};

struct LeftStick : public virtual Letter {
  LeftStick() {
    AddFigures({
      new OffsetFigure(new BlueStick(), -ORANGE_STEP, 0, M_PI / 2),
    });
  }
};

struct VerticalStick : public virtual Letter {
  VerticalStick() {
    AddFigures({
      new OffsetFigure(new BlueStick(), 0, 0, M_PI / 2),
    });
  }
};

struct RightStick : public virtual Letter {
  RightStick() {
    AddFigures({
      new OffsetFigure(new BlueStick(), ORANGE_STEP, 0, M_PI / 2),
    });
  }
};

struct TopStick : public virtual Letter {
  TopStick() {
    AddFigures({
      new OffsetFigure(new OrangeStick(), 0, -BLUE_HALF_LENGTH, 0),
    });
  }
};

struct HorizontalStick : public virtual Letter {
  HorizontalStick() {
    AddFigures({
      new OffsetFigure(new OrangeStick(), 0, 0, 0),
    });
  }
};

struct BottomStick : public virtual Letter {
  BottomStick() {
    AddFigures({
      new OffsetFigure(new OrangeStick(), 0, BLUE_HALF_LENGTH, 0),
    });
  }
};

struct Г : public virtual LeftStick, public virtual TopStick { };

struct Т : public virtual VerticalStick, public virtual TopStick { };

struct Н : public virtual LeftStick, public virtual RightStick,
    public virtual HorizontalStick { };

struct П : public virtual Г, public virtual RightStick { };

struct Е : public virtual Г,
    public virtual HorizontalStick, public virtual BottomStick { };

struct TopArc : public virtual Letter {
  TopArc() {
    AddFigures({
      new OffsetFigure(new PurpleArc(),
        -PURPLE_ARC_RADIUS + PURPLE_ARC_OFFSET, -BLUE_HALF_LENGTH / 2, M_PI),
    });
  }
};

struct BottomArc : public virtual Letter {
  BottomArc() {
    AddFigures({
      new OffsetFigure(new PurpleArc(),
        -PURPLE_ARC_RADIUS + PURPLE_ARC_OFFSET, BLUE_HALF_LENGTH / 2, M_PI),
    });
  }
};

struct З : public virtual TopArc, public virtual BottomArc { };

struct Р : public virtual LeftStick, public virtual TopArc { };

struct Ь : public virtual LeftStick, public virtual BottomArc { };

struct Б : public virtual Г, public virtual BottomArc { };

struct В : public virtual LeftStick, public virtual З { };

struct FarVerticalSticks : public virtual Letter {
  FarVerticalSticks() {
    AddFigures({
      new OffsetFigure(new BlueStick(), -BLUE_HALF_LENGTH, 0, M_PI / 2),
      new OffsetFigure(new BlueStick(), BLUE_HALF_LENGTH, 0, M_PI / 2),
    });
  }
};

struct LongBottomStick : public virtual Letter {
  LongBottomStick() {
    AddFigures({
      new OffsetFigure(new BlueStick(), 0, BLUE_HALF_LENGTH, 0),
    });
  }
};

struct Л : public Letter {
  Л() {
    AddFigures({
      new OffsetFigure(new BlueStick(),
        -ORANGE_STEP + cos(leg_angle) * BLUE_SMALL_STEP, 0, -leg_angle),
      new OffsetFigure(new BlueStick(),
        ORANGE_STEP - cos(leg_angle) * BLUE_SMALL_STEP, 0, leg_angle),
    });
  }
protected:
  const double leg_angle =
    acos(ORANGE_STEP / (BLUE_HALF_LENGTH + BLUE_SMALL_STEP));
};

struct А : public virtual Л {
  А() {
    AddFigures({
      new OffsetFigure(new OrangeStick(),
          0, sin(leg_angle) * BLUE_SMALL_STEP, 0),
    });
  }
};

struct Д : public virtual LongBottomStick {
  Д() {
    AddFigures({
      new OffsetFigure(new BlueStick(), -BLUE_SMALL_STEP / 2,
        BLUE_HALF_LENGTH * (1 - sin(leg_angle)), -leg_angle),
      new OffsetFigure(new BlueStick(), BLUE_SMALL_STEP / 2,
        BLUE_HALF_LENGTH * (1 - sin(leg_angle)), leg_angle),
    });
  }
protected:
  const double leg_angle = acos(BLUE_SMALL_STEP / BLUE_HALF_LENGTH / 2);
};

struct Ё : public virtual Е {
  Ё() {
    AddFigures({
      new OffsetFigure(new PurpleDot(),
          -ORANGE_STEP / 2, -BLUE_HALF_LENGTH - ORANGE_STEP, 0),
      new OffsetFigure(new PurpleDot(),
          ORANGE_STEP / 2, -BLUE_HALF_LENGTH - ORANGE_STEP, 0),
    });
  }
};

struct Ж : public virtual Letter {
  Ж() {
    AddFigures({
      new OffsetFigure(new BlueStick(), 0, 0, -leg_angle),
      new OffsetFigure(new GreenStick(), 0, 0, M_PI / 2),
      new OffsetFigure(new BlueStick(), 0, 0, leg_angle),
    });
  }
protected:
  const double leg_angle = asin(GREEN_STEP / BLUE_HALF_LENGTH);
};

struct И : public virtual Letter {
  И() {
    AddFigures({
      new OffsetFigure(new BlueStick(),
        -(GREEN_STEP + ORANGE_STEP) * cos(mid_angle), 0, M_PI / 2),
      new OffsetFigure(new BlueStick(),
        (GREEN_STEP + ORANGE_STEP) * cos(mid_angle), 0, M_PI / 2),
      new OffsetFigure(new GreenStick(),
        ORANGE_STEP * cos(mid_angle), -ORANGE_STEP * sin(mid_angle), -mid_angle),
      new OffsetFigure(new OrangeStick(),
        -GREEN_STEP * cos(mid_angle), GREEN_STEP * sin(mid_angle), -mid_angle),
    });
  }
protected:
  const double mid_angle =
    asin(BLUE_HALF_LENGTH / (GREEN_STEP + ORANGE_STEP));
};

struct Й : public virtual И {
  Й() {
    AddFigures({
      new OffsetFigure(new OrangeArc(),
        0, -BLUE_HALF_LENGTH - ORANGE_STEP, -M_PI / 2),
    });
  }
};

struct К : public virtual Letter {
  К() {
    AddFigures({
      new OffsetFigure(new BlueStick(),
        -GREEN_STEP * cos(leg_angle), 0, M_PI / 2),
      new OffsetFigure(new GreenStick(),
        0, -GREEN_STEP * sin(leg_angle), -leg_angle),
      new OffsetFigure(new GreenStick(),
        0, GREEN_STEP * sin(leg_angle), leg_angle),
    });
  }
protected:
  const double leg_angle = asin(BLUE_HALF_LENGTH / GREEN_STEP / 2);
};

struct М : public virtual FarVerticalSticks {
  М() {
    AddFigures({
      new OffsetFigure(new BlueStick(), -BLUE_HALF_LENGTH / 2,
        BLUE_HALF_LENGTH * (sin(mid_angle) - 1), mid_angle),
      new OffsetFigure(new BlueStick(), BLUE_HALF_LENGTH / 2,
        BLUE_HALF_LENGTH * (sin(mid_angle) - 1), -mid_angle),
    });
  }
protected:
  const double mid_angle = acos(0.5);
};

struct О : public virtual Letter {
  О() {
    AddFigures({
      new OffsetFigure(new BlueArc(), 0, 0, M_PI),
      new OffsetFigure(new BlueArc(), 0, 0, 0),
    });
  }
};

struct С : public virtual Letter {
  С() {
    AddFigures({
      new OffsetFigure(new BlueArc(), 0, 0, -M_PI / 4),
      new OffsetFigure(new BlueArc(), 0, 0, M_PI / 4),
    });
  }
};

struct У : public virtual Letter {
  У() {
    AddFigures({
      new OffsetFigure(new OrangeStick(), -ORANGE_STEP * cos(leg_angle),
        -ORANGE_STEP * sin(leg_angle), leg_angle),
      new OffsetFigure(new BlueStick(), 0, 0, -leg_angle),
    });
  }
protected:
  const double leg_angle = acos(0.5);
};

struct Ф : public virtual VerticalStick {
  Ф() {
    AddFigures({
      new OffsetFigure(new PurpleArc(),
        -PURPLE_ARC_OFFSET, -BLUE_HALF_LENGTH / 2, 0),
      new OffsetFigure(new PurpleArc(),
        PURPLE_ARC_OFFSET, -BLUE_HALF_LENGTH / 2, M_PI),
    });
  }
};

struct Х : public virtual Letter {
  Х() {
    AddFigures({
      new OffsetFigure(new BlueStick(), 0, 0, -leg_angle),
      new OffsetFigure(new BlueStick(), 0, 0, leg_angle),
    });
  }
protected:
  const double leg_angle = acos(0.5);
};

struct Ц : public virtual LeftStick, public virtual RightStick,
    public virtual BottomStick {
  Ц() {
    AddFigures({
      new OffsetFigure(new OrangeArc(),
        ORANGE_STEP, BLUE_HALF_LENGTH + ORANGE_ARC_RADIUS, M_PI),
    });
  }
};

struct Ч : public virtual RightStick, public virtual HorizontalStick {
  Ч() {
    AddFigures({
      new OffsetFigure(new OrangeStick(), -ORANGE_STEP, -ORANGE_STEP, M_PI / 2),
    });
  }
};

struct Ш : public virtual FarVerticalSticks, public virtual VerticalStick,
    public virtual LongBottomStick { };

struct Щ : public virtual Ш {
  Щ() {
    AddFigures({
      new OffsetFigure(new OrangeArc(),
        BLUE_HALF_LENGTH, BLUE_HALF_LENGTH + ORANGE_ARC_RADIUS, M_PI),
    });
  }
};

struct Ъ : public virtual Ь {
  Ъ() {
    AddFigures({
      new OffsetFigure(new OrangeArc(),
        -ORANGE_STEP - ORANGE_ARC_RADIUS, -BLUE_HALF_LENGTH, M_PI / 2),
    });
  }
};

struct Ы : public virtual Letter {
  Ы() {
    AddFigures({
      new OffsetFigure(new BlueStick(), -1.5 * ORANGE_STEP, 0, M_PI / 2),
      new OffsetFigure(new BlueStick(), 1.5 * ORANGE_STEP, 0, M_PI / 2),
      new OffsetFigure(new PurpleArc(),
        -1.5 * ORANGE_STEP + PURPLE_ARC_OFFSET, BLUE_HALF_LENGTH / 2, M_PI),
    });
  }
};

struct Э : public virtual HorizontalStick {
  Э() {
    AddFigures({
      new OffsetFigure(new BlueArc(), -ORANGE_STEP, 0, M_PI),
    });
  }
};

struct Ю : public virtual Letter {
  Ю() {
    AddFigures({
      new OffsetFigure(new BlueStick(), -3 * ORANGE_STEP, 0, M_PI / 2),
      new OffsetFigure(new OrangeStick(), -2 * ORANGE_STEP, 0, 0),
      new OffsetFigure(new BlueArc(), ORANGE_STEP, 0, 0),
      new OffsetFigure(new BlueArc(), ORANGE_STEP, 0, M_PI),
    });
  }
};

struct Я : public virtual RightStick {
  Я() {
    AddFigures({
      new OffsetFigure(new PurpleArc(),
        ORANGE_STEP - PURPLE_ARC_OFFSET, -BLUE_HALF_LENGTH / 2, 0),
      new OffsetFigure(new GreenStick(),
        ORANGE_STEP - GREEN_STEP * cos(leg_angle),
        GREEN_STEP * sin(leg_angle), -leg_angle),
    });
  }
protected:
  const double leg_angle = asin(BLUE_HALF_LENGTH / GREEN_STEP / 2);
};

#endif
