# Definição das instâncias
inst1 = n3m10A.txt
inst2 = n3m10B.txt
inst3 = n3m10C.txt
inst4 = n3m10D.txt
inst5 = n3m10E.txt
inst6 = n3m20A.txt
inst7 = n3m20B.txt
inst8 = n3m20C.txt
inst9 = n3m20D.txt
inst10 = n3m20E.txt
inst11 = n3m40A.txt
inst12 = n3m40B.txt
inst13 = n3m40C.txt
inst14 = n3m40D.txt
inst15 = n3m40E.txt
inst16 = n5m50A.txt
inst17 = n5m50B.txt
inst18 = n5m50C.txt
inst19 = n5m50D.txt
inst20 = n5m50E.txt

# Regra padrão
all: Flight
	@echo Compilando...
	@g++ *.cc -o main

# Regra para limpar arquivos
clean:
	@echo Limpando Arquivos Objeto e Executavel...
	@rm -f *.o main

# Regra para compilar o Flight (se necessário)
Flight:
	@echo Compilando Flight...

# Regras para as instâncias
instancia1:
	@echo Executando a Instancia 1...
	@./main $(inst1)

instancia2:
	@echo Executando a Instancia 2...
	@./main $(inst2)

instancia3:
	@echo Executando a Instancia 3...
	@./main $(inst3)

instancia4:
	@echo Executando a Instancia 4...
	@./main $(inst4)

instancia5:
	@echo Executando a Instancia 5...
	@./main $(inst5)

instancia6:
	@echo Executando a Instancia 6...
	@./main $(inst6)

instancia7:
	@echo Executando a Instancia 7...
	@./main $(inst7)

instancia8:
	@echo Executando a Instancia 8...
	@./main $(inst8)

instancia9:
	@echo Executando a Instancia 9...
	@./main $(inst9)

instancia10:
	@echo Executando a Instancia 10...
	@./main $(inst10)

instancia11:
	@echo Executando a Instancia 11...
	@./main $(inst11)

instancia12:
	@echo Executando a Instancia 12...
	@./main $(inst12)

instancia13:
	@echo Executando a Instancia 13...
	@./main $(inst13)

instancia14:
	@echo Executando a Instancia 14...
	@./main $(inst14)

instancia15:
	@echo Executando a Instancia 15...
	@./main $(inst15)

instancia16:
	@echo Executando a Instancia 16...
	@./main $(inst16)

instancia17:
	@echo Executando a Instancia 17...
	@./main $(inst17)

instancia18:
	@echo Executando a Instancia 18...
	@./main $(inst18)

instancia19:
	@echo Executando a Instancia 19...
	@./main $(inst19)

instancia20:
	@echo Executando a Instancia 20...
	@./main $(inst20)

# Regra para executar todas as instâncias em sequência
run_all: all
	@echo Executando todas as instâncias...
	@./main $(inst1)
	@./main $(inst2)
	@./main $(inst3)
	@./main $(inst4)
	@./main $(inst5)
	@./main $(inst6)
	@./main $(inst7)
	@./main $(inst8)
	@./main $(inst9)
	@./main $(inst10)
	@./main $(inst11)
	@./main $(inst12)
	@./main $(inst13)
	@./main $(inst14)
	@./main $(inst15)
	@./main $(inst16)
	@./main $(inst17)
	@./main $(inst18)
	@./main $(inst19)
	@./main $(inst20)

# Regras para agrupar instâncias por tamanho
run_n3m10: all
	@echo Executando instâncias n3m10...
	@./main $(inst1)
	@./main $(inst2)
	@./main $(inst3)
	@./main $(inst4)
	@./main $(inst5)

run_n3m20: all
	@echo Executando instâncias n3m20...
	@./main $(inst6)
	@./main $(inst7)
	@./main $(inst8)
	@./main $(inst9)
	@./main $(inst10)

run_n3m40: all
	@echo Executando instâncias n3m40...
	@./main $(inst11)
	@./main $(inst12)
	@./main $(inst13)
	@./main $(inst14)
	@./main $(inst15)

run_n5m50: all
	@echo Executando instâncias n5m50...
	@./main $(inst16)
	@./main $(inst17)
	@./main $(inst18)
	@./main $(inst19)
	@./main $(inst20)

# Alvo .PHONY para alvos que não são arquivos
.PHONY: all clean Flight instancia1 instancia2 instancia3 instancia4 instancia5 instancia6 instancia7 instancia8 instancia9 instancia10 instancia11 instancia12 instancia13 instancia14 instancia15 instancia16 instancia17 instancia18 instancia19 instancia20 run_all run_n3m10 run_n3m20 run_n3m40 run_n5m50