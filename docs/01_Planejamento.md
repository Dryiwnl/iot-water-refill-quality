# Planejamento Inicial do Projeto

## 1. Título e Objetivo do Projeto

- **Nome:** Bebedouro Inteligente IoT com medição de qualidade de água para o meio rural
- **Breve descrição:** sistema baseado em ESP32 que reabastece o bebedouro automaticamente quando o nível da água está baixo e monitora a qualidade da água (pH e turbidez), enviando os dados para um dashboard web.
- **Problema / oportunidade:** Em fazendas de pequeno e médio porte, a água dos bebedouros costuma vir de poços, açudes ou outros corpos d'água, que podem estar contaminados por microrganismos, bactérias, lodo ou terra. Isso aumenta o risco de doenças, mau desenvolvimento e até morte dos animais. Checar a qualidade da água e manter o cocho abastecido de forma manual é trabalhoso e nem sempre é feito com a frequência necessária. O projeto resolve esses dois pontos automatizando o reabastecimento e a medição da qualidade da água.

## 2. Definição dos Requisitos

**Funcionais (o que o sistema deve fazer)**
- Medir o nível da água do bebedouro.
- Acionar a bomba automaticamente quando o nível estiver abaixo do mínimo e desligá-la ao atingir o nível adequado.
- Medir o pH da água após o reabastecimento.
- Medir a turbidez da água.
- Enviar as leituras (nível, pH e turbidez) via MQTT para o dashboard Adafruit IO.

**Não funcionais (desempenho, segurança, usabilidade)**
- As leituras devem ser atualizadas no dashboard a cada 10 segundos.
- O sistema deve continuar funcionando localmente mesmo com a internet instável.
- O dashboard deve ser acessível pelo celular.

**Restrições técnicas / operacionais**
- O ESP32 opera em 3.3V, enquanto os sensores e a bomba operam em 5V/9V, o que exige adequação de tensão (divisor de tensão para as entradas e step-up MT3608 para a bomba).
- Depende de uma rede Wi-Fi disponível no local de instalação.
- Os sensores de pH e de turbidez precisam de calibração antes do uso.

## 3. Materiais e Tecnologias Necessárias

**Hardware:** ESP32, sensor ultrassônico JSN-SR04T, sensor de pH 4502C, sensor de turbidez, módulo relé, bomba d'água, módulo step-up MT3608, fonte 9V, jumpers e protoboard.

**Software:** PlatformIO + VS Code, framework Arduino (espressif32), Adafruit IO (dashboard via MQTT), Git e GitHub.

> Detalhamento completo em [02_Lista_de_Materiais.md](02_Lista_de_Materiais.md) e [04_Softwares_e_Versoes.md](04_Softwares_e_Versoes.md).

## 4. Análise de Riscos

| Risco | Tipo | Estratégia de mitigação |
|-------|------|--------------------------|
| Danificar o ESP32 por tensão incompatível (3.3V x 5V/9V) | Técnico | Divisor de tensão nas entradas, step-up para a bomba e conferência das ligações antes de energizar |
| Contato da água com a parte eletrônica | Técnico | Isolar e vedar as conexões; manter a eletrônica afastada do cocho |
| Leituras imprecisas de pH e turbidez | Técnico | Calibrar os sensores com soluções de referência |
| Bomba não desligar e transbordar | Técnico | Lógica com nível mínimo e máximo e tempo limite de acionamento |
| Atraso na chegada de componentes | Cronograma | Comprar com antecedência e testar por partes |
| Projeto individual (sobrecarga / falta de conhecimento) | Humano | Dividir em entregas pequenas e estudar cada parte antes de implementar |

## 5. Cronograma de Execução

| Fase | Descrição | Período / Estimativa |
|------|-----------|----------------------|
| Planejamento | Definição de requisitos e materiais | Semana 1 |
| Prototipagem | Montagem do circuito e desenvolvimento do firmware | Semanas 2 a 4 |
| Testes | Calibração e validação dos sensores e da bomba | Semanas 5 e 6 |
| Ajustes | Correções e melhorias | Semana 7 |
| Documentação e entrega | Organização do repositório e apresentação | Semana 8 |

## 6. Divisão de Tarefas

Projeto individual. Todas as etapas são de responsabilidade de Matheus Viganó Schirrmann:
- Montagem do circuito (hardware)
- Desenvolvimento do firmware (ESP32)
- Integração com o dashboard (Adafruit IO)
- Documentação do projeto

## 7. Referências e Inspirações

- Repositórios-modelo da disciplina (ex: Horta Automática, Estação Meteorológica IoT)
- Documentação do Adafruit IO
- Documentação do PlatformIO
- Blog da Robótica — Sensor de turbidez com Arduino: https://www.blogdarobotica.com/2023/01/10/como-utilizar-o-modulo-sensor-de-turbidez-de-particulas-suspensas-na-agua-com-arduino/
- Usinainfo — Sensor de pH: como calibrar e configurar: https://www.usinainfo.com.br/blog/sensor-de-ph-arduino-como-calibrar-e-configurar/
- Vídeo de apoio: https://www.youtube.com/watch?v=nT6Q5atNLJM
- Manual de instrução do PH: https://cdn.awsli.com.br/969/969921/arquivos/ph-sensor-ph-4502c.pdf
- Datasheet do Sensor de turbidez (Note que é o datasheet do mesmo sensor porém com outro módulo): https://cdn.awsli.com.br/969/969921/arquivos/ph-sensor-ph-4502c.pdf 

## 8. Expectativas de Resultado

- **Produto final esperado:** bebedouro funcional que reabastece sozinho e exibe nível, pH e turbidez no dashboard.
- **Como será validado / testado:** comparar as leituras dos sensores com medições manuais (por exemplo, medir o pH com um medidor de referência) e testar o acionamento da bomba em diferentes níveis de água.
- **Critérios de sucesso:** os três parâmetros lidos corretamente, a bomba ligando e desligando nos níveis certos, e os dados aparecendo no dashboard de forma remota.
