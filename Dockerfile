FROM rockylinux:9.0 as build_cmake

RUN dnf -y update && \
dnf -y install cmake make g++ curl-devel git openssl-devel zlib-devel && \
dnf clean all

COPY . /src
WORKDIR /build

RUN cmake /src -DCMAKE_INSTALL_PREFIX=/prefix
RUN make -j$(nproc)
RUN make install

FROM node:18.9.0-alpine3.15 as build_node
WORKDIR /app
COPY ./frontend/package.json ./frontend/yarn.lock /app/
RUN yarn --network-timeout 600000 --production
COPY ./frontend/ /app/
COPY Readme.md /
RUN yarn build

FROM rockylinux:9.0-minimal
WORKDIR /data
EXPOSE 8080
ADD https://github.com/yt-dlp/yt-dlp/releases/download/2022.09.01/yt-dlp_linux /usr/bin/yt-dlp
RUN chmod +x /usr/bin/yt-dlp
RUN adduser user 


COPY --from=build_cmake /prefix /usr/
COPY --from=build_node /app/public /usr/share/td/frontend

CMD ["su", "-", "user", "-c", "/usr/bin/tdd"]
