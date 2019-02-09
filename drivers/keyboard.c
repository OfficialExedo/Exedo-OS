#include "keyboard.h"
#include "../cpu/ports.h"
#include "../cpu/isr.h"
#include "screen.h"
#include "../libc/string.h"
#include "../libc/function.h"

#define BACKSPACE 0x0E
#define ENTER 0x1C

#define SC_MAX 57

const char* sc_name [] = 
{
    "ERROR", "Esc", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "Backspace",
    "Tab", "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "L Ctrl",
    "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", "L Shift", "\\", "Z", "X",
    "C", "V", "B", "N", "M", ",", ".", "/", "R Shift", "Keypad *", "L Alt", "Spacebar"
};

const char sc_ascii[] = 
{
    '?', '?', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '?',
    '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '?', '?',
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X',
    'C', 'V', 'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '
};

static void keyboard_callback(registers_t regs)
{
    // The PIC leaves us the scan code in 0x60
    u8 scancode = port_byte_in(0x60);
    
    if (scancode >SC_MAX) return;
    char letter = sc_ascii[(int) scancode];
    char str[2] = {letter, '\0'};
    kprint(str);

    UNUSED(regs);
}

void init_keyboard(void)
{
    register_interrupt_handler(IRQ1, keyboard_callback);
}