\# GoHobby Servo Converter (PIC12F1840)



Este projeto consiste em um firmware desenvolvido em C para o microcontrolador \*\*PIC12F1840\*\*, projetado para ler o sinal PWM de um canal do receptor de controle remoto de um drone GoHobby e convertê-lo/mapeá-lo em um sinal PWM padrão para controle de servomotores de 0 a 180 graus.



\## 📌 Funcionalidades

\* \*\*Leitura de Pulso de Entrada:\*\* Captura e decodifica a largura de pulso (geralmente entre 1ms e 2ms) vinda do receptor do drone.

\* \*\*Mapeamento de Sinal:\*\* Converte a faixa de entrada dinamicamente para os tempos de ciclo de um servomotor mecânico padrão (0° a 180°).

\* \*\*Saída PWM Estabilizada:\*\* Gera o sinal de saída na frequência correta de operação dos servos (50Hz).



\## 🛠️ Tecnologias e Ferramentas

\* \*\*Ambiente de Desenvolvimento:\*\* MPLAB X IDE

\* \*\*Compilador:\*\* Microchip XC8

\* \*\*Microcontrolador:\*\* Microchip PIC12F1840



\## 🔌 Conexões do Circuito (Pinagem)

\* \*\*VCC:\*\* 5V (Garantir alimentação regulada para o PIC)

\* \*\*GND:\*\* Terra comum (interligado com a bateria/ESC do drone e o servo)

\* \*\*Entrada (Signal In):\*\* Pino RC\_IN \_\[Atualizar com o pino correto, ex: RA2]\_ <- Conectado ao receptor do Drone

\* \*\*Saída (Servo Out):\*\* Pino SERVO\_OUT \_\[Atualizar com o pino correto, ex: RA0]\_ -> Conectado ao sinal do Servo



\## 🚀 Como clonar e compilar

1\. Clone o repositório em sua pasta de projetos:

&#x20;  ```bash

&#x20;  git clone https://github.com

&#x20;  ```

2\. Abra o MPLAB X IDE.

3\. Vá em \*\*File > Open Project\*\* e selecione a pasta `GoHobby\_Servo.X`.

4\. Certifique-se de ter o compilador XC8 instalado e configurado nas propriedades do projeto.

5\. Clique em \*\*Clean and Build\*\*.



