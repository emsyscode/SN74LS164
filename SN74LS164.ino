//                  0x80
//                 ------
//        0x40    |      |  0x20
//                | 0x08 |
//                 ------
//        0x02    |      |  0x04
//                | 0x01 |
//                 ------  o 0x10
//
//This is the assignment of the bit weight to the segments.
//Your digits should be created based on these values.
//When sent 0x00 this means all segments will be ON because the
//display is anode commum.
//the weight of bit at binary format: 0b84218421

#define tr1 8
#define tr2 9
#define tr3 10
#define tr4 11

#define dataIn 4
#define clk 5
//This table is to be used without the signal "~" at sendSerial(x); 
//char numbers[10] = {0b00011000, 0b11011011, 0b01010100, 0b01010010, 0b10010011, 0b00110010, 0b00110000, 0b01011011, 0b00010000, 0b00010010};
//char twoPoints = 0b11101111;
//This table is filled inverted is necessary apply the "~" to inverte it!
char numbers[10] = {0b11100111, 0b00100100, 0b10101011, 0b10101101, 0b01101100, 0b11001101, 0b11001111, 0b10100100, 0b11101111, 0b11101101};
char twoPoints = 0b00010000;
//Tis table is to be used with "~" and is in Hexadecimal format to stay more short.
//char numbers[10] = {0xE7, 0x24, 0xAB, 0xAD, 0x6C, 0xCD, 0xCF, 0xA4, 0xEF, 0xED};
//char twoPoints = 0x10;

void setup() {
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  Serial.begin(115200);
}

void serialData(uint8_t val){
  unsigned char data = 0x00;
  unsigned char mask = 1; //our bitmask
  data=val;
      for (mask = 0b00000001; mask>0; mask <<= 1) { //iterate through bit mask
      digitalWrite(clk, LOW);
      delayMicroseconds(1);
        if (data & mask){ // if bitwise AND resolves to true
          digitalWrite(dataIn, HIGH);
          //Serial.print(1); //Only to debug
        }
        else{ //if bitwise and resolves to false
          digitalWrite(dataIn, LOW);
          //Serial.print(0); //Only to debug
        }
        digitalWrite(clk,HIGH);// need invert the signal to allow 8 bits is is low only send 7 bits
        delayMicroseconds(1);
      }
  digitalWrite(clk, LOW);
  //Serial.println(); //Only to debug
}
void sendDigit(int grid, int digit){
  switch (grid){
          case 1: digitalWrite(8, LOW); digitalWrite(9, HIGH); digitalWrite(10, HIGH); digitalWrite(11, HIGH);
                  serialData(~(digit)); break;
          case 2: digitalWrite(8, HIGH); digitalWrite(9, LOW); digitalWrite(10, HIGH); digitalWrite(11, HIGH);
                  serialData(~(digit)); break;
          case 3: digitalWrite(8, HIGH); digitalWrite(9, HIGH); digitalWrite(10, LOW); digitalWrite(11, HIGH);
                  serialData(~(digit)); break;
          case 4: digitalWrite(8, HIGH); digitalWrite(9, HIGH); digitalWrite(10, HIGH); digitalWrite(11, LOW);
                  serialData(~(digit)); break;
        }
}
void showStatic(){
digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
      for (uint8_t i = 0; i<10; i++){
      serialData(~(numbers[i])); //Take attention to the table being used, because it define if you must remove or not the "~"
      delay(1000);
      serialData(~(twoPoints));  //Take attention to the table being used, because it define if you must remove or not the "~"
      delay(1000);
      }
}
void showDinamicBlinking(){
  for (uint8_t s = 0; s<250; s++){
        sendDigit(1, numbers[8]);
        delay(10);
        sendDigit(2, numbers[3]);
        delay(10);
        sendDigit(3, numbers[1]);
        delay(10);
        sendDigit(4, numbers[2]);
        delay(10);
      }
}
void showDinamic(){
  for (uint8_t s = 0; s<250; s++){
        sendDigit(1, numbers[8]);
        delay(5);
        sendDigit(2, numbers[3]);
        delay(5);
        sendDigit(3, numbers[1]);
        delay(5);
        sendDigit(4, numbers[2]);
        delay(5);
      }
}
void loop() {
  // put your main code here, to run repeatedly:
  showStatic();
  showDinamic();
  showDinamicBlinking();
}
