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

struct Four : public Letter {
  Four() {
    AddFigures({
      new OffsetFigure(new BlueStick(), BLUE_SMALL_STEP, 0, M_PI / 2),
      new OffsetFigure(new GreenStick(),
          -BLUE_HALF_LENGTH + GREEN_STEP * cos(green_angle),
          BLUE_SMALL_STEP - GREEN_STEP * sin(green_angle),
          -green_angle),
      new OffsetFigure(new BlueStick(), 0, BLUE_SMALL_STEP, 0),
    });
  }
private:
  const double green_angle = 3 * M_PI / 8;
};

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

struct Six : public Letter {
  Six() {
    AddFigures({
      new OffsetFigure(new GreenStick(),
          -GREEN_ARC_RADIUS * sin(circ_angle)
                       + GREEN_STEP * cos(head_angle),
          GREEN_ARC_RADIUS * (1 - cos(circ_angle))
                       - GREEN_STEP * sin(head_angle),
          -head_angle),
      new OffsetFigure(new GreenArc(), 0, GREEN_ARC_RADIUS, -circ_angle),
      new OffsetFigure(new GreenArc(), 0, GREEN_ARC_RADIUS, M_PI - circ_angle),
    });
  }
private:
  const double circ_angle = M_PI / 4;
  const double head_angle = 5 * M_PI / 16;
};

struct Seven : public Letter {
  Seven() {
    AddFigures({
      new OffsetFigure(new GreenStick(), 0, -BLUE_HALF_LENGTH * sin(angle), 0),
      new OffsetFigure(new BlueStick(),
          GREEN_STEP - BLUE_HALF_LENGTH * cos(angle), 0, -angle),
    });
  }
private:
  const double angle = acos(5 * GREEN_STEP / BLUE_HALF_LENGTH / 8);
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

struct Nine : public Letter {
  Nine() {
    AddFigures({
      new OffsetFigure(new GreenArc(), 0, -GREEN_ARC_RADIUS, -circ_angle),
      new OffsetFigure(new GreenArc(), 0, -GREEN_ARC_RADIUS, M_PI - circ_angle),
      new OffsetFigure(new GreenStick(),
          GREEN_ARC_RADIUS * sin(circ_angle)
                       - GREEN_STEP * cos(head_angle),
          -GREEN_ARC_RADIUS * (1 - cos(circ_angle))
                       + GREEN_STEP * sin(head_angle),
          -head_angle),
    });
  }
private:
  const double circ_angle = M_PI / 4;
  const double head_angle = 5 * M_PI / 16;
};

struct Zero : public Letter {
  Zero() {
    AddFigures({
      new OffsetFigure(new PurpleArc(), 0, -PURPLE_ARC_OFFSET, M_PI / 2),
      new OffsetFigure(new PurpleArc(), 0, PURPLE_ARC_OFFSET, -M_PI / 2),
    });
  }
};

#endif
