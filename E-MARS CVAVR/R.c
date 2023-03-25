/*****************************************************
This program was produced by the
CodeWizardAVR V2.03.9 Standard
Automatic Program Generator
� Copyright 1998-2008 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 4/17/2013
Author  : CarokArmy
Company : CarokCompany.Inc
Comments: 


Chip type               : ATmega644
Program type            : Application
AVR Core Clock frequency: 11.059200 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 1024
*****************************************************/

#include <mega644.h>
#include <stdio.h>
#include <delay.h>

#include <math.h>
                                                                                                      
#define en1 PORTD.5
#define cw1 PORTD.6
#define ccw1 PORTD.7


#define en2 PORTD.2
#define cw2 PORTD.3
#define ccw2 PORTD.4

#define en4 PORTB.5
#define ccw4 PORTB.6
#define cw4 PORTB.7


#define en3 PORTB.4
#define cw3 PORTB.3
#define ccw3 PORTB.2

#define en5 PORTB.1
#define sol PORTB.0

#define sw PINC.0
#define push PINC.1

// Alphanumeric LCD Module functions
#asm
   .equ __lcd_port=0x02 ;PORTA
#endasm
#include <lcd.h>

#define RXB8 1
#define TXB8 0
#define UPE 2
#define OVR 3
#define FE 4
#define UDRE 5
#define RXC 7

#define FRAMING_ERROR (1<<FE)
#define PARITY_ERROR (1<<UPE)
#define DATA_OVERRUN (1<<OVR)
#define DATA_REGISTER_EMPTY (1<<UDRE)
#define RX_COMPLETE (1<<RXC)

// USART Receiver buffer
#define RX_BUFFER_SIZE0 8
char rx_buffer0[RX_BUFFER_SIZE0];

#if RX_BUFFER_SIZE0<256
unsigned char rx_wr_index0,rx_rd_index0,rx_counter0;
#else
unsigned int rx_wr_index0,rx_rd_index0,rx_counter0;
#endif

// This flag is set on USART Receiver buffer overflow
bit rx_buffer_overflow0;


static int sr,sg, sk;
int flag=0;
static int s_rt, s_gt, s_rg, s_gr, s_rk, s_gk, s_ok;
static int m_rt, m_gt, m_rg, m_gr, m_rk, m_gk, m_ok;

int tanda_r, tanda_g;

int kuadran=0;

float Fa,Fb,Fc,Fd;  
int Vel;

float er=0,der,P,D;
static signed int laster;
signed int m;
int Kp=1;
int Kd=46;

unsigned char buffer[128];

char sData[8];
char RIndex;
  
unsigned int KonversiDataSerial()
{
    unsigned int Hasil=0;
    Hasil = (sData[1]-48) *100;
    Hasil += (sData[2]-48) *10;
    Hasil += sData[3]-48;
    
    return Hasil;    
}

unsigned int KonversiDataSerial2()
{
    unsigned int Hasil=0;
    Hasil = (sData[5]-48) *100;
    Hasil += (sData[6]-48) *10;
    Hasil += sData[7]-48;
     
    return Hasil;    
}

// USART Receiver interrupt service routine
interrupt [USART_RXC] void usart_rx_isr(void)
{
char status,data;
status=UCSR0A;
data=UDR0;
if ((status & (FRAMING_ERROR | PARITY_ERROR | DATA_OVERRUN))==0)
   {  
   if (data == 'R' ||data == 'G' ||data == 'r' ||data == 'g' ||data == '!' ||data == 'K' ||data == 'k' || data == '@' || data == 'o' || data == 'z' ) 
    {
        sData[0]=data;   
        RIndex = 1;
    }  
    
    else if (data == 13)
    {   //cek isi dari header
        switch (sData[0])
        {  
           case 'R':  s_rt = KonversiDataSerial();      
                      m_rt = KonversiDataSerial2();  flag=0; break;
           case 'G':  s_gt = KonversiDataSerial();
                      m_gt = KonversiDataSerial2();  flag=0; break;
           case 'r':  s_rg = KonversiDataSerial(); 
                      m_rg = KonversiDataSerial2();  flag=0; break;
           case 'g':  s_gr = KonversiDataSerial(); 
                      m_gr = KonversiDataSerial2();  flag=0; break;
           case '!':  sr = KonversiDataSerial(); 
                      sg = KonversiDataSerial2();   flag=0; break; 
           case 'K':  s_rk = KonversiDataSerial(); 
                      m_rk = KonversiDataSerial2();   flag=0; break; 
           case 'k':  s_gk = KonversiDataSerial(); 
                      m_gk = KonversiDataSerial2();   flag=0; break; 
           case '@':  s_ok = KonversiDataSerial(); 
                      m_ok = KonversiDataSerial2();   flag=0; break; 
           case 'z':  tanda_r = KonversiDataSerial(); 
                      tanda_g = KonversiDataSerial2();   flag=0; break; 
           case 'o': flag=1;  break;
        }
    } 
    else
    {
        sData[RIndex]=data;
        if(RIndex>8) RIndex=0;
        else RIndex++;
    }                          
//   rx_buffer0[rx_wr_index0]=data;
//   if (++rx_wr_index0 == RX_BUFFER_SIZE0) rx_wr_index0=0;
//   if (++rx_counter0 == RX_BUFFER_SIZE0)
//      {
//      rx_counter0=0;
//      rx_buffer_overflow0=1;
//      };
   };
}

#ifndef _DEBUG_TERMINAL_IO_
// Get a character from the USART Receiver buffer
#define _ALTERNATE_GETCHAR_
#pragma used+
char getchar(void)
{
char data;
while (rx_counter0==0);
data=rx_buffer0[rx_rd_index0];
if (++rx_rd_index0 == RX_BUFFER_SIZE0) rx_rd_index0=0;
#asm("cli")
--rx_counter0;
#asm("sei")
return data;
}
#pragma used-
#endif

// Standard Input/Output functions
unsigned int a,pwm1,pwm2,pwm3,pwm4,pwm5;
unsigned char psol;

// Timer 0 overflow interrupt service routine
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
// Place your code here
   a++;        
    
    if(a==255) a=0; 
    if(a<=pwm1)en1=0;   else en1=1;
    if(a<=pwm2)en2=0;   else en2=1;
    if(a<=pwm3)en3=0;   else en3=1;
    if(a<=pwm4)en4=0;   else en4=1; 
    if(a<=pwm5)en5=0;   else en5=1;    
    if(a<=psol)sol=0;   else sol=1;
}

// Declare your global variables here
unsigned char buf[16];

void stop()
{
    cw1=0; ccw1=0; cw2=0; ccw2=0;   cw3=0; ccw3=0; cw4=0; ccw4=0; 
}

void maju(unsigned char v)
{ 

   pwm1=v*cos(60); cw1=0; ccw1=1;  pwm2=v*cos(60); cw2=1; ccw2=0;
   pwm4=v*cos(45); cw4=0; ccw4=1;  pwm3=v*cos(45); cw3=1; ccw3=0;    
}

void mundur(unsigned char v)
{ 

   pwm1=v*cos(60); cw1=1; ccw1=0;  pwm2=v*cos(60); cw2=0; ccw2=1;
   pwm4=v*cos(45); cw4=1; ccw4=0;  pwm3=v*cos(45); cw3=0; ccw3=1;    
}

void kanan(unsigned char v)
{
   pwm1=v*cos(30); cw1=1; ccw1=0;  pwm2=v*cos(120); cw2=1; ccw2=0;
   pwm4=v*cos(120); cw4=0; ccw4=1;  pwm3=v*cos(30); cw3=0; ccw3=1;
}

void kiri(unsigned char v)
{
   pwm1=v*cos(30); cw1=0; ccw1=1;  pwm2=v*cos(120); cw2=0; ccw2=1;
   pwm4=v*cos(120); cw4=1; ccw4=0;  pwm3=v*cos(30); cw3=1; ccw3=0;
}

void tendang()
{
   psol=255; delay_ms(20); psol=0;   
}


//------------Kinematik------------

void CW_CCW_motor(float a, float b, float c, float d)
{
    if(a<0){ cw1=1; ccw1=0; pwm1=-a; }    else { cw1=0; ccw1=1; pwm1=a; }  
    if(b<0){ cw2=1; ccw2=0; pwm2=-b; }    else { cw2=0; ccw2=1; pwm2=b; }
    if(c<0){ cw3=1; ccw3=0; pwm3=-c; }    else { cw3=0; ccw3=1; pwm3=c; }
    if(d<0){ cw4=1; ccw4=0; pwm4=-d; }    else { cw4=0; ccw4=1; pwm4=d; }
}


void Gerak_linier(float alpha, float asudut)
{   float a, b, c, d, tsudut;
   
    tsudut=alpha-asudut;
     a=cos(((35-tsudut)/180)*3.14);            //deg2rad
     b=cos(((145-tsudut)/180)*3.14);
     c=cos(((225-tsudut)/180)*3.14);
     d=cos(((315-tsudut)/180)*3.14);
     
    Fa=Vel*a;                       
    Fb=Vel*b;
    Fc=Vel*c;
    Fd=Vel*d;                                      
}

void Move(float alpha2, int jarak, float act_kompas)          //Linier + Angular
{
    float Fang, f1,f2,f3,f4;
    float dkompas, alpha3;
    int radius=8; 

   // act_kompas=heading;
           
    Gerak_linier(alpha2,act_kompas);
    
    Fang=(Vel/radius);   //Gerak Angular  
    
    if(alpha2>=0 && alpha2<=180)
    {
        if(act_kompas >= (180+alpha2) || act_kompas <= alpha2)
        {                                                                
            if(act_kompas<=alpha2)
            {
                dkompas = act_kompas;
            }
            else
            {
               dkompas = -(360-act_kompas);
            }     
             Fang = Fang;  
        }
        else 
        {                        
            dkompas=act_kompas;  
            Fang= -Fang; 
        }              
    }  
    
    else  if(alpha2>180 && alpha2<=360)       
    {  
        if(alpha2 >= act_kompas && act_kompas >= (alpha2-180))
        {  
            dkompas = act_kompas;      Fang=Fang;           
        }
        else if(act_kompas>=alpha2)
        {
            dkompas = act_kompas;      Fang=-Fang;
        }
        else if(act_kompas<(alpha2-180))
        {
            dkompas = (360+act_kompas);    Fang=-Fang;
        }                                                
    }
            
    
      er=alpha2-dkompas;       
        P=Kp*er;
     der=er-laster;
         D=Kd*der;     
     laster=er;
         m=P+D;       
        
        if(er>=-8 && er<=8) Fang=0;
        else Fang=Fang;
        
      //  if(er>=-3 && er<=3)  maju(200);
      //  else 
     //   {
          f1=Fa+Fang;//+m;
          f2=Fb+Fang;//+m;
          f3=Fc+Fang;//+m;
          f4=Fd+Fang;//+m;
     //   }     
           
 
     CW_CCW_motor(f1,f2,f3,f4);
         
//     lcd_gotoxy(0,0);                                        
//     sprintf(buffer," %.0f  %.0f  %.0f",alpha2,Fa,Fb);
//     lcd_puts(buffer); 
//     lcd_gotoxy(0,1);
//      sprintf(buffer," %.0f  %.0f  %.0f ",act_kompas,Fc,Fd);
//     lcd_puts(buffer);    
//     delay_ms(100);
       
}

void ketarget(float sudt, int jarak, float shead)
{
    if(flag==1) stop();       
    else   Move(sudt, jarak, shead);
}

void kegawang(float alpha, int k_jrak, float act_kompas)
{ 
    if(flag==1) stop();
    else 
    {
        if(m_ok<=k_jrak)
        { if(s_ok<=165 && s_ok>=90) {   Gerak_linier(alpha,act_kompas);     }     //kiri(100); delay_ms(40); 
          else if(s_ok>=195 && s_ok <=270) {  Gerak_linier(alpha,act_kompas);     }   //kanan(100); delay_ms(40); 
        }
    }
}
  
void main(void)
{
// Declare your local variables here

// Input/Output Ports initialization
// Port A initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTA=0x00;
DDRA=0x00;

// Port B initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTB=0x03;
DDRB=0xFF;

// Port C initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTC=0x0F;
DDRC=0x00;

// Port D initialization
// Func7=In Func6=In Func5=In Func4=In Func3=In Func2=In Func1=In Func0=In 
// State7=T State6=T State5=T State4=T State3=T State2=T State1=T State0=T 
PORTD=0x00;
DDRD=0xFC;

// Timer/Counter 0 initialization
// Clock source: System Clock
// Clock value: 11059.200 kHz
// Mode: Normal top=FFh
// OC0A output: Disconnected
// OC0B output: Disconnected
TCCR0A=0x00;
TCCR0B=0x01;
TCNT0=0x00;
OCR0A=0x00;
OCR0B=0x00;

// Timer/Counter 1 initialization
// Clock source: System Clock
// Clock value: Timer 1 Stopped
// Mode: Normal top=FFFFh
// OC1A output: Discon.
// OC1B output: Discon.
// Noise Canceler: Off
// Input Capture on Falling Edge
// Timer 1 Overflow Interrupt: Off
// Input Capture Interrupt: Off
// Compare A Match Interrupt: Off
// Compare B Match Interrupt: Off
TCCR1A=0x00;
TCCR1B=0x00;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

// Timer/Counter 2 initialization
// Clock source: System Clock
// Clock value: Timer 2 Stopped
// Mode: Normal top=FFh
// OC2A output: Disconnected
// OC2B output: Disconnected
ASSR=0x00;
TCCR2A=0x00;
TCCR2B=0x00;
TCNT2=0x00;
OCR2A=0x00;
OCR2B=0x00;

// External Interrupt(s) initialization
// INT0: Off
// INT1: Off
// INT2: Off
// Interrupt on any change on pins PCINT0-7: Off
// Interrupt on any change on pins PCINT8-15: Off
// Interrupt on any change on pins PCINT16-23: Off
// Interrupt on any change on pins PCINT24-31: Off
EICRA=0x00;
EIMSK=0x00;
PCICR=0x00;

// Timer/Counter 0 Interrupt(s) initialization
TIMSK0=0x01;
// Timer/Counter 1 Interrupt(s) initialization
TIMSK1=0x00;
// Timer/Counter 2 Interrupt(s) initialization
TIMSK2=0x00;

// USART initialization
// Communication Parameters: 8 Data, 1 Stop, No Parity
// USART Receiver: On
// USART Transmitter: On
// USART0 Mode: Asynchronous
// USART Baud Rate: 19200
UCSR0A=0x00;
UCSR0B=0x98;
UCSR0C=0x06;
UBRR0H=0x00;
UBRR0L=0x47; //0x23;

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
ADCSRB=0x00;

// LCD module initialization
lcd_init(16);


// Global enable interrupts
#asm("sei")
    
Vel = 210;
//Vel = 240;

while (1)
      {        
     // Place your code here  
            
     while(flag==1) stop();
//    //Untuk RED marker----------//
     
//       if(tanda_r == 1) mundur(100);
//       else if(m_rt <= m_gt)    
//        { 
//           if(m_rt >= 30) ketarget(s_rt, m_rt,sr);
//           else ketarget(s_rk, m_rk, sr);
//        }
//        else 
//        {
//             if(m_rg<120) stop(); 
//             else ketarget(s_rg, m_rg, sr);
//        }   
            
     
    //Untuk GREEN marker----------//  

       if(tanda_g == 1) mundur(100);
       else if(m_gt <= m_rt)    
       { 
           if(m_gt >= 30) ketarget(s_gt, m_gt,sg);
           else ketarget(s_gk, m_gk, sg);
       }
       else 
       {
            if(m_gr<120) stop(); 
            else ketarget(s_gr, m_gr, sg);
       }
  
  
      };
}
