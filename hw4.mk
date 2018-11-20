TXT_PDE=0.000000_1.txt 4998.235340_1.txt 7499.496335_1.txt 29995.842014_1.txt 0.000000_2.txt 66666.000000_2.txt 99999.000000_2.txt 399996.000000_2.txt 0.000000_3.txt 66666.000000_3.txt 99999.000000_3.txt 399996.000000_3.txt promedio_1.txt promedio_2.txt promedio_3.txt
TXT_ODE=10_RK.txt 20_RK.txt 30_RK.txt 40_RK.txt 45_RK.txt 50_RK.txt 60_RK.txt 70_RK.txt
PLOTS=0_1.pdf 4998_1.pdf 7499_1.pdf 29995_1.pdf 0_2.pdf 66666_2.pdf 99999_2.pdf 399996_2.pdf 0_3.pdf 66666_3.pdf 99999_3.pdf 399996_3.pdf 45_RK.pdf promedio.pdf trayectorias.pdf

#El pdf se compila 2 veces para que las referencias a figuras dentro del documento salgan actualizadas.
Resultados_hw4.pdf: Resultados_hw4.tex $(PLOTS)
	pdflatex Resultados_hw4.tex >> log.dat
	pdflatex Resultados_hw4.tex >> log.dat

#Esta regla se ejecuta dos veces. No logre encontrar la dependencia que genera eso.
$(PLOTS):Plots_hw4.py $(TXT_PDE) $(TXT_ODE)
	python Plots_hw4.py *.txt

$(TXT_PDE):PDE.cpp
	g++ -std=gnu++11 PDE.cpp
	./a.out

#Esta regla se ejecuta el mismo numero de archivos dependientes. No logre encontrar la dependencia que genera esto.
$(TXT_ODE):ODE.cpp
	g++ -std=gnu++11 ODE.cpp
	./a.out

.PHONY:clean
clean:
	rm -r *.txt *.pdf *.log *.aux *.out *.dat
