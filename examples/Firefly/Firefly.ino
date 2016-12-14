#include <IRremote.h>
#include <IRremoteInt.h>

/*

IR Reception only active while the physical push button is held.
Without this, the firefly refuses to flash properly

If for some reason you experience the flashing issue, attempt to flash on the port and toggle the power switch

*/

IRrecv irrecv(3);
decode_results results;

void setup()
{
	Serial.begin(115200); // Ignored by Maple. But needed by boards using hardware serial via a USB to Serial adaptor

    pinMode (PA2, INPUT_PULLUP); //PA2 = pushbutton address
    irrecv.enableIRIn();
}

void loop() {
    // STATE_IDLE      2
    // STATE_MARK      3
    // STATE_SPACE     4
    // STATE_STOP      5
    // STATE_OVERFLOW  6
    Serial.print("ir in ");
    Serial.print(irparams.recvpin);
    Serial.print(" ||| ");
    Serial.print(digitalRead(irparams.recvpin));
    Serial.print(" ||| ");
    Serial.print(irparams.rcvstate);
    Serial.print(" ||| ");
    if (irrecv.decode(&results)) {
        Serial.print(results.value);
        irrecv.resume();
    } else {
        Serial.print("no res");
    }

    if(digitalRead(PA2)) {
        Serial.print(" pause");
        Timer4.pause();
    } else {
        Timer4.resume();
    }
    Serial.print("\n");
    delay(1);
}
