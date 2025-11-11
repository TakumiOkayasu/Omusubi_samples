FROM silkeh/clang:latest

ARG USER_NAME ${USER_NAME}
ARG USER_UID  ${USER_UID}
ARG USER_GID  ${USER_GID}

ENV TZ=Asia/Tokyo \
    LANG=ja_JP.UTF-8 \
    LANGUAGE=ja_JP:jp \
    LC_ALL=ja_JP.UTF-8 \
    DEVCONTAINER=true

RUN apt update && apt upgrade -y && apt install -y --no-install-recommends \
    bash \
    curl \
    git \
    sudo \
    ssh \
    unzip \
    locales \
    tzdata \
    build-essential \
    ca-certificates \
    cmake \
    ninja-build \
    gdb \
    valgrind \
    pkg-config \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/* \
    && locale-gen ja_JP.UTF-8 \
    && localedef -f UTF-8 -i ja_JP ja_JP.UTF-8


WORKDIR /tmp/scripts/

# terminal config
RUN curl -o ./create_user.sh https://raw.githubusercontent.com/TakumiOkayasu/shellscript_utility/refs/heads/main/create_user.sh \
    && curl -o ./terminal_config.sh https://raw.githubusercontent.com/TakumiOkayasu/shellscript_utility/refs/heads/main/terminal_config.sh \
    && chmod 777 ./*.sh \
    && ./create_user.sh \
    && ./terminal_config.sh \
    && rm *.sh

WORKDIR /workspace
USER ${USER_NAME}
SHELL ["/bin/bash", "-c"]

