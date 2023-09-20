ALLEGRO_VERSION=4.4.3.1

DOCKERHUB_USERNAME=hldtux
TAG_NAME=allegro-compiler:${ALLEGRO_VERSION}-mingw-w64-i686

compile:
	docker run -v $(shell pwd):/tmp/workdir -w /tmp/workdir \
	-ti ${DOCKERHUB_USERNAME}/${TAG_NAME} \
	bash compilar.sh

shell:
	docker run -v $(shell pwd):/tmp/workdir -w /tmp/workdir \
	-ti ${DOCKERHUB_USERNAME}/${TAG_NAME} \
	bash

clean:
	rm -rf *.exe *.o