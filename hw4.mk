TXT_ODE= 10_RK.txt 20_RK.txt 30_RK.txt 40_RK.txt 45_RK.txt 50_RK.txt 60_RK.txt 70_RK.txt
TXT_PDE=$(wildcard *_1.txt) $(wildcard *_2.txt) $(wildcard *_3.txt)
TXT_PDE_2=promedio-1.txt promedio-2.txt promedio-3.txt
PLOTS=$(patsubst %.txt, %.pdf, $(TXT_PDE)) 45_RK.pdf promedios.pdf trayectorias.pdf

Resultados_hw4.pdf : Resultados_hw4.tex $(PLOTS)
	pdflatex $<

$(PLOTS): Plots_hw4.py $(TXT_ODE) $(TXT_PDE) $(TXT_PDE_2)
	python $<

$(TXT_ODE) $(TXT_PDE_2) : ODE.cpp
	g++ $^
	./a.out >> $@

$(TXT_PDE) : PDE.cpp
	g++ $^
	./a.out >> $@
