import networkx as nx
import matplotlib.pyplot as plt


# Função para desenhar grafos, evitando código duplicado, usando matplotlib
def desenhaGrafo(G, pos):
    plt.figure(figsize=(10, 6))
    nx.draw(G, pos, with_labels=True, node_color="lightblue", edge_color="gray", node_size=800)
    plt.title("Grafo Não Direcionado")
    plt.show()

# Função para colorir as arestas que formam o ciclo
def destacarCiclo(G, ciclo, pos):
    plt.figure(figsize=(10, 6))
    nx.draw(G, pos, with_labels=True, node_color="lightblue", edge_color="gray", node_size=800)
    nx.draw_networkx_edges(G, pos, edgelist=ciclo, edge_color="red", width=2) # Destaca arestas que compõem o ciclo
    plt.title("Grafo com Ciclo Destacado")
    plt.show()


# Arestas que serão inseridas no grafo1
arestas = [ 
    (1, 2), (2, 3), (3, 4), (4, 5), (5, 1),
    (1, 6), (6, 7), (7, 8), (8, 2),
    (3, 9), (9, 10), (10, 4),
    (5, 11), (11, 12), (12, 6),
    (7, 13), (13, 14), (14, 8),
    (9, 15), (15, 16), (16, 10),
    (11, 17), (17, 18), (18, 12)
]

# Criando grafo não direcionado que possui ciclo
grafo1 = nx.Graph(arestas)

# Calcula o layout do grafo1 uma única vez
posG1 = nx.spring_layout(grafo1)

desenhaGrafo(grafo1, posG1) # Desenhando o grafo1

cicloG1 = [] # Instancia uma lista vazia para o ciclo1 do grafo1

# Tenta executar find_cycle no grafo1
try:
    cicloG1 = nx.find_cycle(grafo1) # Retorna uma lista de arestas que formam o ciclo nenhum vértice é passado
    print("Ciclo encontrado:", cicloG1)               # como fonte e nem uma orientação, por ser não-direcionado
except nx.NetworkXNoCycle: # Como o grafo1 possui ciclo, a exception NetworkXNoCycle não é levantada
    print("Nenhum ciclo encontrado.")

if cicloG1: # Ciclo G1 não está vazia, então a função é chamada
    destacarCiclo(grafo1, cicloG1, posG1)



input("") # Pra ter que dar enter, se quiser tirar o segundo grafo vai pular na tua cara



# Criando grafo não direcionado que não possui ciclo
grafo2 = nx.Graph([(1, 2), (2, 3), (4, 2), (3, 5)])

# Calcula o layout do grafo2 uma única vez
posG2 = nx.spring_layout(grafo2)

# Desenhando o grafo2
desenhaGrafo(grafo2, posG2)
cicloG2 = [] # Instancia uma lista vazia para o ciclo do grafo2

try: # Tenta executar find_cycle
    cicloG2 = nx.find_cycle(grafo2)  # Retorna uma lista de arestas que formam o ciclo nenhum vértice é passado
    print("Ciclo encontrado:", cicloG2)               # como fonte e nem uma orientação, por ser não-direcionado
except nx.NetworkXNoCycle: # Por não ter ciclo no grafo2, a exception NetworkXNoCycle é levantada e tratada
    print("Nenhum ciclo encontrado.") # Essa mensagem será impressa no terminal

if cicloG2: # Como não existe ciclo no grafo, o programa é terminado
    destacarCiclo(grafo2, cicloG2, posG2)