#pragma once

#include "wled.h"

uint16_t mode_letterlampe_pinsel(void);
uint16_t mode_letterlampe_rainbow(void);

static const char _data_FX_MODE_LETTER_LAMPE_PINSEL[] PROGMEM = "JULIA Pinsel@Speed,Stroke Length,,,,Buchstabe fuellen,Wort fuellen,;!,!;!;sx=20,ix=10,o1=1,o2=1";
static const char _data_FX_MODE_LETTER_LAMPE_RAINBOW[] PROGMEM = "JULIA Regenbogen@Speed,Stroke Length,,,,Buchstabe fuellen,Wort fuellen,;!,!;!;sx=20,ix=10,o1=1,o2=1";

class LetterLampLetter {
 public:
  int32_t first_led_idx {0};
  int32_t num_leds {0};

  uint16_t last_used_palette_index {0};

  explicit LetterLampLetter(int32_t first_led_idx, int32_t num_leds, std::vector<std::vector<int32_t>> pairs) {
	  this->first_led_idx = first_led_idx;
	  this->num_leds = num_leds;
	  this->pairs = pairs;
  }
  
  void fill_range(int from, int len, uint32_t c) {
    for (int i=from; i<from+len; i++) {
      SEGMENT.setPixelColor(i, c);
    }
  }

  /*
   *
   * Returns true if letter is fully painted
   * 
   * if now == 0 the full letter will be drawn always
   */
  bool draw_pinsel(const uint32_t now, int32_t speed, int32_t length, uint16_t start_palette_index, uint16_t palette_step, bool restart, bool black_rest, bool *brush_reached_end=NULL) {
	  // speed = indices per second
	  //fill_range(first_led_idx, num_leds, BLACK);
	  
	  if (restart) {
		  animation_start = now;
	  }
	  
	  
	  int first_index = 0;
	  int32_t anim_index;
    
    if (now == 0) { //draw full letter
      first_index = 0;
      anim_index = (int32_t)pairs.size()-1;
    } else {
      anim_index = ((now - animation_start) * speed) / 1000;
      if (length == 65535 || length == -1) {
        length = pairs.size();
      }
      if (length > 0) {
        first_index = std::max(0, anim_index - length + 1);
      }
    }
	  
    if (black_rest) {
      for (int i = first_led_idx; i < first_led_idx+num_leds; i++) {
        SEGMENT.setPixelColor(i, BLACK);
      }
    }

	  for (int i = first_index; i <= std::min(anim_index, (int32_t)pairs.size()-1); ++i) {
      last_used_palette_index = start_palette_index + i * palette_step;
      for (int32_t idx : pairs[i]) {
        if (idx > -1) {
          SEGMENT.setPixelColor(first_led_idx + idx, SEGMENT.color_from_palette(last_used_palette_index, false, true, 0));
        } else {
          break;
        }
      }
	  }
	  
    if (brush_reached_end != NULL) {
      *brush_reached_end = anim_index >= pairs.size() - 1;
    }

	  return anim_index >= pairs.size() - 1 + length;
  }
 protected:
  std::vector<std::vector<int32_t>> pairs; // pixel pairs which are positioned opposite to each other
  unsigned long animation_start {0};
};

class UsermodLetterLampe : public Usermod {
  private:
    // configuration (available in API and stored in flash)
    bool     enabled          = true;

    // runtime
    bool     initDone         = false;


  public:
    static LetterLampLetter* letters[5];
    static const uint8_t num_letters = 5;

    void setup() {
      strip.addEffect(255, &mode_letterlampe_pinsel, _data_FX_MODE_LETTER_LAMPE_PINSEL);
      strip.addEffect(255, &mode_letterlampe_rainbow, _data_FX_MODE_LETTER_LAMPE_RAINBOW);
      // J
      letters[0] = new LetterLampLetter(0,
                                        41,
                                        { {22, 23, 24, -1},
                                          {21, 25, -1, -1},
                                          {20, 26, -1, -1},
                                          {19, 27, -1, -1},
                                          {18, 28, -1, -1},
                                          {17, 29, -1, -1},
                                          {16, 30, -1, -1},
                                          {15, 31, -1, -1},
                                          {14, 32, -1, -1},
                                          {13, -1, -1, -1},
                                          {12, 33, -1, -1},
                                          {11, -1, -1, -1},
                                          {10, 34, -1, -1},
                                          {9, -1, -1, -1},
                                          {8, -1, -1, -1},
                                          {7, 35, -1, -1},
                                          {6, -1, -1, -1},
                                          {5, -1, -1, -1},
                                          {4, 36, -1, -1},
                                          {3, -1, -1, -1},
                                          {2, -1, -1, -1},
                                          {1, 37, -1, -1},
                                          {0, 40, 39, 38}});
      // U
      letters[1] = new LetterLampLetter(letters[0]->first_led_idx+letters[0]->num_leds,
                                        58,
                                        { {55, 56, 57, -1},
                                          {0, 54, -1, -1},
                                          {1, 53, -1, -1},
                                          {2, 52, -1, -1},
                                          {3, 51, -1, -1},
                                          {4, 50, -1, -1},
                                          {5, 49, -1, -1},
                                          {6, 48, -1, -1},
                                          {7, 47, -1, -1},
                                          {8, 46, -1, -1},
                                          {9, -1, -1, -1},
                                          {10, 45, -1, -1},
                                          {11, -1, -1, -1},
                                          {12, 44, -1, -1},
                                          {13, -1, -1, -1},
                                          {14, -1, -1, -1},
                                          {15, 43, -1, -1},
                                          {16, -1, -1, -1},
                                          {17, -1, -1, -1},
                                          {18, 42, -1, -1},
                                          {19, -1, -1, -1},
                                          {20, -1, -1, -1},
                                          {21, 41, -1, -1},
                                          {22, 40, -1, -1},
                                          {23, 39, -1, -1},
                                          {24, 38, -1, -1},
                                          {25, 37, -1, -1},
                                          {26, 36, -1, -1},
                                          {27, 35, -1, -1},
                                          {28, 34, -1, -1},
                                          {29, 33, -1, -1},
                                          {30, 31, 32, -1},
                                        });
      // L
      letters[2] = new LetterLampLetter(letters[1]->first_led_idx+letters[1]->num_leds,
                                        43,
                                        { {42, 41, 40, -1},
                                          {0, 39, -1, -1},
                                          {1, 38, -1, -1},
                                          {2, 37, -1, -1},
                                          {3, 36, -1, -1},
                                          {4, 35, -1, -1},
                                          {5, 34, -1, -1},
                                          {6, 33, -1, -1},
                                          {7, 32, -1, -1},
                                          {8, 31, -1, -1},
                                          {9, 30, -1, -1},
                                          {10, -1, -1, -1},
                                          {11, -1, -1, -1},
                                          {12, -1, -1, -1},
                                          {13, -1, -1, -1},
                                          {14, -1, -1, -1},
                                          {15, 29, -1, -1},
                                          {16, 28, -1, -1},
                                          {17, 27, -1, -1},
                                          {18, 26, -1, -1},
                                          {19, 25, -1, -1},
                                          {20, 24, -1, -1},
                                          {21, 22, 23, -1}
                                        });
      // I
      letters[3] = new LetterLampLetter(letters[2]->first_led_idx+letters[2]->num_leds,
                                        32,
                                        { {29, 30, 31, -1},
                                          {0, 28, -1, -1},
                                          {1, 27, -1, -1},
                                          {2, 26, -1, -1},
                                          {3, 25, -1, -1},
                                          {4, 24, -1, -1},
                                          {5, 23, -1, -1},
                                          {6, 22, -1, -1},
                                          {7, 21, -1, -1},
                                          {8, 20, -1, -1},
                                          {9, 19, -1, -1},
                                          {10, 18, -1, -1},
                                          {11, 17, -1, -1},
                                          {12, 16, -1, -1},
                                          {13, 14, 15, -1}
                                        });
      // A
      letters[4] = new LetterLampLetter(letters[3]->first_led_idx+letters[3]->num_leds,
                                        55,
                                        { {25, -1, -1, -1},
                                          {26, -1, -1, -1},
                                          {27, -1, -1, -1},
                                          {28, -1, -1, -1},
                                          {29, 51, -1, -1},
                                          {30, 52, -1, -1},
                                          {31, 53, -1, -1},
                                          {32, 54, -1, -1},
                                          {33, -1, -1, -1},
                                          {34, -1, -1, -1},
                                          {35, 44, -1, -1},
                                          {36, 43, -1, -1},
                                          {37, 42, -1, -1},
                                          {38, 41, -1, -1},
                                          {39, -1, -1, -1},
                                          {40, -1, -1, -1},
                                          {24, -1, -1, -1},
                                          {23, -1, -1, -1},
                                          {22, -1, -1, -1},
                                          {21, -1, -1, -1},
                                          {20, 50, -1, -1},
                                          {19, 49, -1, -1},
                                          {18, 48, -1, -1},
                                          {17, -1, -1, -1},
                                          {16, -1, -1, -1},
                                          {15, 4, -1, -1},
                                          {14, 5, -1, -1},
                                          {13, 6, -1, -1},
                                          {12, 7, -1, -1},
                                          {11, 8, -1, -1},
                                          {9, 10, -1, -1},
                                          {0, 45, -1, -1},
                                          {1, 46, -1, -1},
                                          {2, 47, -1, -1},
                                          {3, -1, -1, -1}
                                        });
    }

    void loop() {

    }
};

LetterLampLetter * UsermodLetterLampe::letters[5];

struct StatusPinsel {
  bool init_finished;
  uint8_t speed;
  bool fill_letter;
  bool fill_word;
  uint8_t stroke_len;
  uint16_t intra_letter_color_step; // steps in palette per pinsel index
  uint16_t inter_letter_color_step; // steps in palette between end of previous and beginning of current letter

  int current_letter;
  bool current_letter_first_run;
  bool word_filled;
  uint16_t palette_index;
  unsigned long start_time;
  bool override_settings;
};

uint16_t mode_letterlampe_pinsel(StatusPinsel *status) {
  unsigned long now = millis();

  if (!status->override_settings) {
    status->speed = SEGMENT.speed;
    status->fill_letter = SEGMENT.check1;
    status->fill_word = SEGMENT.check2;
    status->stroke_len = (status->fill_letter||status->fill_word) ? -1 : SEGMENT.intensity;
  }

  if (!status->init_finished) {
    status->intra_letter_color_step = 0;
    status->inter_letter_color_step = 30;
    
    status->current_letter = 0;
    status->current_letter_first_run = true;
    status->word_filled = false;
    status->palette_index = 0;
    status->init_finished = true;
    SEGMENT.fill(BLACK);
  }

  bool brush_reached_end = false;
  bool letter_finished = UsermodLetterLampe::letters[status->current_letter]->draw_pinsel(now,
                                                                                          status->speed,
                                                                                          status->stroke_len,
                                                                                          status->palette_index,
                                                                                          status->intra_letter_color_step,
                                                                                          status->current_letter_first_run,
                                                                                          !status->fill_letter,
                                                                                          &brush_reached_end);
  status->current_letter_first_run = false;
  if ( (status->fill_word && brush_reached_end) || letter_finished) {
    //status->palette_index += status->inter_letter_color_step; //UsermodLetterLampe::letters[status->current_letter]->last_used_color + status->inter_letter_color_step;
    status->palette_index = UsermodLetterLampe::letters[status->current_letter]->last_used_palette_index + status->inter_letter_color_step;
    status->current_letter = (status->current_letter + 1) % UsermodLetterLampe::num_letters;
    status->current_letter_first_run = true;

    status->word_filled = (status->current_letter == 0);
  }

  return FRAMETIME;
}

uint16_t mode_letterlampe_pinsel(void) {

  if (!SEGMENT.allocateData(sizeof(StatusPinsel))) {
    return FRAMETIME; // allocation failed
  };
  
  StatusPinsel *status = reinterpret_cast<StatusPinsel*>(SEGENV.data);

  return mode_letterlampe_pinsel(status);
}

uint16_t mode_letterlampe_rainbow(void) {
  if (!SEGMENT.allocateData(sizeof(StatusPinsel))) {
    return FRAMETIME; // allocation failed
  };
  
  unsigned long now = millis();
  
  StatusPinsel *status = reinterpret_cast<StatusPinsel*>(SEGENV.data);

  status->speed = SEGMENT.speed;
  status->override_settings = true;

  if (!status->init_finished) {
    status->fill_letter = true;
    status->fill_word = true;
    status->stroke_len = 1;
    status->intra_letter_color_step = 1; // increase color with each pinsel step
    status->inter_letter_color_step = 1;
    
    status->current_letter = 0;
    status->current_letter_first_run = true;
    status->word_filled = false;
    status->palette_index = 0;

    status->init_finished = true;
    SEGMENT.fill(BLACK);
  }

  if (!status->word_filled) {
    // run pinsel animation first until word is filled
    return mode_letterlampe_pinsel(status);
  } else {
    if (status->start_time == 0) {
      status->start_time = now;
    }

    uint16_t start_palette_index = ( (now - status->start_time) * status->speed ) / 1000; // speed = color steps per second
    
    for (int i=0; i<UsermodLetterLampe::num_letters; i++) {
      UsermodLetterLampe::letters[i]->draw_pinsel(0,
                                                                       0,
                                                                       0,
                                                                       start_palette_index,
                                                                       status->intra_letter_color_step,
                                                                       status->current_letter_first_run,
                                                                       false);
      start_palette_index = UsermodLetterLampe::letters[i]->last_used_palette_index + status->inter_letter_color_step; // first color for next letter
    }

    return FRAMETIME;
  }

}