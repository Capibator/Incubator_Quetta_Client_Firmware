#include "rotary.h"

// Define rotaryEncoder and dir here
AiEsp32RotaryEncoder rotaryEncoder;
int dir = IDLE;

void initEncoder()
{
    rotaryEncoder = AiEsp32RotaryEncoder(ROTARY_ENCODER_A_PIN, ROTARY_ENCODER_B_PIN, ROTARY_ENCODER_BUTTON_PIN, -1, ROTARY_ENCODER_STEPS);
    rotaryEncoder.begin();
    rotaryEncoder.setup(readEncoderISR);
    rotaryEncoder.setBoundaries(0, 100, true); // minValue, maxValue, circleValues true|false (when max go to min and vice versa)
}

// ISR for rotary encoder library.
void IRAM_ATTR readEncoderISR()
{
    rotaryEncoder.readEncoder_ISR();
}

void on_button_long_click()
{
    Serial.print("button LONG press ");
    dir = BACK;
}

void handle_rotary_button()
{
    static unsigned long lastTimeButtonDown = 0;
    static bool wasButtonDown = false;

    bool isEncoderButtonDown = rotaryEncoder.isEncoderButtonDown();
    // isEncoderButtonDown = !isEncoderButtonDown; //uncomment this line if your button is reversed

    if (isEncoderButtonDown)
    {
        Serial.print("+"); // REMOVE THIS LINE IF YOU DONT WANT TO SEE
        if (!wasButtonDown)
        {
            // start measuring
            lastTimeButtonDown = millis();
        }
        // else we wait since button is still down
        wasButtonDown = true;
        return;
    }

    // button is up
    if (wasButtonDown)
    {
        if (millis() - lastTimeButtonDown >= longPressAfterMiliseconds)
        {
            on_button_long_click();
        }
    }
    wasButtonDown = false;
}

void updateEncoder()
{
    static int prevVal = 0; // Make prevVal static to retain its value between function calls
    int val;

    if (rotaryEncoder.isEncoderButtonClicked())
    {
        dir = ENTER;
        Serial.println("button pressed");
    }

    if (rotaryEncoder.encoderChanged())
    {
        val = rotaryEncoder.readEncoder();

        // Check for changes in encoder value and determine direction
        if (val != prevVal) // Only proceed if the value has changed
        {
            if (val == 100 || val == 0)
                return;

            // Determine direction
            dir = (val > prevVal) ? UP : DOWN;

            // Print direction
            if (dir == UP)
                Serial.println("UP");
            else
                Serial.println("DOWN");

            prevVal = val; // Update prevVal with the new value
        }
    }
}
