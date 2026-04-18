# PI2 - Projeto 1: Simulador em Linguagem C para a Arquitetura MiniMIPS 8 bits

Repositório referente ao **Projeto 1** da disciplina **Projeto Integrador II**, do curso de **Engenharia de Computação — UNIPAMPA (Campus Bagé)**.

O projeto consiste no desenvolvimento de um **simulador em linguagem C** para a arquitetura **MiniMIPS 8 bits monociclo**.

---

## Sumário
- [Desenvolvedores](#desenvolvedores)
- [Estrutura do repositório](#estrutura-do-repositório)
- [Arquitetura MiniMIPS](#arquitetura-minimips)
- [Requisitos](#requisitos)
- [Uso e funcionalidades do simulador](#uso-e-funcionalidades-do-simulador)

---

## Desenvolvedores

* Sara Vitória Henssler - saravitoriahenssler@gmail.com
* Leonardo Cunha Gazen Manzke - manzkeleonardo@gmail.com
* Hector Bernardo de Quadros Arbiza -

**Disciplina:** Projeto Integrador II
**Curso:** Engenharia de Computação
**Instituição:** UNIPAMPA - Campus Bagé
**Semestre/Ano:** 2026/1

---

## Estrutura do repositório

```text
pi2_projeto1_monociclo/
├── src/                        # Código-fonte 
├── include/                    # Arquivos de cabeçalho 
├── Makefile            
├── main.c                      #arquivo principal
├── memoria1.dat                #arquivo default para memória de dados
├── memoria1.mem                #arquivo default para a memória instruções
└── README.md
```
---

## Arquitetura MiniMIPS

A arquitetura MiniMIPS 8 bits é baseada na clássica arquitetura MIPS 32 e tem propósito didático, que busca facilitar o ensino de conceitos de arquitetura de computadores [[1](https://ieeexplore.ieee.org/document/6128570)]. 

### Componentes

- Contador de Programa (PC)
- Memória de Instruções
- Memória de Dados
- Banco de Registradores 
- Unidade de Controle
- Unidade Lógica Aritmética (ULA)
- Decodificador
- Extensor de bits

### Formato de instruções, registradores e dados

A arquitetura MiniMIPS utiliza instruções de 16 bits, organizadas em três formatos: Tipo R, Tipo I e Tipo J. As instruções do Tipo R são utilizadas para operações entre registradores e são compostas pelos campos Opcode, RS, RT, RD e Function, onde o campo Opcode identifica o tipo da instrução, RS e RT representam os registradores fonte, RD indica o registrador de destino e o campo Function define a operação a ser executada pela Unidade Lógica Aritmética (ULA). As instruções do Tipo I são utilizadas para operações com valores imediatos e acesso à memória, sendo formadas pelos campos Opcode, RS, RT e Imediato, onde RS representa o registrador base, RT o registrador de destino e o campo Imediato contém um valor constante ou deslocamento. Já as instruções do Tipo J são utilizadas para desvios incondicionais e são compostas pelos campos Opcode e Endereço, sendo o campo Endereço responsável por indicar o destino do salto.

A arquitetura possui 8 registradores, sendo o registrador $r0 responsável por armazenar o valor constante zero, os registradores $r1 a $r6 destinados a propósito geral e o registrador $r7, originalmente utilizado para controle de sinais na FPGA. No simulador desenvolvido, como não há necessidade de controle de periféricos da FPGA, o registrador $r7 também é utilizado como registrador de propósito geral.

Além disso, a arquitetura utiliza dados com largura de 8 bits, assim como os campos de imediato e endereço das instruções. A seguir, são descritos os tipos de instruções suportadas e seus respectivos formatos.

### Tipo R — Registradores

Utilizado para operações aritméticas e lógicas entre registradores:

```
15        12 11     9 8      6 5      3 2      0
+-----------+---------+---------+---------+--------+
|  Opcode   |   RS    |   RT    |   RD    | Func   |
+-----------+---------+---------+---------+--------+
```

Campos:

- **Opcode** → Identifica o tipo da instrução  
- **RS** → Registrador fonte 1  
- **RT** → Registrador fonte 2  
- **RD** → Registrador destino  
- **Func** → Operação executada na ULA

---

### Tipo I — Imediato

Utilizado para operações com valores imediatos:

```
15        12 11     9 8      6 5              0
+-----------+---------+---------+---------------+
|  Opcode   |   RS    |   RT    |   Imediato    |
+-----------+---------+---------+---------------+
```

Campos:

- **Opcode** → Identifica a instrução  
- **RS** → Registrador base  
- **RT** → Registrador destino  
- **Imediato** → Valor constante ou offset  

---

### Tipo J — Desvio

Utilizado para instruções de salto:

```
15        12 11     6 5            0
+-----------+---------+--------------+
|  Opcode   |   ---   |   Endereço   |
+-----------+---------+--------------+
```

Campos:

- **Opcode** → Identifica a instrução  
- **Endereço** → Destino do salto  

---

Abaixo estão descritas as instruções suportadas pela arquitetura, em seu formato assembly, divididas por tipo:

### Tabela 1 — Instruções suportadas na arquitetura MiniMIPS

| Tipo | Instrução Assembly | Opcode | Function | Descrição |
|------|--------------------|--------|----------|-----------|
| **R - Registradores** | | | | |
| R | `add $rd, $rs, $rt` | 0000 | 000 | Soma o conteúdo dos registradores rs e rt e armazena o resultado em rd |
| R | `sub $rd, $rs, $rt` | 0000 | 010 | Subtrai o conteúdo de rt de rs e armazena o resultado em rd |
| R | `and $rd, $rs, $rt` | 0000 | 100 | Realiza operação lógica AND entre rs e rt e armazena em rd |
| R | `or $rd, $rs, $rt` | 0000 | 101 | Realiza operação lógica OR entre rs e rt e armazena em rd |
| **I - Imediato** | | | | |
| I | `addi $rt, $rs, imediato` | 0100 | - | Soma o valor imediato ao registrador rs e armazena em rt |
| I | `lw $rt, imediato($rs)` | 1011 | - | Carrega para rt o valor da memória no endereço rs + imediato |
| I | `sw $rt, imediato($rs)` | 1111 | - | Armazena na memória o valor de rt no endereço rs + imediato |
| I | `beq $rt, $rs, imediato` | 1000 | - | Realiza desvio se rs e rt forem iguais |
| **J - Desvio** | | | | |
| J | `j endereço` | 0010 | - | Realiza salto incondicional para o endereço especificado |

---

## Requisitos

* **Compilador:** GCC 
* **Build:** Make 
* **Sistema Operacional:** Linux / Windows com MSY2 ou ambiente tipo Linux

---

## Uso e funcionalidades do simulador

### Compilação e execução

``` 
make        #compila simulador
make run    #roda simulador
make clean  #limpa arquivos antigos de build
```
### Uso do simulador

Após compilar e executar, as opções disponíveis no menu do simulador são: 

```
0_ Fechar programa
1_ Carregar arquivo de memória de dados (.dat)
2_ Carregar arquivo de memória de instruções (.mem)
3_ Mostrar memória de dados
4_ Mostrar memória de instruções
5_ Mostrar banco de registradores
6_ Mostrar instruções no formato Assembly
7_ Mostrar todo o simulador
8_ Salvar arquivo Assembly (.asm)
9_ Salvar dados da memória de dados (.dat)
10_ Rodar programa
11_ Rodar 1 instrução
12_ Voltar 1 instrução
13_ Exibir estatísticas
```
Para verificação e teste, o simulador pode ser testado utilizando a memória de instruções (`memoria1.mem`) e a memória de dados (`memoria1.dat`) já disponíveis neste repositório.
Recomenda-se primeiramente carregar a memória de instruções. O arquivo de memória de instruções deve seguir o formato `.mem`, contendo uma instrução por linha, podendo ser em formato hexadecimal ou binário. A forma de construção das instruções está descrita na seção [Arquitetura MiniMIPS](#arquitetura-minimips).

### Memória de Instruções (`.mem`)

O arquivo `.mem` deve conter uma instrução por linha e devem podem estar em formato binário ou hexadecimal. A capacidade total da memória de instruções é de 256 instruções.

Exemplo em binário:

```
0000001010100000
0100010100000101
0010000000001010
```

Exemplo em hexadecimal:

```
02A0
4505
200A
```

### Memória de Dados (`.dat`)

Também é possível carregar a memória de dados no formato `.dat`, seguindo a convenção de um valor inteiro, em formato decimal, por linha. A memória de dados também possui capacidade para armazenar 265 dados. A arquitetura considera complemento de dois, então dados maiores que 127 ou menores que -128 serão ignorados.

Exemplo:

```
10
25
0
100
-5
```

Após o carregamento das memórias, é possível visualizar os dados contidos nas memórias, no banco de registradores e as instruções em formato Assembly usando as opções **[4]**, **[5]** e **[6]** do menu. A opção **[7]** exibe todas essas informações simultaneamente, adicionando também a posição do PC.

A opção **[8]** permite salvar um arquivo Assembly (`.asm`) com as instruções já carregadas na memória de instruções. Já a opção **[9]** permite salvar um novo arquivo `.dat` com os dados contidos na memória de dados, sendo possível realimentar o simulador com esses valores posteriormente.

As opções **[10]** à **[12]** oferecem diferentes formas de execução do programa carregado no simulador:

* **[10]** Executa todo o programa até o final
* **[11]** Executa uma instrução por vez
* **[12]** Permite voltar uma instrução (não é permitido retornar mais de uma instrução seguida)

Por fim, a opção **[13]** exibe estatísticas sobre o programa carregado, incluindo o número de instruções por tipo e por classe.

## Referências

[1] C. Ortega-Sanchez, "MiniMIPS: An 8-Bit MIPS in an FPGA for Educational Purposes," 
2011 International Conference on Reconfigurable Computing and FPGAs (ReConFig), 
Cancún, México, 2011, pp. 152–157, doi: 10.1109/ReConFig.2011.62.
