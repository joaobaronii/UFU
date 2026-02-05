import xmlrpc.client

try:
    proxy = xmlrpc.client.ServerProxy("http://localhost:8000/")
except Exception as e:
    print(f"Erro: {e}")

def obter_numeros():
     while True:
        try:
            n1 = float(input("Digite o primeiro número: "))
            n2 = float(input("Digite o segundo número: "))
            return n1, n2
        except ValueError:
            print("Digite apenas números.")

def menu():
    while True:
        print("-------------------------")
        print("1- Soma")
        print("2- Subtração")
        print("3- Multiplicação")
        print("4- Divisão")
        print("0- Sair")

        op = input("Escolha uma operação: ")

        if op in ["1","2","3","4"]:
            while True:
                try:
                    n1 = float(input("Digite o primeiro número: "))
                    n2 = float(input("Digite o segundo número: "))
                    break
                except ValueError:
                    print("Digite apenas números.")

        try:
            match op:
                case "1":
                    resultado = proxy.somar(n1, n2)
                case "2":
                    resultado = proxy.subtrair(n1, n2)
                case "3":
                    resultado = proxy.multiplicar(n1, n2)
                case "4":
                    resultado = proxy.dividir(n1, n2)
                case "0":
                    print("Encerrando cliente...")
                    break
                case _:
                    print("Opção inválida, tente novamente.")

            print(f"Resultado: {resultado}")
        
        except Exception as e:
            print(f"Erro: {e}")

if __name__ == "__main__":
    menu()               
