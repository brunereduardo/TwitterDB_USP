# TwitterDB_USP

![TwitterSGDB](https://jornalggn.com.br/sites/default/files/2020/11/pesquisa-mostra-que-75-das-pessoas-acompanham-politica-pelo-twitter-twitterr.jpeg)

#### [English version here!](https://github.com/brunereduardo/TwitterDB_USP/blob/main/README_en.md)

## Descrição do Projeto
<p align="justify"> AQUI</p>


<p align="center">
<a href="#Descrição-do-Projeto">Descrição do Projeto</a> •  
<a href="#Pré-requisitos">Pré-requisitos</a> •	
<a href="#Funções">Funções</a> •
<a href="#Licença">Licença</a> • 
<a href="#Autores">Autores</a>
</p>

<h4 align="center"> 
	🚧  Construído durante a matéria de Estrutura de Dados 🚧 BTREEs são necessárias para escalar o código 🚧
</h4>

### Pré-requisitos

Para começar a se aventurar pelo projeto você vai precisar instalar em sua máquina as seguintes ferramentas:
[Git](https://git-scm.com), [Node.js](https://nodejs.org/en/). 
Além disto, um editor para trabalhar com o código como [VSCode](https://code.visualstudio.com/) servirá para todos os propósitos. Se você utilizar algum sistema operacional baseado em Linux, todas as bibliotecas necessárias já vem instaladas e você pode acessar suas definições através do comando ```man```. Se você utilizar um  sistema Windows será interessante pesquisar pelo Windows Subsystem for Linux (WSL) para facilitar sua vida em relação à  instalações de IDEs e Cygwin para compilar e rodar a aplicação.

### Rodando a Aplicação 🎲

```bash
# Clone este repositório
$ git clone https://github.com/brunereduardo/TwitterDB_USP

# Acesse a pasta do projeto no terminal/cmd
$ cd TwitterDB_USP/Codes

# Compile os arquivos .c e .h em um arquivo objeto com o segunite comando
$ gcc main.c fun.c fun.h arq.c arq.h ed.c ed.h help.c help.h -o app

# Execute a aplicação com o segunite comando
$ ./app

# Há um aqruivo Makefile no diretório que pode ser usado para contruir a aplicação via terminal com o comando make
```

### Funções

1. [X]  Permita a leitura de vários registros obtidos a partir de um arquivo de entrada (arquivo no formato .csv), e a gravação desses registros em um arquivo de dados de saída em formato binário, bem como um arquivo de saída binário com a indexação dos registros.
2. [X] Permita a recuperação dos dados, de todos os registros, armazenados no arquivo de dados pessoa, mostrando os dados de forma organizada na saída padrão para permitir a distinção dos campos e registros
3. [X]  Permita a busca dos dados de todos os registros do arquivo pessoa que satisfaçam um critério de busca determinado pelo usuário (idPessoa utilizando o arquivo indexaPessoa.bin; todos todos os registros de uma determinada idade; nomePessoa; TwitterPessoa)
4. [X] Permita a inserção de registros adicionais, baseado na abordagem estática de registros logicamente removidos
5. [ ]  Permita a atualização de um ou mais campos de um ou mais registros do arquivo de dados pessoa que foram recuperados por meio da funcionalidade de busca. Esta funcionalidade deve ser executada n vezes seguidas. Em situações nas quais não sejam encontrados registros, ou seja, caso a solicitação do usuário não retorne nenhum registro a ser atualizado, o programa deve continuar a executar as atualizações até completar as n vezes seguidas.
6. [x] Permita a leitura de vários registros obtidos a partir de um arquivo de entrada (arquivo no formato .csv), que contém os IDs de cada usuário, datas (de quando uma pessoa seguiu ou deixou de seguir outra) e o grau de amizade. A gravação desses registros deveser feita de de forma binária em um arquivo de dados de saída.
7. [X] Ordene o arquivo de dados de acordo com o campo de ordenação idPessoaQueSegue. Quando houver empate para os valores de idPessoaQueSegue, deve ser usado como critério de desempate o campo idPessoaQueESeguida e, caso ainda haja empate, deve ser usado como critério de desempate o campo dataInicioQueSegue e, caso ainda haja empate, deve ser usado como critério de desempate o campo dataFimQueSegue. A ordenação deve ser implementada considerando que o arquivo de dados segue cabe totalmente em memória primária (RAM). Portanto, o arquivo deve ser: (i) lido inteiramente do disco para a RAM; (ii) ordenado de acordo com a chave de ordenação usando-se qualquer algoritmo de ordenação disponível na biblioteca da linguagem C; e (iii) escrito inteiramente para disco novamente, gerando um novo arquivo de dados segueOrdenado, que encontra-se ordenado de acordo com o campo de ordenação. O arquivo de dados segue original não deve ser removido.
8. [X] Estenda a funcionalidade busca para recuperar os dados armazenados no arquivo de dados pessoa associados aos dados no arquivo de dados segue, mostrando os dados de forma organizada na saída padrão para permitir a distinção dos campos e registros. Esta funcionalidade equivale a uma operação de junção, desde que ela “junta” dados de registros de dois arquivos usando com base em um campo de igualdade (condição de junção).
9. [X] Permita a recuperação dos dados, de todos os registros, armazenados em arquivos de dados no formato binário e a geração de um grafo contendo esses dados na forma de um conjunto de vértices V e um conjunto de arestas A. A representação do grafo deve, obrigatoriamente, ser na forma de listas de adjacências
10.[X] Gere o grafo transposto do grafo gerado na funcionalidade anterior. 
11. [ ] Determine o caminho mais curto entre cada pessoa que segue e uma determinada celebridade definida como parâmetro de entrada. Essa funcionalidade consiste em determinar os caminhos mais curtos com destino único.
12. [ ] Essa funcionalidade consiste em determinar se existe um ciclo no grafo, ou seja, se existe um caminho no qual o primeiro e o último vértices são iguais. No caso dessa funcionalidade, o primeiro e o último vértices devem ser correspondentes ao nome da pessoa que foi passado como parâmetro de entrada (Busca em profundidade).
13. [X] Tratamentos dos dados e tratamento de erros

### 🚀 Tecnologias

As seguintes estruturas de dados, ferramentas e bibliotecas foram usadas na construção do projeto:

- Lista encadeada
- Digrafo (grafo direcional)
- Hexdump
- Valgrind
- String.h
- Stdio.h
- Stdlib.h

### Licença

<p>Este projeto está sob a licença MIT, para mais informações procurar pelo arquivo <a href = "https://github.com/brunereduardo/NextLevelWeek_2/blob/master/LICENSE">LICENSE</a></p>

### Autores
Implementado e criado com ❤️ por [Bruner Eduardo Augusto Albrecht](https://github.com/brunereduardo) | [Felipe Oliveira](https://github.com/felipeoliveir4) 👋🏽
