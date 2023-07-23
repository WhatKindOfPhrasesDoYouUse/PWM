#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h> 
bool i=true;
void port_set () 
{
  DDRD |= (1<<PORTD6);
  DDRD |= (1<<PORTD5);
}

void PWM_set () 
{
  TCCR0A = 0; 
  TCCR0B = 0; 
  TCCR0A |= (1 << COM0B1) | (1 << COM0B0) | (1 << COM0A1) | (0 << COM0A0);
  TCCR0A |= (0 << WGM01)| (1 << WGM00); 
  TCCR0B |= (0 << WGM02); 
  TCCR0B |= (0 << CS02) | (0 << CS01)| (1 << CS00); 
  OCR0A=5;
  OCR0B=50;

  TCCR1A=0;
  TCCR1B |= (1<<CS12) | (0<<CS11) | (1<<CS10);
  TCCR1B|=(1<<WGM12); // Устанавливаем режим СТС с претделителем 1024.
  OCR1A=200; // Устанавливаем значение для сброса по совпадению.
  TIMSK1|=(1<<OCIE0A); // Разрешаем прерывание по совпадению
  sei();
}
ISR (TIMER1_COMPA_vect) // Прерывание по совпадению.
{
  if(OCR0A==49) i=false;
  if(OCR0A==1) i=true;
  if (i=true){
     OCR0B++;
     OCR0A++; 
  }
  if (i=false){
     OCR0B--;
     OCR0A--; 
  }
}
int main()
{
  port_set(); // Вызов функции конфигурации порта.
  PWM_set ();
  while(1){
    
  }
}
