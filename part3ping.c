/*
 * part3ping.c
 */


#include "part3ping.h"
#include "Timer.h"

volatile unsigned long START_TIME = 0;
volatile unsigned long END_TIME = 0;
volatile enum{LOW, HIGH, DONE} STATE = LOW; // State of ping echo pulse

long pulseLength;
int overflow;
int overflowCount = 0;
volatile unsigned long current_time;
volatile unsigned long last_time;
unsigned long time_diff;

/**
 * Initialize ping sensor. Uses PB3 and Timer 3B
 */
void ping_init (void){

  // YOUR CODE HERE
    SYSCTL_RCGCTIMER_R |= 0x08;
    while((SYSCTL_PRTIMER_R & 0x08) == 0){};

    SYSCTL_RCGCGPIO_R |= 0x02;
    while((SYSCTL_PRGPIO_R & 0x02) == 0){};

    GPIO_PORTB_DEN_R |= 0x08;
    GPIO_PORTB_DIR_R &= 0x08;
    GPIO_PORTB_AFSEL_R |= 0x08;
    GPIO_PORTB_PCTL_R |= 0x7000;


    TIMER3_CTL_R &= ~(TIMER_CTL_TBEN);        //disable timer to configure
    TIMER3_CTL_R |= TIMER_CTL_TBEVENT_BOTH;   //enable Trigger on both edges
    TIMER3_CFG_R |= TIMER_CFG_16_BIT;         //set to 16 bit timer
    TIMER3_TBMR_R = 0b000000010111;           //count up, edge-time mode, capture mode
    TIMER3_TBILR_R = 0xFFFF;                  //value to count down from
    TIMER3_ICR_R = 0x400;                     //clears TIMER3 time-out interrupt flags
    TIMER3_IMR_R |= 0b10000000000;            //enable timer b capture mode event interrupt
    TIMER3_TBPR_R |= 0xFF;
    NVIC_EN1_R |= 0x10;                      //enable interrupt for timer 3b
    NVIC_PRI9_R |= 0x20;

    //  TIMER3_CTL_R: Enable TB, Both edges for TB event
    //  TIMER3_CFG_R: 16-bit mode
    //  TIMER3_TBMR_R: Capture mode, Edge-time mode, Count
    //  down
    //  TIMER3_TBILR_R: 0xFFFF (16-bit max value)
    //  TIMER3_TBPR_R: 0xFF (8-bit max value)
    //  TIMER3_IMR_R: Enable TB capture interrupt

    IntRegister(INT_TIMER3B, TIMER3B_Handler);

    IntMasterEnable();

    // Configure and enable the timer
    TIMER3_CTL_R |= 0x100;


}

void ping_trigger (void){
    STATE = LOW;
    // Disable timer and disable timer interrupt
    TIMER3_CTL_R &= ~0x100;
    TIMER3_IMR_R &= ~0x400;
    // Disable alternate function (disconnect timer from port pin)
    GPIO_PORTB_DIR_R |= 0x08;
    GPIO_PORTB_AFSEL_R &= ~0x08; //IDK

    // YOUR CODE HERE FOR PING TRIGGER/START PULSE
    GPIO_PORTB_DATA_R &= ~0x08; //low

    GPIO_PORTB_DATA_R |= 0x08; //high

    timer_waitMicros(5); //wait

    GPIO_PORTB_DATA_R &= ~0x08; //low
    STATE = HIGH;

    GPIO_PORTB_DIR_R &= 0xF7;
    // Clear an interrupt that may have been erroneously triggered
    TIMER3_ICR_R |= 0x400;
    // Re-enable alternate function, timer interrupt, and timer
    GPIO_PORTB_AFSEL_R |= 0x08; //IDK
    TIMER3_IMR_R |= 0x400;
    TIMER3_CTL_R |= 0x100;


}


void TIMER3B_Handler(void){

    if(TIMER3_MIS_R & TIMER_MIS_CBEMIS) {
            if(STATE == HIGH)
            {
                //clear capture interrupt flag
                TIMER3_ICR_R = TIMER_ICR_CBECINT;

                //captures time of rising edge event
                START_TIME = /*((int)TIMER3_TBPS_R << 16) |*/ TIMER3_TBR_R;

                //now capturing falling edge
                STATE = LOW;
            }
            else if(STATE == LOW)
            {
                //clear capture interrupt flag
                TIMER3_ICR_R = TIMER_ICR_CBECINT;

                //capture time of falling edge
                END_TIME = /*((int)TIMER3_TBPS_R << 16) |*/ TIMER3_TBR_R;
                STATE = DONE;

                //disable timerB
//                TIMER3_CTL_R &= ~TIMER_CTL_TBEN;
            }
        }
}

float ping_getDistance(void){
    ping_trigger();

    //wait until end of pulse
    while (STATE != DONE)
    {
    }

    //Correction for overflow
    overflow = (END_TIME < START_TIME);

    pulseLength = END_TIME + (overflow << 24) - START_TIME;

    //calculate distance
    return (pulseLength * (6.25e-8) * 34300) / 2;

}

long getPulseLength(void){

    return pulseLength;
}

int getOverflow(void){
    if (START_TIME < END_TIME){
      overflowCount++;
    }
  return overflowCount;
}

