import networkx as nx
import matplotlib.pyplot as plt

# Função para colorir as arestas que formam o ciclo
def destacarCiclo(G, ciclo):
    plt.figure(figsize=(10, 6))
    
    pos = nx.spring_layout(G)  # Posiciona os nós do grafo de forma organizada
    nx.draw(G, pos, with_labels=True, node_color="lightblue", edge_color="gray", node_size=800)

    # Destacar arestas do ciclo encontrado
    arestas_ciclo = [(u, v) for u, v, _ in ciclo] # Eliminar o terceiro elemento(direciton), que é retornado na função find_cycle
    nx.draw_networkx_edges(G, pos, edgelist=arestas_ciclo, edge_color="red", width=2) # Destaca arestas que compõem o ciclo

    plt.title("Grafo com Ciclo Destacado")
    plt.show()

# Criando um grafo não direcionado
G = nx.Graph()

# Conjunto de arestas que serão adicionadas no grafo
arestas = [
    (1, 2), (2, 3), (3, 4), (4, 5), (5, 1),
    (1, 6), (6, 7), (7, 8), (8, 2),
    (3, 9), (9, 10), (10, 4),
    (5, 11), (11, 12), (12, 6),
    (7, 13), (13, 14), (14, 8),
    (9, 15), (15, 16), (16, 10),
    (11, 17), (17, 18), (18, 12),
    (13, 19), (19, 20), (20, 14),
    (15, 21), (21, 22), (22, 16),  
    (17, 23), (23, 24), (24, 18), 
    (19, 25), (25, 26), (26, 20)  
]

# Adicionando conjunto arestas no grafo
G.add_edges_from(arestas) 

# Desenhando o grafo
plt.figure(figsize=(10, 6))
nx.draw(G, with_labels=True, node_color="lightblue", edge_color="gray", node_size=800)
plt.title("Grafo Não Direcionado")
plt.show()

ciclo = [] # Instancia uma lista vazia 

try: # Tenta executar find_cycle, nesse caso existe ciclo então não ocorre a exception
    ciclo = list(nx.find_cycle(G, orientation="ignore"))  # Ignora a orientação das arestas, pois G é não-direcionado
    print("Ciclo encontrado:", ciclo)
except nx.NetworkXNoCycle:
    print("Nenhum ciclo encontrado.")

if ciclo: # Aqui possui ciclo, então a função é chamada
    destacarCiclo(G, ciclo)