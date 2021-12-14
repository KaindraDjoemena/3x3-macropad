// Libraries
#include <Keyboard.h> // Keyboard 1.0.3


// Variables
// Keyboard
const byte output[3] = {4, 5, 6};                           // Output pins
const byte input[3] = {9, 8, 7};                            // Input pins
const char layout[3][3] = {                                 // Macropad/keyboard layout
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'}
};
const int key_pause = 250;                                  // The pause before the arduino can send multiple keys
const int key_hold_delay = 25;                              // Delays between keys
int key_duration[3][3];                                     // Keeps track of each key's duration
bool is_holding_key[3][3];                                  // Keeps track of each key's state (whether it's being held or not)


// Setup
void setup()
{ 
  // Keyboard
  Keyboard.begin(); // Begin keyboard

  // Configuring pins
  // Output
  for (int i = 0; i < 3; i++)
  {
    pinMode(output[i], OUTPUT);
    digitalWrite(output[i], HIGH);
  }

  // Input
  for (int i = 0; i < 3; i++)
  {
    pinMode(input[i], INPUT_PULLUP);
  }
}


// Loop
void loop() {

  // Send output
  for (int i = 0; i < 3; i++)
  {
    digitalWrite(output[i], LOW);                           // Set pin to low
    delayMicroseconds(5);                                   // Small delay to prevent double clicking

    // Read pins
    for (int j = 0; j < 3; j++)
    {
      if (digitalRead(input[j]) == LOW)                     // Gets executed when the pin reads low
      {
        keyPressed(i, j);                                   // Sends the pins to arduino
      }
      else
      {
        resetKey(i, j);                                     // Reset the data for that key
      }
    }
    digitalWrite(output[i], HIGH);                          // Set pin back to high
    delayMicroseconds(500);                                 // Small delay to prevent double clicking
  }
}


// keyPressed function
void keyPressed(int i, int j)
{
  key_duration[i][j]++;                                     // Increment the key press duration

  if (!is_holding_key[i][j])                                // Gets executed if the key hasn't been pressed before
  {
    outputKey(i, j);
    is_holding_key[i][j] = true;
  }
  else if (key_duration[i][j] > key_pause)                  // Gets executed if the counter is bigger than the key_pause variable
  {
    outputKey(i, j);                                        // Prints the keys
    delay(key_hold_delay);                                  // Delays the keys so the user has more control over the key holding
  }
}


// Output the keystroke(s) corresponding to its place on the 'layout' grid
void outputKey(int i, int j)
{
  if (layout[i][j] == '1')
  {
    Keyboard.print("Modify your own shorcuts!");
    // Official documentation so you can modify it on your own [https://www.arduino.cc/reference/en/language/functions/usb/keyboard/]
  }

  // Find/search
  else if (layout[i][j] == '2')
  {
    Keyboard.press(KEY_RIGHT_CTRL);
    Keyboard.press('f');
    Keyboard.releaseAll();
  }

  // Select all
  else if (layout[i][j] == '3')
  {
    Keyboard.press(KEY_RIGHT_CTRL);
    Keyboard.press('a');
    Keyboard.releaseAll();
  }

  // ctrl + "/" to comment code
  else if (layout[i][j] == '4')
  {
    Keyboard.press(KEY_RIGHT_CTRL);
    Keyboard.press('/');
    Keyboard.releaseAll();
  }

  // Cut
  else if (layout[i][j] == '5')
  {
    Keyboard.press(KEY_RIGHT_CTRL);
    Keyboard.press('x');
    Keyboard.releaseAll();
  }

  // Paste
  else if (layout[i][j] == '6')
  {
    Keyboard.press(KEY_RIGHT_CTRL);
    Keyboard.press('v');
    Keyboard.releaseAll();
  }

  // Redo
  else if (layout[i][j] == '7')
  {
    Keyboard.press(KEY_RIGHT_CTRL);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press('z');
    Keyboard.releaseAll();
  }

  // Undo
  else if (layout[i][j] == '8')
  {
    Keyboard.press(KEY_RIGHT_CTRL);
    Keyboard.press('z');
    Keyboard.releaseAll();
  }

  // Copy
  else if (layout[i][j] == '9')
  {
    Keyboard.press(KEY_RIGHT_CTRL);
    Keyboard.press('c');
    Keyboard.releaseAll();
  }
}


// resetKey function to reset the key states
void resetKey(int i, int j)
{
  key_duration[i][j] = 0;                                   // Resets the key duration
  is_holding_key[i][j] = false;                             // Tells arduino that the user isn't holding the key
}
