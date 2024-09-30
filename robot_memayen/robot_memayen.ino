#include "globals.h"
#include "utils.h"

void i_wanna_go_home_and_then_edge(){
  set_motors_speed(150);
  
  while(true){
    for(int i = 0; i < 4; i++){
      digitalWrite(motors[i].in1, 1);
      digitalWrite(motors[i].in2, 0);

      serial_printf("Activated pins: %u %u", motors[i].in1, motors[i].in2);
      delay(SECOND_MS);
    }
    delay(SECOND_MS);
    reset_motors();
    delay(SECOND_MS);
  }
}


void setup() {
  Serial.begin(9600);
  motors_setup();
  
}

void loop() {
  i_wanna_go_home_and_then_edge();

}
