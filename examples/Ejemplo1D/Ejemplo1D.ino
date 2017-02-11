#include <FiltroKalman.h>
#define TASA_REFRESCO 120

FiltroKalman1D fk;

void setup() {
  Serial.begin(19200);
  while (!Serial);
  fk.init(0.001, 0.1);
}

void loop() {
  Vec1f input(analogRead(A0));
  fk.update(input);
  Vec1f out = fk.getEstimation();
  Serial.print(input[0]);
  Serial.print(',');
  Serial.println(out[0]);
  delay(1000/TASA_REFRESCO);
}
