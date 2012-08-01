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

createpkg: libnxt.dl
	echo Bulding $(PACKAGE)-$(VERSION).zip ...
	rm -rf $(PACKAGE)-$(VERSION)
	rm -rf $(PACKAGE)-$(VERSION).zip
	mkdir -p $(PKGDIR)
	mkdir $(PKGDIR)/lib
	mkdir $(PKGDIR)/include
	mkdir $(PKGDIR)/dl
	mkdir $(PKGDIR)/docs
#	mkdir $(PKGDIR)/config
	mkdir $(PKGDIR)/demos
	mkdir $(PKGDIR)/bin
	cp chnxt.chf $(PKGDIR)/lib
	cp delay.chf $(PKGDIR)/lib
	cp ../nxt.h $(PKGDIR)/include
	cp libnxt.dl $(PKGDIR)/dl
#	cp nxt.config $(PKGDIR)/config
#	cp -rf ../demos/basic $(PKGDIR)/demos/
	cp ../demos/*.ch $(PKGDIR)/demos/
	cp -rf ../demos/vehicle $(PKGDIR)/demos/
	cp -rf ../demos/machine $(PKGDIR)/demos/
	cp -rf ../demos/humanoid $(PKGDIR)/demos/
#	cp -rf ../demos/nonvehicle $(PKGDIR)/demos/
	cp ../demos/iMobotController_Windows/release/* $(PKGDIR)/bin
	cp ../demos/iMobotController_Windows/iMobotController_Windows/res/chnxt.ico $(PKGDIR)/bin
	cp ../../docs/nxt_tutorial-1.07.pdf $(PKGDIR)/docs/chnxt.pdf
	cp ../../docs/mindstorms.pdf $(PKGDIR)/docs/chnxt_bluetooth_setup.pdf
	cp ./index.html $(PKGDIR)/docs/
	cp ./Ch_index.png $(PKGDIR)/docs/
	cp ./mindstorms_index.png $(PKGDIR)/docs/
	cp Makefile.win $(PACKAGE)-$(VERSION)/Makefile
	zip -rq $(PACKAGE)-$(VERSION).zip $(PACKAGE)-$(VERSION)

clean:
	del *.obj 
	del *.dl
	del *.manifest
	del *.lib
	del *.exp
