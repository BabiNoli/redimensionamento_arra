class arrayDinamic:
    def __init__(self, capacidadeInicial):
        self.capacidade = capacidadeInicial 
        self.tamanho = 0
        self.dado = [None] * self.capacidade

    def append(self, valor):
        #Se está cheio redireciona
        if self.tamanho == self.capacidade:
            self.redimensionar()
        #Armazena e incrementa
        self.dado[self.tamanho] = valor
        self.tamanho += 1

    def redimensionar(self):
        print("Relocando de ", self.capacidade, " para ", self.capacidade * 2, " posições.")
        novaCapacidade = self.capacidade * 2
        novoDado = [None] * novaCapacidade

        # Copia todos os elementos do array antigo para o novo

        for i in range(self.tamanho):
            novoDado[i] = self.dado[i]

        self.dado = novoDado
        self.capacidade = novaCapacidade

        
if __name__ == "__main__":
    capacidade_inicial = int(input("Digite a capacidade inicial do array: "))
    array = arrayDinamic(capacidade_inicial)

    while True:
        valor = input("Digite um valor para adicionar ao array (ou 'sair' para terminar): ")
        if valor.lower() == 'sair':
            break
        array.append(valor)

    #print("Array final:", array.dado[:array.tamanho])
    print("Seu array tem ", array.tamanho, "posições.")

    print("Array final: ", end="")
    i = 0
    while i < array.tamanho:
        print(array.dado[i], end=" ")
        i += 1
    print()