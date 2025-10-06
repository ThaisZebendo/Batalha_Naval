Descrição
- Projeto em C que implementa um tabuleiro de Batalha Naval 10x10 com posicionamento de navios e três habilidades com áreas de efeito.
- Objetivo: demonstrar manipulação de matrizes, validação de posicionamento e sobreposição de formas geométricas (cone, cruz, octaedro) sobre o tabuleiro.
O que foi implementado
- Tabuleiro 10x10 inicializado com 0 representando água.
Posicionamento de 4 navios de tamanho fixo 3:
- Dois navios posicionados horizontalmente ou verticalmente.
- Dois navios posicionados na diagonal (↘ e ↙).
- Validação de limites e de sobreposição antes do posicionamento.
Matrizes de habilidade geradas dinamicamente com valores 0 e 1:
- Cone: forma triangular apontando para baixo (topo e expansão até o centro da matriz).
- Cruz: linha central e coluna central marcadas.
- Octaedro: vista frontal simulada por um losango usando distância de Manhattan.
Aplicação das habilidades ao tabuleiro:
- Cada matriz de habilidade é sobreposta ao tabuleiro centrada em um ponto de origem definido no código.
- Casas afetadas pela habilidade são marcadas com 5.
- Habilidades não sobrescrevem navios; se uma posição contém 3, ela permanece 3.
Exibição do tabuleiro no console:
- Valores usados: 0 = água, 3 = navio, 5 = área de habilidade.
- Impressão com cabeçalho de colunas (A–J) e números de linhas (0–9).
- Código organizado em funções para reutilização e legibilidade:
- Funções de validação e posicionamento de navios.
- Funções que constroem as matrizes de habilidade dinamicamente.
- Função que aplica a matriz de habilidade ao tabuleiro.
- Funções de impressão para tabuleiro e matrizes isoladas.
