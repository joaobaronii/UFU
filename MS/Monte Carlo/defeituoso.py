import numpy as np

def monte_carlo(n = 100000):
    estados = [0, 1]

    P = [
        [0.99, 0.01],
        [0.12, 0.88]
    ]

    contagem_defeituosos = 0 

    for _ in range(n):
        estado_atual = 1  # Começa no estado "Defeituoso"

        for _ in range(3):
            estado_atual = np.random.choice(estados, p=P[estado_atual])

        if estado_atual == 1:
            contagem_defeituosos += 1

    probabilidade = contagem_defeituosos / n
    return probabilidade

if __name__ == "__main__":
    
    prob = monte_carlo()
    
    print(f"Probabilidade por Monte Carlo: {prob:.4f}")
    print("Probabilidade: 0.6848")
    print("Erro:", abs(prob - 0.6848))