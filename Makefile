IMG=esp-idf

docker-install-dev:
	docker build -t ${IMG} --progress tty .

docker-dev-cli:
	docker container run --privileged --rm -it -v ${PWD}:/app -w /app ${IMG}
