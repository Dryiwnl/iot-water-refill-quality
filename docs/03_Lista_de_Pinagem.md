# Lista de Pinagem

Conexões entre os pinos (GPIOs) do ESP32 e cada componente, e o circuito de potência da bomba.

## ESP32 → Sensores e atuador (sinais)

| Componente | Sinal | GPIO do ESP32 | Tipo |
|------------|-------|---------------|------|
| Sensor ultrassônico JSN-SR04T | TRIG | GPIO 5 | Digital (saída) |
| Sensor ultrassônico JSN-SR04T | ECHO | GPIO 18 | Digital (entrada) |
| Sensor de pH 4502C | Po (saída analógica) | GPIO 34 | ADC (entrada, somente leitura) |
| Sensor de turbidez | OUT (saída analógica) | GPIO 32 | ADC (entrada) |
| Módulo relé (canal 1) | IN1 | GPIO 23 | Digital (saída) |

## Alimentação e terra

- ESP32 **5V** → barramento de 5V (alimenta os sensores e o lado de controle do relé)
- ESP32 **GND** → barramento de GND (terra comum a todos os componentes)
- Todos os VCC/V+ dos sensores ligam no barramento 5V; todos os GND no barramento GND.

## Pinos não utilizados

- **Sensor de pH 4502C:** pinos `To` (temperatura) e `Do` (saída digital) não são ligados.
- **Módulo relé:** entrada `IN2` (canal 2) não é usada.

## Módulo relé (lado de controle)

| Pino do relé | Liga em |
|--------------|---------|
| VCC | 5V do ESP32 |
| GND | GND do ESP32 |
| IN1 | GPIO 23 |
| Jumper JD-VCC | ligado ao VCC |

> **Lógica invertida:** neste módulo, `LOW` liga o relé e `HIGH` desliga. Por isso o relé inicia em `HIGH` (desligado) no `setup`.

## Circuito de potência (acionamento da bomba)

O ESP32 não alimenta a bomba diretamente. Ele aciona o relé (via GPIO 23), e o relé funciona como uma chave que liga a bomba de 12V. A energia passa pelo step-up MT3608, que eleva a tensão da fonte até os 12V da bomba.

```
ESP32 GPIO23 ──► IN1 do relé (controle)

Fonte 5V ──► MT3608 (eleva 5V → 12V)
               │
               ├─ OUT+ ──► COM1 do relé ──► NO1 ──► (+) Bomba 12V
               │
               └─ OUT- ───────────────────────────► (−) Bomba 12V
```

| Ligação | De | Para |
|---------|----|----|
| Entrada do step-up | Fonte 5V (+ / −) | MT3608 IN+ / IN− |
| Saída do step-up | MT3608 OUT+ | COM1 do relé |
| Chave do relé | NO1 do relé | positivo da bomba |
| Retorno da bomba | negativo da bomba | MT3608 OUT− |

(NC1 fica vazio.)

## Observações técnicas

- **Leitura analógica:** o ESP32 usa resolução de 12 bits (`analogReadResolution(12)`, valores de 0 a 4095) e atenuação de 11 dB (lê até ~3.3V). O pH e a turbidez estão no **ADC1** (GPIOs 34 e 32), o conjunto de pinos compatível com o uso simultâneo do Wi-Fi.
- **Ligação direta nos GPIOs:** as entradas (ECHO, Po, OUT) estão ligadas diretamente nos pinos, sem divisor de tensão.
