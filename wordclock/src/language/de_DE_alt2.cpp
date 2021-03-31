#include <Arduino.h>

#include "de_DE_alt2.h"

#include "../config.h"
#include "../dnd.h"
#include "../led.h"

void Grid_de_DE_alt2::setTime(int hour, int minute) {
  if(hour == -1 || minute == -1) {
	return;
  }

  if(DND::active(hour, minute)) {
	for(int i = 0; i < NUM_LEDS; i++) {
	  Led::ids[i].setRGB(0, 0, 0);
	}

	FastLED.show();

	return;
  }

  int singleMinute = minute % 5;
  int hourLimit = 6;

  minute = (minute - (minute % 5));

  if(minute >= 25) {
	hour += 1;
  }

  minute = minute / 5;
  hour = hour % 12;

  for(int i = 0; i < NUM_LEDS; i++) {
	Led::ids[i].setRGB(Config::color_bg.r * 0.2, Config::color_bg.g * 0.2, Config::color_bg.b * 0.2);
  }

  for(int i = 0; i < 5; i++) {
	Led::ids[Led::getLedId(Grid_de_DE_alt2::time_it_is[i])].setRGB(Config::color_fg.r, Config::color_fg.g, Config::color_fg.b);
  }

  for(int m = 0; m < 12; m++) {
	if(Grid_de_DE_alt2::time_minutes[minute][m] >= 0) {
	  Led::ids[Led::getLedId(Grid_de_DE_alt2::time_minutes[minute][m])].setRGB(Config::color_fg.r, Config::color_fg.g, Config::color_fg.b);
	}
  }

  if(hour == 1 && minute == 0) {
	hourLimit = 3;
  }

  for(int h = 0; h < hourLimit; h++) {
	if(Grid_de_DE_alt2::time_hours[hour][h] >= 0) {
	  Led::ids[Led::getLedId(Grid_de_DE_alt2::time_hours[hour][h])].setRGB(Config::color_fg.r, Config::color_fg.g, Config::color_fg.b);
	}
  }

  if(GRID_SINGLE_MINUTES == 1) {
	// single minutes
	for(int s = (NUM_LEDS - 4); s < (NUM_LEDS - 4 + singleMinute); s++) {
	  Led::ids[s].setRGB(Config::color_fg.r, Config::color_fg.g, Config::color_fg.b);
	}
  } else {
	for(int s = 0; s < singleMinute; s++) {
	  Led::ids[s].setRGB(Config::color_fg.r, Config::color_fg.g, Config::color_fg.b);
	}
  }

  FastLED.setBrightness(Config::brightness * 255);
  FastLED.show();
}

int Grid_de_DE_alt2::time_it_is[5] = {0, 1, 3, 4, 5}; // es ist

int Grid_de_DE_alt2::time_minutes[12][12] = {
  {107, 108, 109,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1}, // uhr
  {  7,   8,   9,  10,  40,  41,  42,  43,  -1,  -1,  -1,  -1}, // fünf nach
  { 11,  12,  13,  14,  40,  41,  42,  43,  -1,  -1,  -1,  -1}, // zehn nach
  { 26,  27,  28,  29,  30,  31,  32,  40,  41,  42,  43,  -1}, // viertel nach
  { 15,  16,  17,  18,  19,  20,  21,  40,  41,  42,  43,  -1}, // zwanzig nach
  {  7,   8,   9,  10,  33,  34,  35,  44,  45,  46,  47,  -1}, // fünf vor halb
  { 44,  45,  46,  47,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1}, // halb
  {  7,   8,   9,  10,  40,  41,  42,  43,  44,  45,  46,  47}, // fünf nach halb
  { 15,  16,  17,  18,  19,  20,  21,  33,  34,  35,  -1,  -1}, // zwanzig vor
  { 26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  -1,  -1}, // viertel vor
  { 11,  12,  13,  14,  33,  34,  35,  -1,  -1,  -1,  -1,  -1}, // zehn vor
  {  7,   8,   9,  10,  33,  34,  35,  -1,  -1,  -1,  -1,  -1}  // fünf vor
};

int Grid_de_DE_alt2::time_hours[12][6] = {
  { 94,  95,  96,  97,  98,  -1}, // zwölf
  { 55,  56,  57,  58,  -1,  -1}, // eins
  { 62,  63,  64,  65,  -1,  -1}, // zwei
  { 66,  67,  68,  69,  -1,  -1}, // drei
  { 73,  74,  75,  76,  -1,  -1}, // vier
  { 51,  52,  53,  54,  -1,  -1}, // fünf
  { 77,  78,  79,  80,  81,  -1}, // sechs
  { 88,  89,  90,  91,  92,  93}, // sieben
  { 84,  85,  86,  87,  -1,  -1}, // acht
  {102, 103, 104, 105,  -1,  -1}, // neun
  { 99, 100, 101, 102,  -1,  -1}, // zehn
  { 49,  50,  51,  -1,  -1,  -1}  // elf
};
