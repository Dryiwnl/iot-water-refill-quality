# Módulo Relé + Bomba — Reabastecimento

## Informações e características

O **módulo relé** é o atuador do sistema: ele funciona como uma chave controlada pelo ESP32 que liga e desliga a **bomba d'água**. Quando o sensor ultrassônico detecta que o nível está baixo, o ESP32 aciona o relé, que fecha o circuito de potência e liga a bomba até o nível voltar ao adequado.

| Característica | Valor |
|----------------|-------|
| Tipo | Relé mecânico, 5V |
| Canal usado | 1 (IN1) |
| Lógica | Invertida (LOW liga, HIGH desliga) |
| Carga controlada | Bomba d'água 12V |
| Função no projeto | Ligar/desligar a bomba para reabastecer o cocho |

> A bomba não é alimentada pelo ESP32. Ela recebe 12V do step-up MT3608, e o relé apenas abre/fecha esse circuito. Detalhes em [03_Lista_de_Pinagem.md](../../../03_Lista_de_Pinagem.md).

## Pinagem (lado de controle)

| Pino do relé | Liga em |
|--------------|---------|
| VCC | 5V do ESP32 |
| GND | GND do ESP32 |
| IN1 | GPIO 23 |
| Jumper JD-VCC | ligado ao VCC |

## Como funciona o código

Por causa da lógica invertida do módulo, o relé inicia desligado com `HIGH`:

1. `iniciaRele()` configura o pino como saída e já deixa o relé desligado (`HIGH`).
2. `ligarRele()` envia `LOW`, que fecha o relé e liga a bomba.
3. `desligarRele()` envia `HIGH`, que abre o relé e desliga a bomba.

## Código executado

```cpp
#include <Arduino.h>

#define RELE_PIN 23

// ATENÇÃO: a lógica do relé é negada: HIGH = desligado e LOW = ligado
void iniciaRele(){
  pinMode(RELE_PIN, OUTPUT);
  digitalWrite(RELE_PIN, HIGH); // inicia desligado
}

void ligarRele(){
  digitalWrite(RELE_PIN, LOW);
}

void desligarRele(){
  digitalWrite(RELE_PIN, HIGH);
}
```

## Tela de saída

> ✍️ Como o relé não imprime no monitor serial, aqui você pode colocar uma foto da bomba ligada/desligada, ou um print do trecho do `main` onde o relé é acionado conforme o nível.
> `![Acionamento do relé](saida_rele.png)`
