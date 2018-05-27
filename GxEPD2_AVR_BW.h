// Display Library for SPI e-paper panels from Dalian Good Display and boards from Waveshare.
// Requires HW SPI and Adafruit_GFX. Caution: these e-papers require 3.3V supply AND data lines!
//
// based on Demo Example from Good Display: http://www.good-display.com/download_list/downloadcategoryid=34&isMode=false.html
//
// Author: Jean-Marc Zingg
//
// Version: see library.properties
//
// Library: https://github.com/ZinggJM/GxEPD2_AVR

#ifndef _GxEPD2_AVR_BW_H_
#define _GxEPD2_AVR_BW_H_

#include "GxEPD2.h"

class GxEPD2_AVR_BW : public Adafruit_GFX
{
  private:
    static const uint16_t buffer_size = 800;
  public:
    GxEPD2_AVR_BW(GxEPD2::Panel panel, int8_t cs, int8_t dc, int8_t rst, int8_t busy);
    void drawPixel(int16_t x, int16_t y, uint16_t color);
    GxEPD2::Panel panel()
    {
      return _panel;
    }
    bool hasColor()
    {
      return false;
    };
    bool hasPartialUpdate()
    {
      return true;
    };
    bool hasFastPartialUpdate()
    {
      return ((_panel < GxEPD2::GDEW027W3) || (_panel == GxEPD2::GDEW042T2));
    }
    bool mirror(bool m);
    void init();
    void fillScreen(uint16_t color); // 0x0 black, >0x0 white, to buffer
    void setFullWindow();
    void setPartialWindow(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
    void firstPage();
    bool nextPage();
    // partial update keeps power on
    void powerOff(void);
    void drawInvertedBitmap(int16_t x, int16_t y, const uint8_t bitmap[], int16_t w, int16_t h, uint16_t color);
    //  Support for Bitmaps (Sprites) to Controller Buffer and to Screen
    void clearScreen(uint8_t value = 0xFF); // init controller memory and screen (default white)
    void writeScreenBuffer(uint8_t value = 0xFF); // init controller memory (default white)
    // write to controller memory, without screen refresh; x and w should be multiple of 8
    void writeImage(const uint8_t bitmap[], int16_t x, int16_t y, int16_t w, int16_t h, bool invert = false, bool mirror_y = false, bool pgm = false);
    void writeImage(const uint8_t* black, const uint8_t* red, int16_t x, int16_t y, int16_t w, int16_t h, bool invert = false, bool mirror_y = false, bool pgm = false);
    // write to controller memory, with screen refresh; x and w should be multiple of 8
    void drawImage(const uint8_t bitmap[], int16_t x, int16_t y, int16_t w, int16_t h, bool invert = false, bool mirror_y = false, bool pgm = false);
    void drawImage(const uint8_t* black, const uint8_t* red, int16_t x, int16_t y, int16_t w, int16_t h, bool invert = false, bool mirror_y = false, bool pgm = false);
    void refresh(bool partial_update_mode = false); // screen refresh from controller memory to full screen
    void refresh(int16_t x, int16_t y, int16_t w, int16_t h); // screen refresh from controller memory, partial screen
  private:
    template <typename T> static inline void
    swap(T& a, T& b)
    {
      T t = a;
      a = b;
      b = t;
    }
    void _writeScreenBuffer(uint8_t value);
    bool _nextPageFull();
    bool _nextPagePart();
    bool _nextPageFull27();
    bool _nextPagePart27();
    bool _nextPageFull42();
    bool _nextPagePart42();
    bool _nextPageFull75();
    bool _nextPagePart75();
    void _send8pixel(uint8_t data);
    void _writeCommand(uint8_t c);
    void _writeData(uint8_t d);
    void _writeData(const uint8_t* data, uint16_t n);
    void _writeDataPGM(const uint8_t* data, uint16_t n);
    void _writeCommandDataPGM(const uint8_t* pCommandData, uint8_t datalen);
    void _setRamEntryWindow(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t em);
    void _setRamArea(uint16_t xs, uint16_t xe, uint16_t ys, uint16_t ye);
    void _setPartialRamArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
    void _setRamPointer(uint16_t x, uint16_t y);
    void _setRamEntryPartialWindow(uint8_t em);
    void _refreshWindow(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
    void _PowerOn(void);
    void _PowerOff(void);
    void _waitWhileBusy(const __FlashStringHelper* comment = 0);
    void _InitDisplay(uint8_t em);
    void _Init_Full(uint8_t em);
    void _Init_Part(uint8_t em);
    void _Update_Full(void);
    void _Update_Part(void);
    void _rotate(uint16_t& x, uint16_t& y, uint16_t& w, uint16_t& h);
    static inline uint16_t gx_uint16_min(uint16_t a, uint16_t b)
    {
      return (a < b ? a : b);
    };
    static inline uint16_t gx_uint16_max(uint16_t a, uint16_t b)
    {
      return (a > b ? a : b);
    };
  protected:
    GxEPD2::Panel _panel;
    int8_t _cs, _dc, _rst, _busy;
    uint8_t _ram_data_entry_mode, _busy_active_level;
    uint16_t _width_bytes, _pixel_bytes;
    int16_t _current_page;
    uint16_t _pages, _page_height;
    bool _initial, _power_is_on, _using_partial_mode, _second_phase, _reverse, _mirror;
    uint16_t _pw_x, _pw_y, _pw_w, _pw_h;
    uint8_t _buffer[buffer_size];
};

#endif
