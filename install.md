💻 Passo a Passo: Instalando o Software no Computador

Para gravar os códigos nas placas Heltec WiFi LoRa 32 V2, utilizaremos o programa oficial chamado Arduino IDE. 

Siga este guia visual e prático:

Passo 1: Baixar e Instalar o Arduino IDE

* Acesse o site oficial do Arduino no seu navegador.
* Baixe a versão mais recente do Arduino IDE compatível com o seu sistema operacional (Windows, Mac ou Linux).
* Instale o programa avançando em todas as telas padrão ("Avançar", "Instalar").



Passo 2: Configurar o Suporte para Placas ESP32

O programa vem configurado de fábrica apenas para placas Arduino comuns. Precisamos ensinar o programa a reconhecer o chip ESP32 da Heltec.

* Abra o Arduino IDE.
* No menu superior, clique em Arquivo -> Preferências.
* Localize o campo chamado "URLs do Gerenciador de Placas Adicionais".
* Copie e cole exatamente o link abaixo nesse campo:

&#x09;https://githubusercontent.com

* Clique em OK.



Passo 3: Instalar o Pacote de Placas da Heltec

* No menu esquerdo do programa, clique no ícone que se parece com uma placa de circuito (ou vá em Ferramentas -> Placa -> Gerenciador de Placas).
* Na barra de pesquisa que aparecer no topo, digite: ESP32.
* Procure pelo pacote chamado esp32 da Espressif Systems ou Heltec ESP32 Series Dev-boards.
* Clique no botão Instalar e aguarde o processo terminar (pode levar alguns minutos).



Passo 4: Instalar as Bibliotecas Necessárias

Para que o rádio LoRa e a tela OLED funcionem, precisamos instalar os "manuais de instrução" dessas peças dentro do programa.

* No menu esquerdo, clique no ícone que se parece com livros numa estante (ou vá em Ferramentas -> Gerenciar Bibliotecas).
* Na barra de pesquisa, digite exatamente: LoRa Sandeep Mistry.
* Encontre a biblioteca chamada apenas LoRa (feita por Sandeep Mistry) e clique em Instalar.
* Limpe a barra de pesquisa e digite: ESP32 OLED Driver For SSD1306.
* Encontre a biblioteca criada por ThingPulse (ou Daniel Eichhorn) e clique em Instalar.



Passo 5: Conectar a Placa e Configurar o Programa

* Pegue uma de suas placas Heltec e conecte-a ao computador usando um cabo USB de boa qualidade (que transmita dados, não apenas energia).
* No menu superior do Arduino IDE, vá em Ferramentas -> Placa -> ESP32 Arduino e selecione WiFi LoRa 32(V2).
* Volte em Ferramentas -> Porta e selecione a porta que apareceu ativa (Geralmente aparece como COM3, COM4, etc. no Windows).



🚀 Como Gravar o Código na Placa:

* Apague todo o texto padrão que vem na tela do Arduino IDE.
* Copie um dos códigos (por exemplo, o da Placa Emissora) e cole dentro do programa.
* Altere o nome e a senha do seu Wi-Fi nas linhas correspondentes.
* Clique no botão de Seta para a direita (-->) localizado no canto superior esquerdo do programa. Esse botão compila o código e envia para a placa.
* Quando o rodapé do programa exibir a mensagem "Concluído a carregar", sua placa já estará programada!



📦 Componentes Necessários

01 Contatora de Potência: Modelo padrão (ex: corrente de 9A, 12A ou 18A) com Bobina de 220V (identificada pelos pinos A1 e A2).

01 Disjuntor Termomagnético: Para proteção do circuito da bomba (recomendado de 10A ou 16A bipolar).

Fios Elétricos: Fios grossos (2,5 mm²) para a bomba e fios finos (0,75 mm² ou 1 mm²) para o comando do relé.



🔌 Manual de Ligação Elétrica (Passo a Passo)

Certifique-se de que a rede elétrica geral do sítio esteja totalmente desligada antes de mexer nos fios de 220V.

\##1. Circuito de Força (Energia da Bomba d'Água)

Este é o caminho onde passa a corrente pesada que vai alimentar o motor da bomba:

* Traga os dois fios da rede elétrica de 220V (Fase 1 e Fase 2) e ligue-os na entrada do seu Disjuntor de proteção.
* Saia com dois fios do Disjuntor e ligue-os nos bornes superiores da contatora, chamados 1/L1 e 3/L2.
* Conecte os dois fios que vão para a sua Bomba d'Água nos bornes inferiores da contatora, chamados 2/T1 e 4/T2.2. 



\##2. Circuito de Comando (Ligação do Relé na Contatora)

Este circuito usa o relé azul de 5V da placa LoRa para injetar energia na bobina da contatora, fazendo com que ela "atraque" (feche os contatos de força):

* Puxe um fio de uma das Fases 220V (pode puxar direto da saída do disjuntor) e ligue-o diretamente no borne A1 da bobina da contatora.
* Puxe um fio da outra Fase 220V e ligue-o no borne central da sua placa de relé azul (geralmente identificado como COM ou Comum).
* Saia com um fio do borne NO (Normally Open ou Normalmente Aberto) da placa de relé e ligue-o no borne A2 da bobina da contatora.





