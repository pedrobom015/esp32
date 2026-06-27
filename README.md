# esp32

\#Esp32 para controle de iluminação e bomba d´água do sítio.



Essa arquitetura é excelente para o seu sítio. Ela evita que você precise passar fios longos entre o poste de iluminação e a bomba d'água, deixando cada ponto totalmente isolado a muitos metros de distância da casa.

Para fazer isso funcionar sem que uma placa interfira na outra, usaremos endereços ou prefixos de texto nos comandos de rádio. O emissor enviará o comando para o ar, e cada receptora só executará a ordem se ler o seu próprio nome.



\##Passo a Passo: Instalando o Software no Computador

Para gravar os códigos nas suas placas Heltec WiFi LoRa 32 V2, utilizaremos o programa oficial chamado Arduino IDE. Siga este guia visual e prático:

\###Passo 1: Baixar e Instalar o Arduino IDE

* Acesse o site oficial do Arduino no seu navegador.
* Baixe a versão mais recente do Arduino IDE compatível com o seu sistema operacional (Windows, Mac ou Linux).
* Instale o programa avançando em todas as telas padrão ("Avançar", "Instalar").



\###Passo 2: Configurar o Suporte para Placas ESP32

O programa vem configurado de fábrica apenas para placas Arduino comuns. Precisamos ensinar o programa a reconhecer o chip ESP32 da Heltec.

* Abra o Arduino IDE.
* No menu superior, clique em Arquivo -> Preferências.
* Localize o campo chamado "URLs do Gerenciador de Placas Adicionais".
* Copie e cole exatamente o link abaixo nesse campo:

&#x09;https://githubusercontent.com

* Clique em OK.
* 

\###Passo 3: Instalar o Pacote de Placas da Heltec

* No menu esquerdo do programa, clique no ícone que se parece com uma placa de circuito (ou vá em Ferramentas -> Placa -> Gerenciador de Placas).
* Na barra de pesquisa que aparecer no topo, digite: ESP32.
* Procure pelo pacote chamado esp32 da Espressif Systems ou Heltec ESP32 Series Dev-boards.
* Clique no botão Instalar e aguarde o processo terminar (pode levar alguns minutos).



\###Passo 4: Instalar as Bibliotecas Necessárias

Para que o rádio LoRa e a tela OLED funcionem, precisamos instalar os "manuais de instrução" dessas peças dentro do programa.

* No menu esquerdo, clique no ícone que se parece com livros numa estante (ou vá em Ferramentas -> Gerenciar Bibliotecas).
* Na barra de pesquisa, digite exatamente: LoRa Sandeep Mistry.
* Encontre a biblioteca chamada apenas LoRa (feita por Sandeep Mistry) e clique em Instalar.
* Limpe a barra de pesquisa e digite: ESP32 OLED Driver For SSD1306.
* Encontre a biblioteca criada por ThingPulse (ou Daniel Eichhorn) e clique em Instalar.



\###Passo 5: Conectar a Placa e Configurar o Programa

* Pegue uma de suas placas Heltec e conecte-a ao computador usando um cabo USB de boa qualidade (que transmita dados, não apenas energia).
* No menu superior do Arduino IDE, vá em Ferramentas -> Placa -> ESP32 Arduino e selecione WiFi LoRa 32(V2).
* Volte em Ferramentas -> Porta e selecione a porta que apareceu ativa (Geralmente aparece como COM3, COM4, etc. no Windows).



\##🚀 Como Gravar o Código na Placa:

* Apague todo o texto padrão que vem na tela do Arduino IDE.
* Copie um dos códigos que te passei anteriormente (por exemplo, o da Placa Emissora) e cole dentro do programa.
* Altere o nome e a senha do seu Wi-Fi nas linhas correspondentes.
* Clique no botão de Seta para a direita (-->) localizado no canto superior esquerdo do programa. Esse botão compila o código e envia para a placa.
* Quando o rodapé do programa exibir a mensagem "Concluído a carregar", sua placa já estará programada!



\##🔌 Esquema de Ligação Física nos Receptores

Como agora as placas são independentes, a ligação física ficou ainda mais simples e idêntica em ambos os lados:

* ESP32 Receptor 1 (Bomba) / ESP32 Receptor 2 (Luz):

  * Fio do pino 5V do ESP32 vai para o VCC do módulo de relé.
  * Fio do pino GND do ESP32 vai para o GND do módulo de relé.
  * Fio do pino GPIO 13 do ESP32 vai para o IN1 do módulo de relé.



