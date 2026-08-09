sbit LCD_RS at RD0_bit;
sbit LCD_EN at RD1_bit;
sbit LCD_D4 at RD4_bit;
sbit LCD_D5 at RD5_bit;
sbit LCD_D6 at RD6_bit;
sbit LCD_D7 at RD7_bit;

sbit LCD_RS_Direction at TRISD0_bit;
sbit LCD_EN_Direction at TRISD1_bit;
sbit LCD_D4_Direction at TRISD4_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D7_Direction at TRISD7_bit;

char txt[17];
unsigned long dividend = 0;
unsigned long divisor  = 0;
unsigned long entry    = 0;
unsigned short stage = 0;

void light_LongToStr(unsigned long value, char *p_txt) {
    char temp[12];
    short i = 0;
    short j = 0;

    if (value == 0) {
        p_txt[0] = '0';
        p_txt[1] = '\0';
        return;
    }

    while (value > 0) {
        temp[i++] = (value % 10) + '0';
        value /= 10;
    }

    for (j = 0; j < i; j++) {
        p_txt[j] = temp[i - 1 - j];
    }
    p_txt[j] = '\0';
}

void display_integer_result(unsigned long div_num, unsigned long div_den) {
    unsigned long whole_rounded_up;


    whole_rounded_up = (div_num + div_den - 1) / div_den;


    light_LongToStr(whole_rounded_up, txt);


    Lcd_Out(2, 1, "R=");
    Lcd_Out(2, 4, txt);
}

void show_number_on_lcd(unsigned long value, unsigned short row) {
    light_LongToStr(value, txt);
    Lcd_Out(row, 1, "                ");
    Lcd_Out(row, 1, txt);
}

void debounce_wait_release() {
    Delay_ms(30);
}

unsigned short read_key() {

    if (PORTB.F0 == 0) { debounce_wait_release(); if (PORTB.F0 == 0) { while (PORTB.F0 == 0); return 0; } }
    if (PORTB.F1 == 0) { debounce_wait_release(); if (PORTB.F1 == 0) { while (PORTB.F1 == 0); return 1; } }
    if (PORTB.F2 == 0) { debounce_wait_release(); if (PORTB.F2 == 0) { while (PORTB.F2 == 0); return 2; } }
    if (PORTB.F3 == 0) { debounce_wait_release(); if (PORTB.F3 == 0) { while (PORTB.F3 == 0); return 3; } }
    if (PORTB.F4 == 0) { debounce_wait_release(); if (PORTB.F4 == 0) { while (PORTB.F4 == 0); return 4; } }
    if (PORTB.F5 == 0) { debounce_wait_release(); if (PORTB.F5 == 0) { while (PORTB.F5 == 0); return 5; } }
    if (PORTB.F6 == 0) { debounce_wait_release(); if (PORTB.F6 == 0) { while (PORTB.F6 == 0); return 6; } }
    if (PORTB.F7 == 0) { debounce_wait_release(); if (PORTB.F7 == 0) { while (PORTB.F7 == 0); return 7; } }


    if (PORTC.F0 == 0) { debounce_wait_release(); if (PORTC.F0 == 0) { while (PORTC.F0 == 0); return 8; } }
    if (PORTC.F1 == 0) { debounce_wait_release(); if (PORTC.F1 == 0) { while (PORTC.F1 == 0); return 9; } }


    if (PORTC.F2 == 0) { debounce_wait_release(); if (PORTC.F2 == 0) { while (PORTC.F2 == 0); return 10; } } // /
    if (PORTC.F3 == 0) { debounce_wait_release(); if (PORTC.F3 == 0) { while (PORTC.F3 == 0); return 11; } } // =
    if (PORTC.F4 == 0) { debounce_wait_release(); if (PORTC.F4 == 0) { while (PORTC.F4 == 0); return 12; } } // C

    return 255;
}

void append_digit(unsigned short digit) {
    if (entry <= 999999999UL) {
        entry = (entry * 10UL) + digit;
    }
    show_number_on_lcd(entry, 2);
}

void main() {
    unsigned short key;


    ADCON1 = 0x07;


    TRISB = 0xFF;
    TRISC = 0x1F;


    TRISD = 0x00;


    Lcd_Init();
    Lcd_Cmd(_LCD_CURSOR_OFF);
    Lcd_Cmd(_LCD_CLEAR);


    Lcd_Out(1, 1, "FE24A505");
    Lcd_Out(2, 1, "FE24507");
    Delay_ms(500);
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Out(1, 1, "FE24A508");
    Lcd_Out(2, 1, "FE24A506");
    Delay_ms(1000);
    
     Reset_Calc:
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Out(1, 1, "INPUT  DIVIDEND");
    Lcd_Out(2, 1, "0");

    dividend = 0;
    divisor  = 0;
    entry    = 0;
    stage    = 0;

    while(1) {
        key = read_key();
        if (key == 255) {
            continue;
        }


        if (key <= 9) {
            append_digit(key);
        }

        else if (key == 10) {
            if (stage == 0) {
                dividend = entry;
                entry = 0;
                stage = 1;
                Lcd_Cmd(_LCD_CLEAR);
                Lcd_Out(1, 1, "NOW INPUT DIVISOR");
                Lcd_Out(2, 1, "0");
            }
        }

        else if (key == 11) {
            if (stage == 1) {
                divisor = entry;
                Lcd_Cmd(_LCD_CLEAR);


                light_LongToStr(dividend, txt);
                Lcd_Out(1, 1, txt);
                Lcd_Out(1, 8, "/");
                light_LongToStr(divisor, txt);
                Lcd_Out(1, 10, txt);

                if (divisor == 0) {
                    Lcd_Out(2, 1, "CHANGE DIVISOR");
                } else {
                
                    display_integer_result(dividend, divisor);
                }


                while(1) {
                    if (read_key() == 12) {
                        goto Reset_Calc;
                    }
                }
            }
        }

        else if (key == 12) {
            goto Reset_Calc;
        }
    }
}