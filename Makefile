build/level:
	rsync -rupE level build/
	rsync -rupE sounds build/

.PHONY: format
format:
	find . -regex '.*\.\(cpp\|hpp\|cu\|c\|h\)' -exec clang-format -style=file -i {} \;
.PHONY: build
build:
	mkdir -p build
	rsync -rupE level build/
	rsync -rupE sounds build/
	cd build && \
	cmake .. && \
	make	

.PHONY: debug
debug:
	mkdir -p build
	rsync -rupE level build/
	rsync -rupE sounds build/
	cp /le
	cd build && \
	cmake -DCMAKE_BUILD_TYPE=debug .. && \
	make

.PHONY: clean
clean:
	rm -rf build

.PHONY: memcheck
memcheck:
	mkdir -p build
	rsync -rupE level build/
	rsync -rupE sounds build/
	cd build && \
	cmake -DCMAKE_BUILD_TYPE=debug .. && \
	make
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file="valgrindReport" ./build/bricks	
