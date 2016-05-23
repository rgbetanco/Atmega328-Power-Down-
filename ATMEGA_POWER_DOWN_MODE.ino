#define LED_PIN 4
void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  //save power by writing all digital IO to low
  for(int i=0; i<20; i++){
    if(i != 2)               //pin 2 will be used to wake up the mcu
    pinMode(i, OUTPUT);
  }
  attachInterrupt(0, digitalInterrupt, FALLING);   //wake up interrupt

  //Setup WATCHDOG Timer
  WDTCSR = (24);  //CHANGE ENABLE AND WDE - ALSO RESETS
  WDTCSR = (33);  //PRESCALERS ONLY - GET RID OF THE WDE AND WDCE BITS
  WDTCSR |= (1 << 6); //ENABLE INTERRUPT MODE
  
  //Disable ADC
  ADCSRA &= ~(1 << 7);
  //ENABLE SLEEP MODE
  SMCR |= (1 << 2);  //set AVR in power down mode
  SMCR |= 1; //enable sleep
  
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_PIN, LOW);
  //delay(5000);

  for(int i=0; i<2; i++){  //gives 16sec
    //BOD Disable
    MCUCR |= (3 << 5);         //set both BODS and BODSE at the same time
    MCUCR = (MCUCR & ~(1 << 5)) | (1 << 6); //then set the BODS bit and clear the BODSE bit at the same time
    __asm__ __volatile__("sleep");
  }
}

void digitalInterrupt (){
}
ISR(WDT_vect){  //watchdog timer interrupt vector
}

}

