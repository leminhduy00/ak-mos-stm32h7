/*
 * display.h
 *
 *  Created on: Feb 25, 2018
 *      Author: desertkun
 */

#ifndef DEVICE_DISPLAY_H_
#define DEVICE_DISPLAY_H_

#include <stdint.h>

enum
{
	COLOR_WHITE = 0x01, // Set pixel
	COLOR_BLACK = 0x00, // Reset pixel
};

class Display
{
  public:
	enum class Font
	{
		f_7x10,
		f_5x7
	};

  public:
	static void init();

  public:
	static uint8_t width();
	static uint8_t height();

	static void setModeSet();
	static void setModeReset();
	static void setModeInvert();

	static void clear();
	static void update();
	static void fillScreen(uint8_t color);
	static void invertDisplay(bool invert);

	static void display_on();
	static void display_off();
	static void setTextColor(uint8_t color);
	static void drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
	static void drawRectangle(uint8_t x, uint8_t y, uint8_t w, uint8_t h);
	static void drawImage(uint8_t X, uint8_t Y, uint8_t W, uint8_t H, const uint8_t* image);
	static void drawImageFullscreen(const uint8_t* image);
	static void drawText(uint8_t X, uint8_t Y, const char *str, Display::Font font);
	static void drawText(uint8_t X, uint8_t Y, const char *str);
	static void drawText(const char* str);
	static void drawPixel(uint8_t x, uint8_t y, uint8_t mode);
	static void drawCircle(uint8_t x, uint8_t y, uint8_t r);
};

extern Display oled_display;

#endif /* DEVICE_DISPLAY_H_ */
