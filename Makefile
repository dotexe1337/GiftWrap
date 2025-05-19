SOURCES=string.c stream.c

64:
	clang -compatibility_version 9999 -o GiftWrap.dylib -dynamiclib $(SOURCES)
	insert_dylib /usr/lib/libSystem.B.dylib GiftWrap.dylib
	mv GiftWrap.dylib_patched GiftWrap.dylib

32:
	clang -m32 -compatibility_version 9999 -o GiftWrap.dylib -dynamiclib $(SOURCES)
	insert_dylib /usr/lib/libSystem.B.dylib GiftWrap.dylib
	mv GiftWrap.dylib_patched GiftWrap.dylib

clean:
	rm -f ./*.o
	rm -f ./GiftWrap.dylib