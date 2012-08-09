VERSION = 2.0.0

all:
	pdflatex nxt-$(VERSION).tex
	makeindex nxt-$(VERSION).idx
	cp nxt-$(VERSION).ind nxt_index.tex
	pdflatex nxt-$(VERSION).tex
clean:
	rm *.log *.aux *.out
