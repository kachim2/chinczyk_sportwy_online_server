FROM alpine:3.17.0 AS build

RUN apk update && \
    apk add --no-cache \
    build-base \
    cmake \
    git

WORKDIR /chinczyk-server

COPY src/ ./src/
COPY include/ ./include/
COPY CMakeLists.txt .

WORKDIR /chinczyk-server/build

RUN cmake -DCMAKE_BUILD_TYPE=Release .. && \
    cmake --build . --parallel $(nproc)

FROM alpine:3.17.0

RUN apk update && \
    apk add --no-cache \
    libstdc++

RUN addgroup -S schs && adduser -S schs -G schs
USER schs

COPY --chown=shs:shs --from=build \
    ./chinczyk-server/build/bin/CMakeSFMLProject \
    ./bin/

ENTRYPOINT [ "./bin/CMakeSFMLProject" ]
