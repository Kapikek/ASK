#include <iostream>

using namespace std;

void jakisPrzyklad() {
    //tu chodzi o reprezentacje bitowa liczby 
    //mialo to przypomniec zapisywanie ujemnych w binarce, i guess
    char z;
    unsigned char a;
    _asm {
        MOV AL, 254
        MOV a, AL
        MOV z, AL

    }

    printf_s("%d\n", a);
    printf_s("%d\n", z);
}

void juzNiePamietamCoToRatunku() {
    short z;
    char y;

    _asm {

        XOR AX, AX //zerowanie bitów
        MOV AL, -2
        CBW //byte to word
        MOV z, AX

    }

    printf_s("%d\n", z);
}

void warunekIfZAlternatywa() {

    //warunek if, ale bardziej zlozony
    char a = 49;
    char b = 48;
    char y = 5;

    if ((a == 49) || (b == 49)) {
        y = 8;
    }
    else y = 5;

    printf_s("%d\n", a);
    printf_s("%d\n", b);
    printf_s("%d\n", y);

    _asm {

        MOV a, 48
        MOV b, 49
        MOV y, 5

        CMP a, 49
        JZ prawda
        CMP b, 49
        JNZ falsz

        prawda : MOV y, 8
        falsz :

    }

    printf_s("%d\n", a);
    printf_s("%d\n", b);
    printf_s("%d\n", y);
}

uint8_t liczenieZerowychBitow(uint8_t a) {

    uint8_t y;
    _asm {
        XOR DH, DH
        //zliczajacy liczbe zer w bajcie
        MOV DL, a
        MOV CL, 8
        ety1:
        SHR DL, 1
            JC ety2
            INC DH

            ety2 :
        DEC CL
            JNZ ety1
            MOV y, DH

    }
    printf_s("%d\n", a);
    printf_s("%d\n", y);

    return y;
}
uint8_t liczenieZerowychBitowProstackie(uint8_t a) {
    //liczenie zerowych bitow

    uint8_t y;
    _asm {

        XOR BL, BL
        MOV DL, a
        XOR DL, 255
        MOV DH, DL
        AND DH, 1
        ADD BL, DH


        SHR DL, 1
        MOV DH, DL
        AND DH, 1
        ADD BL, DH

        //jeszcze 6 razy
        //SHR DL, 1
        //MOV DH, DL
        //AND DH, 1
        //ADD BL, 1
        SHR DL, 1
        MOV DH, DL
        AND DH, 1
        ADD BL, DH

        SHR DL, 1
        MOV DH, DL
        AND DH, 1
        ADD BL, DH

        SHR DL, 1
        MOV DH, DL
        AND DH, 1
        ADD BL, DH

        SHR DL, 1
        MOV DH, DL
        AND DH, 1
        ADD BL, DH

        SHR DL, 1
        MOV DH, DL
        AND DH, 1
        ADD BL, DH

        SHR DL, 1
        MOV DH, DL
        AND DH, 1
        ADD BL, DH

        MOV y, BL
    }


    printf_s("%d\n", a);
    printf_s("%d\n", y);
    return y;
}

void suma2Argumentowa() {

    //y = a+b

    unsigned char a = 34, b = 17, y;

    y = a + b;
    printf_s("c->dec : % d\t hex : % #x \n", y, y);

    _asm {
        xor eax, eax
        mov al, a
        add al, b
        mov y, al
    }
    printf_s("assembler->dec : % d\t hex : % #x \n", y, y);
}
void suma3Argumentowa() {
    //y = a + b + c
    unsigned char a = 34, b = 17, c = 10, y;

    _asm {
        xor eax, eax
        mov al, a
        add al, b
        add al, c
        mov y, al

    }
    printf_s("y = dec:%d    hex:%#x", y, y);
}

//27.10.2023?

void mnozenie() {

    // y = a * 20
    // a -8bit
    // y -16bit

    uint8_t a = 10;
    uint16_t y2 = a * 20;
    printf_s("\nZAD2\n c-> y = dec:%d    hex:%#x", y2, y2);


    _asm {
        xor eax, eax
        mov al, a
        shl ax, 4
        mov y2, ax
        xor eax, eax
        mov al, a
        shl ax, 2
        add y2, ax
    }
    printf_s("\nZAD2\n asm-> y = dec:%d    hex:%#x", y2, y2);
}
void warunekIf() {
    //prosty if
    unsigned char a = 5, y;

    if (a == 5)y = 0; else y = 1;
    printf_s("c->%d\n\n", y);

    _asm {
        mov al, a
        cmp al, 5
        jnz et2

        mov y, 0
        jmp koniec

        et2 :
        mov y, 1
            koniec :


    }
    printf_s("asm->%d\n\n", y);
}


//10.11.2023
void operacjeNaBitach025(uint8_t a) {
    //0,2,5    
    //11011010 zerowanie
    uint8_t a1 = a & 0xDA;
    //00100101 ustawianie
    uint8_t a2 = a | 0x25;
    //00100101 negacja
    uint8_t a3 = a ^ 0x25;

    printf_s("C:\nzerowanie %d\nustawianie %d\nnegacja %d\n", a1, a2, a3);

    _asm {
        MOV al, a
        MOV bl, a
        MOV cl, a
        AND al, 0xDA
        OR bl, 0x25
        XOR cl, 0x25
        MOV a1, al
        MOV a2, bl
        MOV a3, cl
    }
    printf_s("ASM:\nzerowanie %d\nustawianie %d\nnegacja %d\n", a1, a2, a3);
}
uint8_t wstawienieBitu(uint8_t a, uint8_t b) {
    //b7 b6 b5 b4 b3 a1 b1 b0 
    uint8_t c = ((a & 0x02) * 2) | (b & 0xFB);
    printf_s("C: %d\n", c);

    _asm {
        MOV al, a
        MOV bl, b
        AND bl, 0xFB
        AND al, 0x02
        SHL al, 1
        OR al, bl
        MOV c, al
    }
    printf_s("ASM: %d\n", c);
}
uint8_t zamianaBitowParzystychINieparzystych(uint8_t a) {
    //76543210
    //67452301 zamiana bitow
    uint8_t parz = (a & 0xAA) >> 1;
    uint8_t nieparz = (a & 0x55) << 1;
    uint8_t wynik = parz | nieparz;
    printf_s("C: %d\n", wynik);

    _asm {
        MOV al, a
        MOV bl, a
        AND al, 0xAA
        AND bl, 0x55
        SHR al, 1
        SHL bl, 1
        OR al, bl
        MOV wynik, al
    }
    printf_s("ASM: %d\n", wynik);
    return wynik;
}

int main()
{

    //8bit char AL
    //16bit short AX
    //32bit int EAX
    
    //jakisPrzyklad();
    
    //juzNiePamietamCoToRatunku();

    //warunekIfZAlternatywa();

    /*uint8_t a = 0xAA;
    uint8_t wynik = liczenieZerowychBitow(a);*/

    /*uint8_t a = 0xAA;
    uint8_t wynik = liczenieZerowychBitowProstackie(a);*/
    
    //suma2Argumentowa();
    //suma3Argumentowa();


//27.10.2023


    //void mnozenie();
    //void warunekIf();


//10.11.2023
    
    
    /*uint8_t  a = 0xFF;
    operacjeNaBitach025(a);*/

    /*uint8_t a = 0x00;
    uint8_t b = 0xFF;
    uint8_t c = wstawienieBitu(a, b);*/


    /*uint8_t a = 0xAA;
    a = zamianaBitowParzystychINieparzystych(a);*/


}
