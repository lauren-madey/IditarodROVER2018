int bin    = 1;
float tick = 0.5;

void int_to_bin_digit(unsigned int in, int count, int* out)
{
  /* assert: count <= sizeof(int)*CHAR_BIT */
  unsigned int mask = 1U << (count - 1);
  int i;
  for (i = 0; i < count; i++) {
    out[i] = (in & mask) ? 1 : 0;
    in <<= 1;
  }
}

void sleep(float sec) {
  int x = millis() + (sec * 1000.0);
  while (millis() < x) {
    ;
  }
}

void setup()
{
  Serial.begin(9600);
  pinMode(1,  OUTPUT);
  pinMode(2,  OUTPUT);
  pinMode(3,  OUTPUT);
  pinMode(4,  OUTPUT);
  pinMode(5,  OUTPUT);
  pinMode(6,  OUTPUT);
  pinMode(7,  OUTPUT);
  pinMode(8,  OUTPUT);
  pinMode(9,  OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
}

void run() {
  int digit[12] = {0};
  int i = 0;

  while (bin < 4096) {
    int_to_bin_digit(bin, 13, digit);

    for (i = 1; i < 13; ++i) {
      Serial.print(digit[i]);
      if (digit[i] == 1) {
        digitalWrite(i, false);
      } else {
        digitalWrite(i, true);
      }
    }
    Serial.println();

    bin += 1;
    sleep(tick);
  }
  exit(1);
}

void loop()
{
  run();
}
