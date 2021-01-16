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

1. [X]  It reads several records obtained from an input file (in .csv format), and writes these to an output data file in binary format, as well as a binary output file with the indexing of the records.
2. [X] It allows data retrieval, of all records, stored in the personal data file, showing the data in an organized way in standard output to allow the distinction of fields and records.
3. [X]  Searches the data of all records in the person file that satisfy a search criterion determined by the user (idPessoa using the indexaPessoa.bin file, or all records of a certain age, as well as nomePessoa and TwitterPessoa).
4. [X] It allows the insertion of additional records, based on the static approach of logically removed records.
5. [ ] Updates one or more fields of one or more records in the personal data file, which were retrieved using the search functionality. This functionality must be performed n times in a row. In situations in which no records are found, that is, if the user's request does not return any records to be updated, the program must continue to perform the updates until completing the n consecutive times.
6. [x] Reads from various records obtained from an input file (file in .csv format), which contains the IDs of each user, dates (when one person followed or stopped following another) and the degree of friendship. The recording of these records must be done in a binary way in an output data file.
7. [X] Ordene o arquivo de dados de acordo com o campo de ordenação idPessoaQueSegue. Quando houver empate para os valores de idPessoaQueSegue, deve ser usado como critério de desempate o campo idPessoaQueESeguida e, caso ainda haja empate, deve ser usado como critério de desempate o campo dataInicioQueSegue e, caso ainda haja empate, deve ser usado como critério de desempate o campo dataFimQueSegue. A ordenação deve ser implementada considerando que o arquivo de dados segue cabe totalmente em memória primária (RAM). Portanto, o arquivo deve ser: (i) lido inteiramente do disco para a RAM; (ii) ordenado de acordo com a chave de ordenação usando-se qualquer algoritmo de ordenação disponível na biblioteca da linguagem C; e (iii) escrito inteiramente para disco novamente, gerando um novo arquivo de dados segueOrdenado, que encontra-se ordenado de acordo com o campo de ordenação. O arquivo de dados segue original não deve ser removido.
8. [X] Using the search functionality, to retrieve the data stored in the person data file associated with the data in the following data file, display the data in an organized way in standard output to allow the distinction of fields and records. This functionality is equivalent to a join operation, since it "joins" data from records of two files based on an equal field (join condition).
9. [X] Data retrieval, of all records, stored in data files in binary format and the generation of a graph containing these data in the form of a set of vertices V and a set of edges A. The graph is represented in the form of lists adjacencies.
10. [X] Generation of the graph transposed from the graph generated in the previous functionality. 
11. [ ] Determine the shortest path between each person you follow and a particular celebrity set as an input parameter. This functionality consists of determining the shortest paths with a single destination.
12. [ ] Determine if there is a cycle in the graph, that is, if there is a path in which the first and last vertices are equal. In the case of this functionality, the first and last vertices must correspond to the name of the person that was passed as an input parameter (Depth-first search).
13. [X] Data processing and error handling.

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
