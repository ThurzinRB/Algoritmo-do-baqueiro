# Algoritmo do Banqueiro 🏦💸💸💲💲🤑

## 👨‍💻 Compilar e executar

Para compilar é simples, execute o seguinte comando no diretório raíz dos arquivos:

```bash
  make -f makefile
```

Para executar o programa,execute o seguinte comando no diretório raíz dos arquivos:

```bash
  ./banqueiro -n <número_de_processos> -a <recursos_disponíveis>
```

Por exemplo:

```bash
  ./banqueiro -n 3 -a 2 5 7
```

ou

```bash
  ./banqueiro -a 5 4 17 -n 10
```

## 📚 Introdução

O algoritmo do banqueiro foi desenvolvido por Edsger Dijkstra como mecanismo para evitar a ocorrência de deadlock. Deadlocks são um fenômeno que descreve quando diversos processos tentam acessar recursos que estão ocupados enquanto reservam recursos que estão sendo requisitados. Como consequência de tal evento, os processos não são capazes de ser finalizados, ocupando espaço de memória e processamento até a falha completa do processador.

O mecanismo desenvolvido por Dijkstra, tem como principio a aplicação de um sistema real empregado em bancos na orquestra de empréstimo de capital para clientes. No algoritmo do banqueiro, o processo solicita uma determinada quantidade de recursos para a execução de seus processos, o banqueiro, utilizando um crédito aleatório para o cliente, decide se irá entregar ou não esses recursos analisando quanto o cliente necessita e quanto o banco possui. Caso o banco possua recursos suficientes para finalizar o processo do cliente (situação denominada de estado seguro), o banqueiro autoriza o empréstimo do crédito. Caso o cliente necessita de mais do que o banco possui (situação denominada de estado inseguro), o banqueiro requsa a solicitação.

O código nesse repositório tem como intuito simular a execução de um algoritmo do banqueiro utilizando threads e sincronização além da escolha da quantidade de processos simulâneos e a quantidade de recursos disponível. A quantidade de recursos necessários de cada processo é determinado de forma aleatória a partir da quantidade de recursos disponíveis. O crédito também é gerado de forma aleatória a cada requisição do processo apartir da quantidade restante para o processo poder ser finalizado.

## 🧹 Organização de Arquivos

Os arquivos estão organizados da seguinte forma:

- banqueiro.c:

  - Onde a main do algoritmo se localiza;
  - Possui a função requisicao_recursos(int pid) que o processo utiliza para requerir recursos;
  - Possui a função libera_recursos(int pid) que o processo chama para liberar recursos. Se os recursos forem liberados, retorna 0, se não forem, retorna 1.

- processos.c:

  - Possui a função processo passada para as threads. A função processo:
    - Executa requisicao_recursos(int pid);
    - Dorme por um tempo aleatório de até 5 segudos;
    - Executa libera_recursos(int pid);
    - Dorme por um tempo aleatório de até 5 segudos;

- sistema.c:
  - definirRecuso(): função responsável por definir a quantidade necessária de recursos que cada processo necessita para a sua conclusão;
  - printMatrix(): função utilizada para printar matrizes com a quantidade de processos como linha e a quantidade de recursoss como coluna;
  - trataInput(): função responsável por receber os argumentos da main e designar os valores para cada variável, verificar se o usuário inseriu os valores corretamente e se inseriu todas as tags necessárias;
  - iniciaSistema(): função que cria as threads e realiza o join das mesmas. Também inicia a variável de mutex para a sincronização;

## 👨‍👨‍👧‍👦 Integrantes

- Arthur Reis Bello - 11811EMT009
- Erick Tomaz Oliveira 11911EMT020
- Eduardo Apolinario Lopes – 11621EMT005
- Rayssa Alves Guimarães - 11621EMT015

## 👨‍🏫 Professor:

### Marcelo Zanchetta do Nascimento
