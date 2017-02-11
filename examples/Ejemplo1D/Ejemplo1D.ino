#include <FiltroKalman.h>
#define TASA_REFRESCO 120

FiltroKalman1D fk;  // FiltroKalman para 1 dimension
//FiltroKalman2D fk; // FiltroKalman para 2 dimensiones
//FiltroKalman3D fk; // FiltroKalman para 3 dimensiones

void setup() {
  Serial.begin(19200);
  while (!Serial);
  //Más pequeño es más
  //      suave , rápido
  fk.init(0.001 , 0.25);
}

void loop() {
  Vec1f input(analogRead(A0));
  //Vec2F input(analogRead(A0),analogRead(A1));
  //Vec3F input(analogRead(A0),analogRead(A1),analogRead(a2));
  fk.update(input);
  Vec1f out = fk.getEstimation();
  //Vec2f out = fk.getEstimation();
  //Vec3f out = fk.getEstimation();

  Serial.print(input[0]);
  //Serial.print(',');Serial.print(input[1]);  //Cuando se utilice 2D y 3D
  //Serial.print(',');Serial.print(input[2]);  //Cuando se utilice 3D
  Serial.print(',');
  Serial.print(out[0]);
  //Serial.print(',');Serial.print(out[1]);   //Cuando se utilice 2D y 3D
  //Serial.print(',');Serial.print(out[2]);   //Cuando se utilice 3D
  Serial.println();
  delay(1000/TASA_REFRESCO);
}
