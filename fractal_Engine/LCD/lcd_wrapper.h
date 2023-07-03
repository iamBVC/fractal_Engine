#ifndef LCD_WRAPPER_H
#define LCD_WRAPPER_H



#include "lcd_common.h"
#include "fonts.h"


typedef struct {
	void* HandlerPtr;
	lcd_ops_t ops;
	lcd_params_t params;
	uint32_t* buffer;
} lcd_t;



namespace LCD {

	bool init(lcd_t* lcd);
	void write(lcd_t* lcd, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t* data);
	void print(lcd_t* lcd);
	void clear(lcd_t* lcd);
	void clear_buffer(lcd_t* lcd);
	void draw_pixel(lcd_t* lcd, int32_t x, int32_t y, uint32_t color);
	void fill_rect(lcd_t* lcd, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t color);
	void draw_line(lcd_t* lcd, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t color);
	void draw_rect(lcd_t* lcd, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t color);
	void draw_circle(lcd_t* lcd, int32_t x, int32_t y, uint32_t radius, uint32_t color);
	void draw_triangle(lcd_t* lcd, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, uint32_t color);
	void fill_circle(lcd_t* lcd, int32_t x, int32_t y, uint32_t radius, uint32_t color);
	void fill_triangle(lcd_t* lcd, int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, uint32_t color);
	void draw_text(lcd_t* lcd, int32_t x, int32_t y, const GFXfont font, char* text, uint32_t color);
	void draw_image(lcd_t* lcd, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t* data);


}



#endif //LCD_WRAPPER_H
