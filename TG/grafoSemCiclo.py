import networkx as nx
import matplotlib.pyplot as plt

# Função para colorir as arestas que formam o ciclo
def destacarCiclo(G, ciclo):
    plt.figure(figsize=(6, 4))
    
    pos = nx.spring_layout(G)  # Posiciona os nós do grafo de forma organizada
    nx.draw(G, pos, with_labels=True, node_color="lightblue", edge_color="gray", node_size=1500)

    # Destacar arestas do ciclo encontrado
    arestas_ciclo = [(u, v) for u, v, _ in ciclo] # Eliminar o terceiro elemento(direciton), que é retornado na função find_cycle
    nx.draw_networkx_edges(G, pos, edgelist=arestas_ciclo, edge_color="red", width=2) # Destaca arestas que compõem o ciclo

    plt.title("Grafo com Ciclo Destacado")
    plt.show()

# Criando um grafo não direcionado sem ciclo
G = nx.Graph([(1, 2), (2, 3), (4, 2), (3, 5)])

# Desenhando o grafo
plt.figure(figsize=(6, 4))
nx.draw(G, with_labels=True, node_color="lightblue", edge_color="gray", node_size=1500)
plt.title("Grafo Não Direcionado")
plt.show()

ciclo = [] # Instancia uma lista vazia 

try: # Tenta executar find_cycle
    ciclo = list(nx.find_cycle(G, orientation="ignore"))  # Ignora a orientação das arestas, pois G é não-direcionado
    print("Ciclo encontrado:", ciclo)
except nx.NetworkXNoCycle: # Por não ter ciclo no grafo, a exception NetworkXNoCycle é levantada e tratada
    print("Nenhum ciclo encontrado.")

if ciclo: # Como não existe ciclo no grafo, o programa é terminado
    destacarCiclo(G, ciclo)