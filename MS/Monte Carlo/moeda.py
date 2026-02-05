import random

def monte_carlo(n_simulacoes=100_000):
    """
    Simula o lançamento de uma moeda até sair Cara (C).
    Conta quantas vezes o jogo acabou exatamente no 3º lançamento.
    """
    sucessos_tres_lancamentos = 0
    
    for _ in range(n_simulacoes):
        lancamentos = 0
        while True:
            lancamentos += 1
            # Simulando: 0 = Coroa (K), 1 = Cara (C)
            resultado = random.choice(['K', 'C'])
            
            if resultado == 'C':
                break
        
        # Verificamos se parou exatamente no 3 (Sequência K, K, C)
        if lancamentos == 3:
            sucessos_tres_lancamentos += 1
            
    return sucessos_tres_lancamentos / n_simulacoes

if __name__ == "__main__":
    prob = monte_carlo()
    print(f"Probabilidade por Monte Carlo: {prob:.4f}")
    print("Probabilidade: 0.125")
    print("Erro:", abs(prob - 0.125))