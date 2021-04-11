# labe2-robot-deti

Compilar e compilar e enviar, compilar e enviar com pterm

make SOURCES=base.c

make SOURCES=exemplo.c dload

make SOURCES=exemplo.c run

Check usb serial port when connected
- ls -l /dev/ttyUSB*

Add permissions to usb serial port access (require relogin after)
- sudo adduser username dialout

Check permissions to usb serial port access
- cat /etc/group | grep username


Funcões labe

void printStr(string)

void printInt10(val)

void delay_ms(unsigned int ms)

void delay_us(unsigned int us)

void led(ledID, ledState)

unsigned int analog(analog_chan_t channel)

unsigned int battery (void) // [0, 100] 100 = 10V

void setSpeed ( int velL, int velR )  // [-100, 100]

Os pinos tem de ser pré configurados para funcionar como entrada ou saida
quando se liga os pinos estão todos configurados como entradas

Configura para saida e escreve no pino

Digi02_Dir = OUT;
Digi02 = 1;

Configura para entra e le o pino

Digi02_Dir = IN;
if(Digi02==1){
  funcao();
}

LED1, LED2, LED3, LED4

START, STOP

Digi01, Digi02, Digi03, ...
Digi01_Dir, Digi02_Dir, Digi03_Dir, ...




system calls DETPIC32
- char inkey()
- char getChar()
- void putChar(char)
- unsigned int readInt(unsigned int base)
- int readInt10()
- void printInt(unsigned int val, unsigned int base)
- void printInt10(int val)
- void printStr(char *str)
- void readStr(char *buffer, unsigned int nc)
- void exit(int)
- unsigned int readCoreTimer()
- void resetCoreTimer()



