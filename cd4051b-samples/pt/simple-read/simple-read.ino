
// Pino Arduino que receberá o valor lido do CD4051B
// Este pino Arduino deverá estar conectado ao pino 3 do CD4051B
// Podemos utilizar pino digital ou analógico, porém é necessário
// chamar as funções readDigitalValue (para digital),
// readAnalogValue(para analógico) correspondente
#define PIN_INPUT 2

// Pinos **Arduino** conectados aos switches do CD4051B
// Os pinos A, B, C devem estar conectados aos pinos
// 11, 10 e 9 do CD4051B nesta ordem
#define PIN_SWITCH_A 8
#define PIN_SWITCH_B 9
#define PIN_SWITCH_C 10

const int switches[3] = {PIN_SWITCH_A, PIN_SWITCH_B, PIN_SWITCH_C};

void setup() {

  Serial.begin(9600);

  // define modo de entrada/saída dos pinos Arduino
  pinMode(PIN_INPUT, INPUT);
  pinMode(PIN_SWITCH_A, OUTPUT);
  pinMode(PIN_SWITCH_B, OUTPUT);
  pinMode(PIN_SWITCH_C, OUTPUT);

}

void loop() {

  // código de exemplo, responsável por ler todos os
  // canais do CD4051B e imprimir os valores lidos no
  // monitor serial
  for (int channel = 0; channel < 8; channel++) {
 
    int v = readDigitalValue(channel);

    Serial.print("C["); Serial.print(channel); Serial.print("]=");
    Serial.print(v); Serial.print("\t");

  }

  Serial.println("");

  delay(5000);

}

/**
 * Seleciona o canal de entrada do CD4051B.
 * 
 * @param switchPins array com os pinos no Arduino correspondentes aos switches A, B, C respectivamente
 * 
 */
void selectChannel(const int switchPins[3], int channel) {

  digitalWrite(switchPins[0], channel & 1 ? HIGH : LOW);
  digitalWrite(switchPins[1], channel & 2 ? HIGH : LOW);
  digitalWrite(switchPins[2], channel & 4 ? HIGH : LOW);

}

/**
 * Read a digital value from a single CD4051B
 * 
 * @param channel channel number
 * @return the value read from the channel (one of HIGH or LOW)
 * 
 */
int readDigitalValue(int channel) {
  selectChannel(switches, channel);
  return digitalRead(PIN_INPUT);
}

/**
 * Read an analog value from a single CD4051B
 * 
 * @param channel channel number
 * @return the value read from the channel (0-1023)
 * 
 */
int readAnalogValue(int channel) {
  selectChannel(switches, channel);
  return analogRead(PIN_INPUT);
}
