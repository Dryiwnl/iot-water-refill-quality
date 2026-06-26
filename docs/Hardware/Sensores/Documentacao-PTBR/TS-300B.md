# Sensor de Turbidez TS-300B

O TS-300B foi implementado no projeto com a função de medir a turbidez da água. Quanto maior a turbidez, maior é a presença de partículas em suspensão, como terra, lodo, matéria orgânica ou outros contaminantes. O sensor retorna um valor numérico correspondente à turbidez da água, normalmente expresso em NTU (Nephelometric Turbidity Unit).

![Configuração dos pads](/docs/Hardware/Sensores/img/turbidez.png)

---

# Como funciona

O módulo possui três pinos:

* **VCC:** alimentação (5 V)
* **GND:** terra
* **OUT:** saída analógica

O sensor possui duas extremidades, uma emissora e outra receptora. A extremidade emissora envia um feixe de luz para o receptor. Conforme a quantidade de partículas presentes na água aumenta, parte dessa luz é bloqueada ou espalhada, reduzindo a intensidade luminosa recebida pelo receptor.

Quanto menor for a intensidade da luz recebida, maior será a turbidez medida pelo sensor.

![Configuração dos pads](/docs/Hardware/Sensores/img/img2.png)

---

Com isso, o sensor fornece uma tensão proporcional à quantidade de luz recebida pelo receptor.

Como o módulo é utilizado em modo analógico neste projeto, a leitura é realizada pelo conversor Analógico-Digital (ADC) do ESP32.

O ADC do ESP32 possui resolução de **12 bits**, ou seja:

```math
2^{12}=4096
```

Assim, uma leitura pode assumir valores entre **0 e 4095**.

Para converter a leitura do ADC em tensão utiliza-se:

```math
Tensão = ADC \times \frac{3.3}{4095}
```

Como o ADC do ESP32 apresenta melhor resolução em baixas tensões, é recomendado configurar a atenuação do conversor para ampliar sua faixa de leitura.

---

# Pinagem

![Configuração dos pads](/docs/Hardware/Sensores/img/img3.png)

| Sensor | ESP32  |
| ------ | ------ |
| VCC    | Vin    |
| OUT    | GPIO32 |
| GND    | GND    |

---

# Código de teste

```cpp
#include <Arduino.h>

// Define a pinagem
#define TURB_PIN 32

// Tensao medida em agua limpa, usada como referencia (0 NTU)
float tensao_limpa = 2.760;

// Ganho para converter a queda de tensao em turbidez (NTU)
float ganho_turbidez = 1000.0;

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(TURB_PIN, INPUT);

  // ADC com 12 bits de resolucao
  analogReadResolution(12);

  // Atenuacao para uma faixa mais adequada de leitura de tensao
  analogSetPinAttenuation(TURB_PIN, ADC_11db);
}

void loop() {

  int adc = analogRead(TURB_PIN);

  float tensao = adc * (3.3 / 4095.0);

  float ntu = (tensao_limpa - tensao) * ganho_turbidez;

  if (ntu < 0)
    ntu = 0;

  Serial.print("Tensao: ");
  Serial.print(tensao, 3);

  Serial.print(" V | Turbidez: ");
  Serial.print(ntu, 1);

  Serial.println(" NTU");

  delay(500);
}
```

> **Observação:** adicionar posteriormente imagens e resultados das medições em água limpa e água turva.

---

# Configuração Analógica/Digital

O módulo possui três pads para seleção do modo de funcionamento:

* **A:** Analógico
* **B:** Bridge
* **D:** Digital

Dependendo da solda realizada entre os pads, o sensor altera seu modo de operação.

| PAD | Solda                 | Funcionamento                                                                   |
| --- | --------------------- | ------------------------------------------------------------------------------- |
| A   | A soldado com B       | O módulo opera no modo de saída analógica.                                      |
| B   | $\bar{A}$ e $\bar{D}$ | O módulo não possui uma configuração válida, resultando em leituras incorretas. |
| D   | D soldado com B       | O módulo opera no modo de saída digital.                                        |

![Configuração dos pads](/docs/Hardware/Sensores/img/img1.png)

O padrão de muitas lojas de componentes eletrônicos é fornecer o módulo já configurado para operação em modo analógico. Entretanto, essa configuração pode ser alterada conforme a necessidade da aplicação.

Neste projeto foi utilizada a configuração **A soldado com B**, permitindo a leitura analógica do sensor.

---

# Especificações

| Parâmetro                    | Valor                  |
| ---------------------------- | ---------------------- |
| Tensão de operação           | 5 V CC                 |
| Corrente de operação         | Aproximadamente 11 mA  |
| Faixa de detecção            | 0% a 3,5% (0–4550 NTU) |
| Temperatura de operação      | -30 °C a 80 °C         |
| Temperatura de armazenamento | -10 °C a 80 °C         |
| Margem de erro               | ±0,5% F.S.             |
| Peso                         | 18 g                   |
