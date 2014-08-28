labirinto-algoritmos-geneticos
==============================

Exemplo de geração de um labirinto usando algoritmos genéticos e com busca A* não-informada e informada para achar a solução.

O programa gera um labirinto com um custo mínimo e máximo para a solução.

Após a geração uma porta é selecionada, e iterativamente calculada uma solução com busca A* (informada e não-informada).
A solução só é aceita se o custo da mesma está entre o mínimo e máximo (definido como constante).

Ao final o programa exporta o labirinto para arquivo txt.

Onde os seguintes símbolos representam:

    1. Paredes (#)
    2. Entrada (1)
    3. Saída (2)
    4. Caminho explorado e que leva a solução (*)
    5. Caminho explorado mas que não leva diretamente a solução (@)
