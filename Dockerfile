FROM espressif/idf:release-v5.3

RUN apt-get update && apt-get install -y git build-essential wget curl

WORKDIR /app

