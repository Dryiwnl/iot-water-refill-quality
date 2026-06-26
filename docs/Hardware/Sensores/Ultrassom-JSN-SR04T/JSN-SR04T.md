# Documentação - Sensor Ultrassônico JSN-SR04T

# Função do JSN-SR04T

O sensor foi implementado no projeto com a função de interpretar o nível de água do cocho. Desta maneira, a sua leitura retorna a distância (em centímetros) que ele está da superfícia da água.

> **Figura 1:** Representação da medição de distância entre o JSN-SR04T e a superfície da água.

![Figura 1 - Representação da medição de distância](/docs/Hardware/Sensores/img/img8.png)

---

# Como funciona

O sensor é composto por 4 pinos:

* **5v:** alimentação.
* **GND:** terra.
* **Trig:** emite pulso de som.
* **Echo:** calcula o tempo de ida e volta do pulso de som.

Portanto, o Trig é colocado em estado lógico alto emitindo um pulso de som, que por sua vez, bate em uma superfície e retorna para o sensor. No mesmo momento que é emitido, o Echo entra em estado lógico alto, retornando o tempo em que esse pulso chegou até a superfície, colidiu, e retornou a sua origem. Note que o sensor mede a **duração de tempo** e não a distância. Logo teremos que transformar essa duração de segundos para centímetros.

Como temos o tempo, utilizamos a fórmula:

```math
s = v \cdot t
```

onde:

* (s): distância, em centímetros;
* (v): velocidade do som;
* (t): tempo, em segundos.

Para o cálculo utilizado no código, consideramos a velocidade do som em centímetros por microssegundo:

```math
v = 0{,}0343 \; \text{cm}/\mu\text{s}
```

Como o tempo medido corresponde ao percurso de ida e volta do pulso, dividimos o resultado por 2:

```math
d = \frac{v \cdot t}{2}
```

Substituindo o valor da velocidade do som:

```math
d = \frac{0{,}0343 \cdot t}{2}
```

No código, essa fórmula fica representada como:

```math
\text{distancia} = \frac{\text{duracao} \cdot 0{,}0343}{2}
```

---

# Pinagem

> **Figura 2:** Ligação do sensor JSN-SR04T ao ESP32.

![Figura 2 - Ligação do sensor JSN-SR04T ao ESP32](/docs/Hardware/Sensores/img/img9.png)

| Ligação        |
| -------------- |
| 5v -> Vin      |
| Trig -> GPIO5  |
| Echo -> GPIO18 |
| GND -> GND     |

---

# Código de teste

```cpp
#include <Arduino.h>

// Pinagem de acordo com o que foi definido
#define TRIG_PIN 5
#define ECHO_PIN 18

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Define o Trig como saida e o Echo como entrada
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Deixa o Trig inicialmente em estado logico baixo
  digitalWrite(TRIG_PIN, LOW);
}

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(5);

  // Coloca o Trig em estado logico alto (emitindo o pulso)
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(20);
  digitalWrite(TRIG_PIN, LOW);

  // pulseIn retorna quanto tempo o Echo ficou em estado logico alto
  unsigned long duracao = pulseIn(ECHO_PIN, HIGH, 60000);

  if (duracao == 0) {
    Serial.println("Sem_leitura/fora_de_alcance");
  } else {
    // Calcula a distancia em centimetros
    float distancia_cm = duracao * 0.0343 / 2.0;
    Serial.print("Distancia:");
    Serial.print(distancia_cm);
    Serial.println("cm");
  }

  delay(500);
}
```

---

# Observações

É necessário realizar medições com um objeto a pelo menos 20cm de distância do JSN-SR04T, pois qualquer distância menor que essa gera leituras instáveis ou até mesmo inexistentes.

---

# Especificações

| Parâmetro                    | Valor                                                                                                                       |
| ---------------------------- | --------------------------------------------------------------------------------------------------------------------------- |
| Tipo                         | Módulo ultrassônico JSN-SR04T / AJ-SR04M                                                                                    |
| Aplicação                    | Medição de distância em ambientes úmidos, com sonda impermeável.                                                            |
| Material                     | Componentes eletrônicos.                                                                                                    |
| Tensão de alimentação        | 5 V CC                                                                                                                      |
| Corrente de trabalho         | 30 mA                                                                                                                       |
| Corrente em espera           | 5 mA                                                                                                                        |
| Corrente de baixa potência   | 20 μA                                                                                                                       |
| Frequência de operação       | 40 kHz                                                                                                                      |
| Alcance máximo               | 4,5 m                                                                                                                       |
| Alcance mínimo               | 25 cm                                                                                                                       |
| Resolução                    | 0,5 cm                                                                                                                      |
| Ângulo de medição            | < 50°                                                                                                                       |
| Temperatura de operação      | -10 °C a 70 °C                                                                                                              |
| Comprimento do cabo da sonda | Aproximadamente 2,5 m                                                                                                       |
| Dimensões do módulo          | Aproximadamente 41 × 28 × 11 mm                                                                                             |
| Características              | Sonda impermeável integrada, alta estabilidade e sensibilidade, zona cega inferior a 25 cm e proteção contra água e poeira. |
