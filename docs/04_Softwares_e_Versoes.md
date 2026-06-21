# Softwares Instalados e Versões

Ambiente, configuração e bibliotecas usadas no projeto. Como o projeto usa PlatformIO, grande parte dessas informações vem do `platformio.ini`.

## Ambiente de desenvolvimento

| Software | Versão | Uso |
|----------|--------|-----|
| VS Code | 1.124.2 | Editor de código |
| PlatformIO Core | 6.1.19 | Compilação, upload e gerência de bibliotecas |
| Git | 2.53.0.windows.2 | Versionamento e envio para o GitHub |

## Configuração do projeto (platformio.ini)

| Campo | Valor |
|-------|-------|
| platform | espressif32@6.8.1 |
| board | esp32doit-devkit-v1 (ESP32 DOIT DevKit V1) |
| framework | arduino |
| monitor_speed | 115200 |
| upload_port / monitor_port | COM3 |

> A porta `COM3` é a do computador usado no desenvolvimento. Em outra máquina, a porta pode ser diferente (verifique no Gerenciador de Dispositivos ou na lista de portas do PlatformIO).

## Bibliotecas (lib_deps)

| Biblioteca | Versão | Uso |
|------------|--------|-----|
| knolleary/PubSubClient | não fixada no `platformio.ini` (usa a mais recente, atualmente 2.8) | Comunicação MQTT com o Adafruit IO |

> Dica de reprodutibilidade: para garantir que o projeto sempre use a mesma versão, dá pra fixar a biblioteca no `platformio.ini`, por exemplo `knolleary/PubSubClient@2.8`.

## Plataformas e serviços

| Serviço | Uso |
|---------|-----|
| Adafruit IO | Dashboard online e armazenamento das leituras, via protocolo MQTT |
