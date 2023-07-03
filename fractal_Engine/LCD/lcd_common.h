#ifndef LCD_COMMON_H
#define LCD_COMMON_H

#include <stdint.h>

#define	BLACK	0x000000
#define	BLUE	0x0000FF
#define	RED		0xFF0000
#define	GREEN	0x00FF00
#define CYAN	0x00FFFF
#define MAGENTA	0xFF00FF
#define YELLOW	0xFFFF00
#define WHITE	0xFFFFFF
#define GRAY	0x7F7F7F

typedef struct {
	void (*RESET_fn)(void*);
	void (*CLEAR_fn)(void*);
	void (*PRINT_fn)(void*);
	void (*WRITE_fn)(void*, int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t* data);
} lcd_ops_t;



typedef struct {
	int32_t height;
	int32_t width;
} lcd_params_t;



#endif //LCD_COMMON_H
