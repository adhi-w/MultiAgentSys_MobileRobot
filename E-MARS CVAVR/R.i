
#pragma used+
sfrb PINA=0;
sfrb DDRA=1;
sfrb PORTA=2;
sfrb PINB=3;
sfrb DDRB=4;
sfrb PORTB=5;
sfrb PINC=6;
sfrb DDRC=7;
sfrb PORTC=8;
sfrb PIND=9;
sfrb DDRD=0xa;
sfrb PORTD=0xb;
sfrb TIFR0=0x15;
sfrb TIFR1=0x16;
sfrb TIFR2=0x17;
sfrb PCIFR=0x1b;
sfrb EIFR=0x1c;
sfrb EIMSK=0x1d;
sfrb GPIOR0=0x1e;
sfrb EECR=0x1f;
sfrb EEDR=0x20;
sfrb EEARL=0x21;
sfrb EEARH=0x22;
sfrw EEAR=0X21;   
sfrb GTCCR=0x23;
sfrb TCCR0A=0x24;
sfrb TCCR0B=0x25;
sfrb TCNT0=0x26;
sfrb OCR0A=0x27;
sfrb OCR0B=0x28;
sfrb GPIOR1=0x2a;
sfrb GPIOR2=0x2b;
sfrb SPCR0=0x2c;
sfrb SPSR0=0x2d;
sfrb SPDR0=0x2e;
sfrb ACSR=0x30;
sfrb OCDR=0x31;
sfrb SMCR=0x33;
sfrb MCUSR=0x34;
sfrb MCUCR=0x35;
sfrb SPMCSR=0x37;
sfrb RAMPZ=0x3b;
sfrb SPL=0x3d;
sfrb SPH=0x3e;
sfrb SREG=0x3f;
#pragma used-

#asm
	#ifndef __SLEEP_DEFINED__
	#define __SLEEP_DEFINED__
	.EQU __se_bit=0x01
	.EQU __sm_mask=0x0E
	.EQU __sm_powerdown=0x04
	.EQU __sm_powersave=0x06
	.EQU __sm_standby=0x0C
	.EQU __sm_ext_standby=0x0E
	.EQU __sm_adc_noise_red=0x02
	.SET power_ctrl_reg=smcr
	#endif
#endasm

typedef char *va_list;

#pragma used+

char getchar(void);
void putchar(char c);
void puts(char *str);
void putsf(char flash *str);

char *gets(char *str,unsigned int len);

void printf(char flash *fmtstr,...);
void sprintf(char *str, char flash *fmtstr,...);
void snprintf(char *str, unsigned int size, char flash *fmtstr,...);
void vprintf (char flash * fmtstr, va_list argptr);
void vsprintf (char *str, char flash * fmtstr, va_list argptr);
void vsnprintf (char *str, unsigned int size, char flash * fmtstr, va_list argptr);
signed char scanf(char flash *fmtstr,...);
signed char sscanf(char *str, char flash *fmtstr,...);

#pragma used-

#pragma library stdio.lib

#pragma used+

void delay_us(unsigned int n);
void delay_ms(unsigned int n);

#pragma used-

#pragma used+

signed char cmax(signed char a,signed char b);
int max(int a,int b);
long lmax(long a,long b);
float fmax(float a,float b);
signed char cmin(signed char a,signed char b);
int min(int a,int b);
long lmin(long a,long b);
float fmin(float a,float b);
signed char csign(signed char x);
signed char sign(int x);
signed char lsign(long x);
signed char fsign(float x);
unsigned char isqrt(unsigned int x);
unsigned int lsqrt(unsigned long x);
float sqrt(float x);
float floor(float x);
float ceil(float x);
float fmod(float x,float y);
float modf(float x,float *ipart);
float ldexp(float x,int expon);
float frexp(float x,int *expon);
float exp(float x);
float log(float x);
float log10(float x);
float pow(float x,float y);
float sin(float x);
float cos(float x);
float tan(float x);
float sinh(float x);
float cosh(float x);
float tanh(float x);
float asin(float x);
float acos(float x);
float atan(float x);
float atan2(float y,float x);

#pragma used-
#pragma library math.lib

#asm
   .equ __lcd_port=0x02 ;PORTA
#endasm

#pragma used+

void _lcd_ready(void);
void _lcd_write_data(unsigned char data);

void lcd_write_byte(unsigned char addr, unsigned char data);

unsigned char lcd_read_byte(unsigned char addr);

void lcd_gotoxy(unsigned char x, unsigned char y);

void lcd_clear(void);
void lcd_putchar(char c);

void lcd_puts(char *str);

void lcd_putsf(char flash *str);

unsigned char lcd_init(unsigned char lcd_columns);

void lcd_control (unsigned char control);

#pragma used-
#pragma library lcd.lib

char rx_buffer0[8];

unsigned char rx_wr_index0,rx_rd_index0,rx_counter0;

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

interrupt [21] void usart_rx_isr(void)
{
char status,data;
status=(*(unsigned char *) 0xc0);
data=(*(unsigned char *) 0xc6);
if ((status & ((1<<4) | (1<<2) | (1<<3)))==0)
{  
if (data == 'R' ||data == 'G' ||data == 'r' ||data == 'g' ||data == '!' ||data == 'K' ||data == 'k' || data == '@' || data == 'o' || data == 'z' ) 
{
sData[0]=data;   
RIndex = 1;
}  

else if (data == 13)
{   
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

};
}

#pragma used+
char getchar(void)
{
char data;
while (rx_counter0==0);
data=rx_buffer0[rx_rd_index0];
if (++rx_rd_index0 == 8) rx_rd_index0=0;
#asm("cli")
--rx_counter0;
#asm("sei")
return data;
}
#pragma used-

unsigned int a,pwm1,pwm2,pwm3,pwm4,pwm5;
unsigned char psol;

interrupt [19] void timer0_ovf_isr(void)
{

a++;        

if(a==255) a=0; 
if(a<=pwm1)PORTD.5=0;   else PORTD.5=1;
if(a<=pwm2)PORTD.2=0;   else PORTD.2=1;
if(a<=pwm3)PORTB.4=0;   else PORTB.4=1;
if(a<=pwm4)PORTB.5=0;   else PORTB.5=1; 
if(a<=pwm5)PORTB.1=0;   else PORTB.1=1;    
if(a<=psol)PORTB.0=0;   else PORTB.0=1;
}

unsigned char buf[16];

void stop()
{
PORTD.6=0; PORTD.7=0; PORTD.3=0; PORTD.4=0;   PORTB.3=0; PORTB.2=0; PORTB.7=0; PORTB.6=0; 
}

void maju(unsigned char v)
{ 

pwm1=v*cos(60); PORTD.6=0; PORTD.7=1;  pwm2=v*cos(60); PORTD.3=1; PORTD.4=0;
pwm4=v*cos(45); PORTB.7=0; PORTB.6=1;  pwm3=v*cos(45); PORTB.3=1; PORTB.2=0;    
}

void mundur(unsigned char v)
{ 

pwm1=v*cos(60); PORTD.6=1; PORTD.7=0;  pwm2=v*cos(60); PORTD.3=0; PORTD.4=1;
pwm4=v*cos(45); PORTB.7=1; PORTB.6=0;  pwm3=v*cos(45); PORTB.3=0; PORTB.2=1;    
}

void kanan(unsigned char v)
{
pwm1=v*cos(30); PORTD.6=1; PORTD.7=0;  pwm2=v*cos(120); PORTD.3=1; PORTD.4=0;
pwm4=v*cos(120); PORTB.7=0; PORTB.6=1;  pwm3=v*cos(30); PORTB.3=0; PORTB.2=1;
}

void kiri(unsigned char v)
{
pwm1=v*cos(30); PORTD.6=0; PORTD.7=1;  pwm2=v*cos(120); PORTD.3=0; PORTD.4=1;
pwm4=v*cos(120); PORTB.7=1; PORTB.6=0;  pwm3=v*cos(30); PORTB.3=1; PORTB.2=0;
}

void tendang()
{
psol=255; delay_ms(20); psol=0;   
}

void CW_CCW_motor(float a, float b, float c, float d)
{
if(a<0){ PORTD.6=1; PORTD.7=0; pwm1=-a; }    else { PORTD.6=0; PORTD.7=1; pwm1=a; }  
if(b<0){ PORTD.3=1; PORTD.4=0; pwm2=-b; }    else { PORTD.3=0; PORTD.4=1; pwm2=b; }
if(c<0){ PORTB.3=1; PORTB.2=0; pwm3=-c; }    else { PORTB.3=0; PORTB.2=1; pwm3=c; }
if(d<0){ PORTB.7=1; PORTB.6=0; pwm4=-d; }    else { PORTB.7=0; PORTB.6=1; pwm4=d; }
}

void Gerak_linier(float alpha, float asudut)
{   float a, b, c, d, tsudut;

tsudut=alpha-asudut;
a=cos(((35-tsudut)/180)*3.14);            
b=cos(((145-tsudut)/180)*3.14);
c=cos(((225-tsudut)/180)*3.14);
d=cos(((315-tsudut)/180)*3.14);

Fa=Vel*a;                       
Fb=Vel*b;
Fc=Vel*c;
Fd=Vel*d;                                      
}

void Move(float alpha2, int jarak, float act_kompas)          
{
float Fang, f1,f2,f3,f4;
float dkompas, alpha3;
int radius=8; 

Gerak_linier(alpha2,act_kompas);

Fang=(Vel/radius);   

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

f1=Fa+Fang;
f2=Fb+Fang;
f3=Fc+Fang;
f4=Fd+Fang;

CW_CCW_motor(f1,f2,f3,f4);

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
{ if(s_ok<=165 && s_ok>=90) {   Gerak_linier(alpha,act_kompas);     }     
else if(s_ok>=195 && s_ok <=270) {  Gerak_linier(alpha,act_kompas);     }   
}
}
}

void main(void)
{

PORTA=0x00;
DDRA=0x00;

PORTB=0x03;
DDRB=0xFF;

PORTC=0x0F;
DDRC=0x00;

PORTD=0x00;
DDRD=0xFC;

TCCR0A=0x00;
TCCR0B=0x01;
TCNT0=0x00;
OCR0A=0x00;
OCR0B=0x00;

(*(unsigned char *) 0x80)=0x00;
(*(unsigned char *) 0x81)=0x00;
(*(unsigned char *) 0x85)=0x00;
(*(unsigned char *) 0x84)=0x00;
(*(unsigned char *) 0x87)=0x00;
(*(unsigned char *) 0x86)=0x00;
(*(unsigned char *) 0x89)=0x00;
(*(unsigned char *) 0x88)=0x00;
(*(unsigned char *) 0x8b)=0x00;
(*(unsigned char *) 0x8a)=0x00;

(*(unsigned char *) 0xb6)=0x00;
(*(unsigned char *) 0xb0)=0x00;
(*(unsigned char *) 0xb1)=0x00;
(*(unsigned char *) 0xb2)=0x00;
(*(unsigned char *) 0xb3)=0x00;
(*(unsigned char *) 0xb4)=0x00;

(*(unsigned char *) 0x69)=0x00;
EIMSK=0x00;
(*(unsigned char *) 0x68)=0x00;

(*(unsigned char *) 0x6e)=0x01;

(*(unsigned char *) 0x6f)=0x00;

(*(unsigned char *) 0x70)=0x00;

(*(unsigned char *) 0xc0)=0x00;
(*(unsigned char *) 0xc1)=0x98;
(*(unsigned char *) 0xc2)=0x06;
(*(unsigned char *) 0xc5)=0x00;
(*(unsigned char *) 0xc4)=0x47; 

ACSR=0x80;
(*(unsigned char *) 0x7b)=0x00;

lcd_init(16);

#asm("sei")

Vel = 210;

while (1)
{        

while(flag==1) stop();

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
