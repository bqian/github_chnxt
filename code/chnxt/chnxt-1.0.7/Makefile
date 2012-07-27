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
	ch cp -R $(CHHOME)/dl/Mi* $(CHHOME)/package/chmobot/dl/

uninstal:
	ch pkginstall.ch -u $(PACKAGE)

createpkg: libnxt.dl
	echo Bulding $(PACKAGE)-$(VERSION).zip ...
	rm -rf $(PACKAGE)-$(VERSION)
	rm -rf $(PACKAGE)-$(VERSION).zip
	mkdir -p $(PKGDIR)
	mkdir $(PKGDIR)/lib
	mkdir $(PKGDIR)/include
	mkdir $(PKGDIR)/dl
#	mkdir $(PKGDIR)/config
	mkdir $(PKGDIR)/demos
	mkdir $(PKGDIR)/bin
	cp chnxt.chf $(PKGDIR)/lib
	cp delay.chf $(PKGDIR)/lib
	cp ../nxt.h $(PKGDIR)/include
	cp libnxt.dl $(PKGDIR)/dl
#	cp nxt.config $(PKGDIR)/config
	cp -rf ../demos/basic $(PKGDIR)/demos/
	cp -rf ../demos/vehicle $(PKGDIR)/demos/
	cp -rf ../demos/nonvehicle $(PKGDIR)/demos/
	cp ../demos/iMobotController_Windows/release/* $(PKGDIR)/bin
	cp ../demos/iMobotController_Windows/iMobotController_Windows/res/chnxt.ico $(PKGDIR)/bin
	cp Makefile $(PACKAGE)-$(VERSION)
	zip -rq $(PACKAGE)-$(VERSION).zip $(PACKAGE)-$(VERSION)

clean:
	rm *.obj *.dl
