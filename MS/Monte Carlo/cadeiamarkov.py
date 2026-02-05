import numpy as np

def monte_carlo_cadeia(n = 100_000):
    
    p = [
        [0.3, 0.2, 0.5],
        [0.5, 0.1, 0.4],
        [0.5, 0.2, 0.3] 
    ]

    prob_inicial = [0.5, 0.5, 0.0]

    estados = [0, 1, 2]
    
    sucessos = 0

    for _ in range(n):
        x0 = np.random.choice(estados, p=prob_inicial)

        x1 = np.random.choice(estados, p=p[x0])

        x2 = np.random.choice(estados, p=p[x1])

        if x0 == 1 and x1 == 1 and x2 == 0:
            sucessos += 1
    
    return sucessos / n

if __name__ == "__main__":
    prob = monte_carlo_cadeia(1)
    print(f"Probabilidade estimada: {prob:.4f}")
    print(f"Probabilidade exata: 0.025")
    print(f"Erro absoluto: {abs(prob - 0.025):.4f}")""