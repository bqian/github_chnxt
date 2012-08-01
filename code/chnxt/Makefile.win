PACKAGE = chnxt
VERSION = 1.0.7
PKGDIR = $(PACKAGE)-$(VERSION)/$(PACKAGE)

target: libnxt.dl

libnxt.dl: nxt.obj chnxt_chdl.obj
	ch dllink libnxt.dl nxt.obj chnxt_chdl.obj ws2_32.lib irprops.lib

nxt.obj: ../nxt.cpp ../nxt.h
	ch dlcomp libnxt.dl ../nxt.cpp -I../

chnxt_chdl.obj: chnxt_chdl.cpp ../nxt.h
	ch dlcomp libnxt.dl chnxt_chdl.cpp -I../

install: 
	ch pkginstall.ch $(PACKAGE)
	ch cp -R "$(CHHOME)/dl/Mi*" "$(CHHOME)/package/chnxt/dl/"

uninstall:
	ch pkginstall.ch -u $(PACKAGE)

clean:
	del *.obj 
	del *.dl
	del *.manifest
	del *.lib
	del *.exp
