from xmlrpc.server import SimpleXMLRPCServer

server = SimpleXMLRPCServer(("localhost", 8000))
print("Servidor RPC iniciado na porta 8000...")

def somar(a, b):
    print(f"Somando {a} + {b}")
    return a+b

def subtrair(a, b):
    print(f"Subtraindo {a} - {b}")
    return a-b

def multiplicar(a, b):
    print(f"Multiplicando {a} * {b}")
    return a*b

def dividir(a, b):
    print(f"Dividindo {a} / {b}")
    if b == 0:
        raise ValueError("Divisão por zero não é permitida.")
    return a/b

server.register_function(somar, "somar")
server.register_function(subtrair, "subtrair")
server.register_function(multiplicar, "multiplicar")
server.register_function(dividir, "dividir")

server.serve_forever()