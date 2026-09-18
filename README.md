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

## Componentes Utilizados (Hardware)

* 1x Microcontrolador ATmega328P (Placa Arduino Uno R3)
* 1x Display LCD 16x2 (com ou sem módulo I2C)
* 1x Sensor de Luz LDR (Resistor Dependente de Luz)
* 1x Buzzer Piezoelétrico
* 1x LED Verde
* 1x LED Amarelo
* 1x LED Vermelho
* 4x Resistores (Valores adequados para os LEDs e o divisor de tensão do LDR)
* 1x Protoboard e Jumpers de conexão

## Dependências e Bibliotecas (Software)
* **LiquidCrystal** (Padrão para controle do display LCD via pinos paralelos)

## Linguagem Utilizada
<img
  align="left" 
  alt="CSS" 
  title="CSS"
  width="30px" 
  style="padding-right: 10px;" 
  src="https://cdn.jsdelivr.net/gh/devicons/devicon@latest/icons/cplusplus/cplusplus-original.svg" 
/><br>

## Como Usar e Executar o Projeto

### 1. Simulação no Tinkercad
Caso queira testar a lógica antes de montar o circuito físico:
1. Acesse o ambiente do [Tinkercad Circuits](https://www.tinkercad.com/things/71KqeWCbZWd-projeto-sistema-de-monitoramento-luminosidade).
2. Monte os componentes seguindo o diagrama elétrico construído ou importe o arquivo de design.
3. Copie o código presente no arquivo principal deste repositório e cole na aba de código do Tinkercad.
4. Clique em **Iniciar Simulação**.

### 2. Execução Física (Arduino IDE)
1. Conecte o seu Arduino Uno ao computador via cabo USB.
2. Abra a **Arduino IDE** e carregue o arquivo de código principal do projeto.
3. Instale as dependências de display necessárias através do Gerenciador de Bibliotecas.
4. Selecione a Placa (`Arduino Uno`) e a Porta COM correta nas configurações da IDE.
5. Clique em **Carregar (Upload)** para gravar o código no microcontrolador.

## Integrantes do Grupo CALM  TECH:
* **Nome do Aluno 1** - Caio Fernando De Deus Gomes
* **Nome do Aluno 2** - Amanda Souza de Barros
* **Nome do Aluno 3** - Luiza de Freitas Benevides
* **Nome do Aluno 4** - Mariana do Nascimento
