TEX=pdflatex
BIB=bibtex

FLG=-shell-escape

figs = $(wildcard figs/*.pdf)

#make the pdf
all:  BE.pdf

#run pdflatex and bibtex (runs only if you update something in pdfs or in the tex file)
BE.pdf:  BE.tex $(figs) refs.bib
	$(TEX) $(FLG) $< 
	$(BIB) BE || true
	$(TEX) $(FLG) $< 

	#remove all output except the pdf file
	rm -f *.aux 
	rm -f *.log 
	rm -f *.out 
	rm -f *.bbl 
	rm -f *.blg 
	rm -rf _minted-BE
clean:
	rm -f BE.pdf 
	
