/////////////////////////////////////////////////////
//
// K M U T N B B R A I L L E K E Y B O A R D
//
/////////////////////////////////////////////////////
//
// Version: 1.1, Rev.1
// Licensed: TGDE, KMUTNB
// Maintainer: Gunjarit Yoothongin
// Parinyawat Yoothongin
// Released: 26 June 2017
//
// Documentation: None
//
/////////////////////////////////////////////////////
// U S E R C O N F I G U R A T I O N S ::
/////////////////////////////////////////////////////
// Baud rate of MCU <~> Pro Micro
#define PROMICRO_BAUD 38400
// HV509 Pinout
#define HVCLK 8
#define HVLAT 9
#define HVDAT 21


#define KEY_CTRL 0x01
#define KEY_SHIFT 0x02
#define KEY_ALT 0x04

#define KEY_0 0x27
#define KEY_1 0x1E
#define KEY_2 0x1F
#define KEY_3 0x20
#define KEY_4 0x21
#define KEY_5 0x22
#define KEY_6 0x23
#define KEY_7 0x24
#define KEY_8 0x25
#define KEY_9 0x26
#define KEY_A 0x04
#define KEY_B 0x05
#define KEY_C 0x06
#define KEY_D 0x07
#define KEY_E 0x08
#define KEY_F 0x09
#define KEY_G 0x0A
#define KEY_H 0x0B
#define KEY_I 0x0C
#define KEY_J 0x0D
#define KEY_K 0x0E
#define KEY_L 0x0F
#define KEY_M 0x10
#define KEY_N 0x11
#define KEY_O 0x12
#define KEY_P 0x13
#define KEY_Q 0x14
#define KEY_R 0x15
#define KEY_S 0x16
#define KEY_T 0x17
#define KEY_U 0x18
#define KEY_V 0x19
#define KEY_W 0x1A
#define KEY_X 0x1B
#define KEY_Y 0x1C
#define KEY_Z 0x1D
#define KEY_ENTER 0x28
#define KEY_ESC 0x29
#define KEY_BACKSPACE 0x2A
#define KEY_TAB 0x2B
#define KEY_SPACE 0x2C
#define KEY_MINUS 0x2D
#define KEY_EQUAL 0x2E
#define KEY_LEFT_BRACE 0x2F
#define KEY_RIGHT_BRACE 0x30
#define KEY_BACKSLASH 0x31
#define KEY_NUMBER 0x32
#define KEY_SEMICOLON 0x33
#define KEY_QUOTE 0x34
#define KEY_TILDE 0x35
#define KEY_COMMA 0x36
#define KEY_PERIOD 0x37
#define KEY_SLASH 0x38
#define KEY_CAPS_LOCK 0x39
#define KEY_F1 0x3A
#define KEY_F2 0x3B
#define KEY_F3 0x3C
#define KEY_F4 0x3D
#define KEY_F5 0x3E
#define KEY_F6 0x3F
#define KEY_F7 0x40
#define KEY_F8 0x41
#define KEY_F9 0x42
#define KEY_F10 0x43
#define KEY_F11 0x44
#define KEY_F12 0x45
#define KEY_PRINTSCREEN 0x46
#define KEY_SCROLL_LOCK 0x47
#define KEY_PAUSE 0x48
#define KEY_INSERT 0x49
#define KEY_HOME 0x4A
#define KEY_PAGE_UP 0x4B
#define KEY_DELETE 0x4C
#define KEY_END 0x4D
#define KEY_PAGE_DOWN 0x4E
#define KEY_RIGHT 0x4F
#define KEY_LEFT 0x50
#define KEY_DOWN 0x51
#define KEY_UP 0x52
#define KEY_NUM_LOCK 0x53
#define KEYPAD_SLASH 0x54
#define KEYPAD_ASTERIX 0x55
#define KEYPAD_MINUS 0x56
#define KEYPAD_PLUS 0x57
#define KEYPAD_ENTER 0x58
#define KEYPAD_1 0x59
#define KEYPAD_2 0x5A
#define KEYPAD_3 0x5B
#define KEYPAD_4 0x5C
#define KEYPAD_5 0x5D
#define KEYPAD_6 0x5E
#define KEYPAD_7 0x5F
#define KEYPAD_8 0x60
#define KEYPAD_9 0x61
#define KEYPAD_0 0x62
#define KEYPAD_PERIOD 0x63
#define UART_MAX_BUFFER     100



// Braille Remapping Config
const byte BRAILLE_MAPPING[] = { 7, 8, 1, 2, 3, 4, 5, 6 };
// Braille Keyboard Pinout
const byte BRAILLE_KEY[] = { A4, A5, A6, A0, A1, A2, A7, A3 };
const byte COMMAND_KEY[] = { 4, 3, 2, 5, 6, 7 };
const byte CURSOR_KEY[] =
{
  22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
  32, 33, 34, 35, 36, 37, 38, 39, 40, 41,
  42, 43, 44, 45, 46, 47, 48, 49, 13, 12,
  11, 10, A8, A9, A10, A11, A12, A13, A14, A15,
};
const byte THUMB_KEY[] = { 17, 16, 15, 14 };
const byte BUZZER = 18; // Buzzer output
const byte SPACE_KEY = 20; // Spacebar
const byte RESERVED_1 = 19; // Reserved for future use (Current: RX1)
const byte RESERVED_2 = 50; // Reserved for future use (Current: MISO)
const byte RESERVED_3 = 51; // Reserved for future use (Current: MOSI)
const byte RESERVED_4 = 52; // Reserved for future use (Current: SCK)
// Keyboard Mode Configuration
const int KEYBOARD_MODE = INPUT_PULLUP; // Use external resistors on keyboard PCB
/////////////////////////////////////////////////////
// G L O B A L V A R I A B L E S ::
/////////////////////////////////////////////////////
// Enum for playback method


    byte buff[5];

    
typedef enum {
  BD_START,
  BD_READY,
} playlist;
// Use to store NVDA raw data
String nvdaBuffer;
// Use to store keyboard's state
byte keyboardBuffer[13];
// Use to store state of keyboard
bool CURSOR_BITS[40];
bool BRAILLE_BITS[8];
bool COMMAND_BITS[6];
bool THUMB_BITS[4];
int SPACE_BIT;
// Keyboard pressing state
bool isKeyPressing;
// Counter on NVDA stream reader
int nvda_read = 0;
// Use to store data for Braille display
byte dataBuffer[42];
// Prototype of the keyboard state
const byte STATE_PROTOTYPE[] = { 0x10, 0x02, 0, 0, 0, 0, 0, 0, 0, 0,
                                 0, 0x10, 0x03
                               };
// Identity flag for NVDA data
bool isNotEqual = false;
// Secondary buffer for NVDA data
byte secondBuffer[40];


byte buf_read[UART_MAX_BUFFER] ;
unsigned int uart_index_write = 0;

byte buf_read2[UART_MAX_BUFFER] ;
unsigned int uart_index_write2 = 0;

unsigned int uart_index_write3 = 0;
int j = 0;


uint8_t BT_buf[8] = {
  0
};
/////////////////////////////////////////////////////
// I N I T I A L I Z E R ::
/////////////////////////////////////////////////////
void setup() {
  // Initialize state array
  for (int i = 0; i < 13; i++) 
    keyboardBuffer[i] = STATE_PROTOTYPE[i];
  // For PC communication, initialize serial port #0
  Serial.begin(PROMICRO_BAUD);
  Serial1.begin(PROMICRO_BAUD);
  // Fix serial0 port error
  pinMode(1, INPUT_PULLUP);
  // Initialize buzzer
  pinMode(BUZZER, OUTPUT);
  // Initialize HV509 pin mode139
  pinMode(HVCLK, OUTPUT); // Clock pin
  pinMode(HVLAT, OUTPUT); // Latch pin
  pinMode(HVDAT, OUTPUT); // Data pin
  // Initialize keyboard input
  for (int i = 0; i < 8; i++) pinMode(BRAILLE_KEY[i], KEYBOARD_MODE);
  for (int i = 0; i < 6; i++) pinMode(COMMAND_KEY[i], KEYBOARD_MODE);
  for (int i = 0; i < 40; i++) pinMode(CURSOR_KEY[i], KEYBOARD_MODE);
  for (int i = 0; i < 4; i++) pinMode(THUMB_KEY[i], KEYBOARD_MODE);
  pinMode(SPACE_KEY, KEYBOARD_MODE);
  // Initial dataBuffer to zero
  for (int i = 0; i < 40; i++) dataBuffer[i] = 0;
  play(BD_READY);
  // First send data to Pro Micro
  serialSender();
}
/////////////////////////////////////////////////////
// L O O P E V E N T ::
/////////////////////////////////////////////////////
void loop() {
  // Invoke keyboard event
  keyboardEvent();
  // If NVDA counter reach 40...
  if (nvda_read == 40) {
    // If data received is not equal...
    if (isNotEqual) {
      // Send data to Pro Micro
      serialSender();
      // Turn flag into false
      isNotEqual = false;
    }
    // Clear NVDA counter to zero
    nvda_read = 0;
  }
}
/////////////////////////////////////////////////////
// K E Y B O A R D E V E N T ::
/////////////////////////////////////////////////////
void keyboardEvent() {
  // Read state of spacebar key
  // if (!digitalRead(SPACE_KEY)) {
  //   SPACE_BIT = 1;
  //   keyboardBuffer[9] = 1;
  // }
  // // Read state of thumb key
  // int j = 4; 
  // for (int i = 0; i < j; i++) 
  //   if (!digitalRead(THUMB_KEY[i])) THUMB_BITS[i] = true;
  // for (int i = 0; i < j; i++) 
  //   keyboardBuffer[10] += THUMB_BITS[i] * (1 << i);
  // // Read state of command key
  // j = 6; 
  // for (int i = 0; i < j; i++) 
  //   if (!digitalRead(COMMAND_KEY[i])) COMMAND_BITS[i] = true;
  // for (int i = 0; i < j; i++) 
  //   keyboardBuffer[3] += COMMAND_BITS[i] * (1 << i);
  // // Read state of Braille key
  // j = 8; 
  // for (int i = 0; i < j; i++) 
  //   if (!digitalRead(BRAILLE_KEY[i])) BRAILLE_BITS[i] = true;
  // for (int i = 0; i < j; i++) 
  //   keyboardBuffer[2] += BRAILLE_BITS[i] * (1 << i);
  // // Read state of cursor key
  // j = 40; 
  // for (int i = 0; i < j; i++) 
  //   if (!digitalRead(CURSOR_KEY[i])) 
  //     CURSOR_BITS[i] = true;
  // for (int i = 0; i < j; i++) 
  //   keyboardBuffer[4 + (i / 8)] += CURSOR_BITS[i] * (1 << (i % 8));
  // // Checking what key pressing
  // bool _press = false;
  // for (int i = 0; i < 4; i++) _press |= !digitalRead(THUMB_KEY[i]);
  // for (int i = 0; i < 6; i++) _press |= !digitalRead(COMMAND_KEY[i]);
  // for (int i = 0; i < 8; i++) _press |= !digitalRead(BRAILLE_KEY[i]);
  // for (int i = 0; i < 40; i++) _press |= !digitalRead(CURSOR_KEY[i]);
  // _press |= !digitalRead(SPACE_KEY);
  // isKeyPressing = _press;
  // // Compare state
  // bool isSame = true;
  // for (int i = 0; i < 13; i++) {
  //   if (keyboardBuffer[i] != STATE_PROTOTYPE[i]) {
  //     isSame = false;
  //     break;
  //   }
  // }
  // If Key is not press (already release) and state is not same as prototype
 // if (!isKeyPressing && !isSame) {
    // Extract data from keyboardBuffer
    // byte buff[5];
    // buff[0] = keyboardBuffer[2]; // Braille[0]
    // buff[1] = 0x00; // Braille[1], in case of Thai
    // buff[2] = keyboardBuffer[3]; // Command byte
    // buff[3] = SPACE_BIT; // Space byte
    // buff[4] = keyboardBuffer[10]; // Thumb byte
    // // Send data through serial port

    // buff[0] = 0x13; // Braille[0]
    // buff[1] = 0x00; // Braille[1], in case of Thai
    // buff[2] = 0x00; // Command byte
    // buff[3] = 0x00; // Space byte
    // buff[4] = 0x00; // Thumb byte
    buff[0] = 0x00; // Braille[0]
    buff[1] = 0x00; // Braille[1], in case of Thai
    buff[2] = 0x0A; // Command byte
    buff[3] = 0x00; // Space byte
    buff[4] = 0x00; // Thumb byte


    //Serial.println("case 3");
    if (buff[0] != 0 && buff[2] == 0 && buff[3] == 0 && buff[4] == 0 ) { //Braille Key
      
      F_BrailleKey();
    }
    else if (buff[0] == 0 && buff[1] == 0 && buff[2] != 0 && buff[3] == 0 && buff[4] == 0 ) { // Cmd Key
      //Serial.println("Cmd Key");
      F_CMDKey();
    }
    else if (buff[0] != 0 && buff[1] == 0 && buff[2] == 0 && buff[3] != 0 && buff[4] == 0 ) { // Space Key
      //Serial.println("Space Key");
      F_SpaceKey();
    }
    else if (buff[0] == 0 && buff[1] == 0 && buff[2] == 0 && buff[3] == 0 && buff[4] != 0 ) { // Arrow Key
      //Serial.println("Arrow Key");
      F_ArrowKey();
    }
    else if (buff[0] == 0 && buff[1] == 0 && buff[2] == 0 && buff[3] != 0 && buff[4] == 0 ) { // Arrow Key
      //Serial.println("Space");
      BT_buf[0] = 0xFE;
      BT_buf[1] = 0x03;
      BT_buf[2] = 0x00;
      BT_buf[3] =  0x00;
      BT_buf[4] =  KEY_SPACE;
      Serial1.write(BT_buf, 5);
      Serial.write(BT_buf, 5);
    }

    //Serial.write(buff, 1);
    // Serial.write(buff, 5);
    // Serial1.write(buff, 5);
    // Clear entire bits after serial has been sent
    int j = 4; for (int i = 0; i < j; i++) THUMB_BITS[i] = false;
    j = 6; for (int i = 0; i < j; i++) COMMAND_BITS[i] = false;
    j = 8; for (int i = 0; i < j; i++) BRAILLE_BITS[i] = false;
    j = 40; for (int i = 0; i < j; i++) CURSOR_BITS[i] = false;
    SPACE_BIT = 0;
    // Clear pressing state after serial has been sent
    isKeyPressing = false;
  //}
  // Clear entire state
  for (int i = 0; i < 13; i++) 
    keyboardBuffer[i] = STATE_PROTOTYPE[i];
}
/////////////////////////////////////////////////////
// S E R I A L S E N D E R E V E N T ::
/////////////////////////////////////////////////////
void serialSender() {
  // Begin transmission
  shiftStart();
  // Send 40 bytes of data throught shift register
  for (int i = 0; i < 40; i++) {
    secondBuffer[i] = dataBuffer[i];
    shiftByte(secondBuffer[i], true);
    dataBuffer[i] = 0;
  }
  // End transmission
  shiftStop();
}
/////////////////////////////////////////////////////
// S E R I A L E V E N T # 0 ::
/////////////////////////////////////////////////////
void serialEvent() {
  // Read serial stream
  while (Serial.available()) {
    dataBuffer[nvda_read] = (byte) Serial.read();
    if ((secondBuffer[nvda_read] != dataBuffer[nvda_read]) &&
        (dataBuffer[nvda_read] - secondBuffer[nvda_read] != 0xC0)) {
      isNotEqual = true;
    }
    nvda_read++;
    if (nvda_read > 40) nvda_read = 0;
  }
}
/////////////////////////////////////////////////////
// C O M M U N I C A T I O N F U N C T I O N S ::
/////////////////////////////////////////////////////
// Hold latch to low state to begin the transmission
void shiftStart() {
  digitalWrite(HVLAT, LOW);
}
// Begin to send data via shiftOut command, extended142
void shiftByte(byte data, bool useRemapping) {
  if (useRemapping == true) {
    // Start shifting data
    shiftOut(HVDAT, HVCLK, MSBFIRST, brailleRemapping(data));
  }
  else {
    // Start shifting data
    shiftOut(HVDAT, HVCLK, MSBFIRST, data);
  }
}
// Change latch and data pin to high state to end the transmission
void shiftStop() {
  digitalWrite(HVLAT, HIGH);
  digitalWrite(HVDAT, HIGH);
}
// Clear Braille display
void clearDisplay() {
  shiftStart();
  for (int i = 0; i < 40; i++) {
    shiftByte(0, false);
  }
  shiftStop();
}
// Display a specific content to the display
void display(String content) {
  shiftStart();
  // Draw content to Braille display
  for (int i = 0; i < content.length(); i++)
    shiftByte(ConvertCharToBraille(content[i]), true);
  // Fill until 40 characters
  for (int i = 0; i < 40 - content.length(); i++) shiftByte(0,
        false);
  shiftStop();
}
/////////////////////////////////////////////////////
// O T H E R F U N C T I O N S ::
/////////////////////////////////////////////////////
// Play a listed sound
void play(playlist select) {
  switch (select) {
    case BD_READY : {
        digitalWrite(BUZZER, 0); delay(70);
        digitalWrite(BUZZER, 1); delay(40);
        digitalWrite(BUZZER, 0); delay(70);
        digitalWrite(BUZZER, 1); delay(40);
        digitalWrite(BUZZER, 0); delay(70);
        digitalWrite(BUZZER, 1); delay(40);
        break;
      }
    case BD_START : {
        digitalWrite(BUZZER, 0); delay(125);
        digitalWrite(BUZZER, 1); delay(50);
        digitalWrite(BUZZER, 0); delay(125);
        digitalWrite(BUZZER, 1); delay(50);
        break;
      }
    default:;
  }
}
// Blink function
void blink(byte pin, byte times, int interval) {
  pinMode(pin, OUTPUT);
  for (int i = 0; i < times; i++) {
    digitalWrite(pin, HIGH); delay(interval);
    digitalWrite(pin, LOW); delay(interval);
  }
}
// Convert character to Braille byte
byte ConvertCharToBraille(char c) {
  switch (c) {
    case '0' : return B00110100; break;
    case '1' : return B00000010; break;
    case '2' : return B00000110; break;
    case '3' : return B00010010; break;
    case '4' : return B00110010; break;
    case '5' : return B00100010; break;
    case '6' : return B00010110; break;
    case '7' : return B00110110; break;
    case '8' : return B00100110; break;
    case '9' : return B00010100; break;
    case 'A' : return B01000001; break;
    case 'B' : return B01000011; break;
    case 'C' : return B01001001; break;
    case 'D' : return B01011001; break;
    case 'E' : return B01010001; break;
    case 'F' : return B01001011; break;
    case 'G' : return B01011011; break;
    case 'H' : return B01010011; break;
    case 'I' : return B01001010; break;
    case 'J' : return B01011010; break;
    case 'K' : return B01000101; break;
    case 'L' : return B01000111; break;
    case 'M' : return B01001101; break;
    case 'N' : return B01011101; break;
    case 'O' : return B01010101; break;
    case 'P' : return B01001111; break;
    case 'Q' : return B01011111; break;
    case 'R' : return B01010111; break;
    case 'S' : return B01001110; break;
    case 'T' : return B01011110; break;
    case 'U' : return B01100101; break;
    case 'V' : return B01100111; break;
    case 'W' : return B01111010; break;
    case 'X' : return B01101101; break;
    case 'Y' : return B01111101; break;
    case 'Z' : return B01110101; break;
    case 'a' : return B00000001; break;
    case 'b' : return B00000011; break;
    case 'c' : return B00001001; break;
    case 'd' : return B00011001; break;
    case 'e' : return B00010001; break;
    case 'f' : return B00001011; break;
    case 'g' : return B00011011; break;
    case 'h' : return B00010011; break;
    case 'i' : return B00001010; break;
    case 'j' : return B00011010; break;
    case 'k' : return B00000101; break;
    case 'l' : return B00000111; break;
    case 'm' : return B00001101; break;
    case 'n' : return B00011101; break;
    case 'o' : return B00010101; break;
    case 'p' : return B00001111; break;
    case 'q' : return B00011111; break;
    case 'r' : return B00010111; break;
    case 's' : return B00001110; break;
    case 't' : return B00011110; break;
    case 'u' : return B00100101; break;
    case 'v' : return B00100111; break;
    case 'w' : return B00111010; break;
    case 'x' : return B00101101; break;
    case 'y' : return B00111101; break;
    case 'z' : return B00110101; break;
    case ',' : return B00100000; break;
    case ';' : return B00110000; break;
    case ':' : return B00110001; break;
    case '.' : return B00101000; break;
    case '!' : return B00101110; break;
    case '\"': return B00010000; break;
    case '\'': return B00000100; break;
    case '(' : return B00110111; break;
    case ')' : return B00111110; break;
    case '-' : return B00100100; break;
    case '_' : return B00111000; break;
    case '<' : return B00100011; break;
    case '=' : return B00111111; break;
    case '>' : return B00011100; break;
    case '%' : return B00101001; break;
    case '+' : return B00101100; break;
    case '~' : return B00011000; break;
    case '`' : return B00001000; break;
    case '&' : return B00101111; break;
    case '$' : return B00101011; break;
    case '?' : return B00111001; break;
    case '{' : return B00101010; break;
    case '[' : return B01101010; break;
    case '}' : return B00111011; break;
    case ']' : return B01111011; break;
    case '^' : return B01011000; break;
    case '@' : return B01001000; break;
    case '#' : return B00111100; break;
    case '\\': return B01110011; break;
    case '|' : return B00110011; break;
    case '/' : return B00001100; break;
    case '*' : return B00100001; break;
    default: return 0;
  }
}
// Pin remapping for NVDA data
byte brailleRemapping(byte original) {
  byte result;
  for (int i = 0; i < 8; i++) {
    bitWrite(result, i, bitRead(original, BRAILLE_MAPPING[i] - 1));
  }
  return result;
}
/////////////////////////////////////////////////////
// S C E N E S M A N A G E R ::
/////////////////////////////////////////////////////
// Welcome screen display
void scene_splash() {
  // Play start sound
  play(BD_START);
  // Wait a second
  delay(500);
  // Display welcome screen
  display("KMUTNB Braille Display");
  // Wait for 3 seconds
  delay(3000);
  // Clear entire screen
  scene_clear();
  // Play ready sound
  play(BD_START);
}
// Clear entire screen
void scene_clear() {
  clearDisplay();
}

#define UART_MAX_BUFFER     100

int default_lang_index = 0;

byte ArrowKey[16] = {
  0x00,//0
  KEY_UP  ,//1
  KEY_LEFT ,//2
  0x00,//3
  KEY_RIGHT  ,//4
  0x00,//5
  0x00,//6
  0x00,//7
  KEY_DOWN,//8
  0x00,//9
  0x00,//10
  0x00,//11
  0x00,//12
  0x00,//13
  0x00,//14
  0x00,//15
};

byte CMDKEY[64][4] = {
  {0x00, 0x00,  0x00, 0x00}, //0
  {KEY_ENTER, 0x00,  0x00, 0x00}, //1
  {KEY_BACKSPACE, 0x00,  0x00, 0x00}, //2
  {KEY_DELETE, 0x00,  0x00, 0x00}, //3
  {KEY_TAB , 0x00,  0x00, 0x00}, //4
  {KEY_CAPS_LOCK , 0x00,  0x00, 0x00}, //5
  {KEY_TILDE , 0x00, 0x00, 0x00}, //6 Change KB Com & Android
  {KEY_ESC , 0x00,  0x00, 0x00}, //7
  {KEY_INSERT , 0x00,  0x00, 0x00}, //8
  {KEY_HOME , 0x00,  0x00, 0x00}, //9
  {KEY_PAGE_UP ,  0x00, 0x00, 0x00}, //10
  {KEY_END , 0x00,  0x00, 0x00}, //11
  {KEY_PAGE_DOWN , 0x00,  0x00, 0x00}, //12
  {0x00, 0x00, 0x00, 0x00}, //13
  {0x00, 0x00, 0x00, 0x00}, //14
  {0x00, 0x00, 0x00, 0x00}, //15
  {0x00, 0x00, 0x00, 0x00}, //16
  {0x00, 0x00, 0x00, 0x00}, //17
  {0x00, 0x00, 0x00, 0x00}, //18
  {0x00, 0x00, 0x00, 0x00}, //19
  {0x00, 0x00, 0x00, 0x00}, //20
  {0x00, 0x00, 0x00, 0x00}, //21
  {0x00, 0x00, 0x00, 0x00}, //22
  {0x00, 0x00, 0x00, 0x00}, //23
  {0x00, 0x00, 0x00, 0x00}, //24
  {0x00, 0x00, 0x00, 0x00}, //25
  {0x00, 0x00, 0x00, 0x00}, //26
  {0x00, 0x00, 0x00, 0x00}, //27
  {0x00, 0x00, 0x00, 0x00}, //28
  {0x00, 0x00, 0x00, 0x00}, //29
  {0x00, 0x00, 0x00, 0x00}, //30
  {0x00, 0x00, 0x00, 0x00}, //31
  {0x00, 0x00, 0x00, 0x00}, //32
  {KEY_F1 , 0x00,  0x00, 0x00}, //33
  {KEY_F2 , 0x00,  0x00, 0x00}, //34
  {KEY_F3 , 0x00,  0x00, 0x00}, //35
  {KEY_F4 , 0x00,  0x00, 0x00}, //36
  {KEY_F5 , 0x00,  0x00, 0x00}, //37
  {KEY_F6 , 0x00,  0x00, 0x00}, //38
  {KEY_F7 , 0x00,  0x00, 0x00}, //39
  {KEY_F8 , 0x00,  0x00, 0x00}, //40
  {KEY_F9 , 0x00,  0x00, 0x00}, //41
  {KEY_F10 , 0x00,  0x00, 0x00}, //42
  {KEY_F11 , 0x00,  0x00, 0x00}, //43
  {KEY_F12 , 0x00,  0x00, 0x00}, //44
  {0x00, 0x00, 0x00, 0x00}, //45
  {0x00, 0x00, 0x00, 0x00}, //46
  {0x00, 0x00, 0x00, 0x00}, //47
  {0x00, 0x00, 0x00, 0x00}, //48
  {0x00, 0x00, 0x00, 0x00}, //49
  {0x00, 0x00, 0x00, 0x00}, //50
  {0x00, 0x00, 0x00, 0x00}, //51
  {0x00, 0x00, 0x00, 0x00}, //52
  {0x00, 0x00, 0x00, 0x00}, //53
  {0x00, 0x00, 0x00, 0x00}, //54
  {0x00, 0x00, 0x00, 0x00}, //55
  {0x00, 0x00, 0x00, 0x00}, //56
  {0x00, 0x00, 0x00, 0x00}, //57
  {0x00, 0x00, 0x00, 0x00}, //58
  {0x00, 0x00, 0x00, 0x00}, //59
  {0x00, 0x00, 0x00, 0x00}, //60
  {0x00, 0x00, 0x00, 0x00}, //61
  {0x00, 0x00, 0x00, 0x00}, //62
  {0x00, 0x00,  0x00, 0x00} //63
};

//Define Braille Key
byte BrailleKey[128][4] = {
  {0x00, 0x00, 0x00, 0x00}, //0
  {0x00, KEY_A, 0x00, KEY_T}, //1 char a or ะ
  {0x00, KEY_1 , 0x00, KEY_Q}, //2 char 1 or ๆ
  {0x00, KEY_B, 0x00, KEY_B}, //3 char b or อิ
  {0x00, KEY_QUOTE , 0x00, 0x00}, //4 char ' or
  {0x00, KEY_K, 0x00, KEY_EQUAL  }, //5 char k or ช
  {0x00, KEY_2, 0x00, KEY_U}, //6 char 2 or อี
  {0x00, KEY_L, 0x00, KEY_RIGHT_BRACE }, //7 char l or ล
  {0x00, KEY_TILDE , 0x00, 0x00}, //8 char ` or
  {0x00, KEY_C, 0x00, KEY_6}, //9 char c or อุ
  {0x00, KEY_I, KEY_SHIFT, KEY_F}, //10 char i or โ
  {0x00, KEY_F, 0x00, KEY_G}, //11 char f or เ
  {0x00, KEY_SLASH , KEY_SHIFT, KEY_C}, //12 char / or ฉ
  {0x00, KEY_M, 0x00, 0x00,}, //13 char m or ม
  {0x00, KEY_S, 0x00, KEY_L}, //14 char s or ส
  {0x00, KEY_P, 0x00, KEY_Z}, //15 char p or ผ
  {0x00, KEY_QUOTE , 0x00, 0x00}, //16 char " or
  {0x00, KEY_E, 0x00, KEY_Y}, //17 char e or ั
  {0x00, KEY_3, KEY_SHIFT, KEY_6}, //18 char 3 or ู
  {0x00, KEY_H, 0x00, KEY_S}, //19 char h or ห
  {0x00, KEY_9, 0x00, KEY_J}, //20 char 9 or ่
  {0x00, KEY_O, 0x00, KEY_V}, //21 char o or อ
  {0x00, KEY_6, 0x00, 0x00}, //22 char 6 or
  {0x00, KEY_R, 0x00, KEY_I}, //23 char r or ร
  {KEY_SHIFT, KEY_TILDE, 0x00, 0x00}, //24 char ~ or
  {0x00, KEY_D, 0x00, KEY_F}, //25 char d or ด
  {0x00, KEY_J, 0x00, KEY_0}, //26 char j or จ
  {0x00, KEY_G, 0x00, KEY_D}, //27 char g or ก
  {KEY_SHIFT, KEY_PERIOD , 0x00, 0x00}, //28 char > or
  {0x00, KEY_N, 0x00, KEY_O}, //29 char n or น
  {0x00, KEY_T, 0x00, KEY_5},//30 char t or ถ
  {0x00, KEY_Q, 0x00, 0x00}, //31 char q or
  {0x00, KEY_COMMA  , 0x00, KEY_H}, //32 char , or ็
  {KEY_SHIFT, KEY_8 , 0x00, KEY_K}, //33 char * or า
  {0x00, KEY_5, 0x00, KEY_N}, //34 char 5 or ื
  {KEY_SHIFT, KEY_COMMA , 0x00, KEY_C}, //35 char < or แ
  {0x00, KEY_MINUS , 0x00, 0x00}, //36 char - or
  {0x00, KEY_U, 0x00, KEY_8}, //37 char u or ค
  {0x00, KEY_8, KEY_SHIFT, KEY_J}, //38 char 8 or ๋
  {0x00, KEY_V, 0x00, KEY_LEFT_BRACE }, //39 char v or บ
  {0x00, KEY_PERIOD , 0x00, 0x00}, //40 char . or
  {KEY_SHIFT, KEY_5 , 0x00, 0x00}, //41 char % or
  {KEY_SHIFT, KEY_LEFT_BRACE , 0x00, KEY_7},//42 char { or ึ
  {KEY_SHIFT, KEY_4 , 0x00, KEY_A}, //43 char $ or ฟ
  {KEY_SHIFT, KEY_EQUAL , 0x00, KEY_MINUS  }, //44 char + or ข
  {0x00, KEY_X, 0x00, KEY_SLASH  }, //45 char x or ฝ
  {KEY_SHIFT, KEY_1, 0x00, KEY_BACKSLASH },//46 char ! or ฃ
  {KEY_SHIFT, KEY_7, 0x00, KEY_X}, //47 char & or ป
  {0x00, KEY_SEMICOLON  , 0x00, 0x00}, //48 char ; or
  {KEY_SHIFT, KEY_SEMICOLON , 0x00, KEY_W}, //49 char : or ไ
  {0x00, KEY_4, 0x00, KEY_H}, //50 char 4 or ้
  {KEY_SHIFT, KEY_BACKSLASH, 0x00, KEY_9}, //51 char | or ต
  {0x00, KEY_0, KEY_SHIFT, KEY_N}, //52 char 0 or ์
  {0x00, KEY_Z, 0x00, KEY_E}, //53 char z or ำ
  {0x00, KEY_7, KEY_SHIFT, KEY_U}, //54 char 7 or ๊
  {KEY_SHIFT, KEY_9, 0x00, 0x00}, //55 char ( or
  {0x00, KEY_MINUS , 0x00, 0x00}, //56 char _ or
  {KEY_SHIFT, KEY_SLASH , 0x00, KEY_R}, //57 char ? or พ
  {0x00, KEY_W, 0x00, KEY_SEMICOLON }, //58 char w or ว
  {KEY_SHIFT, KEY_RIGHT_BRACE, 0x00, KEY_QUOTE},//59 char } or ง

  {KEY_SHIFT, KEY_3, 0x00, 0x00}, //60 char # or
  {0x00, KEY_Y, 0x00, KEY_P},//61 char y or ย
  {KEY_SHIFT, KEY_0 , 0x00, KEY_M}, //62 char ) or ท
  {0x00, KEY_EQUAL , KEY_SHIFT, KEY_V}, //63 char = or ฮ

  {0x00, 0x00, 0x00, 0x00}, //64

  {KEY_SHIFT, KEY_A, 0x00, 0x00}, //65 char A
  {KEY_SHIFT, KEY_B, 0x00, 0x00}, //67 char B
  {KEY_SHIFT, KEY_K, 0x00, 0x00}, //69 char K
  {KEY_SHIFT, KEY_L, 0x00, 0x00}, //71 char L
  {0x00, 0x00, 0x00, 0x00}, // char
  {KEY_SHIFT, KEY_2, 0x00, 0x00}, //72 char @
  {KEY_SHIFT, KEY_C, 0x00, 0x00}, //73 char C
  {KEY_SHIFT, KEY_I, 0x00, 0x00}, //74 char I
  {KEY_SHIFT, KEY_F, 0x00, 0x00}, //75 char F
  {0x00, 0x00, 0x00, 0x00}, // char
  {KEY_SHIFT, KEY_M, 0x00, 0x00}, //77 char M
  {KEY_SHIFT, KEY_S, 0x00, 0x00}, //78 char S
  {KEY_SHIFT, KEY_P, 0x00, 0x00}, //79 char P
  {0x00, 0x00, 0x00, 0x00}, // char
  {KEY_SHIFT, KEY_E, 0x00, 0x00}, //81 char E
  {0x00, 0x00, 0x00, 0x00}, // char
  {KEY_SHIFT, KEY_H, 0x00, 0x00}, //83 char H
  {0x00, 0x00, 0x00, 0x00}, // char
  {KEY_SHIFT, KEY_O, 0x00, 0x00}, //85 char O
  {0x00, 0x00, 0x00, 0x00}, // char
  {KEY_SHIFT, KEY_R, 0x00, 0x00}, //87 char R
  {KEY_SHIFT, KEY_6 , 0x00, 0x00}, //88 char ^
  {KEY_SHIFT, KEY_D, 0x00, 0x00}, //89 char D
  {KEY_SHIFT, KEY_J, 0x00, 0x00}, //90 char J
  {KEY_SHIFT, KEY_G, 0x00, 0x00}, //91 char G
  {0x00, 0x00, 0x00, 0x00}, // char
  {KEY_SHIFT, KEY_N, 0x00, 0x00}, //93 char N
  {KEY_SHIFT, KEY_T, 0x00, 0x00}, //94 char T
  {KEY_SHIFT, KEY_Q, 0x00, 0x00}, //95 char Q


  {0x00, 0x00, 0x00, 0x00}, //96
  {0x00, 0x00, 0x00, 0x00}, //97
  {0x00, 0x00, 0x00, 0x00}, //98
  {0x00, 0x00, 0x00, 0x00}, //99
  {0x00, 0x00, 0x00, 0x00}, //100
  {KEY_SHIFT, KEY_U, 0x00, 0x00}, //101 char U
  {0x00, 0x00, 0x00, 0x00}, //102
  {KEY_SHIFT, KEY_V, 0x00, 0x00}, //103 char V
  {0x00, 0x00, 0x00, 0x00}, //104
  {0x00, 0x00, 0x00, 0x00}, //105
  {0x00, KEY_LEFT_BRACE , 0x00, 0x00}, //106 char [
  {0x00, 0x00, 0x00, 0x00}, //107
  {0x00, 0x00, 0x00, 0x00}, //108
  {KEY_SHIFT, KEY_X, 0x00, 0x00}, //109 char X
  {0x00, 0x00, 0x00, 0x00}, //110
  {0x00, 0x00, 0x00, 0x00}, //111
  {0x00, 0x00, 0x00, 0x00}, //112
  {0x00, 0x00, 0x00, 0x00}, //113
  {0x00, 0x00, 0x00, 0x00}, //114
  {0x00, KEY_BACKSLASH , 0x00, 0x00}, //115 char \
  {0x00, 0x00, 0x00, 0x00}, //116
  {KEY_SHIFT, KEY_Z, 0x00, 0x00}, //117 char Z
  {0x00, 0x00, 0x00, 0x00}, //118
  {0x00, 0x00, 0x00, 0x00}, //119
  {0x00, 0x00, 0x00, 0x00}, //120
  {0x00, 0x00, 0x00, 0x00}, //121
  {KEY_SHIFT, KEY_W, 0x00, 0x00}, //122 char W
  {0x00, KEY_RIGHT_BRACE , 0x00, 0x00}, //123 char ]
  {0x00, 0x00, 0x00, 0x00}, //124
  {KEY_SHIFT, KEY_Y, 0x00, 0x00}, //125 char Y

  {0x00, 0x00, 0x00, 0x00}, //126
  {0x00, 0x00, 0x00, 0x00} //127


};

byte BrialleKey2Byte[19][4] = {
  {0x07, 0x02, KEY_SHIFT , KEY_SLASH },//0 ฦ
  {0x17, 0x02, KEY_SHIFT , KEY_A },//1 ฤ
  {0x20, 0x25, KEY_SHIFT , KEY_BACKSLASH  },//2 ฅ
  {0x20, 0x2C, KEY_SHIFT , KEY_G },//3 ฌ
  {0x20, 0x3D, KEY_SHIFT , KEY_P },//4 ญ
  {0x20, 0x19, KEY_SHIFT , KEY_E },//5 ฎ
  {0x20, 0x33, KEY_SHIFT , KEY_D },//6 ฎ
  {0x20, 0x1E, KEY_SHIFT , KEY_LEFT_BRACE },//7 ฐ
  {0x20, 0x3E, KEY_SHIFT , KEY_R },//8 ฑ
  {0x20, 0x1D, KEY_SHIFT , KEY_I },//9 ณ
  {0x20, 0x39, 0x00 , KEY_4 },//10 ภ
  {0x20, 0x0E, KEY_SHIFT , KEY_L },//11 ศ

  {0x24, 0x25, KEY_SHIFT , KEY_S },//12 ฆ
  {0x24, 0x05, KEY_SHIFT , KEY_SEMICOLON  },//13 ซ
  {0x24, 0x0E, KEY_SHIFT , KEY_K },//14 ษ
  {0x24, 0x07, KEY_SHIFT , KEY_PERIOD }, //15 ฬ

  {0x30, 0x3E, KEY_SHIFT , KEY_COMMA  },//16 ฒ
  {0x31, 0x01, 0x00 , KEY_PERIOD  },//17 ใ
  {0x34, 0x3E, KEY_SHIFT , KEY_T }//18 ธ

};

//Define Space + Braille Command
byte SpaceKey[129][4] = {
  {0x00, 0x00, 0x00, 0x00}, //0
  {0x00, 0x00, 0x00, 0x00}, //1
  {KEY_ALT, 0x00, KEY_F, 0x00}, //2  File menu options in current program. (Key_1)
  {0x00, 0x00, 0x00, 0x00}, //3
  {0x00, 0x00, 0x00, 0x00}, //4
  {0x00, 0x00, 0x00, 0x00}, //5
  {KEY_ALT, 0x00, KEY_E, 0x00}, //6 Edit options in current program (Key_2)
  {0x00, 0x00, 0x00, 0x00}, //7
  {0x00, 0x00, 0x00, 0x00}, //8 
  {0x00, 0x00, 0x00, 0x00}, //9
  {0x00, 0x00, 0x00, 0x00}, //10
  {0x00, 0x00, 0x00, 0x00}, //11
  {0x00, 0x00, 0x00, 0x00}, //12
  {0x00, 0x00, 0x00, 0x00}, //13
  {0x00, 0x00, 0x00, 0x00}, //14
  {0x00, 0x00, 0x00, 0x00}, //15
  {0x00, 0x00, 0x00, 0x00}, //16
  {0x00, 0x00, 0x00, 0x00}, //17
  {KEY_ALT, 0x00, KEY_TAB, 0x00}, //18 Switch between open programs (Key_3)
  {0x00, 0x00, 0x00, 0x00}, //19
  {0x00, 0x00, KEY_9, 0x00}, //20 (Key_9)
  {0x00, 0x00, 0x00, 0x00}, //21
  {KEY_CTRL, KEY_SHIFT, KEY_ESC, 0x00}, //22  Opens Windows Task Manager (Key_6)
  {0x00, 0x00, 0x00, 0x00}, //23
  {0x00, 0x00, 0x00, 0x00}, //24
  {0x00, 0x00, 0x00, 0x00}, //25
  {0x00, 0x00, 0x00, 0x00}, //26
  {0x00, 0x00, 0x00, 0x00}, //27
  {0x00, 0x00, 0x00, 0x00}, //28
  {0x00, 0x00, 0x00, 0x00}, //29
  {0x00, 0x00, 0x00, 0x00}, //30
  {0x00, 0x00, 0x00, 0x00}, //31
  {0x00, 0x00, 0x00, 0x00}, //32
  {0x00, 0x00, 0x00, 0x00}, //33
  {KEY_CTRL, 0x00, KEY_ESC, 0x00}, //34 Opens the START menu (Key_5)
  {0x00, 0x00, 0x00, 0x00}, //35
  {0x00, 0x00, 0x00, 0x00}, //36
  {0x00, 0x00, 0x00, 0x00}, //37
  {KEY_ALT, 0x00, KEY_ENTER, 0x00}, //38 Open the Properties for the selected item (file, folder, shortcut, etc.) (Key_8)
  {0x00, 0x00, 0x00, 0x00}, //39
  {0x00, 0x00, 0x00, 0x00}, //40
  {0x00, 0x00, 0x00, 0x00}, //41
  {0x00, 0x00, 0x00, 0x00}, //42
  {0x00, 0x00, 0x00, 0x00}, //43
  {0x00, 0x00, 0x00, 0x00}, //44
  {0x00, 0x00, 0x00, 0x00}, //45
  {0x00, 0x00, 0x00, 0x00}, //46
  {0x00, 0x00, 0x00, 0x00}, //47
  {0x00, 0x00, 0x00, 0x00}, //48
  {0x00, 0x00, 0x00, 0x00}, //49
  {KEY_SHIFT, 0x00, KEY_DELETE, 0x00}, //50 Cut selected item. (Key_4)
  {0x00, 0x00, 0x00, 0x00}, //51
  {0x00, 0x00, KEY_0, 0x00}, //52 (Key_0)
  {0x00, 0x00, 0x00, 0x00}, //53
  {KEY_ALT, 0x00, KEY_F4, 0x00}, //54 Close the currently active program (Key_7)
  {0x00, 0x00, 0x00, 0x00}, //55
  {0x00, 0x00, 0x00, 0x00}, //56
  {0x00, 0x00, 0x00, 0x00}, //57
  {0x00, 0x00, 0x00, 0x00}, //58
  {0x00, 0x00, 0x00, 0x00}, //59
  {0x00, 0x00, 0x00, 0x00}, //60
  {0x00, 0x00, 0x00, 0x00}, //61
  {0x00, 0x00, 0x00, 0x00}, //62
  {0x00, 0x00, 0x00, 0x00}, //63
  {0x00, 0x00, 0x00, 0x00}, //64
  {KEY_CTRL, 0x00, KEY_A, 0x00}, //65 Select all text.
  {0x00, 0x00, 0x00, 0x00}, //66
  {KEY_CTRL, 0x00, KEY_B, 0x00}, //67  Change selected text to be Bold
  {0x00, 0x00, 0x00, 0x00}, //68
  {KEY_CTRL, 0x00, KEY_K, 0x00}, //69 Insert hyperlink for selected text
  {0x00, 0x00, 0x00, 0x00}, //70
  {0x00, 0x00, KEY_L, 0x00}, //71
  {0x00, 0x00, 0x00, 0x00}, //72
  {KEY_CTRL, 0x00, KEY_C, 0x00}, //73 Copy selected item
  {KEY_CTRL, 0x00, KEY_I, 0x00}, //74 Change selected text to be in Italics
  {KEY_CTRL, 0x00, KEY_F, 0x00}, //75 Open find window for current document or window
  {0x00, 0x00, 0x00, 0x00}, //76
  {0x00, 0x00, KEY_M, 0x00}, //77
  {KEY_CTRL, 0x00, KEY_S, 0x00}, //78 Save current document file.
  {KEY_CTRL, 0x00, KEY_P, 0x00}, //79 Print the current page or document.
  {0x00, 0x00, 0x00, 0x00}, //80
  {0x00, 0x00, KEY_E, 0x00}, //81
  {0x00, 0x00, 0x00, 0x00}, //82
  {0x00, 0x00, KEY_H, 0x00}, //83
  {0x00, 0x00, 0x00, 0x00}, //84
  {KEY_CTRL, 0x00, KEY_O, 0x00}, //85  Open a file in current software program
  {0x00, 0x00, 0x00, 0x00}, //86
  {0x00, 0x00, KEY_R, 0x00}, //87
  {0x00, 0x00, 0x00, 0x00}, //88
  {0x00, 0x00, KEY_D, 0x00}, //89
  {0x00, 0x00, KEY_J, 0x00}, //90
  {0x00, 0x00, KEY_G, 0x00}, //91
  {0x00, 0x00, 0x00, 0x00}, //92
  {KEY_CTRL, 0x00, KEY_N, 0x00}, //93  Create a new, blank document in some software programs
  {0x00, 0x00, KEY_T, 0x00}, //94
  {0x00, 0x00, KEY_Q, 0x00}, //95
  {0x00, 0x00, 0x00, 0x00}, //96
  {0x00, 0x00, 0x00, 0x00}, //97
  {0x00, 0x00, 0x00, 0x00}, //98
  {0x00, 0x00, 0x00, 0x00}, //99
  {0x00, 0x00, 0x00, 0x00}, //100
  {KEY_CTRL, 0x00, KEY_U, 0x00}, //101 Change selected text to be Underlined
  {0x00, 0x00, 0x00, 0x00}, //102
  {KEY_CTRL, 0x00, KEY_V, 0x00}, //103 Paste
  {0x00, 0x00, 0x00, 0x00}, //104
  {0x00, 0x00, 0x00, 0x00}, //105
  {0x00, 0x00, 0x00, 0x00}, //106
  {0x00, 0x00, 0x00, 0x00}, //107
  {0x00, 0x00, 0x00, 0x00}, //108
  {KEY_CTRL, 0x00, KEY_X, 0x00}, //109 Cut selected item.
  {0x00, 0x00, 0x00, 0x00}, //110
  {0x00, 0x00, 0x00, 0x00}, //111
  {0x00, 0x00, 0x00, 0x00}, //112
  {0x00, 0x00, 0x00, 0x00}, //113
  {0x00, 0x00, 0x00, 0x00}, //114
  {0x00, 0x00, 0x00, 0x00}, //115
  {0x00, 0x00, 0x00, 0x00}, //116
  {KEY_CTRL, 0x00, KEY_Z, 0x00}, //117
  {0x00, 0x00, 0x00, 0x00}, //118
  {0x00, 0x00, 0x00, 0x00}, //119
  {0x00, 0x00, 0x00, 0x00}, //120
  {0x00, 0x00, 0x00, 0x00}, //121
  {0x00, 0x00, KEY_W, 0x00}, //122
  {0x00, 0x00, 0x00, 0x00}, //123
  {0x00, 0x00, 0x00, 0x00}, //124
  {KEY_CTRL, 0x00, KEY_Y, 0x00}, //125
  {0x00, 0x00, 0x00, 0x00}, //126
  {0x00, 0x00, 0x00, 0x00}, //127
  {0x00, 0x00, KEY_ENTER, 0x00} //128 Key Enter

};

void F_BrailleKey() {
  if (buff[1] != 0) { //Braille Data 2 Byte
      Serial.println("1111111111111111");
    for (int i = 0; i < 19; i++) {
      if (buff[0] == BrialleKey2Byte[i][0] && buff[1] == BrialleKey2Byte[i][1] ) {
        BT_buf[0] = 0xFE;
        BT_buf[1] = 0x03;
        BT_buf[2] = BrialleKey2Byte[i][2];
        BT_buf[3] =  0x00;
        BT_buf[4] =  BrialleKey2Byte[i][3];
        Serial1.write(BT_buf, 5);
        Serial.write(BT_buf, 5);
        //releaseKey();
      }
    }
  }
  else {
    int key_index = buff[0];
    //Serial.write(key_index);
    //Serial.write(key_index);
    //Serial.print(key_index);
    //Serial.write(buff[0]);
    BT_buf[0] = 0xFE;
    BT_buf[1] = 0x03;
    BT_buf[2] = BrailleKey[buff[0]][default_lang_index];
    BT_buf[3] =  0x00;
    BT_buf[4] =  BrailleKey[buff[0]][default_lang_index + 1];
    Serial1.write(BT_buf, 5);
    Serial.write(BT_buf, 5);
    //Serial.write(key_index);
    //Serial.write(BT_buf[4]);
    //Serial.write(BrailleKey[key_index][default_lang_index + 1]);
    //releaseKey();
  }
}

void F_CMDKey() {
  if (CMDKEY[buff[2]][0] == KEY_TILDE || CMDKEY[buff[2]][0] == KEY_CAPS_LOCK) { //CT Lang (Com)
    if (default_lang_index == 0) {
      default_lang_index = 2;
      Serial.println("Change KB Thai");
    }
    else {
      default_lang_index = 0;
      Serial.println("Change KB Eng");
    }
    int key_index = buff[2];
    BT_buf[0] = 0xFE;
    BT_buf[1] = 0x03;
    BT_buf[2] = 0x00;
    BT_buf[3] =  0x00;
    BT_buf[4] =  CMDKEY[key_index][0];
    Serial1.write(BT_buf, 5);
    Serial.write(BT_buf, 5);
    //releaseKey();
  }
  else {
    int key_index = buff[2];
    BT_buf[0] = 0xFE;
    BT_buf[1] = 0x03;
    BT_buf[2] = 0x00;
    BT_buf[3] =  0x00;
    BT_buf[4] =  CMDKEY[key_index][0];
    Serial1.write(BT_buf, 5);
    Serial.write(BT_buf, 5);
    //releaseKey();
  }
}
void F_SpaceKey() {
  int key_index = buff[0];
  BT_buf[0] = 0xFE;
  BT_buf[1] = 0x03;
  BT_buf[2] = SpaceKey[key_index][0];
  BT_buf[3] =  SpaceKey[key_index][1];
  BT_buf[4] =  SpaceKey[key_index][2];
  Serial1.write(BT_buf, 5);
  Serial.write(BT_buf, 5);
  //releaseKey();
}

void F_ArrowKey() {
  int key_index = buff[4];
  BT_buf[0] = 0xFE;
  BT_buf[1] = 0x03;
  BT_buf[2] = 0x00;
  BT_buf[3] =  0x00;
  BT_buf[4] =  ArrowKey[key_index];
  Serial1.write(BT_buf, 5);
  Serial.write(BT_buf, 5);
  //releaseKey();
}

void releaseKey()
{
  BT_buf[0] = 0xFE;
  BT_buf[1] = 0x03;
  BT_buf[2] = 0x00;
  BT_buf[3] =  0x00;
  BT_buf[4] =  0x00;
  Serial1.write(BT_buf, 5);
  Serial.write(BT_buf, 5);
}
