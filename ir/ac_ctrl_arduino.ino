#include <SPI.h>
#include "RF24.h"

bool radioNumber = 0;
/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
/* CE, CSN/CE0 */
RF24 radio(10, 9);
char mask = 0b10101010;
uint64_t dest_addr = 0x65646f4e32;

#define TIMER_ENABLE_PWM    (TCCR2A |= _BV(COM2B1))
#define TIMER_DISABLE_PWM   (TCCR2A &= ~(_BV(COM2B1)))
void setup() {
  Serial.begin(115200);
  radio.begin();
  radio.setRetries(15, 15);
  radio.setChannel(120);

  radio.openReadingPipe(1, dest_addr);
  radio.startListening();

  TCCR2A = _BV(WGM20);
  TCCR2B = _BV(WGM22) | _BV(CS20);

  // Set frequency 38kHz
  OCR2A = 210;

  OCR2B = 70;
}

uint8_t pipe;
char data[9];
char output[10];
char pre[35];
char post[32];
int ir_led = 3;


void de_xor() {
  for (char &ch: data)
    ch ^= mask;
}

void emit_seq(char *seq, int len)
{
  int i;
  for (i = 0; i < len; i++) {
    if (seq[i] == '1') {
      TIMER_ENABLE_PWM;
      delayMicroseconds(666);
      TIMER_DISABLE_PWM;
      delayMicroseconds(1620);
    } else {
      TIMER_ENABLE_PWM;
      delayMicroseconds(666);
      TIMER_DISABLE_PWM;
      delayMicroseconds(560);
    }
  }

}
void emit_ir_led(char pre[35], char post[32])
{
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
  
  TIMER_ENABLE_PWM;
  delayMicroseconds(9000);
  TIMER_DISABLE_PWM;
  delayMicroseconds(4500);

  emit_seq(pre, 35);
  
  TIMER_ENABLE_PWM;
  delayMicroseconds(640);
    
  TIMER_DISABLE_PWM;
  delay(20);

  emit_seq(post, 32);

  TIMER_ENABLE_PWM;
  delayMicroseconds(640);
    
  TIMER_DISABLE_PWM;
}

void loop() {

  if (radio.available(&pipe)) {
    radio.read(data, sizeof(data));
    de_xor();

    int i, j;
    for (i = 5, j = 0; i < 35 + 5; i++, j++) {
      char ch = data[i / 8];
      if (ch & (1 << (i % 8))) {
        pre[j] = '1';
      } else {
        pre[j] = '0';
      }
    }

    for (i = 35 + 5, j = 0; i < 35 + 32 + 5; i++, j++) {
      char ch = data[i / 8];
      if (ch & (1 << (i % 8))) {
        post[j] = '1';
      } else {
        post[j] = '0';
      }
    }
   
    for (i = 0; i < 35; i++) {
      Serial.print(pre[i]);
    }
    Serial.println();
    
    for (i = 0; i < 32; i++) {
      Serial.print(post[i]);
    }
    Serial.println();
    
    emit_ir_led(pre, post);
  }
}
