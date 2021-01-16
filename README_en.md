# TwitterDB_USP

![TwitterSGDB](https://jornalggn.com.br/sites/default/files/2020/11/pesquisa-mostra-que-75-das-pessoas-acompanham-politica-pelo-twitter-twitterr.jpeg)

## Project description
<p align="justify">The project aims to store and retrieve data related to people who follow people on twitter. In order to meet the requirements of a good database design, two data files are defined to be used in practical work: personal data file and data file follows. So implement a program through which the user can obtain data from an input binary file, be able to use the functions described below to generate the output files and generate a directed graph, which can be used to perform interesting investigations within the context of social networks.</p>


<p align="center">
<a href="#Project-description">Project description</a> •  
<a href="#Prerequisites">Prerequisites</a> •	
<a href="#Features">Features</a> •
<a href="#License">License</a> • 
<a href="#Authors">Authors</a>
</p>

<h4 align="center"> 
	🚧  Built during the course of Data Structure 🚧 BTREEs are needed to scale the code 🚧
</h4>

### Prerequisites

To start venturing through the project you will need to install the following tools on your pc:
[Git](https://git-scm.com) and an editor to work with the code, like [VSCode](https://code.visualstudio.com/), which will serve all purposes. If you use any Linux-based operating system, all the necessary libraries are already installed and you can access their definitions through the `` man`` command. If you use a Windows system it will be interesting to search for Windows Subsystem for Linux (WSL) to make your life easier in relation to the IDEs and Cygwin installations to compile and run the application.

### Running the Application  🎲

```bash
# Clone this repository
$ git clone https://github.com/brunereduardo/TwitterDB_USP

# Access the project folder on terminal/cmd
$ cd TwitterDB_USP/Codes

# Compile the .c and .h files into an object file with the following command
$ gcc main.c fun.c fun.h arq.c arq.h ed.c ed.h help.c help.h -o app

# Run the application with the following command to inject any test case and compare the output with the .out files
$ ./app < test.in

# There is a Makefile in the directory that can be used to build the application via terminal with the make command
```

### Features

1. [X]  Faz a leitura de vários registros obtidos a partir de um arquivo de entrada (no formato .csv), e a gravação destes em um arquivo de dados de saída em formato binário, bem como um arquivo de saída binário com a indexação dos registros.
2. [X] Permite a recuperação dos dados, de todos os registros, armazenados no arquivo de dados pessoa, mostrando os dados de forma organizada na saída padrão para permitir a distinção dos campos e registros
3. [X]  Faz a busca dos dados de todos os registros do arquivo pessoa que satisfaçam um critério de busca determinado pelo usuário (idPessoa utilizando o arquivo indexaPessoa.bin, ou todos os registros de uma determinada idade, bem como nomePessoa e TwitterPessoa)
4. [X] Permite a inserção de registros adicionais, baseado na abordagem estática de registros logicamente removidos
5. [ ] Atualiza um ou mais campos de um ou mais registros do arquivo de dados pessoa, que foram recuperados por meio da funcionalidade de busca. Essa funcionalidade deve ser executada n vezes seguidas. Em situações nas quais não sejam encontrados registros, ou seja, caso a solicitação do usuário não retorne nenhum registro a ser atualizado, o programa deve continuar a executar as atualizações até completar as n vezes seguidas.
6. [x] Lê de vários registros obtidos a partir de um arquivo de entrada (arquivo no formato .csv), que contém os IDs de cada usuário, datas (de quando uma pessoa seguiu ou deixou de seguir outra) e o grau de amizade. A gravação desses registros deveser feita de de forma binária em um arquivo de dados de saída.
7. [X] Ordene o arquivo de dados de acordo com o campo de ordenação idPessoaQueSegue. Quando houver empate para os valores de idPessoaQueSegue, deve ser usado como critério de desempate o campo idPessoaQueESeguida e, caso ainda haja empate, deve ser usado como critério de desempate o campo dataInicioQueSegue e, caso ainda haja empate, deve ser usado como critério de desempate o campo dataFimQueSegue. A ordenação deve ser implementada considerando que o arquivo de dados segue cabe totalmente em memória primária (RAM). Portanto, o arquivo deve ser: (i) lido inteiramente do disco para a RAM; (ii) ordenado de acordo com a chave de ordenação usando-se qualquer algoritmo de ordenação disponível na biblioteca da linguagem C; e (iii) escrito inteiramente para disco novamente, gerando um novo arquivo de dados segueOrdenado, que encontra-se ordenado de acordo com o campo de ordenação. O arquivo de dados segue original não deve ser removido.
8. [X] Utilizando a funcionalidade de busca, para recuperar os dados armazenados no arquivo de dados pessoa associados aos dados no arquivo de dados segue, mostrar os dados de forma organizada na saída padrão para permitir a distinção dos campos e registros. Esta funcionalidade equivale a uma operação de junção, desde que ela “junta” dados de registros de dois arquivos usando como base um campo de igualdade (condição de junção).
9. [X] Recuperação dos dados, de todos os registros, armazenados em arquivos de dados no formato binário e a geração de um grafo contendo estes dados na forma de um conjunto de vértices V e um conjunto de arestas A. A representação do grafo é na forma de listas de adjacências
10. [X] Geração do grafo transposto do grafo gerado na funcionalidade anterior. 
11. [ ] Determinar o caminho mais curto entre cada pessoa que segue e uma determinada celebridade definida como parâmetro de entrada. Essa funcionalidade consiste em determinar os caminhos mais curtos com destino único.
12. [ ] Determinar se existe um ciclo no grafo, ou seja, se existe um caminho no qual o primeiro e o último vértices são iguais. No caso dessa funcionalidade, o primeiro e o último vértices devem ser correspondentes ao nome da pessoa que foi passado como parâmetro de entrada (Busca em profundidade).
13. [X] Tratamentos dos dados e tratamento de erros

### 🚀 Technology

The following data structures, tools and libraries were used in the construction of the project:

- Linked list
- Digraph (grafo direcional)
- Hexdump
- Valgrind
- String.h
- Stdio.h
- Stdlib.h

### License

<p>This project is under the MIT license, for more information look for the file <a href = "https://github.com/brunereduardo/TwitterDB_USP/blob/main/LICENSE">LICENSE.</a></p>

### Autores
Implemented  and built  with ❤️ by [Bruner Eduardo Augusto Albrecht](https://github.com/brunereduardo) | [Felipe Oliveira](https://github.com/felipeoliveir4) 👋🏽
