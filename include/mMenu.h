#ifndef MMENU_H
#define MMENU_H

#include <Arduino.h> 
#include <LcdMenu.h>
#include <interface/LiquidCrystalI2CAdapter.h>
#include <utils/commandProccesors.h>

#define LCD_ROWS 2
#define LCD_COLS 16

// Configure keyboard keys (ASCII) TODO: change this to rotary encoder tingy 
// mine working with rotary encoder. if using keyboard uncomment this. 
// #define UP 'w'
// #define DOWN 's'
// #define LEFT 'a'
// #define RIGHT 'd'
// #define ENTER ' '
// #define BACK 'b'
// #define BACKSPACE 'v'
// #define CLEAR 'c'

MAIN_MENU(
    ITEM_BASIC("Check Updates"),
    ITEM_BASIC("Start Hatch"),
    ITEM_BASIC("Cancel Hatch"),
    ITEM_BASIC("Days Left"),
    ITEM_BASIC("Reset Hatch")
);

LiquidCrystalI2CAdapter lcdAdapter(0x27, LCD_COLS, LCD_ROWS);
LcdMenu menu(lcdAdapter);

#endif