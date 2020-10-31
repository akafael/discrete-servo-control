# Modelo de Relatório para Laboratórios

Modelo de Relatório em LaTeX. Capa e layout colocados em arquivos separados para facilitar a portabilidade para o uso em múltiplos relatórios da mesma matéria.

## Requisitos

 - LaTeX

## Descrição arquivos e pastas

 - [main.tex](main.tex) Arquivo Principal do relatório
 - [relat_capa.tex](relat_capa.tex) Capa do Relatório
 - [relat_layout.tex](relat_layout.tex) Configurações do modelo e pacotes acrescentados
 - [reference.bib](reference.bib) Arquivo de referências do BibTeX

## Guia de uso

Estes arquivos podem ser importados para qualquer editor, incluindo o online como o sharelatex. Apenas garanta que todos os pacotes usado dentro de "relat_layout.tex" estejam previamente instalados.

## Pacotes Interessantes:

* [CircuiTikz](https://www.ctan.org/pkg/circuitikz?lang=en) Desenhe Circuitos Elétricos
* [pgfplot](https://www.ctan.org/pkg/pgfplots?lang=en) Gráficos gerados direto no LaTeX
* [pgfplottable](https://www.ctan.org/pkg/pgfplotstable?lang=en) Tabelas geradas a partir de dados direto no LaTeX
* [minted](https://www.ctan.org/pkg/circuitikz?lang=en) Colore e formata código de várias linguagens de programação.
