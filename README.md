## Dicionário de Frequências
O projeto "Dicionários" consiste na implementação de dicionários de ocorrência baseados em quatro estruturas de dados específicas: árvore binária AVL, árvore binária rubro-negra, tabela hash por encadeamento exterior e tabela hash por endereçamento aberto. O propósito principal desse projeto é receber um arquivo .txt, percorrê-lo, contar a incidência de cada palavra dentro do texto, ignorando sinais de pontuação, e gerar um novo arquivo contendo cada palavra e seu respectivo número referente à quantidade de vezes que ela apareceu no texto. 

## Como executar
Para executar este projeto, é necessário ter instalada, na máquina, a biblioteca ICU. Após garantir isso, abra seu terminal na raiz do projeto e navegue até o diretório /src do projeto:

`cd \Dicionario\src`

Então, gere um arquivo executável pelo terminal:

Caso esteja compilando em uma máquina UNIX:

`g++ -Wall -Wextra main.cpp -std=gnu++17 -licuuc -licui18n -o programa`

Caso esteja compilando em uma máquina Windows:

`g++ -Wall -Wextra main.cpp -std=gnu++17 -IC:/icu/include -LC:/icu/lib -licuuc -licuin -o programa`

Note que os campos `-IC:/icu/include` e `-LC:/icu/lib` são caminhos para determinados diretórios, então lembre-se de verificar em que local os arquivos do ICU foram instalados em sua máquina [`-I` busca a pasta onde estão os headers (arquivos `.h`) e `-L` busca a pasta onde estão as bibliotecas (arquivos `.a`, `.lib`, `.dll.a`)].

Por último, execute o arquivo `programa`, passando os seguintes parâmetros no terminal:

`.\programa <structure_type> <file_in> <file_out>`

#### \<structure_type\>: dicAVL, dicRB, dicChainedHash ou dicOpenHash
#### \<file_in\>: qualquer arquivo .txt presente no diretório do projeto
#### \<file_out\>: um nome qualquer de arquivo

Exemplo de execução:

`.\programa dicAVL files/kjv-bible.txt  bible-avl.txt`

Isso irá gerar um arquivo .txt na pasta `results` com o nome `bible-avl` contendo a contagem de frequência de cada palavra do arquivo `kjv-bible`, além de informações sobre as métricas implementadas no dicionário da AVL e a apresentação de quanto tempo (em segundos) a construção do dicionário em questão levou.

## Documentação
A documentação de toda a implementação está na pasta docs.
