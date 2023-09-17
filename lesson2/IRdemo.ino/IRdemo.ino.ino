/*  ___   ___  ___  _   _  ___   ___   ____ ___  ____  
 * / _ \ /___)/ _ \| | | |/ _ \ / _ \ / ___) _ \|    \ 
 *| |_| |___ | |_| | |_| | |_| | |_| ( (__| |_| | | | |
 * \___/(___/ \___/ \__  |\___/ \___(_)____)___/|_|_|_|
 *                  (____/ 
 * Infrared Remote Controller & IR Receiver demo program
 * Tutorial URL https://osoyoo.com/2014/12/08/decode-infrared-remote-controller-with-ir-receiver-vs1838b/
 * CopyRight www.osoyoo.com
 * IRremote library must be installed before running the code
 * After running the code, open your Arduino Serial monitor, then push any key in your IR remote controller,
 * you will see the IR code of each key, please write down these code of each key
 * in future, whey you programming IR remote control code, you can use these code to determine which key is pressed, 
 * and let arduino make corresponding reactions 
 */
#include <IRremote.h>
int input_pin = 12; //connect S12 in extension shield(D12 in Arduino) to IR receiver S pin
IRrecv irrecv(input_pin);
decode_results signals;
void setup()
{
 Serial.begin(9600);
  irrecv.enableIRIn(); // enable input from IR receiver
}
void loop() {
if (irrecv.decode(&signals)) {
    Serial.println(signals.value, HEX);
    irrecv.resume(); // get the next signal
  }
}
