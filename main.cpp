#include "stdint.h"
#include "inc/lm4f120h5qr.h"
#include "time.h"
#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "string.h"


void Lcd_Komut_Gonder(unsigned char c) {
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, (c & 0xf0) );
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 0x00);
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0x02);
        SysCtlDelay(50000);
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0x00);
        SysCtlDelay(50000);
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, (c & 0x0f) << 4 );
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 0x00);
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0x00);
        SysCtlDelay(50000);

}
void Lcd_Ekrani_Sil(void){
        Lcd_Komut_Gonder(0x01);
        SysCtlDelay(10);
}

void Lcd_Baslangic_Ayar() {
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
        GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, 0xFF);
        SysCtlDelay(50000);
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0,  0x00 );
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7,  0x30 );
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0x00);
        SysCtlDelay(50000);
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7,  0x30 );
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0x00);
        SysCtlDelay(50000);
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7,  0x30 );
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0x00);
        SysCtlDelay(50000);
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7,  0x20 );
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0x00);
        SysCtlDelay(50000);
        Lcd_Komut_Gonder(0x28);
        Lcd_Komut_Gonder(0xC0);
        Lcd_Komut_Gonder(0x06);
        Lcd_Komut_Gonder(0x80);
        Lcd_Komut_Gonder(0x28);
        Lcd_Komut_Gonder(0x0f);
        Lcd_Ekrani_Sil();
}


void Lcd_Harf_Yazdir(unsigned char d) {
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, (d & 0xf0) );
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 0x01);
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0x00);
        SysCtlDelay(50000);
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, (d & 0x0f) << 4 );
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 0x01);
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0x02);
        SysCtlDelay(10);
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0x00);

        SysCtlDelay(50000);

}
void Lcd_Konuma_Git(char x, char y){
	switch(x){
		case 1:
			Lcd_Komut_Gonder(0x80+((y-1)%16));
			break;
		default:
			Lcd_Komut_Gonder(0xC0+((y-1)%16));
			break;
	}
}



void Lcd_Kelime_Yerlestir( char* s){
	for(;*s;){
		Lcd_Harf_Yazdir(*s++);
	}
}




void init_port_B() {
     volatile unsigned long delay;
     SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB;
     delay = SYSCTL_RCGC2_R;
     GPIO_PORTB_DIR_R |= 0xFF; // 0xff == 0b11111111, hepsini cikis olarak ayarla
     GPIO_PORTB_AFSEL_R &= ~0xFF; // alternatif fonksiyo kapali
     GPIO_PORTB_DEN_R |= 0xFF; // hepsi aktif
 }

void init_port_D() {
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOD; // Port D’yi aktiflestir
	delay = SYSCTL_RCGC2_R;  	// zaman gecirmek icin
	GPIO_PORTD_DIR_R |= 0x0F;	// PD 3,2,1,0 pinlerini cikis yap
	GPIO_PORTD_AFSEL_R &= ~0x0F; // PD 3,2,1,0 pinlerini alternatif fonksinunu 0 yap
	GPIO_PORTD_DEN_R |= 0x0F;	// PD 3,2,1,0 pinlerini aktiflestir
}
void init_port_A() {
	volatile unsigned long delay;
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA; // Port D’yi aktiflestir
	delay = SYSCTL_RCGC2_R;  	// zaman gecirmek icin
	GPIO_PORTA_DIR_R |= 0x0F;	// PD 3,2,1,0 pinlerini cikis yap
	GPIO_PORTA_AFSEL_R &= ~0x0F; // PD 3,2,1,0 pinlerini alternatif fonksinunu 0 yap
	GPIO_PORTA_DEN_R |= 0x0F;	// PD 3,2,1,0 pinlerini aktiflestir
}
#define BIT_SET(PORT, PIN) do { \
	PORT |= 1<<PIN; \
} while (0)

#define BIT_RESET(PORT, PIN) do { \
	PORT &= ~(1<<PIN); \
} while (0)

#define PORTD (GPIO_PORTD_DATA_R)
#define PORTB (GPIO_PORTB_DATA_R)
#define PORTA (GPIO_PORTA_DATA_R)

void Bekle(int saniye){
	volatile unsigned long delay;
	for (delay = 0; delay < saniye*1500000; delay++)
		/* bos dongu ile bekle */;
}

#define LedYak(PORT, PIN) do { \
	BIT_RESET(PORTD, 2);\
	BIT_RESET(PORTD, 3);\
	BIT_RESET(PORTA, 3);\
	BIT_RESET(PORTB, 3);\
	BIT_SET(PORT, PIN); \
} while (0)

int main(void) {
	init_port_B();
	init_port_D();
	init_port_A();
	SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ| SYSCTL_OSC_MAIN);

	Lcd_Baslangic_Ayar();
	volatile unsigned long delay; // compiler optimizasyonunu engellemek icin volatile kullandik
	volatile int rastSayi;
	volatile int yedekSayi;
	rastSayi=rand()%4;
	yedekSayi=rastSayi;

	while (1) {
		while(yedekSayi==rastSayi){
			rastSayi=rand()%4;
		}
		yedekSayi=rastSayi;
		//rastSayi=rand()%4;
		if(rastSayi%10==0){
			LedYak(PORTD,2);
			Lcd_Ekrani_Sil();
			Lcd_Konuma_Git(1,1);
			Lcd_Kelime_Yerlestir("KOCAELI UNI");
			Bekle(2);
			Lcd_Konuma_Git(2,1);
			Lcd_Kelime_Yerlestir("MURAT KARAKOC");
			Bekle(1);
		}
		if(rastSayi%10==1){
			LedYak(PORTD,3);
			Lcd_Ekrani_Sil();
			Lcd_Konuma_Git(2,1);
			Lcd_Kelime_Yerlestir("MURAT KARAKOC");
			Bekle(2);
			Lcd_Konuma_Git(1,1);
			Lcd_Kelime_Yerlestir("KOCAELI UNI");
			Bekle(1);
		}
		if(rastSayi%10==2){
			//GPIO_PORTD_DATA_R|=0b01000000;
			char dizi_isim[]="MURAT KARAKOC";
			char dizi_uni[]="KOCAELI UNI";
			int i;
			int uzunluk_isim=strlen(dizi_isim);
			int uzunluk_uni=strlen(dizi_uni);
			int sayac_isim=uzunluk_isim;
			int sayac_uni=uzunluk_uni;

			LedYak(PORTA,3);

			for(i=0;i<uzunluk_uni+1;i++){
				Lcd_Ekrani_Sil();
				Lcd_Konuma_Git(1,1);
				/*
				Lcd_Kelime_Yerlestir("MURAT KARAKOC");
				Lcd_Konuma_Git(2,1);*/
				Lcd_Kelime_Yerlestir(dizi_uni+sayac_uni);
				for(delay = 0; delay < 1000000; delay++){

				}
				if(sayac_uni!=0){
					sayac_uni--;
				}
			}
			Bekle(2);

			for(i=0;i<uzunluk_isim+1;i++){
				Lcd_Ekrani_Sil();
				Lcd_Konuma_Git(1,1);
				Lcd_Kelime_Yerlestir("KOCAELI UNI");
				Lcd_Konuma_Git(2,1);
				Lcd_Kelime_Yerlestir(dizi_isim+sayac_isim);
				for(delay = 0; delay < 1000000; delay++){

				}
				if(sayac_isim!=0){
					sayac_isim--;
				}
			}
			Bekle(1);
		}
		if(rastSayi%10==3) {
			LedYak(PORTB,3);
			Lcd_Ekrani_Sil();
			int i;
			for(i=0;i<16;i++){
				Lcd_Ekrani_Sil();
				Lcd_Konuma_Git(1,16-i);
				Lcd_Kelime_Yerlestir("KOCAELI UNI");
				for(delay = 0; delay < 1000000; delay++){

				}
			}
			Bekle(2);
			for(i=0;i<16;i++){
				Lcd_Ekrani_Sil();
				Lcd_Konuma_Git(1,1);
				Lcd_Kelime_Yerlestir("KOCAELI UNI");
				Lcd_Konuma_Git(2,16-i);
				Lcd_Kelime_Yerlestir("MURAT KARAKOC");
				for(delay = 0; delay < 1000000; delay++){

				}
			}
			Bekle(1);
		}
	}
}







