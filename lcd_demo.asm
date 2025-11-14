ORG 0000H

SCL BIT P3.7
SDA BIT P3.6

I2C_START:  CLR SCL   ; SCL = 0;
            SETB SDA  ; SDA = 1;
            NOP
            SETB SCL  ; SCL = 1;
            NOP
            CLR SDA   ; SDA = 0;
            NOP
            CLR SCL   ; SCL = 0;

I2C_STOP:   CLR SCL   ; SCL = 0;
            NOP
            CLR SDA   ; SDA = 0;
            NOP
            SETB SCL  ; SCL = 1;
            NOP
            SETB SDA  ; SDA = 1;

I2C_WRITE:  MOV A, #0
            MOV R0, #8

; bit I2C_Write(unsigned char datax)
; {
;   unsigned char i;
;   for (i = 0; i < 8; i++)
;   {
;     SDA = datax & 0x80;
;     _nop_ ();
;     SCL = 1;
;     _nop_ ();
;     SCL = 0;
;     datax = datax << 1;
;   }
WRITE_LOOP: DJNZ R0, WRITE_LOOP

END
