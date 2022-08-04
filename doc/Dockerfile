FROM alpine:latest

# Install python/pip
ENV PYTHONUNBUFFERED=1
RUN apk add --update --no-cache python3 doxygen && ln -sf python3 /usr/bin/python
RUN python3 -m ensurepip
RUN pip3 install --no-cache --upgrade pip setuptools

RUN pip3 install sphinx breathe sphinx_rtd_theme

WORKDIR /src/doc

CMD /bin/sh -c 'doxygen Doxyfile; sphinx-build . _build'