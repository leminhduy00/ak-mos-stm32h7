
#include <display.h>

extern "C"
{
	#include "sh1106.h"
	#include "font7x10.h"
	#include "font5x7.h"
}

uint8_t Display::width()
{
	return LCD_Width();
}

uint8_t Display::height()
{
	return LCD_Height();
}

void Display::clear()
{
	fillScreen(COLOR_BLACK);
	setTextColor(COLOR_WHITE);
	// update();
}

void Display::setTextColor(uint8_t color)
{
	if (color != 0)
	{
		setModeSet();
	}
	else
	{
		setModeReset();
	}
}

void Display::display_on()
{
	SH1106_SetDisplayState(LCD_ON);
}

void Display::display_off()
{
	SH1106_SetDisplayState(LCD_OFF);
}

void Display::fillScreen(uint8_t color)
{
	if (color != 0)
	{
		SH1106_SetModeSet();
		LCD_FillRect(0, 0, width() - 1, height() - 1);
	}
	else
	{
		SH1106_SetModeReset();
		LCD_FillRect(0, 0, width() - 1, height() - 1);
	}
}

void Display::update()
{
	SH1106_Flush();
}

void Display::setModeSet()
{
	SH1106_SetModeSet();
}

void Display::setModeReset()
{
	SH1106_SetModeReset();
}

void Display::setModeInvert()
{
	SH1106_SetModeInvert();
}

void Display::drawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
	LCD_Line(x1, y1, x2, y2);
}

void Display::invertDisplay(bool invert)
{
	SH1106_SetInvert((uint8_t)invert);
}

void Display::drawRectangle(uint8_t x, uint8_t y, uint8_t w, uint8_t h)
{
	LCD_FillRect(x, y, w, h);
}

void Display::drawImage(uint8_t X, uint8_t Y, uint8_t W, uint8_t H, const uint8_t* image)
{
	LCD_DrawBitmap(X, Y, W, H, image);
}

void Display::drawImageFullscreen(const uint8_t* image)
{
	LCD_DrawBitmapFullscreen(image);
}

void Display::drawText(uint8_t X, uint8_t Y, const char *str)
{
	drawText(X, Y, str, Display::Font::f_5x7);
}

void Display::drawText(uint8_t X, uint8_t Y, const char *str, Display::Font font)
{
	const Font_TypeDef *f;

	switch (font)
	{
		case Display::Font::f_7x10:
		{
			f = &Font7x10;
			break;
		}
		case Display::Font::f_5x7:
		default:
		{
			f = &Font5x7;
			break;
		}
	}

	LCD_PutStr(X, Y, str, f);
}

void Display::drawPixel(uint8_t x, uint8_t y, uint8_t color)
{
	if (color != 0)
	{
		LCD_Pixel(x, y, LCD_PSET);
	}
	else
	{
		LCD_Pixel(x, y, LCD_PRES);
	}
}

void Display::drawCircle(uint8_t x, uint8_t y, uint8_t r)
{
	LCD_Circle(x, y, r);
}

void Display::init()
{
	SH1106_Init();
	SH1106_Flush();

	SH1106_Orientation(LCD_ORIENT_NORMAL);
	SH1106_Contrast(127);
}
