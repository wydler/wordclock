#ifndef WORDCLOCK_GRID_LANG_de_DE_s2_H
#define WORDCLOCK_GRID_LANG_de_DE_s2_H

class Grid_de_DE_s2 {
  public:
  static int time_it_is[5];
  static int time_minutes[12][12];
  static int time_hours[12][6];

  static void setTime(int hour, int minute);
};

typedef class Grid_de_DE_s2 Grid;

#endif
