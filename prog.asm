ORG 0000H

JMP MAIN

INIT_TIMER: MOV TMOD,#01H
            CLR TF0
            CLR TR0

DELAY:      MOV TL0,#0F5H
            MOV TH0,#0FFH
            SETB TR0
DELAY_LOOP: JNB TF0,DELAY_LOOP
            CLR TR0
            CLR TF0
            RET

TRIG_SENS:  SETB P2.7
            ACALL DELAY
            CLR P2.7

MAIN:       MOV A,#55H
            ADD A,#21H
            MOV B,A

END
