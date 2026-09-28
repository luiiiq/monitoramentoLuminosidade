# Sistema de Monitoramento de Luminosidade - Vinheria Agnello

Este projeto consiste em um sistema automatizado de monitoramento de luminosidade desenvolvido para a **Vinheria Agnello**. O objetivo principal é garantir a integridade e a qualidade dos vinhos armazenados, prevenindo a exposição excessiva à luz (especialmente raios ultravioletas), fator que pode desencadear reações químicas indesejadas em vinhos brancos e espumantes.

O sistema utiliza a plataforma Arduino (baseada no microcontrolador **ATmega328P**) para coletar dados em tempo real, gerenciar alertas visuais/sonoros e exibir informações cruciais em um display de cristal líquido (LCD).

# Funcionalidades do Desafio 1

- **Monitoramento de Luz:** Captura da luminosidade ambiente utilizando um sensor LDR e o conversor Analógico/Digital (ADC) interno do ATmega328P.
- **Tratamento de Dados:** Conversão analógica parametrizada utilizando a função `map()` para exibir a luminosidade em uma escala percentual de **0% a 100%**. Os limites são calculados com base em valores médios para evitar falsos alarmes.
- **Interface Visual (LCD):** Exibição obrigatória do logotipo da Vinheria Agnello acompanhado de uma mensagem de boas-vindas na inicialização do sistema.
- **Sistema de Alarme Visual por LEDs:**
  - 🟢 **LED Verde:** Ambiente OK (luminosidade dentro do limite ideal).
  - 🟡 **LED Amarelo:** Nível de Alerta (luminosidade média atingida).
  - 🔴 **LED Vermelho:** Problema Detectado (luminosidade alta: ERROR!).
- **Alarme Sonoro (Buzzer):** Ativado por **3 segundos** assim que o nível de alerta (LED Amarelo) é atingido, voltando a soar caso a luminosidade permaneça instável ou inadequada.
- **Alarme Sonoro (Buzzer - ERROR):** Ativado quando a luminosidade atinge o nível crítico (LED vermelho), emitindo alertas sonoros em intervalos menores e repetidamente enquanto o ambiente permanecer nesse estado.

## Componentes Utilizados (Hardware)

* 1x Microcontrolador ATmega328P (Placa Arduino Uno R3)
* 1x Display LCD 16x2 (com I2C)
* 1x Sensor de Luz LDR (Resistor Dependente de Luz)
* 1x Buzzer Piezoelétrico
* 1x LED Verde
* 1x LED Amarelo
* 1x LED Vermelho
* 4x Resistores (Valores adequados para os LEDs e o divisor de tensão do LDR)
* 1x Protoboard e Jumpers de conexão

## Dependências e Bibliotecas (Software)
* **LiquidCrystal_I2C** (Biblioteca responsável pelo controle do display LCD por meio da comunicação I2C.)
* **Wire** (Biblioteca utilizada para a comunicação I2C entre o Arduino e o display LCD.)
*  **Configuração do Ambiente (PlatformIO)**
  Este projeto utiliza o **PlatformIO** no VS Code para o desenvolvimento do firmware do Arduino. Para que o código compile corretamente sem erros de importação, preste atenção aos seguintes pontos:
  O PlatformIO é muito rígido com a organização dos arquivos. O arquivo principal de código **`main.cpp`** deve ficar solto obrigatoriamente dentro da pasta raiz **`src/`**, e **NÃO** dentro de subpastas (como `src/arduino/main.cpp`).
Se o seu arquivo estiver no lugar errado, basta arrastá-lo diretamente para a raiz da pasta `src/` pelo explorador do VS Code.
  Se o VS Code exibir uma linha vermelha de erro embaixo do `#include <LiquidCrystal_I2C.h>`, siga estes passos para resolver:
  1. Abra o arquivo **`platformio.ini`** na raiz do projeto.
  2. Adicione a dependência **`lib_deps`** logo abaixo das configurações da sua placa:
```ini
[env:uno]
platform = atmelavr
board = uno
framework = arduino
lib_deps = marcoschwartz/LiquidCrystal_I2C @ ^1.1.4
```
  3. Salve o arquivo (`Ctrl + S`) para que o PlatformIO baixe os arquivos automaticamente.
  4. Se a linha vermelha continuar aparecendo, force a atualização do VS Code:
   * Pressione **`Ctrl + Shift + P`**
   * Digite: `PlatformIO: Rebuild IntelliSense Index`
   * Pressione **`Enter`**

## Linguagem Utilizada
<img
  align="left" 
  alt="c++" 
  title="c++"
  width="30px" 
  style="padding-right: 10px;" 
  src="https://cdn.jsdelivr.net/gh/devicons/devicon@latest/icons/cplusplus/cplusplus-original.svg" 
/>
<img
  align="left" 
  alt="JavaScript" 
  title="JavaScript"
  width="30px" 
  style="padding-right: 10px;" 
  src="https://cdn.jsdelivr.net/gh/devicons/devicon@latest/icons/javascript/javascript-plain.svg" 
/>
<br>

## Como Usar e Executar o Projeto

### 1. Simulação no WOKWI
Caso queira testar a lógica antes de montar o circuito físico:
1. Acesse o [projeto no WOKWI](https://wokwi.com/projects/475776420176598017).
2. Certifique-se que a biblioteca LiquidCrystal I2C esteja instalada.
3. Clique no botão verde de iniciar a simulação (Start the Simulation).
4. Aguarde a animação de abertura da folha e a apresentação do logotipo da equipe CALM TECH TEAM.
5. Após a abertura, observe o monitoramento dos níveis de luminosidade no LCD, os LEDs indicadores e os alertas sonoros.
6. Altere a intensidade de luz do sensor LDR na simulação para observar as mudanças de indicação conforme a luminosidade.

### 2. Execução Física (Arduino IDE)
1. Conecte o seu Arduino Uno ao computador via cabo USB.
2. Abra a **Arduino IDE** e carregue o arquivo de código principal do projeto.
3. Instale as dependências de display necessárias através do Gerenciador de Bibliotecas.
4. Selecione a Placa (`Arduino Uno`) e a Porta COM correta nas configurações da IDE.
5. Clique em **Carregar (Upload)** para gravar o código no microcontrolador.

### 3. Vídeo do Projeto 1.0

Para visualizar a apresentação e o funcionamento do projeto, acesse o vídeo pelo link abaixo:

[Acessar o vídeo do trabalho](https://youtu.be/xalAVg7U42U)

### 4. Vídeo do Projeto 2.0

Mesma ideia do Projeto 1.0. Porém, com interface no Display e na tela do computador, usando a metodologia do Digital Twin.

[Acessar o vídeo do trabalho 2.0](https://youtu.be/BvonR4OcRyg)

## Integrantes do Grupo CALM  TECH:
* **Nome do Aluno 1** - Caio Fernando De Deus Gomes
* **Nome do Aluno 2** - Amanda Souza de Barros
* **Nome do Aluno 3** - Luiza de Freitas Benevides
* **Nome do Aluno 4** - Mariana do Nascimento
