
<h1>Questão 1</h1>

O FreeRTOS é um sistema operacional de tempo real voltado para microcontroladores e pequenos microprocessadores. Distribuído gratuitamente sob licença aberta do MIT, possui larga utilização em aplicações com necessidade de múltiplas tarefas a serem executadas e aplicações com criticidade de tempo real [1]. Utilizando a versão do FreeRTOS para computadores (Windows ou Linux), implemente uma aplicação que execute as seguintes tarefas, onde ambas compartilham uma mesma variável do tipo float simulando um valor de temperatura:

• Tarefa 1: Leia a variável compartilhada, adicione 1.5 °C ao seu valor, imprima o resultado na serial com uma frequência de 1 Hz e salve a variável com seu novo valor;

• Tarefa 2: Leia a variável compartilhada, converta seu valor para Fahrenheit, imprima o resultado na serial com uma frequência de 2 Hz e salve a variável com seu novo valor.


<h1>Questão 2</h1>

Você recebeu, juntamente com esse documento, dois arquivos para auxiliar na resolução desta questão: decoder.h e message.txt. O primeiro representa um arquivo de cabeçalho contendo protótipos de funções e o segundo contendo uma mensagem codificada. Implemente um código em linguagem de programação C capaz de realizar a leitura do arquivo message.txt, decodificá-lo e imprimir a mensagem final corretamente na tela. Os nomes de cada protótipo de função indicam, por si só, o que deve ser executado.
