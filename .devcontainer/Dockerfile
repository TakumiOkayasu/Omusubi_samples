FROM mcr.microsoft.com/devcontainers/cpp:ubuntu-24.04

ENV TZ=Asia/Tokyo \
    LANG=ja_JP.UTF-8 \
    LANGUAGE=ja_JP:jp \
    LC_ALL=ja_JP.UTF-8 \
    DEVCONTAINER=true \
    DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
    # 日本語ロケールとタイムゾーン設定用
    locales \
    tzdata \
    # 追加のデバッグ・ビルドツール
    valgrind \
    pkg-config \
    bear \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/* \
    && locale-gen ja_JP.UTF-8 \
    && localedef -f UTF-8 -i ja_JP ja_JP.UTF-8

# uvのインストール
RUN curl -LsSf https://astral.sh/uv/install.sh | sh \
    && mv /root/.local/bin/uv /usr/local/bin/uv \
    && chmod 755 /usr/local/bin/uv

# PlatformIOをuvを使ってインストール
RUN uv tool install platformio \
    && cp /root/.local/bin/pio* /usr/local/bin/ \
    && pio system info

# terminal config - Git補完機能とカスタムプロンプトを追加
RUN curl -o /usr/share/bash-completion/completions/git-completion.bash \
        https://raw.githubusercontent.com/git/git/master/contrib/completion/git-completion.bash \
    && curl -o /usr/share/bash-completion/completions/git-prompt.sh \
        https://raw.githubusercontent.com/git/git/master/contrib/completion/git-prompt.sh \
    && chmod 755 /usr/share/bash-completion/completions/git-*.bash \
    && chmod 755 /usr/share/bash-completion/completions/git-*.sh \
    # .bashrcに追記（上書きしない）
    && cat >> /home/${REMOTE_USER}/.bashrc <<'EOF'

# Git補完機能とカスタムプロンプト
if [ -f /usr/share/bash-completion/completions/git-completion.bash ]; then
    source /usr/share/bash-completion/completions/git-completion.bash
fi
if [ -f /usr/share/bash-completion/completions/git-prompt.sh ]; then
    source /usr/share/bash-completion/completions/git-prompt.sh
    GIT_PS1_SHOWDIRTYSTATE=true
    GIT_PS1_SHOWUNTRACKEDFILES=true
    GIT_PS1_SHOWUPSTREAM=auto
fi
EOF

WORKDIR /workspace
SHELL ["/bin/bash", "-c"]
