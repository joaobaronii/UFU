import random

def monte_carlo_dados(n_simulacoes=100_000):
    contagem_pelo_menos_um_6 = 0
    
    contagem_faces_diferentes = 0
    contagem_6_dado_diferentes = 0
    
    for _ in range(n_simulacoes):
        d1 = random.randint(1, 6)
        d2 = random.randint(1, 6)
        
        # Parte 1: Pelo menos um 6
        if d1 == 6 or d2 == 6:
            contagem_pelo_menos_um_6 += 1
            
        # Parte 2: Probabilidade Condicional
        if d1 != d2:
            contagem_faces_diferentes += 1
            if d1 == 6 or d2 == 6:
                contagem_6_dado_diferentes += 1
                
    prob_a = contagem_pelo_menos_um_6 / n_simulacoes
        
    return prob_a, prob_b

if __name__ == "__main__":
    prob_a, prob_b = monte_carlo_dados()

    print(f"Probabilidade A: {prob_a:.4f}")
    print("Probabilidade A esperada:", 11/35)
    print("Erro A:", abs(prob_a - (11/35)))

    print(f"Probabilidade B: {prob_b:.4f}")
    print("Probabilidade B esperada:", 1/3)
    print("Erro B:", abs(prob_b - (1/3)))
