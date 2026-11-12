# Entrag 4: Mercadinho
Trabalho acadêmico de Algoritmo e Pensamento computacional.

## Membros do grupo
Yuri Bezerra, Theo Carlo e Lucas Trevesan.
 
## Objetivo
O Mercadinho UNICID é um programa em C, executado no terminal, que simula o cadastro de produtos de um mercado. Ele foi criado como trabalho da UNICID para praticar vetores, funções, manipulação de arquivos de texto e o algoritmo de ordenação Bubble Sort. Os dados ficam guardados no arquivo mercado.txt, então continuam salvos mesmo depois de fechar o programa.
 
## O que pode ser feito nele
Pelo menu, é possível listar todos os produtos em formato de tabela, inserir um produto novo, alterar os dados de um produto, excluir um produto, buscar por nome ou por categoria (inclusive digitando só uma parte do texto), listar os produtos ordenados por nome com Bubble Sort e comprar um produto, o que diminui a quantidade em estoque e mostra o valor total da compra.
Cada produto tem ID, nome, categoria, preço e quantidade. O ID é gerado automaticamente e nunca é reaproveitado, mesmo que um produto seja excluído. O programa não deixa cadastrar dois produtos com o mesmo nome, aceita preço com vírgula ou ponto e recusa compras com quantidade inválida ou maior que o estoque. Se o arquivo mercado.txt não existir, ele é criado vazio ao iniciar.
 
## Explicação do processo
Começamos a partir do exemplo de cadastro em arquivo de texto visto em aula e trocamos o tema para um mercadinho. Primeiro escrevemos as funções de salvar e carregar, para ter certeza de que os dados iam e voltavam do arquivo, e depois montamos o cadastro completo com listar, inserir e alterar, testando cada parte pelo menu. Nos testes, percebemos que digitar o preço com vírgula fazia a pergunta seguinte ser pulada, e resolvemos isso limpando o teclado a cada leitura e trocando a vírgula por ponto. Em seguida acrescentamos o ID automático, a verificação de nomes repetidos, a exclusão, a busca, a ordenação com Bubble Sort e, por fim, a compra com controle de estoque. Para terminar, testamos sessões completas e conferimos o conteúdo do arquivo.

