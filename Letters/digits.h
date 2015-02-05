#ifndef Letters_digits_h
#define Letters_digits_h

#include "figures.h"
#include "letters.h"

struct One : public Letter {
  One() {
    AddFigures({
      new OffsetFigure(new BlueStick(), 0, 0, M_PI / 2),
      new OffsetFigure(new OrangeStick(), -ORANGE_STEP / sqrt(2),
          -BLUE_HALF_LENGTH + ORANGE_STEP / sqrt(2), -M_PI / 4),
    });
  }
};

struct Two : public Letter {
  Two() {
    AddFigures({
      new OffsetFigure(new GreenStick(),
          GREEN_STEP - 2 * ORANGE_STEP / sqrt(2), 2 * ORANGE_STEP / sqrt(2), 0),
      new OffsetFigure(new OrangeStick(),
          -ORANGE_STEP / sqrt(2), ORANGE_STEP / sqrt(2), -M_PI / 4),
      new OffsetFigure(new PurpleArc(),
          (PURPLE_ARC_OFFSET - PURPLE_ARC_RADIUS) / sqrt(2),
          (-PURPLE_ARC_OFFSET - PURPLE_ARC_RADIUS) / sqrt(2),
          3 * M_PI / 4),
    });
  }
};

struct Three : public Letter {
  Three() {
    AddFigures({
      new OffsetFigure(new OrangeStick(),
          GREEN_STEP / sqrt(2) - ORANGE_STEP, -2 * GREEN_STEP / sqrt(2), 0),
      new OffsetFigure(new GreenStick(), 0, -GREEN_STEP / sqrt(2), -M_PI / 4),
      new OffsetFigure(new PurpleArc(),
          -GREEN_STEP / sqrt(2) + PURPLE_ARC_OFFSET, PURPLE_ARC_RADIUS, M_PI),
    });
  }
};

struct Four : public Letter { };

struct Five : public Letter {
  Five() {
    AddFigures({
      new OffsetFigure(new OrangeStick(), 0, -2 * ORANGE_STEP, 0),
      new OffsetFigure(new OrangeStick(), -ORANGE_STEP, -ORANGE_STEP, M_PI / 2),
      new OffsetFigure(new PurpleArc(),
          -ORANGE_STEP + PURPLE_ARC_OFFSET, PURPLE_ARC_RADIUS, M_PI),
    });
  }
};

struct Six : public Letter { };

struct Seven : public Letter {
  Seven() {
    AddFigures({
      new OffsetFigure(new GreenStick(), 0, -BLUE_HALF_LENGTH * sin(angle), 0),
      new OffsetFigure(new BlueStick(), 0, 0, -angle),
    });
  }
private:
  const double angle = acos(GREEN_STEP / BLUE_HALF_LENGTH);
};

struct Eight : public Letter {
  Eight() {
    AddFigures({
      new OffsetFigure(new GreenArc(), 0, -GREEN_ARC_RADIUS, 0),
      new OffsetFigure(new GreenArc(), 0, -GREEN_ARC_RADIUS, M_PI),
      new OffsetFigure(new GreenArc(), 0, GREEN_ARC_RADIUS, 0),
      new OffsetFigure(new GreenArc(), 0, GREEN_ARC_RADIUS, M_PI),
    });
  }
};

struct Nine : public Letter { };

struct Zero : public Letter {
  Zero() {
    AddFigures({
      new OffsetFigure(new PurpleArc(), 0, -PURPLE_ARC_OFFSET, M_PI / 2),
      new OffsetFigure(new PurpleArc(), 0, PURPLE_ARC_OFFSET, -M_PI / 2),
    });
  }
};

#endif
